/*
    For some reason this file has a red squiggle on the first line and doesn't work properly.  WTF??
*/

#include "rogueutil.h"

#ifndef _WIN32

/**
 * @brief Get a charater without waiting on a Return
 * @details Windows has this functionality in conio.h
 * @return The character
 */
int getch(void)
{
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}


/**
 * @brief Determines if a button was pressed.
 * @details Windows has this in conio.h
 * @return Number of characters read
 */
int kbhit(void)
{
	static struct termios oldt, newt;
	int cnt = 0;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag    &= ~(ICANON | ECHO);
	newt.c_iflag     = 0; /* input mode */
	newt.c_oflag     = 0; /* output mode */
	newt.c_cc[VMIN]  = 1; /* minimum time to wait */
	newt.c_cc[VTIME] = 1; /* minimum characters to wait for */
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ioctl(0, FIONREAD, &cnt); /* Read count */
	struct timeval tv;
	tv.tv_sec  = 0;
	tv.tv_usec = 100;
	select(STDIN_FILENO+1, NULL, NULL, NULL, &tv); /* A small time delay */
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return cnt; /* Return number of characters */
}

#endif /* _WIN32 */

#ifndef gotoxy
/**
 * @brief Sets the cursor to the specified x and y position.
 * @details Windows has this functionality in conio.h
 * @see locate()
 */
void
gotoxy(int x, int y)
{
// #ifdef __cplusplus
// 	rogueutil::
// #endif
                locate(x,y);
}
#endif /* gotoxy */

/**
 * @brief Printing wrapper independent of C/C++
 * @param st String to print
 * @see colorPrint()
 * @see colorPrintBG()
 */
static void
rutil_print(RUTIL_STRING st)
{
// #ifdef __cplusplus
//         std::cout << st;
// #else
        printf("%s", st);
		fflush(stdout);
// #endif
}

/**
 * @brief Reads a key press (blocking)
 * @details At the moment, only Arrows, ESC, Enter and Space are working
 * @return Key code that was read
 */
int getkey(void)
{
#ifndef _WIN32
	int cnt = kbhit(); /* for ANSI escapes processing */
#endif
	int k = getch();
	switch(k) {
	case 0: {
		int kk;
		switch (kk = getch()) {
		case 71:
			return KEY_NUMPAD7;
		case 72:
			return KEY_NUMPAD8;
		case 73:
			return KEY_NUMPAD9;
		case 75:
			return KEY_NUMPAD4;
		case 77:
			return KEY_NUMPAD6;
		case 79:
			return KEY_NUMPAD1;
		case 80:
			return KEY_NUMPAD2;
		case 81:
			return KEY_NUMPAD3;
		case 82:
			return KEY_NUMPAD0;
		case 83:
			return KEY_NUMDEL;
		default:
			return kk-59+KEY_F1; /* Function keys */
		}
	}
	case 224: {
		int kk;
		switch (kk = getch()) {
		case 71:
			return KEY_HOME;
		case 72:
			return KEY_UP;
		case 73:
			return KEY_PGUP;
		case 75:
			return KEY_LEFT;
		case 77:
			return KEY_RIGHT;
		case 79:
			return KEY_END;
		case 80:
			return KEY_DOWN;
		case 81:
			return KEY_PGDOWN;
		case 82:
			return KEY_INSERT;
		case 83:
			return KEY_DELETE;
		default:
			return kk-123+KEY_F1; /* Function keys */
		}
	}
	case 13:
		return KEY_ENTER;
#ifdef _WIN32
	case 27:
		return KEY_ESCAPE;
#else /* _WIN32 */
	case 155: /* single-character CSI */
	case '\33': {
		/* Process ANSI escape sequences */
		if (cnt >= 3 && getch() == '[') {
			switch (k = getch()) {
			case 'A':
				return KEY_UP;
			case 'B':
				return KEY_DOWN;
			case 'C':
				return KEY_RIGHT;
			case 'D':
				return KEY_LEFT;
			default:
				return KEY_ESCAPE;
			}
		} else return KEY_ESCAPE;
	}
#endif /* _WIN32 */
	default:
		return k;
	}
}

/**
 * @brief Non-blocking version of getch()
 * @return The character pressed or 0 if no key was pressed.
 * @see getch()
 */
int nb_getch(void)
{
	if (kbhit()) return getch();
	else return 0;
}

/**
 * @brief Returns ANSI color escape sequence for specified number
 * @param c Number 0-15 corresponding to the color code
 * @see color_code
 */
RUTIL_STRING getANSIColor(const int c)
{
	switch (c) {
	case BLACK       :
		return ANSI_BLACK;
	case BLUE        :
		return ANSI_BLUE; /* non-ANSI */
	case GREEN       :
		return ANSI_GREEN;
	case CYAN        :
		return ANSI_CYAN; /* non-ANSI */
	case RED         :
		return ANSI_RED; /* non-ANSI */
	case MAGENTA     :
		return ANSI_MAGENTA;
	case BROWN       :
		return ANSI_BROWN;
	case GREY        :
		return ANSI_GREY;
	case DARKGREY    :
		return ANSI_DARKGREY;
	case LIGHTBLUE   :
		return ANSI_LIGHTBLUE; /* non-ANSI */
	case LIGHTGREEN  :
		return ANSI_LIGHTGREEN;
	case LIGHTCYAN   :
		return ANSI_LIGHTCYAN; /* non-ANSI; */
	case LIGHTRED    :
		return ANSI_LIGHTRED; /* non-ANSI; */
	case LIGHTMAGENTA:
		return ANSI_LIGHTMAGENTA;
	case YELLOW      :
		return ANSI_YELLOW; /* non-ANSI */
	case WHITE       :
		return ANSI_WHITE;
	default:
		return "";
	}
}

/**
 * @brief Returns the ANSI background color escape sequence
 * @param c Number 0-15 corresponding to the color code
 * @see color_code
 */
RUTIL_STRING getANSIBgColor(const int c)
{
	switch (c) {
	case BLACK  :
		return ANSI_BACKGROUND_BLACK;
	case BLUE   :
		return ANSI_BACKGROUND_BLUE;
	case GREEN  :
		return ANSI_BACKGROUND_GREEN;
	case CYAN   :
		return ANSI_BACKGROUND_CYAN;
	case RED    :
		return ANSI_BACKGROUND_RED;
	case MAGENTA:
		return ANSI_BACKGROUND_MAGENTA;
	case BROWN  :
		return ANSI_BACKGROUND_YELLOW;
	case GREY   :
		return ANSI_BACKGROUND_WHITE;
	default:
		return "";
	}
}

/**
 * @brief Changes color as specified by a number
 * @param c Number 0-15 corresponding to a color code
 * @see color_code
 */
void
setColor(int c)
{
#if defined(_WIN32) && !defined(RUTIL_USE_ANSI)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFFF0) | (WORD)c); // Foreground colors take up the least significant byte
#else
	rutil_print(getANSIColor(c));
#endif
}

/**
 * @brief Changes the background color as specified by a number
 * @param c Number 0-15 corresponding to a color code
 * @see color_code
 */
void
setBackgroundColor(int c)
{
#if defined(_WIN32) && !defined(RUTIL_USE_ANSI)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFF0F) | (((WORD)c) << 4)); // Background colors take up the second-least significant byte
#else
	rutil_print(getANSIBgColor(c));
#endif
}

/**
 * @brief Saves the color to use in resetColor() on Windows
 * @detail Returns -1 if not on Windows or if RUTIL_USE_ANSI is defined
 */
int
saveDefaultColor(void)
{
#if defined(_WIN32) && !defined(RUTIL_USE_ANSI)
	static char initialized = 0; /* bool */
	static WORD attributes;

	if (!initialized) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		attributes = csbi.wAttributes;
		initialized = 1;
	}
	return (int)attributes;
#else
	return -1;
#endif
}

/**
 * @brief Resets the color to one set by saveDefaultColor()
 * @see color_code
 * @see setColor()
 * @see saveDefaultColor()
 */
void
resetColor(void)
{
#if defined(_WIN32) && !defined(RUTIL_USE_ANSI)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)saveDefaultColor());
#else
	rutil_print(ANSI_ATTRIBUTE_RESET);
#endif
}

/**
 * @brief Clears screen, resets all attributes and moves cursor home.
 */
void cls(void)
{
#if defined(_WIN32) && !defined(RUTIL_USE_ANSI)
	/* Based on https://msdn.microsoft.com/en-us/library/windows/desktop/ms682022%28v=vs.85%29.aspx */
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const COORD coordScreen = {0, 0};
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	const DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

	SetConsoleCursorPosition(hConsole, coordScreen);
#else
	rutil_print(ANSI_CLS);
	rutil_print(ANSI_CURSOR_HOME);
#endif
}

/**
 * @brief Sets the cursor position to one defined by x and y.
 */
void locate(int x, int y)
{
#if defined(_WIN32) && !defined(RUTIL_USE_ANSI)
	COORD coord;
	coord.X = (SHORT)(x - 1);
	coord.Y = (SHORT)(y - 1); /* Windows uses 0-based coordinates */
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else /* _WIN32 || USE_ANSI */
// #ifdef __cplusplus
//         std::stringstream ss;
//         ss << "\033[" << y << ";" << x << "H";
// 	rutil_print(ss.str());
// #else
	char buf[32];
	sprintf(buf, "\033[%d;%df", y, x);
	rutil_print(buf);
// #endif /* __cplusplus */
#endif /* _WIN32 || USE_ANSI */
}

void setString(RUTIL_STRING str)
{
	unsigned int len = (unsigned int)strlen(str);
// #endif /* __cplusplus */
#if defined(_WIN32) && !defined(RUTIL_USE_ANSI)
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD numberOfCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);

#ifdef UNICODE
	WriteConsoleOutputCharacterA(hConsoleOutput, str,
                                     len, csbi.dwCursorPosition,
                                     &numberOfCharsWritten);
#else
	WriteConsoleOutputCharacter(hConsoleOutput, str,
                                    len, csbi.dwCursorPosition,
                                    &numberOfCharsWritten);
#endif /* UNICODE */

#else /* _WIN32 || USE_ANSI */
	rutil_print(str);
// #ifdef __cplusplus
//         std::stringstream ss;
//         ss << "\033[" << len << 'D';
// 	rutil_print(ss.str());
// #else
	char buf[3 + 20 + 1]; /* 20 = max length of 64-bit
                                 * unsigned int when printed as dec */
	sprintf(buf, "\033[%uD", len);
	rutil_print(buf);
// #endif /* __cplusplus */
#endif /* _WIN32 || USE_ANSI */
}

/**
 * @brief Sets the character at the cursor without advancing the cursor
 */
void setChar(char ch)
{
	const char buf[] = {ch, 0};
	setString(buf);
}

/**
 * @brief Shows/hides the cursor.
 * @param visible 0 to hide the cursor, anything else to show the cursor
 */
void setCursorVisibility(char visible)
{
#if defined(_WIN32) && !defined(RUTIL_USE_ANSI)
	HANDLE hConsoleOutput = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo( hConsoleOutput, &structCursorInfo ); // Get current cursor size
	structCursorInfo.bVisible = (visible ? TRUE : FALSE);
	SetConsoleCursorInfo( hConsoleOutput, &structCursorInfo );
#else /* _WIN32 || USE_ANSI */
	rutil_print((visible ? ANSI_CURSOR_SHOW : ANSI_CURSOR_HIDE));
#endif /* _WIN32 || USE_ANSI */
}

/**
 * @brief Hides the cursor
 * @see setCursorVisibility()
 */
void hidecursor(void)
{
	setCursorVisibility(0);
}

/**
 * @brief Shows the cursor
 * @see setCursorVisibility()
 */
void showcursor(void)
{
	setCursorVisibility(1);
}

/**
 * @brief Pauses the program for a given number of milliseconds
 */
void msleep(unsigned int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	struct timespec ts;

	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000L;

	if(nanosleep(&ts, NULL) < 0) {
		perror("sleep failed");
	}
#endif /* _WIN32 */
}

/**
 * @brief Returns the number of rows in the terminal window or -1 on error.
 */
int trows(void)
{
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	else
		return csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // Window height
#else
#ifdef TIOCGSIZE
	struct ttysize ts;
	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
	return ts.ts_lines;
#elif defined(TIOCGWINSZ)
	struct winsize ts;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
	return ts.ws_row;
#else /* TIOCGSIZE */
	return -1;
#endif /* TIOCGSIZE */
#endif /* _WIN32 */
}

/**
 * @brief Returns the number of columns in the terminal or -1 on error.
 */
int tcols(void)
{
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	else
		return csbi.srWindow.Right - csbi.srWindow.Left + 1; // Window width
#else
#ifdef TIOCGSIZE
	struct ttysize ts;
	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
	return ts.ts_cols;
#elif defined(TIOCGWINSZ)
	struct winsize ts;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
	return ts.ws_col;
#else /* TIOCGSIZE */
	return -1;
#endif /* TIOCGSIZE */
#endif /* _WIN32 */
}

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
void anykey(RUTIL_STRING msg)
{
	if (msg)
		rutil_print(msg);
// #endif /* __cplusplus */
	getch();
}

/**
 * @brief Sets the console title given a string.
 */
void setConsoleTitle(RUTIL_STRING title)
{
	const char * true_title =
// #ifdef __cplusplus
// 	        title.c_str();
// #else /* __cplusplus */
	        title;
// #endif /* __cplusplus */
#if defined(_WIN32) && !defined(RUTIL_USE_ANSI)
	SetConsoleTitleA(true_title);
#else
	rutil_print(ANSI_CONSOLE_TITLE_PRE);
	rutil_print(true_title);
	rutil_print(ANSI_CONSOLE_TITLE_POST);
#endif /* defined(_WIN32) && !defined(RUTIL_USE_ANSI) */
}

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
void colorPrintUTF(color_code color, color_code bgcolor, const char *fmt, ...)
{
	// va_list args;
	// va_start(args, fmt);

	if (color >= 0)
        	setColor(color);

	if (bgcolor >= 0)
		setBackgroundColor(bgcolor);

    printf("%s", fmt);
	//va_end(args);

	resetColor();
}

void colorPrint(color_code color, color_code bgcolor, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	if (color >= 0)
        	setColor(color);

	if (bgcolor >= 0)
		setBackgroundColor(bgcolor);

        vprintf(fmt, args);
	va_end(args);

	resetColor();
}
// #endif /* __cplusplus */

/**
 * @brief Returns the username of the user running the program.
 */
char* getUsername(void)
{
#ifdef _WIN32
        /* TODO: Find a better way that doesn't use a static var. */
        static char ret[UNLEN + 1];
        DWORD len = UNLEN + 1;
        if (GetUserNameA(ret, &len))
                return ret;
        return NULL;
#else /* _WIN32 */	
	struct passwd *pw = getpwuid(getuid());
	if (pw) {
		return pw->pw_name;
	} else {
		return NULL;
	}
#endif
}

/**
 * @brief Print a message at a position given by x and y.
 * @see locate()
 * @see rutil_print()
 */
void printXY(int x, int y, RUTIL_STRING msg)
{
        locate(x, y);
        rutil_print(msg);
}

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
