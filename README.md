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
uft --base --extra --blacklist --bl_keyword --bl-file --slack --email

--base: base branch or tag id, this is necessary

--extra: extra commits that have been backported

--blacklist: blacklist the commits

--bl-keyword: blacklist the commits that contain the keywords

--bl-file: blacklist the commits that in the src files

--slack: send to slack channel

--email:  send to emails

## DEMO

```Bash
`#:~/libvirt$ uft -b v8.1.0 -k /tmp/bl-keywords
revision is v8.1.0..HEAD 
ca6122d237e3 docs: remove extra closing tag
19faa6f01a60 qemuMigrationSrcRun: Fix misleading comment about NBD with TLS support
4d7bb0177a33 qemu_tpm: Do async IO when starting swtpm emulator
7767454267b9 fix documentation for sockets topology
d83d9dde1da8 qemu: Accept <allowReboot value='default'/>
77c638c3c780 conf: Restore error checking in VideoAccelDefParseXML()
06f5c092b8a3 conf: Format managed property of hostdev-pci ports correctly
167ac6354ce9 network: Convert managed property of hostdev-pci ports correctly
eac8de54a687 domain_cgroup: Fix a condition in virDomainCgroupConnectCgroup()
b399f2c00044 virnetdev: Fix regression in setting VLAN tag
b6705cdefb09 conf: Fix smm=off handling
ed8984306e1c virDomainDiskTranslateSourcePool: Fix check of 'startupPolicy' definition
7b28561c8572 schemas: Update ref acpi for devices
14f42129fce2 qemu_hotplug: Close FDs in QEMU on failed chardev hotplug
a1dd3576b57b qemu_hotplug: Create chardev files before attempting to relabel them
Found 1331 objects (15 matches)
`