SCRIPT_DIR=$( cd "$( dirname "$0" )" && pwd )
APP="$SCRIPT_DIR/bin/Editor_x64"
export LD_LIBRARY_PATH="$SCRIPT_DIR/bin:$LD_LIBRARY_PATH"
if [ -f "$APP" ]; then
	"$APP" -video_app vk -video_adapter 0 -video_refresh 0 -video_debug 0 -main_window_size 2560 1440 -main_window_resizable 1 -main_window_fullscreen 0 -render_vsync 0 -video_offscreen 0 -sound_app auto -data_path ../data/ -extern_plugin UnigineFbxImporter,UnigineGLTFImporter,UnigineFbxExporter -console_command "config_autosave 1 && world_load \"111\""
else
	echo "$APP not found"
fi
# gdb -args
# world_load "guid://89711a67fb2583f01744c818fb26bca667bfa93e"