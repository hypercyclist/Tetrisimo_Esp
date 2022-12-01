clear
g++ \
-std=c++17 -w \
-I . \
-I ./include/ \
-I ./include/arduino \
-L ./lib/ \
../Background.cpp \
../Button.cpp \
../CheckBox.cpp \
Camera.cpp \
../Color.cpp \
../Config.cpp \
Display.cpp \
../DisplayBuffer.cpp \
../Game.cpp \
IpAddress.cpp \
../KeyboardHook.cpp \
../Label.cpp \
../Layout.cpp \
../LineEdit.cpp \
Log.cpp \
../Painter.cpp \
../PaletteView.cpp \
../PhysButton.cpp \
PlatformTime.cpp \
../Point.cpp \
../Port.cpp \
../Resistor.cpp \
../ResourceTheme.cpp \
../Scene.cpp \
../ServiceAddress.cpp \
ShadersProcessor.cpp \
../Size.cpp \
../StringUtf.cpp \
../TableView.cpp \
../TextView.cpp \
../VerticalLayout.cpp \
../Viewport.cpp \
../Widget.cpp \
../WidgetId.cpp \
../WifiSettings.cpp \
main.cpp \
-o bin/main.exe \
-lglfw3dll \
-lgdi32 \
-lopengl32 \
lib/glad.c