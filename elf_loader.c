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

// Returns 0 on success, negative on error
int load_elf(const char *path, int argc, char **argv)
{
    printf("[LOADER] Starting load: %s\n", path);

    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        printf("[LOADER] ERROR: open failed, errno=%d\n", errno);
        return -1;
    }

    Elf32_Ehdr ehdr;
    ssize_t sz = read(fd, &ehdr, sizeof(ehdr));
    if (sz != sizeof(ehdr)) {
        printf("[LOADER] ERROR: header read failed (%zd bytes)\n", sz);
        close(fd);
        return -2;
    }

    // Check ELF magic
    if (ehdr.e_ident[0] != 0x7F || ehdr.e_ident[1] != 'E' ||
        ehdr.e_ident[2] != 'L' || ehdr.e_ident[3] != 'F') {
        printf("[LOADER] ERROR: Invalid ELF magic (%02x %02x %02x %02x)\n",
               ehdr.e_ident[0], ehdr.e_ident[1], ehdr.e_ident[2], ehdr.e_ident[3]);
        close(fd);
        return -3;
    }

    if (ehdr.e_type != 2) { // ET_EXEC
        printf("[LOADER] ERROR: Not an executable ELF (type=%d)\n", ehdr.e_type);
        close(fd);
        return -4;
    }

    printf("[LOADER] ELF OK - Entry: 0x%08x, PHnum: %d\n", ehdr.e_entry, ehdr.e_phnum);

    if (ehdr.e_entry == 0) {
        printf("[LOADER] ERROR: Entry point is 0x0 - invalid!\n");
        close(fd);
        return -5;
    }

    // Load program headers
    Elf32_Phdr *phdrs = malloc(ehdr.e_phnum * sizeof(Elf32_Phdr));
    if (!phdrs) {
        printf("[LOADER] ERROR: malloc failed for phdrs\n");
        close(fd);
        return -6;
    }

    lseek(fd, ehdr.e_phoff, SEEK_SET);
    read(fd, phdrs, ehdr.e_phnum * sizeof(Elf32_Phdr));

    int i;
    for (i = 0; i < ehdr.e_phnum; i++) {
        if (phdrs[i].p_type == PT_LOAD) {
            printf("[LOADER] Loading segment %d → vaddr=0x%08x, size=%u\n",
                   i, phdrs[i].p_vaddr, phdrs[i].p_filesz);

            lseek(fd, phdrs[i].p_offset, SEEK_SET);
            read(fd, (void*)phdrs[i].p_vaddr, phdrs[i].p_filesz);

            if (phdrs[i].p_memsz > phdrs[i].p_filesz) {
                memset((void*)(phdrs[i].p_vaddr + phdrs[i].p_filesz), 0,
                       phdrs[i].p_memsz - phdrs[i].p_filesz);
            }
        }
    }

    free(phdrs);
    close(fd);

    // Triple flush - sometimes needed on real hardware
    FlushCache(0);
    FlushCache(2);
    FlushCache(0);

    printf("[LOADER] Load complete. Preparing jump (entry=0x%08x)\n", ehdr.e_entry);

    // Safe high stack (top 64KB of RAM)
    u32 *new_sp = (u32 *)0x01ff0000;

    // Standard ELF stack frame
    *--new_sp = 0;                    // envp = NULL
    *--new_sp = (u32)argv;            // argv
    *--new_sp = (u32)argc;            // argc
    *--new_sp = 0;                    // auxv terminator (safer)

    // Align to 16 bytes
    new_sp = (u32 *)(((u32)new_sp) & ~0xF);

    printf("[LOADER] Jumping... sp=0x%08x, argc=%d\n", (u32)new_sp, argc);

    // Safe inline asm jump
    __asm__ volatile (
        "move   $sp, %0\n"
        "move   $a0, %1\n"
        "move   $a1, %2\n"
        "move   $a2, $zero\n"
        "jr     %3\n"
        "nop\n"
        :
        : "r"(new_sp), "r"((u32)argc), "r"((u32)argv), "r"(ehdr.e_entry)
        : "memory", "$sp", "$a0", "$a1", "$a2", "$v0", "$v1", "$t0", "$t1", "$t2",
          "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9", "$ra"
    );

    // Should never reach here
    printf("[LOADER] CRITICAL: Jump returned unexpectedly!\n");
    return -7;
}
