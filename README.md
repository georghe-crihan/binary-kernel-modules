# Binary kernel modules for various FS

* [bindfs](bindfs) - Basically, a s/null/bind/ from the xnu/bsd/miscfs/nullfs/*.
An attempt to re-implement nullfs as kext under different
name, as Apple prohibits its use by third-party applications (see
com.apple.private.nullfs_allow entitlement). Apparently, one couldn't defeat it,
as it's _private_, even if the GateKeeper subsystem would be disabled entirely.

I often regard it as shame, that Apple *believes that BSD stackable file system
doesn't fit Mac OS X*, as I find it very lucrative under FreeBSD and can't think
of anything similar in OSX.

See, for example,
[here](https://developer.apple.com/library/content/qa/qa1242/_index.html).

Also, another point of regret is that it's apparently read-only.

Alas, all the VNOPS_* functions are kernel-private entities.

But, I might try
[MacOSX-FileSystem-Filter](https://github.com/slavaim/MacOSX-FileSystem-Filter)
sometime in the future.

* [mount_bindfs](mount_bindfs) - mount component for the above.

* [mount_nullfs](mount_nullfs) - mount component for stock nullfs filesystem.
Ironically, it's always been there since the very first days of OSX as part
of bsd kernel of XNU. But apparently no binary mount_nullfs has been ever
distributed.

So, for systems prior to the GateKeeper and Entitlements frameworks, it might
work. Sadly, I don't own such a system anymore, to test if it works.

