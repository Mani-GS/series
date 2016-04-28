# Series
Keep track of your favourite TV series!
With this simple program, you can create a sqlite db and add the last episode/season you watched. You can do this for every series you want!
You'll never forget which was the last episode.
This program uses Qt and sqlite libraries

# How to install
## Download source code and compile it by yourself
To install this program make sure you've installed the following libraries:
- qt5-default;
- qtcreator (optional);
- libsqlite3-dev.

First of all, download the latest release, then extract the source code in one folder.
Open a terminal in that folder and execute:
```script
$ qmake series.pro
$ make
```
It will create a lot of files, you need only one of them: the ELF, named **series**. Double click it and the program will start!

If you want to create a .desktop file you can use series_.png image (128x128) as file icon.

## Install on Ubuntu Trusty or newer
You can download and install the binary package from the PPA repository **mani-ddev/series**. Open a terminal and execute:

```script
$ sudo add-apt-repository ppa:mani-ddev/series
$ sudo apt-get update
$ sudo apt-get install series
```

# Features
- Add new TV Series to a sqlite database;
- Keep track about last season and episode watched, with a "finish" flag used at users leisure;
- Rename series, reorder them or remove them.

# TO DO
- Implement cloud service to share the db with other devices
