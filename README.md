## gnu-global-plug-in-parser

### What is this?

This is a plugin parser for GNU Global.

### How to make GNU Global

#### Download

Use the following link to obtain the latest source archive.

[Getting GLOBAL](https://www.gnu.org/software/global/download.html)

#### Build & Install

Here treat the latest version as 6.5.6.

Copy `plugin-factory/user-custom.c` to `global-6.5.6/plugin-factory/user-custom.c`.

And then, as always, fire Following command lines under the global-6.5.6.

```
./configure --prefix=/Users/Shared/global
make install
```

#### How to use

Following command lines is usage example:

```
cp cheapscala/gtags.conf ~/.globalrc
cd /path/to/your\ project
gtags --gtagslabel=user-custom
global -xs '.*'
global -xd '.*'
global -xr '.*'
```

Or use a environment variable `GTAGSLABEL`.
