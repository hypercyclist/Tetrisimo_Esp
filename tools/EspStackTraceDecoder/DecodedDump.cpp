Exception Cause: 29  [StoreProhibited: A store referenced a page mapped with an attribute that does not permit stores]

0x4020460e: std::__shared_ptr<Scene, (__gnu_cxx::_Lock_policy)0>::operator=(std::__shared_ptr<Scene, (__gnu_cxx::_Lock_policy)0> const&) at s:\product\programming\ArduinoOutput\sketch/Scene.cpp:186
 (inlined by) std::shared_ptr<Scene>::operator=(std::shared_ptr<Scene> const&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) Scene::setPreviousScene(std::shared_ptr<Scene>) at s:\product\programming\ArduinoOutput\sketch/Scene.cpp:70
0x40202e15: std::__shared_ptr<Scene, (__gnu_cxx::_Lock_policy)0>::~__shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) std::shared_ptr<Scene>::~shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) Game::initializeMainMenu() at s:\product\programming\ArduinoOutput\sketch/Game.cpp:191
0x40209758: std::_Function_base::_Base_manager<Game::initializeMainMenu()::{lambda()#1}>::_M_manager(std::_Any_data&, std::_Function_base::_Base_manager<Game::initializeMainMenu()::{lambda()#1}> const&, std::_Manager_operation) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0/functional:1734
0x40202260: std::_Function_handler<void (), Game::initializeMainMenu()::{lambda()#1}>::_M_invoke(std::_Any_data const&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) _M_invoke at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0/functional:1871
0x40204f89: Widget::setSize(Size) at s:\product\programming\ArduinoOutput\sketch/Widget.cpp:200
0x402030b3: Game::initialize() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x402011e2: std::__shared_ptr<Game, (__gnu_cxx::_Lock_policy)0>::__shared_ptr<std::allocator<Game>>(std::_Sp_make_shared_tag, std::allocator<Game> const&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x40203108: Game::start() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x40201204: std::__shared_ptr<Game, (__gnu_cxx::_Lock_policy)0>::~__shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) std::shared_ptr<Game>::~shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) setup at s:\product\programming\Tetrisimo_Esp\source/Tetrisimo_Esp.ino:5
0x40207ab0: loop_wrapper() at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/core_esp8266_main.cpp:194
0x40100c49: cont_wrapper at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/cont.S:81
0x4010f000: ?? ??:0
