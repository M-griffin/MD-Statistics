#ifndef __PLAYERFUNCT_H    /*  An extra safeguard to prevent this header from  */
#define __PLAYERFUNCT_H    /*  being included twice in the same source file    */


// This file is the basic i/o for PLAYER.DAT and hold all Player and Player Weapon Information

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

//#include <iostream>             // C++ I/o   For Cin / Cout ...
//#include <stdio.h>              // C Standard I/o
//#include <string>               // C++ String Library
//#include <conio.h>              // Basic C Console I/o
//#include <stdlib.h>             // Program Exit() - Fix to Disconenct, Error Handling.. Later
//#include <windows.h>            // FindFirstFile - FindNextFile
//#include <fstream>              // C++ File I/o
//#include <direct.h>             // _getcwd  (Get Current Working Directory)

#include "structs.h"
#include "Mapfunc.h"
//#include "PlayerFunc.h"

using namespace std;            // Standard C++ Namespace


/*--------------------------------------------------------------------------------*/
// GLOBALS 
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Link list for Faster Player Purging 
//struct ListItem14 *List14 = 0;

/*--------------------------------------------------------------------------------*/
// LINKLIST Functions for Faster Player Purging
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearList14(void);

/*--------------------------------------------------------------------------------*/
// MAPNAME.IDX FUNCTIONS - Indexing of Player Data
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// MAPNAME.IDX Write - Indexes of Each Data file for Faster Searching
int writepidx(PLAYERRECIDX * player, int idx);

/*--------------------------------------------------------------------------------*/
// MAPNAME.DAT Reads - Indexes of Each Data file for Faster Searching
int readpidx(PLAYERRECIDX * player, int idx);

/*--------------------------------------------------------------------------------*/
// Reads player.dat and gets Total number of Players that have been loaded
int countpidx();

/*--------------------------------------------------------------------------------*/
// Find Player record By Matching name - Gets player Index
int findpidx(char * tplayer);

/*--------------------------------------------------------------------------------*/
// Function Check if Name already exists in Player.dat
bool matchpidx(char * name);

/*--------------------------------------------------------------------------------*/
// Checks if Player.dat file exists,  if not Creates it
bool pidxdataexists();

/*--------------------------------------------------------------------------------*/
// Adds Index
void addpidx(char * name, int idx);

/*--------------------------------------------------------------------------------*/
// MAPNAME.DAT FUNCTIONS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// MAPNAME.DAT Write - I/O Adds logname to Log File
int writep(PLAYERREC * player, int idx);

/*--------------------------------------------------------------------------------*/
// PLAYERNAME.DAT Reads - I/O Read Any Log by Index Number
int readp(PLAYERREC * player, int idx);

/*--------------------------------------------------------------------------------*/
// Select and Save User Data to Temp file
void save_player_temp(PLAYERREC * player);

/*--------------------------------------------------------------------------------*/
// Grabs information form Temp and Puts into Normal.. Then Deletes Temp File
void restore_player_data();

/*--------------------------------------------------------------------------------*/
// Purges Players with 0 Kills and 0 Damage Delt in all MAP Data Files
void delplayer();

/*--------------------------------------------------------------------------------*/
// Add New Playername to STRUCTURE AND player.dat
void addplayer(char * name);

/*--------------------------------------------------------------------------------*/
// Checks if Player.dat file exists,  if not Creates it
bool pdataexists();

/*--------------------------------------------------------------------------------*/
// PLAYERRANK.IDX FUNCTIONS - Indexing of Playerrank.dat
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// PLAYERRANK.IDX Write 
int writepridx(PLAYERREC2IDX * player, int idx);

/*--------------------------------------------------------------------------------*/
//  PLAYERRANK.IDX Reads - I/O Read Any Log by Index Number
int readpridx(PLAYERREC2IDX * player, int idx);

/*--------------------------------------------------------------------------------*/
// Reads player.dat and gets Total number of Players that have been loaded
int countpridx();

/*--------------------------------------------------------------------------------*/
// Find Player record By Matching name - Gets player Index
int findpridx(char * tplayer);

/*--------------------------------------------------------------------------------*/
// Function Check if Name already exists in Player.dat
bool matchpridx(char * name);

/*--------------------------------------------------------------------------------*/
// Checks if PlayerRank.idx file exists,  if not Creates it
bool pridxdataexists();

/*--------------------------------------------------------------------------------*/
// Adds Index
void addpridx(char * name, int idx);

/*--------------------------------------------------------------------------------*/
// PLAYERRANK.DAT FUNCTIONS Contains totals from all map files for overall stats
/*--------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------*/
// PLAYER.DAT Write - I/O Adds logname to Log File
int writeprank(PLAYERREC2 * player, int idx);

/*--------------------------------------------------------------------------------*/
// PLAYER.DAT Reads - I/O Read Any Log by Index Number
int readprank(PLAYERREC2 * player, int idx);

/*--------------------------------------------------------------------------------*/
// Checks if PlayerRank.dat file exists,  if not Creates it
bool prankdataexists();


#endif
