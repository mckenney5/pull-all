pull-all
==========
_./pull-all_

This program `cd`s into every dir in its directory, then runs `git pull && cd ..`

### Notes
- All source code in this repository is public domain (see LICENSE)
- I doubt I will be accepting pull/merge requests for this repo
- See man file for more info

### Make Options
* `make`                : compiles pull-all.c
* `make no-color`       : compiles pull-all.c with colors disabled
* `make install`        : creates pull-all.out and compresses the man page, then copies pull-all to /usr/bin file and installs the manpage
* `make uninstall`      : deletes /usr/bin/pull-all and /usr/share/man/man1/pull-all.1.gz

