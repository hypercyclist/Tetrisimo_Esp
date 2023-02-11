project_name=Tetrisimo
clear
cd src
g++ -std=c++17 -w -g -ggdb \
-I crossplatform \
-I windows \
-I lib/include \
-L lib \
crossplatform/*.cpp windows/*.cpp \
-o ../build/linux/$project_name \
lib/glad.c -lglfw -ldl
cd ..