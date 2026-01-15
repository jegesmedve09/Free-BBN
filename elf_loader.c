#include <tamtypes.h>
#include <kernel.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

typedef struct {
    u8  e_ident[16];
    u16 e_type;
    u16 e_machine;
    u32 e_version;
    u32 e_entry;
    u32 e_phoff;
    u32 e_shoff;
    u32 e_flags;
    u16 e_ehsize;
    u16 e_phentsize;
    u16 e_phnum;
    u16 e_shentsize;
    u16 e_shnum;
    u16 e_shstrndx;
} Elf32_Ehdr;

typedef struct {
    u32 p_type;
    u32 p_offset;
    u32 p_vaddr;
    u32 p_paddr;
    u32 p_filesz;
    u32 p_memsz;
    u32 p_flags;
    u32 p_align;
} Elf32_Phdr;

#define PT_LOAD 1

int load_and_chain_elf(const char *path, int argc, char **argv)
{
    printf("[LOADER] Starting: path='%s', argc=%d\n", path, argc);

    int fd = open(path, O_RDONLY);
    printf("[LOADER] open() fd = %d\n", fd);
    if (fd < 0) {
        printf("[LOADER] ERROR: open failed (errno=%d)\n", errno);
        return -1;
    }

    Elf32_Ehdr ehdr;
    ssize_t hdr_size = read(fd, &ehdr, sizeof(ehdr));
    printf("[LOADER] read header: %zd bytes (expected %zu)\n", hdr_size, sizeof(ehdr));
    if (hdr_size != sizeof(ehdr)) {
        printf("[LOADER] ERROR: header read incomplete\n");
        close(fd);
        return -2;
    }

    printf("[LOADER] Magic: %02x %02x %02x %02x\n",
           ehdr.e_ident[0], ehdr.e_ident[1], ehdr.e_ident[2], ehdr.e_ident[3]);

    if (ehdr.e_ident[0] != 0x7F || ehdr.e_ident[1] != 'E' ||
        ehdr.e_ident[2] != 'L' || ehdr.e_ident[3] != 'F') {
        printf("[LOADER] ERROR: Invalid ELF magic\n");
        close(fd);
        return -3;
    }

    printf("[LOADER] Valid ELF! Entry=0x%08x, PHoff=0x%08x, PHnum=%d, Type=%d\n",
           ehdr.e_entry, ehdr.e_phoff, ehdr.e_phnum, ehdr.e_type);

    if (ehdr.e_entry == 0) {
        printf("[LOADER] FATAL: Entry point is 0x00000000 - cannot jump!\n");
        close(fd);
        return -4;
    }

    Elf32_Phdr *phdrs = malloc(ehdr.e_phnum * sizeof(Elf32_Phdr));
    if (!phdrs) {
        printf("[LOADER] ERROR: malloc failed\n");
        close(fd);
        return -5;
    }

    lseek(fd, ehdr.e_phoff, SEEK_SET);
    read(fd, phdrs, ehdr.e_phnum * sizeof(Elf32_Phdr));

    int i;
    for (i = 0; i < ehdr.e_phnum; i++) {
        if (phdrs[i].p_type == PT_LOAD) {
            printf("[LOADER] PT_LOAD %d: vaddr=0x%08x, offset=0x%08x, filesz=%u, memsz=%u\n",
                   i, phdrs[i].p_vaddr, phdrs[i].p_offset, phdrs[i].p_filesz, phdrs[i].p_memsz);

            if (phdrs[i].p_vaddr < 0x00100000) {
                printf("[LOADER] WARNING: Suspicious low vaddr 0x%08x\n", phdrs[i].p_vaddr);
            }

            lseek(fd, phdrs[i].p_offset, SEEK_SET);
            read(fd, (void*)phdrs[i].p_vaddr, phdrs[i].p_filesz);
            if (phdrs[i].p_memsz > phdrs[i].p_filesz) {
                printf("[LOADER] Zeroing BSS at 0x%08x, size %u\n",
                       phdrs[i].p_vaddr + phdrs[i].p_filesz,
                       phdrs[i].p_memsz - phdrs[i].p_filesz);
                memset((void*)(phdrs[i].p_vaddr + phdrs[i].p_filesz), 0,
                       phdrs[i].p_memsz - phdrs[i].p_filesz);
            }
        }
    }

    free(phdrs);
    close(fd);

    printf("[LOADER] Load complete. Flushing caches...\n");
    FlushCache(0);
    FlushCache(2);
    FlushCache(0);  // Twice - sometimes needed

// After loading segments, free/close, FlushCache(0); FlushCache(2); FlushCache(0);

// Debug print before jump
printf("[LOADER] All segments loaded. Entry point: 0x%08x\n", ehdr.e_entry);
if (ehdr.e_entry == 0) {
    printf("[LOADER] FATAL: Entry point is 0x0 - invalid ELF!\n");
    return -7;
}

// Safe high-memory stack (top of RAM, 64KB free zone)
u32 *new_stack = (u32 *)0x01ff0000;

// Build standard MIPS ELF stack frame (argc, argv pointers, NULL terminator, envp=NULL)
*--new_stack = 0;                     // envp = NULL
*--new_stack = (u32)argv;             // argv array pointer
*--new_stack = (u32)argc;             // argc
*--new_stack = 0;                     // auxv NULL (optional but safer)

// Align stack to 16 bytes (MIPS ABI requirement)
new_stack = (u32 *)(((u32)new_stack) & ~0xF);

// Final debug prints
printf("[LOADER] Jump prep: sp=0x%08x, argc=%d, argv=0x%08x, entry=0x%08x\n",
       (u32)new_stack, argc, (u32)argv, ehdr.e_entry);

// Safe inline asm jump - preserve caller-saved regs if needed
__asm__ volatile (
    "move   $sp, %0\n"      // Set new stack pointer
    "move   $a0, %1\n"      // argc
    "move   $a1, %2\n"      // argv
    "move   $a2, $zero\n"   // envp = NULL
    "jr     %3\n"           // Jump to entry point
    "nop\n"
    :
    : "r"(new_stack), "r"((u32)argc), "r"((u32)argv), "r"(ehdr.e_entry)
    : "memory", "$sp", "$a0", "$a1", "$a2", "$v0", "$v1", "$t0", "$t1", "$t2",
      "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9", "$ra"
);

// Should NEVER reach here
printf("[LOADER] CRITICAL: Jump instruction returned! This means entry point is invalid.\n");
return -8;
}
