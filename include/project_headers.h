#ifndef PROJECT_HEADERS_H
#define PROJECT_HEADERS_H

using u8 = unsigned char;
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <unordered_map>
#include <memory>
//#include <conio.h> //microsoft
//#include <curses.h>
//#include <termios.h>
#ifndef _WIN32
#include <unistd.h>
#endif // _WIN32
#include <stdarg.h>
#include "entity_structs_consts.h"
#include "dice_roll.h"
#include "simdjson.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "rogueutil.h"

#ifdef __cplusplus
}
#endif
#endif