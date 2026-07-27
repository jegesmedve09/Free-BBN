#include <tamtypes.h>
#include <libpad.h>
#include <kernel.h>
#include <sifrpc.h>
#include <audsrv.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <libcdvd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sbv_patches.h>
#include <gsKit.h>
#include <libpad.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h>

#include "irx.c"
#include "loader_bin.c"

#define NEWLIB_PORT_AWARE
#include <fileXio_rpc.h>
#include <io_common.h>

#define LOADER_BASE         0x01F00000
#define WORKPATH_ADDRESS    0x01EFFC00
#define PORTABLE_ADDRESS    0x01EFF800

#define SHARED_BASE_ADDR    0x01EFF7F0

#define INTERLACED          (SHARED_BASE_ADDR + 0x00)
#define PAL_NTSC            (SHARED_BASE_ADDR + 0x01)
#define PRIM_ALPHA          (SHARED_BASE_ADDR + 0x02)
#define HAS_TO_BE_TRUE      (SHARED_BASE_ADDR + 0x03)
#define GS_WIDTH            (SHARED_BASE_ADDR + 0x04)
#define GS_HEIGHT           (SHARED_BASE_ADDR + 0x08)
#define SIGNATURE_SPACE     (SHARED_BASE_ADDR + 0x0C)
#define SIGNATURE           0x4741597E

#define DEV_EXIST(path) (stat(path, &(struct stat){0}) == 0)

#define GS_BGCOLOR ((volatile u64*)0x120000e0)

void FuckAroundSilentlyMs(int miliseconds)
{
    unsigned int start, now;

    __asm__ volatile("mfc0 %0, $9" : "=r"(start));

    while (1)
    {
        __asm__ volatile("mfc0 %0, $9" : "=r"(now));
        if ((now - start) >= (unsigned int)(miliseconds * 147456))
            break;
    }
}
char savepath[1024];
char **read_config(const char *fn, char **out_buffer)
{
    if (!fn || !*fn || !*savepath) return NULL;

    char p[1088];
    snprintf(p, sizeof(p), "%sCONFIG/%s", savepath, fn);

    int fd = open(p, O_RDONLY);
    if (fd < 0) return NULL;

    struct stat st;
    if (fstat(fd, &st) < 0 || st.st_size <= 0) { close(fd); return NULL; }

    size_t sz = st.st_size;
    char *buf = malloc(sz + 1);
    if (!buf) { close(fd); return NULL; }

    if (read(fd, buf, sz) != (int)sz) { close(fd); free(buf); return NULL; }
    close(fd);
    buf[sz] = '\0';

    int n = 0;
    for (char *q = buf; *q; q++) if (*q == '\n') n++;
    if (buf[sz-1] != '\n') n++;
    n = n ? n : 1;

    char **lines = malloc((n + 1) * sizeof(char*));
    if (!lines) { free(buf); return NULL; }

    int i = 0;
    char *t = strtok(buf, "\n\r");
    while (t && i < n) {
        lines[i++] = t;
        t = strtok(NULL, "\n\r");
    }
    lines[i] = NULL;

	*out_buffer = buf;
    return lines;
}

int str_to_int(const char *str, int def) {
    if (!str || !*str) return def;
    int val = def;
    sscanf(str, "%d", &val);
    if (val < 0) val = 0;
    // Removed the 255 limit so higher numbers can pass through safely
    return val;
}

int mount_hdd_from_argv(const char *argv0, char *out_dir, size_t out_size)
{
    if (strncmp(argv0, "hdd", 3) != 0) return 0; // not an HDD launch

    const char *pfsMarker = strstr(argv0, ":pfs:");
    if (!pfsMarker) return -1; // unexpected format

    size_t devLen = pfsMarker - argv0; // e.g. "hdd0:+freebbn"
    char blockdev[64];
    if (devLen >= sizeof(blockdev)) return -1;
    memcpy(blockdev, argv0, devLen);
    blockdev[devLen] = '\0';

    if (fileXioMount("pfs0:", blockdev, FIO_MT_RDWR) < 0)
        return -1;

    snprintf(out_dir, out_size, "pfs0:%s", pfsMarker + 5); // skip ":pfs:"
    char *slash = strrchr(out_dir, '/');
    if (slash) *(slash + 1) = '\0';

    return 1;
}

void init(const char *argv0)
{
    SifInitRpc(0);
    while (!SifIopReset("", 0)) {};
    while (!SifIopSync()) {};
    SifInitRpc(0);
    SifLoadFileInit();
    sbv_patch_enable_lmb();
    
    //sound
	SifExecModuleBuffer(irx_freesd, irx_freesd_size, 0, NULL, NULL);
	SifExecModuleBuffer(irx_audsrv, irx_audsrv_size, 0, NULL, NULL);
    audsrv_init();
    
    //controller
    SifLoadModule("rom0:SIO2MAN", 0, NULL);
    SifLoadModule("rom0:PADMAN", 0, NULL);
    static char padBuf[2][256] __attribute__((aligned(64)));
    padInit(0);
	padPortOpen(0, 0, padBuf[0]);
	padPortOpen(1, 0, padBuf[1]);
    
	//memory card
    SifLoadModule("rom0:MCMAN", 0, NULL);
	SifLoadModule("rom0:MCSERV", 0, NULL);
	
	//USB I/O
	SifExecModuleBuffer(irx_iomanx, irx_iomanx_size, 0, NULL, NULL);
	SifExecModuleBuffer(irx_filexio, irx_filexio_size, 0, NULL, NULL);
	
	//USB Mass
	SifExecModuleBuffer(irx_usbd, irx_usbd_size, 0, NULL, NULL);
	SifExecModuleBuffer(irx_usbhdfsd, irx_usbhdfsd_size, 0, NULL, NULL);

    //HDD
    SifExecModuleBuffer(irx_ps2dev9, irx_ps2dev9_size, 0, NULL, NULL);
    SifExecModuleBuffer(irx_ps2atad, irx_ps2atad_size, 0, NULL, NULL);
    SifExecModuleBuffer(irx_ps2hdd,  irx_ps2hdd_size,  0, NULL, NULL);    
    SifExecModuleBuffer(irx_ps2fs, irx_ps2fs_size, 0, NULL, NULL);
    SifExecModuleBuffer(irx_loadfile, irx_loadfile_size, 0, NULL, NULL);

    // then separately, wrap the mount call itself:
    *GS_BGCOLOR = 0x800080; // purple - about to mount
    if (strncmp(argv0, "hdd", 3) == 0) {
        int r = mount_hdd_from_argv(argv0, savepath, sizeof(savepath));
        *GS_BGCOLOR = (r > 0) ? 0x0000FF : 0xFF0000; // blue = mounted ok, red = mount failed
        //FuckAroundSilentlyMs(3000); // hold it so you can actually see it
    }
    else
    {
        strncpy(savepath, argv0, sizeof(savepath) - 1);
        savepath[sizeof(savepath) - 1] = '\0';

        char *slash = strrchr(savepath, '/');
        if (!slash) slash = strrchr(savepath, '\\');

        if (slash != NULL) *(slash + 1) = '\0';
        else strcpy(savepath, "host:/");
    }
    //FuckAroundSilentlyMs(5000);
    *GS_BGCOLOR = 0x00FF7F; // spring green - about to call read_config
	char **fd;
	char *settingsBuffer = NULL;    

	fd = read_config("init.gs.config", &settingsBuffer);
    *GS_BGCOLOR = 0xFF69B4; // pink - read_config returned
    //FuckAroundSilentlyMs(5000);
	//graphics
    GSGLOBAL *gsGlobal;
    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    gsGlobal = gsKit_init_global();
    
    gsGlobal->Field = GS_FIELD;
    gsGlobal->DoubleBuffering = GS_SETTING_OFF;
    gsGlobal->ZBuffering   = GS_SETTING_OFF;
    
    if(fd)
    {
        if ( fd[1] && strcmp(fd[1], "VIDEO=NTSC") == 0 )
        { 
            gsGlobal->Mode = GS_MODE_NTSC;
            *(volatile u8 *)(PAL_NTSC) = 1;
        }
        else
        { 
            gsGlobal->Mode = GS_MODE_PAL;
            *(volatile u8 *)(PAL_NTSC) = 0;
        }
        
        if ( fd[0] && strcmp( fd[0], "INTERLACING=DISABLE" ) == 0 )
        {
            gsGlobal->Interlace = GS_NONINTERLACED;
            *(volatile u8 *)(INTERLACED) = 0;
        }
        else
        {
            gsGlobal->Interlace = GS_INTERLACED;
            *(volatile u8 *)(INTERLACED) = 1;
        }

        if ( fd[3] && fd[4] )
        {
            gsGlobal->Width = str_to_int(fd[3],640);
            *(volatile u32 *)(GS_WIDTH) = (str_to_int(fd[3], 640));
            gsGlobal->Height = str_to_int(fd[4],480);
            *(volatile u32 *)(GS_HEIGHT) = (str_to_int(fd[4], 480));
        }
        else
        {
            gsGlobal->Width = 640;
            gsGlobal->Height = 480;
        }

        if ( fd[2] && strcmp( fd[2], "PRIMALPHA=DISABLE" ) == 0 )
        {
            gsGlobal->PrimAlphaEnable = GS_SETTING_OFF;
            *(volatile u8 *)(PRIM_ALPHA) = 0;
        }
        else
        {
            gsGlobal->PrimAlphaEnable = GS_SETTING_ON;
            *(volatile u8 *)(PRIM_ALPHA) = 1;
        }
    }
    else
    {
        gsGlobal->Mode = GS_MODE_PAL;
        gsGlobal->Interlace = GS_INTERLACED;
        gsGlobal->Width = 640;
        gsGlobal->Height = 480;
        gsGlobal->PrimAlphaEnable = GS_SETTING_ON;
        *(volatile u8 *)(PAL_NTSC)    = 0;
        *(volatile u8 *)(INTERLACED)  = 1;
        *(volatile u8 *)(PRIM_ALPHA)  = 1;
        *(volatile u32 *)(GS_WIDTH)   = 640;
        *(volatile u32 *)(GS_HEIGHT)  = 480;

    }

	free(settingsBuffer);     

    gsKit_init_screen(gsGlobal);

    gsKit_set_primalpha(gsGlobal, GS_SETREG_ALPHA(0, 1, 0, 1, 0), 0);
    gsKit_mode_switch(gsGlobal, GS_ONESHOT);

 
	gsKit_clear(gsGlobal, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0));
	gsKit_queue_exec(gsGlobal);
	gsKit_sync_flip(gsGlobal);

	//loader
	memcpy((void*)LOADER_BASE, loader, size_loader);
	FlushCache(0);
	FlushCache(2);
}

int main(int argc, char **argv)
{	
    const char *argv0 = (argc > 0 && argv[0] != NULL) ? argv[0] : "host:/";

    init(argv0);
    
    strcpy((char*)PORTABLE_ADDRESS, savepath);    

    static const char relativepath[1024] = "main.elf";
    strcpy((char*)WORKPATH_ADDRESS, relativepath);  

    padPortClose(0,0);
    padPortClose(1,0);
    audsrv_stop_audio();
    audsrv_set_volume(0);

//    SifExitIopHeap();
    SifLoadFileExit();

    *(volatile u32 *)(SIGNATURE_SPACE) = SIGNATURE;
    *(volatile u8 *)(HAS_TO_BE_TRUE) = 0x01;

    ExecPS2((void*)LOADER_BASE, NULL, 0, NULL);
	
	return 0;
}

