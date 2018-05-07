all: mount_nullfs

DEFS = -D__APPLE_API_PRIVATE=1

CFLAGS += -Wall -mdynamic-no-pic \
	-D_DARWIN_USE_64_BIT_INODE=1

LDFLAGS += -dead_strip

mount_nullfs: mount_null.c getmntopts.c
	$(CC) $(DEFS) -O2 -o mount_nullfs mount_null.c getmntopts.c
	strip mount_nullfs

install:
	mkdir -p /Library/Filesystems/nullfs.fs/Contents/Resources
	cp mount_nullfs /Library/Filesystems/nullfs.fs/Contents/Resources

clean:
	rm -f *.o

distclean: clean
	rm -f mount_nullfs
