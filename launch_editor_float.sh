SCRIPT_DIR=$( cd "$( dirname "$0" )" && pwd )
APP="$SCRIPT_DIR/bin/Editor_x64"
export LD_LIBRARY_PATH="$SCRIPT_DIR/bin:$LD_LIBRARY_PATH"
if [ -f "$APP" ]; then
	"$APP" $(COMMAND_LINE)
else
	echo "$APP not found"
fi
