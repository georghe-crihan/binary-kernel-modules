
DEFS = -D__APPLE_API_PRIVATE=1

CFLAGS += -Wall -mdynamic-no-pic \
	-D_DARWIN_USE_64_BIT_INODE=1

LDFLAGS += -dead_strip

PROG = mount_null

all: ${PROG} 

${PROG}: mount_null.c getmntopts.c
	$(CC) $(DEFS) -O2 -o ${PROG} mount_null.c getmntopts.c
	strip ${PROG}

install: ${PROG}
	mkdir -p /Library/Filesystems/null.fs/Contents/Resources
	cp ${PROG} Entitlements.plist Info.plist /Library/Filesystems/null.fs/Contents/Resources
	cat mount_null.8 | gzip -9 > /usr/local/share/man/man8/mount_null.8.gz

codesign:
	/usr/bin/codesign --force --sign 'Self-signed certificate' \
          --entitlements /Users/mac/share/entitlements.plist \
	  /Library/Filesystems/null.fs/Contents/Resources/mount_null

verify:
	codesign --verify -vvvv /Library/Filesystems/null.fs

dump_entitlements:
	 codesign -d --entitlements - ./mount_null

clean:
	rm -f *.o

distclean: clean
	rm -f ${PROG}
