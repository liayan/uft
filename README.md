# upstream-fixes-tracking
upstream-fixes-tracking(uft) tracks the git-fixes and cve-fixes between upstream latest branch to a specific(downstream) branch.
It will search "Fixes:" and "CVE-" lines in commit message. 

This project is based on https://github.com/joergroedel/git-fixes, reused some of the fuctions in git-fixes.cc.

## Building
The libgit2 library is required.
$make

when the build is completed successfully, you can install:
$make install 
It will be installed into $HOME/bin by default.

## Running
uft --base --extra --blacklist --bl_keyword --bl-file --slack --email []

--base: base..stable branch or tag id

--extra: extra commits that have been backported

--blacklist: blacklist the commits

--bl-keyword: blacklist the commits that contain the keywords

--only-file: search the commits from the src files

--slack: send to slack channel

## DEMO

```Bash
`#:~/libvirt$ uft -b v7.4.0 -k /tmp/bl-keywords
Upstream fixes tracking: Sat Jul 30 15:27:41 2022

Git Repo: https://gitlab.com/libvirt/libvirt.git
Git-fixes-commit between v7.4.0 and HEAD
=================================================
6f25a5ac8aa6 meson: Fix vstorage detection
9d225ea28436 virDomainDiskDefParseSource: parse source bits from driver element
9a82146fcde5 qemuxml2arvtest: Ensure newline at the end of generated .args files
fb1289c15516 qemu: Don't set NVRAM label when creating it
e8863b91fb98 conf: require target for external virtiofsd
54b602019d7d qemu_hotplug: don't forget to add hostdev interfaces to the interface list
36d6da4ebf9b virresctrl: fix starting VMs with cputune.memorytune specified
a9c7da612675 virresctrl: Fix updating the mask for a cache resource
12f96b06118e schemas: Allow cache attribute for bandwidth element for HMAT
f58349c9c6d2 qemu: migration: Use correct flag constant for enabling storage migration
447f69dec47e storage_driver: Unlock object on ACL fail in storagePoolLookupByTargetPath
77f7067059a5 testutils: Don't leak @testBitmap and @failedTests
f14d6ab537f3 security: fix use-after-free in virSecuritySELinuxReserveLabel
6d7a16361b54 virsh-snapshot: Don't leak @then in cmdSnapshotList()
a082c462290b util: virIdentitySetCurrent: only unref the old identity on success
cf6b34c683d2 conf: Don't call 'virDomainDiskDefAssignAddress' when disk->dst is NULL
0b2a2e84e4a3 qemu: remove private data from virDomainFSDef
f1818032f5ac qemu: Revert "qemuExtDevicesStart: pass logManager"
ebd796b811bc syntax-check: Fix regex for sc_require_attribute_cleanup_initialization
d73265af6ec4 qemu_command: do not use host-nodes for system memory
47c439ce4490 spec: Don't create unnecessary directory
591cb9d0d5e4 meson: Define qemu_moddir correctly
b41c95af5b0d qemu: Set QEMU data location correctly
28bb7266a05d conf: match by network alias only if aliases are assigned
04e91af13ec9 qemu_snapshot: revert: fix incorrect jump to cleanup
3179220e4fac Revert "qemu: Avoid crash in qemuStateShutdownPrepare() and qemuStateShutdownWait()"
00c4dd794a50 nss: Use shared_library() for nss_libvirt_lib
019b74103bdd virDomainDiskInsert: Don't access NULL disk target
ca6122d237e3 docs: remove extra closing tag
19faa6f01a60 qemuMigrationSrcRun: Fix misleading comment about NBD with TLS support
7767454267b9 fix documentation for sockets topology
06f5c092b8a3 conf: Format managed property of hostdev-pci ports correctly
167ac6354ce9 network: Convert managed property of hostdev-pci ports correctly
ed8984306e1c virDomainDiskTranslateSourcePool: Fix check of 'startupPolicy' definition
7b28561c8572 schemas: Update ref acpi for devices
ok=================================================
Searched 4147 objects, 35 matches 
`