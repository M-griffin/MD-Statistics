#ifndef __HTML1_H    /*  An extra safeguard to prevent this header from  */
#define __HTML1_H    /*  being included twice in the same source file    */

// This file Processes both the Rank and Players HTML Files, Also Computing Statistics

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

//#include <iostream>             // C++ I/o   For Cin / Cout ...
//#include <stdio.h>              // C Standard I/o
//#include <string>               // C++ String Library
//#include <stdlib.h>             // Program Exit() - Fix to Disconenct, Error Handling.. Later

#include "structs.h"              // Player / Weapon / Linklist Structures
#include "LogFunc.h"
#include "PlayerFunc.h"           // Displaying Link list with Players
#include "WeaponFunc.h"
#include "FA26.h"

using namespace std;              // Standard C++ Namespace

/*--------------------------------------------------------------------------------*/
// GLOBALS - Link List's For Data Contianers
/*--------------------------------------------------------------------------------*/
/*
struct ListItem   *MyList   = 0 ; // Player Ranks Sorting for Index.HTML
struct ListItem2  *MyList2  = 0 ; // IndexStats Write Out
struct ListItem3  *MyList3  = 0 ; // PlayerStats Write Out
struct ListItem4  *MyList4  = 0 ; // Weapon Sorting Players.HTML
struct ListItem5  *MyList5  = 0 ; // PlayerTop.HTML
struct ListItem6  *MyList6  = 0 ; // PlayerRow1.HTML
struct ListItem7  *MyList7  = 0 ; // PlayerRow2.HTML

struct ListItem12 *myList12 = 0 ; // Holds Player Ranks .dat Data			PLAYERREC2
struct ListItem14 *myList14 = 0 ; // Holding All Player Data while Creating HTML Files	PLAYERREC
struct ListItem15 *myList15 = 0 ; // Holding all Weapon Data While Calculating Stats	WEAPONREC

/*--------------------------------------------------------------------------------*/
// LINK LISTS Data Sorting Functions & Memory Freeing Functions
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Initalize and Handle Output file streams
void init_index();

/*--------------------------------------------------------------------------------*/
// Close Output file streams
void init_index_clean();

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void RemoveList(void);

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void RemoveListWeapon(void);

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearplayerrank();

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void RemovePlayerHTML(void);

/*--------------------------------------------------------------------------------*/
// DATA SORTING FUNCTIONS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// This Function Holds All Player Data While Creating HTML Files
// Contains no Sorting of Player Records
void playerrankeddata(PLAYERREC2 * player, int num);

/*--------------------------------------------------------------------------------*/
// Link List for Sorting By a single Player's Weapon by Kills
// Sorts Players in Player.html
void weaponkillsort(int rank,
                    char * name,
                    long   kills,
                    long   deaths,   // Deaths by this Weapon
                    long   sui,      // Suicides with this weapon
                    double kdp,      // Weapon Kill Death Sui Percentage
                    char * kdr,      // Kill Death Ratio
                    double pkills,   // Weapons Total Kills
                    long   damdelt,  // Damage Delt
                    long   damrec,   // Damage Received
                    char * dratio);   // Damage Ratio

/*--------------------------------------------------------------------------------*/
// PARSE HTML FILE TEMPLATES AND OUTPUT STATISTICS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Reads Link List Then Writes Out HTML Files for Players Ranks
void buildHTML(string html);

/*--------------------------------------------------------------------------------*/
// Reads Link List Then Writes Out HTML Files for Players Stats
void buildHTML2(string html);

/*--------------------------------------------------------------------------------*/
// Display's Link List in Current Memory    - TESTING PURPOSE ONLY!!
void printHTML(void);

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearHTML(void);

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearHTML2(void);

/*--------------------------------------------------------------------------------*/
// Write out the HTML FILE from Link List - By Kills
void writeHTMLrank(int num);

/*--------------------------------------------------------------------------------*/
// Write out the HTML FILE from Link List
void writeHTMLplayer(int rank);

/*--------------------------------------------------------------------------------*/
// Processes HTML for Write out to the Link List
void checkHTMLrank(string htmlline, char *tplayer, int rank);

/*--------------------------------------------------------------------------------*/
// Parses HTML and Replaces $Variables with Values for Write out to the Link List
void checkHTMLplayer2(string htmlline,        // HTML Data String
                      char *tplayer,          // Current Player Name
                      int rank,               // Weapons Rank
                      WEAPONREC * tweapon,    // Handle to Top Weapon
                      WEAPONREC * weapon);

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerTop.HTML For Multiple Runs
void buildHTMLplayertop(string html);

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerRow1.HTML For Multiple Runs
void buildHTMLplayerrow1(string html);

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerRow2.HTML For Multiple Runs
void buildHTMLplayerrow2(string html);

/*--------------------------------------------------------------------------------*/
// Read Rank.html and setup for parsing. Into Link List
void loadHTMLplayer(void);

/*--------------------------------------------------------------------------------*/
// Read Rank.html and setup for parsing.  *NEW Read Link List Loaded Templates...
void readHTMLplayer(char * playername);

/*--------------------------------------------------------------------------------*/
// Does the Inital Top Rankings
void ranktop(int num);

/*--------------------------------------------------------------------------------*/
// Read Rank.html and setup for parsing.
void readHTMLrank();

/*--------------------------------------------------------------------------------*/
// Adds Footer to Index.html
void footerHTMLrank();

/*--------------------------------------------------------------------------------*/
// Gets Player from Playerrank.dat and Setups Link List
void getplayerrank(int num);

/*--------------------------------------------------------------------------------*/
// This Function will setups the players Rankings
void doplayersrankHTML();

/*--------------------------------------------------------------------------------*/
// This Function will setup the a Link List, sort for And create The HTML STAT Files for All Players
void doplayersHTML();

#endif
