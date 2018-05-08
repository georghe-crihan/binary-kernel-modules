#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/fcntl.h>
#include <sys/malloc.h>
#include <sys/stat.h>

#include "bindfs.h"

static vfstable_t bind_tableid;

kern_return_t bind_start (kmod_info_t * ki, void * d) {
    
    struct vfs_fsentry fsc;
    struct vnodeopv_desc* vnops[] =
    {
        &bindfs_vnodeop_opv_desc,
        NULL,
        NULL
    };
    
    int kret, i;

    // See xnu/bsd/vfs/vfs_conf.c
    //
    // extern struct vnodeopv_desc bindfs_vnodeop_opv_desc;
    // ...
    // struct vnodeopv_desc *vfs_opv_descs[] = {
    //    ...
    // &bindfs_vnodeop_opv_desc,
    
    // enum fs_type_num {
    // ...
    // FT_NULLFS = 22,
    // ...
    // };

    
    bzero(&fsc, sizeof(struct vfs_fsentry));

    extern struct vfsops bindfs_vfsops;
    
    fsc.vfe_vfsops = &bindfs_vfsops;
    fsc.vfe_vopcnt = 3;
    fsc.vfe_opvdescs = vnops;
    strncpy(&fsc.vfe_fsname[0], "bindfs", MFSNAMELEN);
    // Otherwise, the VFS is not installed, at least under OSX 10.8
    // Something has to be done to sysctl though.
    fsc.vfe_flags = MNT_DONTBROWSE | MNT_RDONLY;

    // See xnu/bsd/vfs/vfs_conf.c
    //{ &nullfs_vfsops, "nullfs", FT_NULLFS, 0, (MNT_DONTBROWSE | MNT_RDONLY), NULL, NULL, 0, 0, VFC_VFS64BITREADY, NULL, 0, NULL},

    kret = vfs_fsadd(&fsc, &bind_tableid);
    if (kret) {
        printf ("bindfs_start: Failed to register with kernel, error = %d\n", kret);
        return (KERN_FAILURE);
    }
    
    return (KERN_SUCCESS);
}

kern_return_t bind_stop (kmod_info_t * ki, void * d) {
    int error;
    
    /* Deregister with the kernel */
    
    if ((error = vfs_fsremove(bind_tableid)))
        return (KERN_FAILURE);
    
    return(KERN_SUCCESS);
}
