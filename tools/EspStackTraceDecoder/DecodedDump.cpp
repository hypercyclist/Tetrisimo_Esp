Exception Cause: Not found

0x40205c9b: TextView::render() at s:\product\programming\ArduinoOutput\sketch/TextView.cpp:58
0x40203186: std::__shared_ptr<Label, (__gnu_cxx::_Lock_policy)0>::__shared_ptr<std::allocator<Label>, std::string&>(std::_Sp_make_shared_tag, std::allocator<Label> const&, std::string&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:488
 (inlined by) std::shared_ptr<Label>::shared_ptr<std::allocator<Label>, std::string&>(std::_Sp_make_shared_tag, std::allocator<Label> const&, std::string&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:319
 (inlined by) std::shared_ptr<Label> std::allocate_shared<Label, std::allocator<Label>, std::string&>(std::allocator<Label> const&, std::string&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:614
 (inlined by) std::shared_ptr<Label> std::make_shared<Label, std::string&>(std::string&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:630
 (inlined by) Game::initializeBasicScene(std::shared_ptr<Scene>, std::string, int) at s:\product\programming\ArduinoOutput\sketch/Game.cpp:171
0x402010a2: Background::drawNet() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x40203186: std::__shared_ptr<Label, (__gnu_cxx::_Lock_policy)0>::__shared_ptr<std::allocator<Label>, std::string&>(std::_Sp_make_shared_tag, std::allocator<Label> const&, std::string&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:488
 (inlined by) std::shared_ptr<Label>::shared_ptr<std::allocator<Label>, std::string&>(std::_Sp_make_shared_tag, std::allocator<Label> const&, std::string&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:319
 (inlined by) std::shared_ptr<Label> std::allocate_shared<Label, std::allocator<Label>, std::string&>(std::allocator<Label> const&, std::string&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:614
 (inlined by) std::shared_ptr<Label> std::make_shared<Label, std::string&>(std::string&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:630
 (inlined by) Game::initializeBasicScene(std::shared_ptr<Scene>, std::string, int) at s:\product\programming\ArduinoOutput\sketch/Game.cpp:171
0x4020ca46: fde_unencoded_compare at /workdir/repo/gcc/libgcc/unwind-dw2-fde.c:344
0x4020b4be: Widget::draw() at s:\product\programming\ArduinoOutput\sketch/Widget.cpp:137
0x40203f84: Layout::render() at s:\product\programming\ArduinoOutput\sketch/Layout.cpp:76
0x4020b4be: Widget::draw() at s:\product\programming\ArduinoOutput\sketch/Widget.cpp:137
0x40206638: Widget::traverse() at s:\product\programming\ArduinoOutput\sketch/Widget.cpp:106
0x40202850: std::__shared_ptr<Scene, (__gnu_cxx::_Lock_policy)0>::~__shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:488
 (inlined by) std::shared_ptr<Scene>::~shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) Game::run() at s:\product\programming\ArduinoOutput\sketch/Game.cpp:68
0x40203b71: Game::start() at ??:?
0x40201204: std::__shared_ptr<Game, (__gnu_cxx::_Lock_policy)0>::~__shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) std::shared_ptr<Game>::~shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) setup at s:\product\programming\Tetrisimo_Esp\source/Tetrisimo_Esp.ino:6
0x402091d4: loop_wrapper() at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/core_esp8266_main.cpp:194
0x40100c49: cont_wrapper at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/cont.S:81
0x4010f000: ?? ??:0
