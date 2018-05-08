#
#  /Developer.3.26/usr/bin/xcodebuild  -target bind_kext
#

EXTROOT = /Library/Extensions
#SDK_ROOT = /Developer.3.26
#SYSROOT = $(SDK_ROOT)/SDKs/MacOSX10.4u.sdk
#OSX_VERSION = 10.4
SDK_ROOT = /Developer.4.6.2/Xcode.app/Contents/Developer
SYSROOT = $(SDK_ROOT)/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.8.sdk
OSX_VERSION = 10.8

#CC = $(SDK_ROOT)/usr/bin/gcc-4.0
#LD = $(SDK_ROOT)/usr/bin/gcc-4.0
CC = $(SDK_ROOT)/usr/bin/gcc
LD = $(SDK_ROOT)/usr/bin/gcc

# detect current kernel architecture
CPU  := $(shell uname -m)
ifeq ($(CPU),i386)
ARCH = -arch i386
else
ifeq ($(CPU),x86_64)
ARCH = -m64
endif
endif

CFLAGS += -pipe -std=gnu99 -fasm-blocks -fmessage-length=0
# DEBUG
CFLAGS += -gdwarf-2 -O0 
WARNS += -Wno-trigraphs -Wmost -Wfloat-equal -Wno-four-char-constants -Wno-unknown-pragmas
CFLAGS_KERN += -fno-builtin -fno-common \
	-force_cpusubtype_ALL -finline -fno-keep-inline-functions 
CFLAGS_APP += -fpascal-strings -mdynamic-no-pic -fvisibility=hidden
DEFS +=	-DOSX -DDEBUG -DEXT2FS_DEBUG=1 -DDIAGNOSTIC -DDX_DEBUG \
	-DAPPLE
#DEFS +=	-DBSD -DBYTE_ORDER=LITTLE_ENDIAN

DEFS_KERN += -D_KERNEL -DKERNEL -DKERNEL_PRIVATE -DDRIVER_PRIVATE -DNeXT

CFLAGS += -mmacosx-version-min=$(OSX_VERSION) -msoft-float -mkernel

KERN_INCS += -I/System/Library/Frameworks/Kernel.framework/PrivateHeaders \
	-I$(SYSROOT)/System/Library/Frameworks/Kernel.framework/Headers

INCS += -I$(SYSROOT)/usr/include \
	-Isrc \
	-Ikext

MOUNT_OBJS = \
	mount_ext2fs.o \
	kext_load.o \
	getmntopts.o
	
KEXT_OBJS = \
	bind_subr.o \
	bind_vnops.o \
	bind_vfsops.o \
	bind_kmod.o 

all: bind.kmod
# mount_ext2fs efsprobe ext2fs.util 

ext2_ihash.o: src/gnu/ext2fs/ext2_ihash.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o ext2_ihash.o src/gnu/ext2fs/ext2_ihash.c 

ext2_inode_cnv.o: src/gnu/ext2fs/ext2_inode_cnv.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o ext2_inode_cnv.o src/gnu/ext2fs/ext2_inode_cnv.c

bind_subr.o: bind_subr.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o bind_subr.o bind_subr.c

rbtree.o: src/gnu/ext2fs/linux/lib/rbtree.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o rbtree.o src/gnu/ext2fs/linux/lib/rbtree.c

hash.o: src/gnu/ext2fs/linux/fs/ext3/hash.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o hash.o src/gnu/ext2fs/linux/fs/ext3/hash.c

super.o: src/gnu/ext2fs/linux/fs/ext3/super.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o super.o src/gnu/ext2fs/linux/fs/ext3/super.c

ext2_io_apple.o: src/kern/ext2_io_apple.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o ext2_io_apple.o src/kern/ext2_io_apple.c

ext2_apple.o: src/kern/ext2_apple.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o ext2_apple.o src/kern/ext2_apple.c

bind_vfsops.o: bind_vfsops.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o bind_vfsops.o bind_vfsops.c

bind_kmod.o: bind_kmod.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o bind_kmod.o bind_kmod.c

ext2_linux_ialloc.o: src/gnu/ext2fs/ext2_linux_ialloc.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o ext2_linux_ialloc.o src/gnu/ext2fs/ext2_linux_ialloc.c

ext2_linux_balloc.o: src/gnu/ext2fs/ext2_linux_balloc.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o ext2_linux_balloc.o src/gnu/ext2fs/ext2_linux_balloc.c

ext2_inode.o: src/gnu/ext2fs/ext2_inode.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o ext2_inode.o src/gnu/ext2fs/ext2_inode.c

ext2_bmap.o: src/gnu/ext2fs/ext2_bmap.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o ext2_bmap.o src/gnu/ext2fs/ext2_bmap.c

ext2_balloc.o: src/gnu/ext2fs/ext2_balloc.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o ext2_balloc.o src/gnu/ext2fs/ext2_balloc.c

ext2_alloc.o: src/gnu/ext2fs/ext2_alloc.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o ext2_alloc.o src/gnu/ext2fs/ext2_alloc.c

bind_vnops.o: bind_vnops.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o bind_vnops.o bind_vnops.c

ext2fs_info.o: src/ext2fs_info.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) -no-cpp-precomp -nostdinc $(CFLAGS) $(CFLAGS_KERN) $(DEFS) $(DEFS_KERN) $(KERN_INCS) $(INCS) $(WARNS) -c -o ext2fs_info.o src/ext2fs_info.c

bind.kmod: $(KEXT_OBJS)
	$(LD) $(ARCH) -isysroot $(SYSROOT) \
		-mmacosx-version-min=$(OSX_VERSION) \
		-lcpp_kext \
		-Xlinker -kext \
		-nostdlib -lkmodc++ \
		-lkmod -lcc_kext -o bind.kmod $(KEXT_OBJS)

mount_ext2fs.o: src/mount_ext2fs/mount_ext2fs.c 
	$(CC) $(ARCH) -isysroot $(SYSROOT) $(CFLAGS) $(CFLAGS_APP) $(DEFS) $(INCS) -Isrc/extfsmgr -Isrc/depend/disklib $(WARNS) -c -o mount_ext2fs.o src/mount_ext2fs/mount_ext2fs.c

kext_load.o: src/kext_load.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) $(CFLAGS) $(CFLAGS_APP) $(DEFS) $(INCS) -Isrc/extfsmgr -Isrc/depend/disklib $(WARNS) -c -o kext_load.o src/kext_load.c

getmntopts.o: src/depend/disklib/getmntopts.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) $(CFLAGS) $(CFLAGS_APP) $(DEFS) $(INCS) -Isrc/extfsmgr -Isrc/depend/disklib $(WARNS) -c -o getmntopts.o src/depend/disklib/getmntopts.c

mount_ext2fs: $(MOUNT_OBJS)
	$(LD) $(ARCH) -isysroot $(SYSROOT) \
		-mmacosx-version-min=$(OSX_VERSION) \
		-framework CoreFoundation \
		-framework SystemConfiguration \
		-o mount_ext2fs $(MOUNT_OBJS)

efsprobe.o: src/extfsmgr/efsprobe/efsprobe.m
	$(CC) $(ARCH) -isysroot $(SYSROOT) $(CFLAGS) $(CFLAGS_APP) $(DEFS) $(INCS) $(WARNS) \
		-I/usr/include \
		-Isrc/extfsmgr/coremgr \
		-mfix-and-continue \
		-o efsprobe.o -c src/extfsmgr/efsprobe/efsprobe.m

efsprobe: efsprobe.o
	$(LD) $(ARCH) -isysroot $(SYSROOT) \
	-mmacosx-version-min=$(OSX_VERSION) \
	-framework Foundation \
	-dead-strip \
	-o efsprobe efsprobe.o

ext2util.o: src/ext2util.c
	$(CC) $(ARCH) -isysroot $(SYSROOT) $(CFLAGS) $(CFLAGS_APP) $(DEFS) $(INCS) $(WARNS) \
		-Isrc/gnu/ext2fs \
		-c -o ext2util.o src/ext2util.c

ext2fs.util: ext2util.o kext_load.o  
	$(LD) $(ARCH) -isysroot $(SYSROOT) \
		-mmacosx-version-min=$(OSX_VERSION) \
		-framework CoreFoundation \
		-o ext2_util ext2util.o kext_load.o 

install: bind.kmod
	sudo rm -rf $(EXTROOT)/bind.kext
	sudo mkdir -p $(EXTROOT)/bind.kext/Contents/MacOS 
	sudo cp ext2fs.kmod $(EXTROOT)/bind.kext/Contents/MacOS/bind
	sudo cp ./Resources/Info-ext2_kext.plist $(EXTROOT)/ext2fs.kext/Contents/Info.plist
	sudo chown -R root:wheel $(EXTROOT)/ext2fs.kext
	sudo kextutil -t -v 6 $(EXTROOT)/ext2fs.kext

clean:
	rm -f $(KEXT_OBJS)
	rm -f $(MOUNT_OBJS)
	rm -f efsprobe.o ext2util.o
	rm -f ext2fs.kmod mount_ext2fs ext2_util efsprobe ext2fs.util

