Exception Cause: 28  [LoadProhibited: A load referenced a page mapped with an attribute that does not permit loads]

0x40207b70: ResourceTheme::getFocusColor() const at s:\product\programming\in_progress\real_tetris\ESPOutput\sketch/ResourceTheme.cpp:44
0x40202597: Game::initialize() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:466
0x4020532c: HardwareSerial::begin(unsigned long, SerialConfig, SerialMode, unsigned char, bool) at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/HardwareSerial.cpp:131
0x401009c0: malloc at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266\umm_malloc/umm_malloc.cpp:552
0x40205a50: operator new[](unsigned int) at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/abi.cpp:64
0x40202691: Game::start() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr_base.h:466
0x402010dc: std::__shared_ptr<Game, (__gnu_cxx::_Lock_policy)0>::~__shared_ptr() at s:\product\programming\in_progress\real_tetris\Tetrisimo_Esp\source/Background.cpp:20
 (inlined by) std::shared_ptr<Game>::~shared_ptr() at c:\users\ev7\appdata\local\arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\2.5.0-4-b40a506\xtensa-lx106-elf\include\c++\5.2.0\bits/shared_ptr.h:93
 (inlined by) setup at s:\product\programming\in_progress\real_tetris\Tetrisimo_Esp\source/Tetrisimo_Esp.ino:6
0x40205c6c: loop_wrapper() at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/core_esp8266_main.cpp:194
0x40100c3d: cont_wrapper at C:\Users\EV7\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.7.4\cores\esp8266/cont.S:81
0x4010f000: ?? ??:0
