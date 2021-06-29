Exception Cause: 28  [LoadProhibited: A load referenced a page mapped with an attribute that does not permit loads]

0x401000cf: std::function<void ()>::operator()() const at c:\Soft\programming\projects\build\sketch/Scene.cpp:78
0x40201f6a: std::__shared_ptr<Scene, (__gnu_cxx::_Lock_policy)0>::operator=(std::__shared_ptr<Scene, (__gnu_cxx::_Lock_policy)0> const&) at c:\users\anikulin\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) std::shared_ptr<Scene>::operator=(std::shared_ptr<Scene> const&) at c:\users\anikulin\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) Display::setActiveScene(std::shared_ptr<Scene>) at c:\Soft\programming\projects\build\sketch/Display.cpp:53
0x40204545: std::__shared_ptr<Scene, (__gnu_cxx::_Lock_policy)0>::~__shared_ptr() at c:\users\anikulin\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) std::shared_ptr<Scene>::~shared_ptr() at c:\users\anikulin\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) Game::initialize() at c:\Soft\programming\projects\build\sketch/Game.cpp:61
0x4020120a: std::__shared_ptr<Game, (__gnu_cxx::_Lock_policy)0>::__shared_ptr<std::allocator<Game>>(std::_Sp_make_shared_tag, std::allocator<Game> const&) at c:\users\anikulin\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x4020457c: Game::start() at c:\users\anikulin\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x4020122c: std::__shared_ptr<Game, (__gnu_cxx::_Lock_policy)0>::~__shared_ptr() at c:\users\anikulin\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) std::shared_ptr<Game>::~shared_ptr() at c:\users\anikulin\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) setup at c:\Soft\programming\projects\Tetrisimo_Esp\source/Tetrisimo_Esp.ino:6
0x4020a410: loop_wrapper() at C:\Users\anikulin\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/core_esp8266_main.cpp:194
0x40100c49: cont_wrapper at C:\Users\anikulin\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/cont.S:81
0x4010f000: ?? ??:0
