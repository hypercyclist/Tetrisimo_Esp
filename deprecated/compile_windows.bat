set project_name=Tetrisimo
cls
cd src
g++ -std=c++17 -w -g -ggdb ^
-I crossplatform ^
-I windows ^
-I lib\include ^
-L lib ^
crossplatform\*.cpp windows\*.cpp ^
-o ..\build\windows\%project_name%.exe ^
-lglfw3dll -lgdi32 -lopengl32 lib\glad.c
cd ..
