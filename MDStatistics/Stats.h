#ifndef __STATS_H    /*  An extra safeguard to prevent this header from  */
#define __STATS_H    /*  being included twice in the same source file    */

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
#include "Mapfunc.h"
#include "WeaponFunc.h"
#include "FA26.h"

using namespace std;              // Standard C++ Namespace

/*--------------------------------------------------------------------------------*/
// GLOBALS - Link List's For Data Contianers
/*--------------------------------------------------------------------------------*/
/*
struct ListItem12 *MyList12 = 0 ; // Holds Player Ranks .dat Data            PLAYERREC
struct ListItem14 *MyList14 = 0 ; // Holding All Player Data while Creating HTML Files    PLAYERREC
struct ListItem15 *MyList15 = 0 ; // Holding all Weapon Data While Calculating Stats    WEAPONREC

/*--------------------------------------------------------------------------------*/
// LINK LISTS Data Sorting Functions & Memory Freeing Functions
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearplayercontainer();

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearprank2();

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearweaponcont();

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearplayerrank();

/*--------------------------------------------------------------------------------*/
// This Function Holds All Player Data While Creating HTML Files
// Contains no Sorting of Player Records
void playerdatacontainer(PLAYERREC * player);

/*--------------------------------------------------------------------------------*/
// This Function Holds All Weapon Data While Creating HTML Files
// Contains no Data Sorting
void weapondatacont(WEAPONREC * weapon);

/*--------------------------------------------------------------------------------*/
// Sorting Functions for Rankings & Calculating Statistics
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// This Function Updates Players Statsics in the Link List
void addplayermapstats(PLAYERREC * player);

/*--------------------------------------------------------------------------------*/
// This Function Add New Players to the Link List #13 for Log Parsing
bool newmapdata(string name);

/*--------------------------------------------------------------------------------*/
// This Function Copy's All Player Data From Link List to Player.dat
void copyrankdata();

/*--------------------------------------------------------------------------------*/
// Link List for Sorting By Player's Kills
// Sorts Players in Index.HTML
void killsort(PLAYERREC * player);

/*--------------------------------------------------------------------------------*/
// Link List For Sorting PlayerRank.dat Players by Kills
// Sorts Players in Index.HTML
void rankkillsort(PLAYERREC2 * player);

/*--------------------------------------------------------------------------------*/
// Link List For Sorting PlayerRank.dat Players by Kills
// Sorts Players in Index.HTML
void rankkillsort2(PLAYERREC2 * player);

/*--------------------------------------------------------------------------------*/
/*// Container For holding Playerrank.dat Player's
void playerlist3();


/*--------------------------------------------------------------------------------*/
// Statistics Calculations
/*--------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------*/
// Computes Weapons KILL DEATH+SUICIDE RADIO
long GreatestCommonDivisor(long alpha, // Kills
                           long beta); // Deaths

/*--------------------------------------------------------------------------------*/
// definition of Simplify() Converts fractions to it simpliest form
string simplify(long myNumerator,   // Player / Weapon Kills
                long myDenominator);// Player / Weapon Deaths

/*--------------------------------------------------------------------------------*/
// Computes Weapons KILL DEATH SUICIDE PERCENTAGE
double compstatspercent(long double wk,  // Weapon Kills     // Player Kills
                        long double wd,  // Weapon Deaths    // Player Deaths
                        long double ws); // Weapon sui  // Player sui

/*--------------------------------------------------------------------------------*/
// Computes Weapons KILL Out of Total players Kills Percentage
double compwkillpercent(long double wk,  // Weapon Kills
                        long double pk); // Player Kills

/*--------------------------------------------------------------------------------*/
// Computes Players & Weapons KILL DEATH SUICIDE PERCENTAGE And Assigns to Players Rec
// With Kill : Death Ratio / And New Attack Damage Statistics
void calcRankPlayerStats();

/*--------------------------------------------------------------------------------*/
// Computes Players & Weapons KILL DEATH SUICIDE PERCENTAGE And Assigns to Players Rec
// With Kill : Death Ratio / And New Attack Damage Statistics
void calcPlayerStats();

/*--------------------------------------------------------------------------------*/
/*// Reveices Player Weapons and Sorts by kills for Players.HTML
void calcweapons(PLAYERREC * player);

/*--------------------------------------------------------------------------------*/
// Copys from Link List to Weapon.dat
void writeweapondc();

/*--------------------------------------------------------------------------------*/
// Adds All Weapons to Link List for Stat Calculations
void setupweapondc();

/*--------------------------------------------------------------------------------*/
// Gets Players from Map.dats and Loads them into Memory for Fast Statistics Calcs
void getplayerlist();

/*--------------------------------------------------------------------------------*/
// Gets Players from Map.dats and Loads them into Memory for Fast Statistics Calcs
void getplayerlist2();

/*--------------------------------------------------------------------------------*/
// Gets Player from Playerrank.dat and Setups Link List
void getplayerlist3();

/*--------------------------------------------------------------------------------*/
// Gets Player from Playerrank.dat and Setups Link List
void getweaponlist3();

/*--------------------------------------------------------------------------------*/
// This Function will setups Player Statistics Calculations
void dostatcacl();


#endif
