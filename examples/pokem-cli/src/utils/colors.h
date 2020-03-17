#ifndef COLORS_H
#define COLORS_H
/* Using the CSI (Control Sequence Initiator): "\x1B[", to manipulate video graphics using standarized ANSI escape sequences */

/*
    Copyright (C) 2017  Carlos Enrique Pérez Sánchez

    Usage: With this header you can get multiple colors on console output, even in the same line.
    See examples of usage bellow.

    This generic and platform-independent C header works on terminals with ANSI escape characters
    enabled, like UNIX-based terminal (MacOS terminal and terminals of most Linux distributions).
    The Microsoft Win32 console command prompt (cmd.exe) not support it fully.
    However, if you call C standard system(char *command) function, you will get ANSI escape sequences
    support on Windows. The best way to do this is calling system(char *command) passing an empty
    C-style string like this: system("");

                                                                                    The author
                                                                                    
    PD: The info used here has been extracted from Wikipedia (EN) and others web sites.
*/

/* ********************************************* EXAMPLES OF USAGE *********************************************

C:
    fprintf(stdout, LRED "Differents " LYELLOW DRED_BG UNDERLINE "colors" RESET WHITE ".\n");

C++:
    std::cout << LRED "Differents " LYELLOW DRED_BG UNDERLINE "colors" RESET WHITE "." << std::endl;

************************************************************************************************************* */

/*
    Copyright (C) 2017  Carlos Enrique Pérez Sánchez

    This program is under the terms of the GNU Lesser
    General Public License version 3 as published by the Free Software
    Foundation. Please review the following information to
    ensure the GNU Lesser General Public License version 3 requirements
    will be met: https://www.gnu.org/licenses/lgpl-3.0.html.

    DISCLAIMER:
    This file is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    CONTACT:
        carlosps@gmail.com
*/

/** SGR (Select Graphic Rendition) parameters */
/* SGR syntax is: \x1B[#;...m */

#ifndef NO_USE_COLORS

    #define RESET   "\x1B[0m"   /* all attributes off */

    /* *** TEXT COLOR (TX) *** */
    /* dark colors (RGB palette defined by the implementation) */
    #define DRED        "\x1B[31m"
    #define DGREEN      "\x1B[32m"
    #define DYELLOW     "\x1B[33m"
    #define DBLUE       "\x1B[34m"
    #define DMAGENTA    "\x1B[35m"
    #define DCYAN       "\x1B[36m"
    #define DGRAY       "\x1B[30;1m"

    /* light colors (RGB palette defined by the implementation) */
    #define LRED        "\x1B[31;1m"
    #define LGREEN      "\x1B[32;1m"
    #define LYELLOW     "\x1B[33;1m"
    #define LBLUE       "\x1B[34;1m"
    #define LMAGENTA    "\x1B[35;1m"
    #define LCYAN       "\x1B[36;1m"
    #define LGRAY       "\x1B[37m"

    /* black and white */
    #define WHITE       "\x1B[37;1m"
    #define BLACK       "\x1B[30m"

    /* light */
    #define LIGHT       "\x1B[;1m"  


    /* *** BACKGROUNG COLOR (BG) *** */
    /* dark colors (RGB palette defined by the implementation) */
    #define DRED_BG     "\x1B[41m"
    #define DGREEN_BG   "\x1B[42m"
    #define DYELLOW_BG  "\x1B[43m"
    #define DBLUE_BG    "\x1B[44m"
    #define DMAGENTA_BG "\x1B[45m"
    #define DCYAN_BG    "\x1B[46m"
    #define DGRAY_BG    "\x1B[100m"

    /* light colors (RGB palette defined by the implementation) */
    #define LRED_BG     "\x1B[101m"
    #define LGREEN_BG   "\x1B[102m"
    #define LYELLOW_BG  "\x1B[103m"
    #define LBLUE_BG    "\x1B[104m"
    #define LMAGENTA_BG "\x1B[105m"
    #define LCYAN_BG    "\x1B[106m"
    #define LGRAY_BG    "\x1B[47m"

    /* black and white */
    #define WHITE_BG    "\x1B[107m"
    #define BLACK_BG    "\x1B[40m"


    /* *** CUSTOM COLORS *** */
    /* 256 colors */
        #define COLOR256(N)     "\x1B[38;5;" #N "m"
        #define COLOR256_BG(N)  "\x1B[48;5;" #N "m"
    /* RGB palette (0 <= R,G,B <= 255 (0xFF) ) */
        #define COLOR(R,G,B)    "\x1B[38;2;" #R ";" #G ";" #B "m"
        #define COLOR_BG(R,G,B) "\x1B[48;2;" #R ";" #G ";" #B "m"


    /* *** ADVANCED HANDLING *** */
    #define UNDERLINE   "\x1B[4m"   /* underline using the current foreground color */
    #define INVERSE     "\x1B[7m"   /* swap foreground and background */
    #define INVERSE_OFF "\x1B[27m"  /* restore the inverted foreground and background */

#else

#define RESET   ""

    /* *** TEXT COLOR (TX) *** */
    /* dark colors (RGB palette defined by the implementation) */
    #define DRED        ""
    #define DGREEN      ""
    #define DYELLOW     ""
    #define DBLUE       ""
    #define DMAGENTA    ""
    #define DCYAN       ""
    #define DGRAY       ""

    /* light colors (RGB palette defined by the implementation) */
    #define LRED        ""
    #define LGREEN      ""
    #define LYELLOW     ""
    #define LBLUE       ""
    #define LMAGENTA    ""
    #define LCYAN       ""
    #define LGRAY       ""

    /* black and white */
    #define WHITE       ""
    #define BLACK       ""

    /* light */
    #define LIGHT       ""


    /* *** BACKGROUNG COLOR (BG) *** */
    /* dark colors (RGB palette defined by the implementation) */
    #define DRED_BG     ""
    #define DGREEN_BG   ""
    #define DYELLOW_BG  ""
    #define DBLUE_BG    ""
    #define DMAGENTA_BG ""
    #define DCYAN_BG    ""
    #define DGRAY_BG    ""

    /* light colors (RGB palette defined by the implementation) */
    #define LRED_BG     ""
    #define LGREEN_BG   ""
    #define LYELLOW_BG  ""
    #define LBLUE_BG    ""
    #define LMAGENTA_BG ""
    #define LCYAN_BG    ""
    #define LGRAY_BG    ""

    /* black and white */
    #define WHITE_BG    ""
    #define BLACK_BG    ""


    /* *** CUSTOM COLORS *** */
    /* 256 colors */
        #define COLOR256(N)     ""
        #define COLOR256_BG(N)  ""
    /* RGB palette (0 <= R,G,B <= 255 (0xFF) ) */
        #define COLOR(R,G,B)    ""
        #define COLOR_BG(R,G,B) ""


    /* *** ADVANCED HANDLING *** */
    #define UNDERLINE   ""
    #define INVERSE     ""
    #define INVERSE_OFF ""

#endif
#endif /* COLORS_H */