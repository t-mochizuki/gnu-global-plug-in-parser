## gnu-global-plug-in-parser

### What is this?

This is a plugin parser for GNU Global.

### How to make GNU Global

#### Download

Use the following link to obtain the latest source archive.

[Getting GLOBAL](https://www.gnu.org/software/global/download.html)

#### Build & Install

Here version 6.5.6 is used.

Copy `plugin-factory/user-custom.c` to `global-6.5.6/plugin-factory/user-custom.c`.

And then, as always, fire the following command lines in `global-6.5.6`.

```
./configure --prefix=/Users/Shared/global
make install
```

#### How to use

Following is a usage example:

```
cp cheapscala/gtags.conf ~/.globalrc
cd /path/to/your\ project
gtags --gtagslabel=user-custom
global -xs '.*'
global -xd '.*'
global -xr '.*'
```

Or use an environment variable `GTAGSLABEL`.
