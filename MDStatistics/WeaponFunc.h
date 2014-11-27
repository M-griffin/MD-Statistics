#ifndef __WEAPONFUNCT_H    /*  An extra safeguard to prevent this header from  */
#define __WEAPONFUNCT_H    /*  being included twice in the same source file    */


// This file is the basic i/o for WEAPON.DAT and holds all Weapon Statistics

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

#include "structs.h"
#include "WeaponFunc.h"

using namespace std;            // Standard C++ Namespace

/*--------------------------------------------------------------------------------*/
// WEAPON.DAT FUNCTIONS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// WEAPON.DAT Write - I/O Adds logname to Log File
int writew ( WEAPONREC * weapon, int idx );

/*--------------------------------------------------------------------------------*/
// WEAPON.DAT Reads - I/O Read Any Log by Index Number
int readw ( WEAPONREC * weapon, int idx );

/*--------------------------------------------------------------------------------*/
// Reads weapon.dat and gets Total number of Weapons that have been loaded
int countweapons();

/*--------------------------------------------------------------------------------*/
/*// Lists ALL Weapons's By Name from Weapon.dat
void listweapons();

/*--------------------------------------------------------------------------------*/
// Find Weapon record By Matching name - Gets Weapons Index
int findweapon ( char * tweapon );

/*--------------------------------------------------------------------------------*/
// Function Check if Name already exists in Weapon.dat
bool matchweapon ( char * name );

/*--------------------------------------------------------------------------------*/
// Checks if Weapon.dat file exists,  if not Creates it
bool wdataexists();

/*--------------------------------------------------------------------------------*/
// Add New Weaponname to STRUCTURE AND Weapon.dat
void addweapon ( char * name );

/*--------------------------------------------------------------------------------*/
// Create Starting Weapon Structures
void createweapons();

#endif
