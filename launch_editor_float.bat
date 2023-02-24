@echo off
setlocal EnableDelayedExpansion
rem set PYTHONHOME=P:\bin\Python3Home\
rem set PYTHONPATH="P:\UnigineEditorPlugin_Python3Scripting\Python-3.10.1\Lib"
rem unset PYTHONPATH
set APP="bin\Editor_x64.exe"
if exist %APP% (
	start "" %APP%  -video_app auto -video_vsync 0 -video_refresh 0 -video_mode 1 -video_resizable 1 -video_fullscreen 0 -video_debug 0 -sound_app auto -data_path "../data/" -extern_plugin "FbxImporter,GLTFImporter,FbxExporter" -console_command "config_autosave 1"
) else (
	set MESSAGE=%APP% not found"
	echo !MESSAGE!
)