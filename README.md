# upstream-fixes-tracking
upstream-fixes-tracking(uft) tracks the git-fixes and cve-fixes between upstream latest branch to a specific(downstream) branch.
It will search "Fixes:" and "CVE-" lines in commit message. 

This project is based on https://github.com/joergroedel/git-fixes, reused some of the fuctions in git-fixes.cc.

#Building
The libgit2 library is required.
$make

when the build is completed successfully, you can install:
$make install 
It will be installed into $HOME/bin by default.

#Running
uft --base --extra --blacklist --bl_keyword --bl-file --slack --email

--base: base branch or tag id

--extra: extra commits that have been backported

--blacklist: blacklist the commits

--bl-keyword: blacklist the commits that contain the keywords

--bl-file: blacklist the commits in the src files

--slack: send to slack channel

--email:  send to emails