cls
g++ ^
-std=c++17 -w -g -ggdb ^
-I . ^
-I ./include/ ^
-L ./lib/ ^
../Background.cpp ^
../Button.cpp ^
../CheckBox.cpp ^
Camera.cpp ^
../Color.cpp ^
../Config.cpp ^
Display.cpp ^
../DisplayBuffer.cpp ^
../Game.cpp ^
../Game_AboutSettings.cpp ^
../Game_AdvancedSettings.cpp ^
../Game_ColorsSettings.cpp ^
../Game_CooperativeGame.cpp ^
../Game_CreateServer.cpp ^
../Game_CustomColorsSettings.cpp ^
../Game_CustomFigureSettings.cpp ^
../Game_GameSettings.cpp ^
../Game_HighScore.cpp ^
../Game_MainMenu.cpp ^
../Game_Multiplayer.cpp ^
../Game_NetworkSettings.cpp ^
../Game_ResistorSettings.cpp ^
../Game_ServerBrowser.cpp ^
../Game_Settings.cpp ^
../Game_SingleGame.cpp ^
../Game_VersusGame.cpp ^
../Game_WidgetViewer.cpp ^
IpAddress.cpp ^
../KeyboardHook.cpp ^
../Label.cpp ^
../Layout.cpp ^
../LineEdit.cpp ^
Log.cpp ^
Painter.cpp ^
../PaletteView.cpp ^
../PhysButton.cpp ^
PlatformTime.cpp ^
../Point.cpp ^
../Port.cpp ^
../Resistor.cpp ^
../ResourceTheme.cpp ^
../Scene.cpp ^
../ServiceAddress.cpp ^
ShadersProcessor.cpp ^
../Size.cpp ^
../StringUtf.cpp ^
../TableView.cpp ^
../TextView.cpp ^
../VerticalLayout.cpp ^
../Viewport.cpp ^
../Widget.cpp ^
../WidgetId.cpp ^
../WifiSettings.cpp ^
main.cpp ^
-o bin\main.exe ^
-lglfw3dll ^
-lgdi32 ^
-lopengl32 ^
lib\glad.c