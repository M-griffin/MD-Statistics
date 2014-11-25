#ifndef __HTML2_H    /*  An extra safeguard to prevent this header from  */
#define __HTML2_H    /*  being included twice in the same source file    */

// This file Processes Indivual Weapon Statistics HTML Files

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
//#include "html1.h"
#include "Html2.h"


using namespace std;            // Standard C++ Namespace      

/*--------------------------------------------------------------------------------*/
// LINK LISTS Data Sorting Functions
/*--------------------------------------------------------------------------------*/    


/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearweaponcontainer(void);

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearplayercont(void);

/*--------------------------------------------------------------------------------*/
// This Function Holds All Player Data While Creating HTML Files
void weapondatacontainer(WEAPONREC * weapon);

/*--------------------------------------------------------------------------------*/
// This Function Holds All Player Data While Creating HTML Files
void playerdatacont(PLAYERREC2 * player);

/*--------------------------------------------------------------------------------*/
// Link List for Sorting By a single Player's Weapon by Kills
// Sorts Players in Index.HTML
void wkillsort(int rank,
               char * name,
               long kills,
               long damdelt);

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearwkillsort(void);

/*--------------------------------------------------------------------------------*/
// Runs Though Weapon.dat and Sorts Ky Kills Into Link List, Then Sets Rank for Each
void calcwrank();

/*--------------------------------------------------------------------------------*/
// Take Current Player and Weapon Information, Puts into Link List and Ranks Ky Kills
void wprank1(int  rank,     // Weapon Rank
             char * name,   // Weapon Name
             long kills,    // Weapon Kills
             long damdelt); // Weapon Damage

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearwprank1();                   // Clears Playersort Link List

/*--------------------------------------------------------------------------------*/
// Calculates Top Players Per Each Weapon - Send Players to LL to be Sorted by Kills
void topweaponplayers(PLAYERREC2 * player,   // Handle to Player
                      char       * name);    // Weapon Name

/*--------------------------------------------------------------------------------*/
// PARSE HTML FILE TEMPLATES AND OUTPUT STATISTICS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void RemoveWeaponHTML(void);                // Clears 3 Link Lists For Fast HTML Processing

/*--------------------------------------------------------------------------------*/
// Write out the HTML FILE from Link List
void writeHTMLweapon(char * tweapon);

/*--------------------------------------------------------------------------------*/
// Write out the HTML FILE from Link List
void writeHTMLweaponrank();

/*--------------------------------------------------------------------------------*/
// Reads Link List Then Writes Out HTML Files for Players Stats
void buildHTMLweapon(string html);

/*--------------------------------------------------------------------------------*/
// Parses HTML for Write out to the Link List - Weapons
void checkHTMLWeapon(string htmlline, char * tweapon);

/*--------------------------------------------------------------------------------*/
// Parses HTML for Write out to the Link List - Top Players
void checkHTMLWeaponp(string htmlline,  // HTML String to Parse
                      int    rank,      // Players Ranks
                      char * name,      // Players Name
                      long   kills,     // Weapon Kills
                      long   damdelt,   // Weapon Damage
                      int    count);    // Player Counter

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing
void buildHTMLweapontop(string html);

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing
void buildHTMLweaponptop(string html);

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing
void buildHTMLweaponrow1(string html);

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing
void buildHTMLweaponprow1(string html);

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing
void buildHTMLweaponrow2(string html);

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing 
void buildHTMLweaponprow2(string html);

/*--------------------------------------------------------------------------------*/
// Read Rank.html and setup for parsing. Into Link List
void loadHTMLweapon(void);

/*--------------------------------------------------------------------------------*/
// Read Rank.html and setup for parsing.  *NEW Read Link List Loaded Templates...
void readHTMLweapon(char * weaponname);


/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearHTMLweapon(void);

/*--------------------------------------------------------------------------------*/
// Read WeaponRankTOP.html and setup for parsing. Into Link List
void loadHTMLweaponrank(void);

/*--------------------------------------------------------------------------------*/
// Processes HTML for Write out to the Link List - Weapons
void checkHTMLweaponrank(string htmlline, char *tweapon);

/*--------------------------------------------------------------------------------*/
// Setup And Process Weapon Rankings
void readHTMLweaponrank();

/*--------------------------------------------------------------------------------*/
// Adds All Weapons to Link List for Stat Calculations
void setupplayerdc();

/*--------------------------------------------------------------------------------*/
// Calculate each weapons Percentage of Total Overall Kills
void doweaponpkills();

/*--------------------------------------------------------------------------------*/
// Gets Information for Weapon.dat And adds all Weapon Data to Link List
void addweapondc(char * weaponname);

/*--------------------------------------------------------------------------------*/
// This Function will setup the a Link List, sort for And create The HTML STAT Files for All Players
void doweaponHTML();

/*--------------------------------------------------------------------------------*/
// This Function will setup the a Link List, sort for And create The HTML STAT Files       
void doweaponrankHTML();


#endif
