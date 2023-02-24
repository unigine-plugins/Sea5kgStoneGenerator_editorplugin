# Development


## Building plugin (step by step)

Install requirements

1. Require UNIGINE SDK Browser
Pluging for scripting by python3 in Unigine Editor https://unigine.com/get-unigine/


2. Require System Packages

Ubuntu/Debian:
```bash
$ sudo apt install qt5-default cmake gcc git-core
```

Windows:
- install cmake >= 3.20 
- install Visual Studio 2015
- install qt 5.12.3 (And set system environment variable `QTDIR=C:\Qt\Qt5.12.3\5.12.3\`)
- install python3 (for command scripts)

### step 1: create a empty project

Use a UNIGINE SDK Browser and create some empty project, for example `my_project`

*`my_project` folder - where you can see `data` and with `bin` and with `include` and launchers*

### step 2: clone the sources

Ubuntu/Debian:
```bash
$ cd my_project
$ git clone https://github.com/unigine-plugins/commands-from-outside
$ cd unigine-editor-commands-from-outside
$ cp -rf * ../
```

### step 3: build plugin

Ubuntu/Debian:
```bash
$ cd my_project
$ cd UnigineEditorPlugin_PrototypeStoneGenerator
$ python3 -u build_plugin.py
```

Windows:
```bash
$ cd my_project
$ cd UnigineEditorPlugin_PrototypeStoneGenerator
$ python3 -u build_plugin.py
```

### step 5: run editor

After this call `./launch_editor.sh` or launch editor from `UNIGINE SDK Browser`

After this call `./launch_editor.bat`


## Helpful links

Mp4 to gif
- https://cloudconvert.com/mp4-to-gif
