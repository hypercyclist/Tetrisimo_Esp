Exception Cause: 28  [LoadProhibited: A load referenced a page mapped with an attribute that does not permit loads]

0x402059f5: Scene::setBackgroundWidget(std::shared_ptr<Background>) at s:\product\programming\ArduinoOutput\sketch/Scene.cpp:78
0x402059f1: std::__shared_ptr<Widget, (__gnu_cxx::_Lock_policy)0>& std::__shared_ptr<Widget, (__gnu_cxx::_Lock_policy)0>::operator=<Background>(std::__shared_ptr<Background, (__gnu_cxx::_Lock_policy)0> const&) at s:\product\programming\ArduinoOutput\sketch/Scene.cpp:78
 (inlined by) std::shared_ptr<Widget>& std::shared_ptr<Widget>::operator=<Background>(std::shared_ptr<Background> const&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:277
 (inlined by) Scene::setBackgroundWidget(std::shared_ptr<Background>) at s:\product\programming\ArduinoOutput\sketch/Scene.cpp:45
0x40204214: std::__shared_ptr<Background, (__gnu_cxx::_Lock_policy)0>::~__shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) std::shared_ptr<Background>::~shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) Game::initializeWidgetViewer() at s:\product\programming\ArduinoOutput\sketch/Game.cpp:404
0x40205114: ResourceTheme::~ResourceTheme() at s:\product\programming\ArduinoOutput\sketch/ResourceTheme.cpp:41
0x40204329: Game::initialize() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x4020120a: std::__shared_ptr<Game, (__gnu_cxx::_Lock_policy)0>::__shared_ptr<std::allocator<Game>>(std::_Sp_make_shared_tag, std::allocator<Game> const&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x4020439c: Game::start() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x4020122c: std::__shared_ptr<Game, (__gnu_cxx::_Lock_policy)0>::~__shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) std::shared_ptr<Game>::~shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) setup at s:\product\programming\Tetrisimo_Esp\source/Tetrisimo_Esp.ino:6
0x4020a110: loop_wrapper() at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/core_esp8266_main.cpp:194
0x40100c49: cont_wrapper at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/cont.S:81
0x4010f000: ?? ??:0
