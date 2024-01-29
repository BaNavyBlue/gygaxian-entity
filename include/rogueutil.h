/**
 * @section LICENSE
 * Copyright 2020 Sergei Akhmatdinov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied *.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Antone Bajor Modified this code 2023 to remove the cpp flags because of 
 * strange spurious cursor or characters. No compelling reason to use std::iostream.
 * 
 * Also moved the implementation into a .c file to allow sharing between classes
 * and implementation files to prevent previous definition errors.
 * 
 */

/**
 * @file rogueutil.h
 * @brief Cross-platform C/C++ utility for creating text-based user interfaces
 *
 * @section Description
 * Rogueutil provides some useful functions for creating TUIs and console-based
 * games, such as color printing and clearing the console.
 * It can be used both as a C or C++ header file and it aims at being
 * cross-platform between Windows and *nix.
 *
 */

#ifndef RUTIL_H
#define RUTIL_H

#ifdef _DOXYGEN_
	/** @brief Define to use ANSI escape sequences instead of WinAPI on Windows */
	#define RUTIL_USE_ANSI

	/**
	* @brief Define to override rogueutil's string type.
	* @details Defaults to std::string in C++ and char* in C.
	*/
	#define RUTIL_STRING char*
#endif /* _DOXYGEN */

// #ifdef __cplusplus
// 	/* Common C++ headers */
// 	#include <iostream>
// 	#include <string>
// 	#include <sstream>
// 	#include <cstdio> /* for getch() */
// 	#include <cstdarg> /* for colorPrint() */

// 	/* Namespace forward declarations */
// 	namespace rogueutil
// 	{
//         	void locate(int x, int y);
//         }
// #else
	#include <stdio.h> /* for getch() / printf() */
	#include <string.h> /* for strlen() */
	#include <stdarg.h> /* for colorPrint() */

	//void locate(int x, int y); /* Forward declare for C to avoid warnings */
// #endif

#ifdef _WIN32
	#include <windows.h>  /* for WinAPI and Sleep() */
	#define _NO_OLDNAMES  /* for MinGW compatibility */
	#include <conio.h>    /* for getch() and kbhit() */
	#include <lmcons.h>   /* for getUsername()      */
	#define getch _getch
	#define kbhit _kbhit
#else
	#include <termios.h> /* for getch() and kbhit() */
	#include <unistd.h> /* for getch(), kbhit() and getuid() */
	#include <time.h>   /* for nanosleep() */
	#include <sys/ioctl.h> /* for getkey() */
	#include <sys/types.h> /* for kbhit() */
	#include <sys/time.h> /* for kbhit() */
	#include <pwd.h> /* for getpwuid() */
#endif

/* Functions covered by Window's conio.h */
#ifndef _WIN32

/**
 * @brief Get a charater without waiting on a Return
 * @details Windows has this functionality in conio.h
 * @return The character
 */
int getch(void);

/**
 * @brief Determines if a button was pressed.
 * @details Windows has this in conio.h
 * @return Number of characters read
 */
int kbhit(void);

#endif /* _WIN32 */


#ifndef gotoxy
/**
 * @brief Sets the cursor to the specified x and y position.
 * @details Windows has this functionality in conio.h
 * @see locate()
 */
void gotoxy(int x, int y);
#endif /* gotoxy */

// #ifdef __cplusplus
// /**
//  * @brief Default namespace for C++
//  */
// namespace rogueutil
// {
// #endif /* __cplusplus */

// #ifdef __cplusplus
// 	#ifndef RUTIL_STRING
// 		typedef std::string RUTIL_STRING;
// 	#endif /* RUTIL_STRING */

// #else
	#ifndef RUTIL_STRING
		typedef const char* RUTIL_STRING;
	#endif /* RUTIL_STRING */

// #endif /* __cplusplus */

/**
 * @brief Provides easy color codes with similar numbers to QBasic
 * @brief 's Changing this to ansi 256 color mode because this is dumb - Antone
 * 
 */
typedef enum color_code {
    NOCOLOR = -1,
#ifndef _WIN32
	BLACK,
	DARKRED,
	DARKGREEN,
	DARKYELLOW,
	DARKBLUE,
	DARKPURPLE,
	AQUA,
	LIGHTGREY,
	GREY,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
 #else
    BLACK,	
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	GREY,
	DARKGREY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
#endif
} color_code;

/* Constant strings for ANSI colors ans seqiences */
static const RUTIL_STRING ANSI_CLS                = "\033[2J\033[3J";
static const RUTIL_STRING ANSI_CONSOLE_TITLE_PRE  = "\033]0;";
static const RUTIL_STRING ANSI_CONSOLE_TITLE_POST = "\007";
static const RUTIL_STRING ANSI_ATTRIBUTE_RESET    = "\033[0m";
static const RUTIL_STRING ANSI_CURSOR_HIDE        = "\033[?25l";
static const RUTIL_STRING ANSI_CURSOR_SHOW        = "\033[?25h";
static const RUTIL_STRING ANSI_CURSOR_HOME        = "\033[H";
static const RUTIL_STRING ANSI_BLACK              = "\033[22;30m";
static const RUTIL_STRING ANSI_RED                = "\033[22;31m";
static const RUTIL_STRING ANSI_GREEN              = "\033[22;32m";
static const RUTIL_STRING ANSI_BROWN              = "\033[22;33m";
static const RUTIL_STRING ANSI_BLUE               = "\033[22;34m";
static const RUTIL_STRING ANSI_MAGENTA            = "\033[22;35m";
static const RUTIL_STRING ANSI_CYAN               = "\033[22;36m";
static const RUTIL_STRING ANSI_GREY               = "\033[22;37m";
static const RUTIL_STRING ANSI_DARKGREY           = "\033[01;30m";
static const RUTIL_STRING ANSI_LIGHTRED           = "\033[01;31m";
static const RUTIL_STRING ANSI_LIGHTGREEN         = "\033[01;32m";
static const RUTIL_STRING ANSI_YELLOW             = "\033[01;33m";
static const RUTIL_STRING ANSI_LIGHTBLUE          = "\033[01;34m";
static const RUTIL_STRING ANSI_LIGHTMAGENTA       = "\033[01;35m";
static const RUTIL_STRING ANSI_LIGHTCYAN          = "\033[01;36m";
static const RUTIL_STRING ANSI_WHITE              = "\033[01;37m";
static const RUTIL_STRING ANSI_BACKGROUND_BLACK   = "\033[40m";
static const RUTIL_STRING ANSI_BACKGROUND_RED     = "\033[41m";
static const RUTIL_STRING ANSI_BACKGROUND_GREEN   = "\033[42m";
static const RUTIL_STRING ANSI_BACKGROUND_YELLOW  = "\033[43m";
static const RUTIL_STRING ANSI_BACKGROUND_BLUE    = "\033[44m";
static const RUTIL_STRING ANSI_BACKGROUND_MAGENTA = "\033[45m";
static const RUTIL_STRING ANSI_BACKGROUND_CYAN    = "\033[46m";
static const RUTIL_STRING ANSI_BACKGROUND_WHITE   = "\033[47m";
/* Remaining colors not supported as background colors */

/**
 * @brief Provides keycodes for special keys
 */
typedef enum key_code {
	KEY_ESCAPE  = 0,
	KEY_ENTER   = 1,
	KEY_SPACE   = 32,
	KEY_BKSP    = 8,

	KEY_INSERT  = 2,
	KEY_HOME    = 3,
	KEY_PGUP    = 4,
	KEY_DELETE  = 5,
	KEY_END     = 6,
	KEY_PGDOWN  = 7,

	KEY_UP      = 14,
	KEY_DOWN    = 15,
	KEY_LEFT    = 16,
	KEY_RIGHT   = 17,

	KEY_F1      = 18,
	KEY_F2      = 19,
	KEY_F3      = 20,
	KEY_F4      = 21,
	KEY_F5      = 22,
	KEY_F6      = 23,
	KEY_F7      = 24,
	KEY_F8      = 25,
	KEY_F9      = 26,
	KEY_F10     = 27,
	KEY_F11     = 28,
	KEY_F12     = 29,

	KEY_NUMDEL  = 30,
	KEY_NUMPAD0 = 31,
	KEY_NUMPAD1 = 127,
	KEY_NUMPAD2 = 128,
	KEY_NUMPAD3 = 129,
	KEY_NUMPAD4 = 130,
	KEY_NUMPAD5 = 131,
	KEY_NUMPAD6 = 132,
	KEY_NUMPAD7 = 133,
	KEY_NUMPAD8 = 134,
	KEY_NUMPAD9 = 135,
	KEY_NRMLDEL = 666,
} key_code;

/**
 * @brief Printing wrapper independent of C/C++
 * @param st String to print
 * @see colorPrint()
 * @see colorPrintBG()
 */
static void rutil_print(RUTIL_STRING st);


/**
 * @brief Reads a key press (blocking)
 * @details At the moment, only Arrows, ESC, Enter and Space are working
 * @return Key code that was read
 */
int getkey(void);

/**
 * @brief Non-blocking version of getch()
 * @return The character pressed or 0 if no key was pressed.
 * @see getch()
 */
int nb_getch(void);

/**
 * @brief Returns ANSI color escape sequence for specified number
 * @param c Number 0-15 corresponding to the color code
 * @see color_code
 */
RUTIL_STRING getANSIColor(color_code c);

/**
 * @brief Returns the ANSI background color escape sequence
 * @param c Number 0-15 corresponding to the color code
 * @see color_code
 */
RUTIL_STRING getANSIBgColor(color_code c);

/**
 * @brief Changes color as specified by a number
 * @param c Number 0-15 corresponding to a color code
 * @see color_code
 */
void setColor(color_code c);

/**
 * @brief Changes the background color as specified by a number
 * @param c Number 0-15 corresponding to a color code
 * @see color_code
 */
void setBackgroundColor(color_code c);

/**
 * @brief Saves the color to use in resetColor() on Windows
 * @detail Returns -1 if not on Windows or if RUTIL_USE_ANSI is defined
 */
int saveDefaultColor(void);


/**
 * @brief Resets the color to one set by saveDefaultColor()
 * @see color_code
 * @see setColor()
 * @see saveDefaultColor()
 */
void resetColor(void);

/**
 * @brief Clears screen, resets all attributes and moves cursor home.
 */
void cls(void);

/**
 * @brief Sets the cursor position to one defined by x and y.
 */
void locate(int x, int y);

/**
 * @brief Prints the supplied string without advancing the cursor
 */
// #ifdef __cplusplus
// void
// setString(const RUTIL_STRING & str_)
// {
// 	const char * const str = str_.data();
// 	unsigned int len = static_cast<unsigned int>(str_.size());
// #else /* __cplusplus */
void setString(RUTIL_STRING str);

/**
 * @brief Sets the character at the cursor without advancing the cursor
 */
void setChar(char ch);

/**
 * @brief Shows/hides the cursor.
 * @param visible 0 to hide the cursor, anything else to show the cursor
 */
void setCursorVisibility(char visible);

/**
 * @brief Hides the cursor
 * @see setCursorVisibility()
 */
void hidecursor(void);

/**
 * @brief Shows the cursor
 * @see setCursorVisibility()
 */
void showcursor(void);

/**
 * @brief Pauses the program for a given number of milliseconds
 */
void msleep(unsigned int ms);

/**
 * @brief Returns the number of rows in the terminal window or -1 on error.
 */
int trows(void);

/**
 * @brief Returns the number of columns in the terminal or -1 on error.
 */
int tcols(void);

/**
 * @brief Waits until a key is pressed.
 * @param msg The message to display or NULL. Optional in C++.
 */
// #ifdef __cplusplus
// void
// anykey()
// {
// 	getch();
// }

// template <class T> 
// void 
// anykey(const T& msg)
// {
// 	rutil_print(msg);
// #else
void anykey(RUTIL_STRING msg);

/**
 * @brief Sets the console title given a string.
 */
void setConsoleTitle(RUTIL_STRING title);

/**
 * @brief Prints a message in a given color.
 * @param fmt printf-style formatted string to print in C or a list of objects in C++
 * @param color Foreground color to be used, use -1 to use the currently set foreground color
 * @param bgcolor Background color to be used, use -1 to use the currently set background color
 * @see color_code
 */
// #ifdef __cplusplus
// void 
// colorPrint(color_code, color_code) {

// 	resetColor();
// }

// template <typename T, typename... F>
// void 
// colorPrint(color_code color, color_code bgcolor, T arg, F... fmt)
// {
// 	if (color >= 0)
// 		setColor(color);

// 	if (bgcolor >= 0)
// 		setBackgroundColor(bgcolor);

// 	std::cout << arg << " "; /* Let me know if I should remove the space */
// 	colorPrint(color, bgcolor, fmt...);
// }
// #else
void colorPrintUTF(color_code color, color_code bgcolor, const char *fmt, ...);

void colorPrint(color_code color, color_code bgcolor, const char *fmt, ...);
// #endif /* __cplusplus */

/**
 * @brief Returns the username of the user running the program.
 */
char* getUsername(void);

/**
 * @brief Print a message at a position given by x and y.
 * @see locate()
 * @see rutil_print()
 */
void printXY(int x, int y, RUTIL_STRING msg);

// #ifdef __cplusplus
// /**
//  * RAII OOP wrapper for <rogueutil.hidecursor>.
//  * Hides the cursor and shows it again
//  * when the object goes out of scope.
//  */
// struct CursorHider {
// 	CursorHider()
// 	{
// 		hidecursor();
// 	}
// 	~CursorHider()
// 	{
// 		showcursor();
// 	}
// };

// } /* namespace rogueutil */
// #endif
#endif /* RUTIL_H */
