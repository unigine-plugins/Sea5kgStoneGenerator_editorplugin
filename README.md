# Sea5kg / Stone Generator

UnigineEditor (2.19.1.2) Plugin for generation of meshes representing stones of various sizes and shapes.

v0.0.7

[![Unigine Version](https://img.shields.io/badge/Unigine-2.19.1.2-yellow.svg)](https://developer.unigine.com/en/docs/2.19.1.2/) [![Unigine ADD-ON STORE](https://img.shields.io/badge/Unigine-AddonStore-black.svg)](https://store.unigine.com/add-on/1ee2ef39-4458-6124-aefe-dbe1b97903ce/description) [![Unigine Version](https://img.shields.io/badge/Youtube-Playlist-red.svg)](https://youtube.com/playlist?list=PL-Ky59xTi1WRCFocly-FhrFLLKwdbqEkO&feature=shared) [![Telegram](https://img.shields.io/badge/Telegram-Sea5kgStoneGenerator-blue.svg)](https://t.me/sea5kg_stonegenerator)



Plugin for Unigine Editor https://unigine.com/get-unigine/

Preview on Youtube:
- https://www.youtube.com/watch?v=7TaOFSUmlas

![preview](preview.gif)


* License of plugin: MIT
* Unigine SDK 2.19.1.2 - tested on `Community` (Free)


## Build on linux:

```
$ docker run --rm -it -v `pwd`:/opt/sources sea5kg/unigine-editor-pluigns:latest ./build_plugin.py
```


## Helper scripts PM

```
$ ./pm.py --help
usage: pm [--help] {py-check,copyrights-check} ...

Project Manager for StoneGenerator

options:
  --help, -h            help

subcommands:
  {py-check,copyrights-check}

Helper tools for work with current project

  py-check           Search all py files and run pylint+pycodestyle for check it
  copyrights-check   Check copyrights (now only for rc+h files)
```