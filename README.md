# Series
Keep track of your favourite TV series!
With this simple program, you can create a sqlite db and add the last episode/season you watched. You can do this for every series you want!
You'll never forget which was the last episode.
This program uses Qt and sqlite libraries
It's available on **Linux** (Debian distros), **Windows** and **Mac OS X**. You can download source code and build it by yourself or you can simply download the pre-built binary for your OS.
# Features
- [x] Add new TV Series to a sqlite database;
- [x] Keep track about last season and episode watched, with a "finish" flag used at users leisure;
- [x] Rename series, reorder them or remove them.
- [x] Automatic checking for new updates.

# TO DO
- [ ] Implement cloud service to share the db with other devices

# How to install

## Linux OS

### Download source code and compile it by yourself
To install this program make sure you've installed the following libraries:
- qt5-default;
- qtcreator (optional);
- libsqlite3-dev.

First of all, download the latest release, then extract the source code in one folder.
Open a terminal in that folder and execute:
```script
$ qmake -config release
$ make
```
Double click the ELF file, named **series**, and the program will start!

If you want to create a .desktop file you can use series_.png image (128x128) as file icon.

### Install on Ubuntu Trusty or newer
You can download and install the binary package from the PPA repository **mani-ddev/series**. Open a terminal and execute:

```script
$ sudo add-apt-repository ppa:mani-ddev/series
$ sudo apt-get update
$ sudo apt-get install series
```

## Mac OS X

To build this program make sure you installed all the **Qt** libraries; if you're running an OS X version lower than 10.5 (Leopard), you'll need to install also **sqlite3** libraries. <br/>
Also be sure to export the _**qmake path**_ in this way:

```script
$ PATH=/users/<your_user>/Qt/<qt_version>/bin:$PATH
$ export PATH
```

First of all, download the latest release, then extract the source code in one folder. Open a terminal in that folder and execute:

```script
$ qmake -config release
$ make
```

If you want to run it on another MAC (a MAC without Qt libraries), you have to execute this:

```script
$ macdeployqt ./series.app
```

Double click the APP file, named **series**, and the program will start!

## Windows OS

First, _download Qt Creator_.
Then, once you downloaded the latest release, open the **series.pro** file with your favourite text editor to include the sqlite3.c and sqlite3.h files:

```script
File: series.pro
[...]
SOURCES += main.cpp\
        mainwindow.cpp \
    series.cpp \
    manager.cpp \
    insertdialog.cpp \
    modifydialog.cpp \
    tutorialdialog.cpp \
    aboutdialog.cpp \
 #    sqlite3.c			#only for Windows

HEADERS  += mainwindow.h \
    series.h \
    manager.h \
    insertdialog.h \
    modifydialog.h \
    tutorialdialog.h \
    aboutdialog.h \
 #    sqlite3.h			#only for Windows

FORMS    += mainwindow.ui \
    insertdialog.ui \
    modifydialog.ui \
[...]
```

You just have to remove the # character at the beginning of the two lines that have (before sqlite3.c and sqlite3.h). Then, open the project with Qt Creator, select Build -> Release and build it.
To make it works (in your PC, which has Qt libraries installed) you need the following .dll files in the .exe file folder:

```script
libgcc_s_dw2-1.dll
libstdc++-6.dll
libwinpthread-1.dll
Qt5Core.dll
Qt5Gui.dll
Qt5widgets.dll
```

If you want to run it on another PC (a PC without Qt libraries), you have to make a folder like this:

```script
-Series/
-   platforms/
-      	qwindows.dll
-   icudt54.dll
-   icuin54.dll
-   icuuc54.dll
-   libgcc_s_dw2-1.dll
-   libstdc++-6.dll
-   libwinpthread-1.dll
-   Qt5Core.dll
-   Qt5Gui.dll
-   Qt5widgets.dll
-   series.exe
```

Now, double click the EXE file, named **series**, and the program will start!
