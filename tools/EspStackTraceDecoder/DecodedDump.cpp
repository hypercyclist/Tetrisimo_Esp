Exception Cause: 28  [LoadProhibited: A load referenced a page mapped with an attribute that does not permit loads]

0x4020a014: Widget::getSize() at s:\product\programming\ArduinoOutput\sketch/Widget.cpp:200
0x40210dd8: std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::string const&) at /workdir/arena.x86_64/gcc/xtensa-lx106-elf/libstdc++-v3/include/bits/basic_string.tcc:734
0x4020515b: std::_MakeUniq<Size>::__single_object std::make_unique<Size, int, int>(int&&, int&&) at s:\product\programming\ArduinoOutput\sketch/Widget.cpp:200
 (inlined by) Widget::Widget() at s:\product\programming\ArduinoOutput\sketch/Widget.cpp:20
0x40201464: CheckBox::CheckBox(std::string) at s:\product\programming\ArduinoOutput\sketch/CheckBox.cpp:104
0x40207bdc: operator new(unsigned int) at ??:?
0x40202a44: void __gnu_cxx::new_allocator<CheckBox>::construct<CheckBox, char const (&) [17]>(CheckBox*, char const (&) [17]) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) std::enable_if<std::__and_<std::allocator_traits<std::allocator<CheckBox> >::__construct_helper<CheckBox, char const (&) [17]>::type>::value, void>::type std::allocator_traits<std::allocator<CheckBox> >::_S_construct<CheckBox, char const (&) [17]>(std::allocator<CheckBox>&, CheckBox*, char const (&) [17]) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/alloc_traits.h:256
 (inlined by) decltype (_S_construct({parm#1}, {parm#2}, (forward<char const (&) [17]>)({parm#3}))) std::allocator_traits<std::allocator<CheckBox> >::construct<CheckBox, char const (&) [17]>(std::allocator<CheckBox>&, CheckBox*, char const (&) [17]) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/alloc_traits.h:402
 (inlined by) std::__shared_ptr<CheckBox, (__gnu_cxx::_Lock_policy)0>::__shared_ptr<std::allocator<CheckBox>, char const (&) [17]>(std::_Sp_make_shared_tag, std::allocator<CheckBox> const&, char const (&) [17]) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:1129
0x40210aca: std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() at /workdir/arena.x86_64/gcc/xtensa-lx106-elf/libstdc++-v3/include/bits/basic_string.tcc:734
0x40203245: std::shared_ptr<CheckBox>::shared_ptr<std::allocator<CheckBox>, char const (&) [17]>(std::_Sp_make_shared_tag, std::allocator<CheckBox> const&, char const (&) [17]) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) std::shared_ptr<CheckBox> std::allocate_shared<CheckBox, std::allocator<CheckBox>, char const (&) [17]>(std::allocator<CheckBox> const&, char const (&) [17]) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:614
 (inlined by) std::shared_ptr<CheckBox> std::make_shared<CheckBox, char const (&) [17]>(char const (&) [17]) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:630
 (inlined by) Game::initializeGameSettings() at s:\product\programming\ArduinoOutput\sketch/Game.cpp:288
0x402033ba: Game::initialize() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x402011e2: std::__shared_ptr<Game, (__gnu_cxx::_Lock_policy)0>::__shared_ptr<std::allocator<Game>>(std::_Sp_make_shared_tag, std::allocator<Game> const&) at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x40203414: Game::start() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
0x40201204: std::__shared_ptr<Game, (__gnu_cxx::_Lock_policy)0>::~__shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:127
 (inlined by) std::shared_ptr<Game>::~shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) setup at s:\product\programming\Tetrisimo_Esp\source/Tetrisimo_Esp.ino:5
0x40207dd4: loop_wrapper() at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/core_esp8266_main.cpp:194
0x40100c49: cont_wrapper at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/cont.S:81
0x4010f000: ?? ??:0
