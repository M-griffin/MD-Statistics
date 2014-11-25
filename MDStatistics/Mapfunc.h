#ifndef __MAPFUNCT_H    /*  An extra safeguard to prevent this header from  */
#define __MAPFUNCT_H    /*  being included twice in the same source file    */

/*--------------------------------------------------------------------------------*/
// map.DAT FUNCTIONS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// map.DAT Write - I/O Adds MAPNAMEREC to map File
int writem(MAPNAMEREC * map, int idx);


/*--------------------------------------------------------------------------------*/
// map.DAT Reads - I/O Read Any map by Index Number
int readm(MAPNAMEREC * map, int idx);


/*--------------------------------------------------------------------------------*/
// Reads map.dat and gets Total number of maps that have been loaded
int countmaps();

/*--------------------------------------------------------------------------------*/
// Lists ALL Users By Name from user.dat
void listmaps();


/*--------------------------------------------------------------------------------*/
// Find map record By Matching name
int findmap(char *tmap);


/*--------------------------------------------------------------------------------*/
// Function for Seeing if A map has already been loaded before
bool matchmap(char* name);


/*--------------------------------------------------------------------------------*/
// Checks if map.dat file exists,  if not Creates it
bool mdataexists();

#endif

