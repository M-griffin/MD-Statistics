#ifndef __WINCON_H    /*  An extra safeguard to prevent this header from  */
#define __WINCON_H    /*  being included twice in the same source file    */


//#include <conio.h>

using namespace std;


//#define BLINK 0

/*
#ifndef COLORS
#define COLORS
typedef enum
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
} COLORS;
#endif
*/

/*--------------------------------------------------------------------------------*/
// Function for Printing out to the screen
void setcolor (int fg, int bg);

void clrscr();
void gotoxy(int, int);
void delline();
void clreol ();
void setrgb(int);
int wherex();
int wherey();
void bgcolor (int color);
void color (int color);
void textattr (int _attr);



/*--------------------------------------------------------------------------------*/
// GUI Screen Drawing Function for Windows
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Main Title Portion for text in GUI
void drawtop(char * text, int fc, int bc, int x);

/*--------------------------------------------------------------------------------*/
// Bottom Left Box for text in GUI
void drawleft(char * text, int fc, int bc);

/*--------------------------------------------------------------------------------*/
// Bottom Left Box for text in GUI
void drawleft2(char * text, int fc, int bc);

/*--------------------------------------------------------------------------------*/
// Main Title Portion for text in GUI
void cleartop();

/*--------------------------------------------------------------------------------*/
// Clears Bottom Left Box for text in GUI
void clearleft();

/*--------------------------------------------------------------------------------*/
// Clears Bottom Left Box for text in GUI
void clearleft2();

/*--------------------------------------------------------------------------------*/
// Bottom Left Box for text in GUI
void drawright(char * text, int fc, int bc);

/*--------------------------------------------------------------------------------*/
// Bottom Left Box for text in GUI
void drawright2(char * text, int fc, int bc);

/*--------------------------------------------------------------------------------*/
// Clears Bottom Left Box for text in GUI
void clearright();

/*--------------------------------------------------------------------------------*/
// Clears Bottom Left Box for text in GUI
void clearright2();

/*--------------------------------------------------------------------------------*/
// Top Percentage Bar
void percenttop(long double percentage);

/*--------------------------------------------------------------------------------*/
// Left Percentage Bar
void percentleft(long double percentage);

/*--------------------------------------------------------------------------------*/
// Right Percentage Bar
void percentright(long double percentage);

/*--------------------------------------------------------------------------------*/
// Clear Top Percentage Bar
void clearpercenttop();

/*--------------------------------------------------------------------------------*/
// Clear Left Percentage Bar
void clearpercentleft();

/*--------------------------------------------------------------------------------*/
// Clear Right Percentage Bar
void clearpercentright();

/*--------------------------------------------------------------------------------*/
// Clear All GUI for Full Refresh
void clearall();

/*--------------------------------------------------------------------------------*/
// Clear All GUI for Full Refresh
void clearallleft();

/*--------------------------------------------------------------------------------*/
// Clear All GUI for Full Refresh
void clearallright();




#endif
