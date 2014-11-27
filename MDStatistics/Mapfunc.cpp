#ifndef __MAPFUNCT_CPP    /*  An extra safeguard to prevent this header from  */
#define __MAPFUNCT_CPP    /*  being included twice in the same source file    */


// This file is the basic i/o for map.DAT and hold all map File Names

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

#include "structs.h"
#include "Mapfunc.h"

using namespace std;

/*--------------------------------------------------------------------------------*/
// map.DAT FUNCTIONS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// map.DAT Write - I/O Adds MAPNAMEREC to map File
int writem(MAPNAMEREC * map, int idx) {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\map.dat";
       #else
    path += "Data/map.dat";
       #endif

    FILE *stream;
    int x=0;

    stream=fopen(path.c_str(),"rb+");         // file test
    if(stream == NULL) {
        stream=fopen(path.c_str(), "wb"); // open file Writing
        if(stream == NULL) {
            fprintf(stderr, "Error Creating User.dat!\n");
            return x;
        }
    }
    if(fseek(stream,(long)idx*sizeof(MAPNAMEREC),SEEK_SET)==0)
         x = fwrite(map,sizeof(MAPNAMEREC),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// map.DAT Reads - I/O Read Any map by Index Number
int readm(MAPNAMEREC * map, int idx) {

    int x;

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\map.dat";
       #else
    path += "Data/map.dat";
       #endif

    FILE * stream = fopen(path.c_str(), "rb");
    if(fseek(stream,(long)idx*sizeof(MAPNAMEREC),SEEK_SET)==0)
            x = fread(map,sizeof(MAPNAMEREC),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// Reads map.dat and gets Total number of maps that have been loaded
int countmaps() {

    int i=0;
    MAPNAMEREC map;

    while(readm(&map,i++));
    if(i < 1)    i =- 1;
    else        i--;
    return(i);
}

/*--------------------------------------------------------------------------------*/
// Lists ALL Users By Name from user.dat
void listmaps() {

    char maprec[30];
    MAPNAMEREC map;
    int idx;
    idx=0;
    printf("\nListing all maps Processed!\n");
    while(readm(&map,idx)){                       // Loop Tests Each record in map.dat
        printf("#%i\t map: %s\n",idx+1,map.name); // List All users in File [TESTING]
        idx++;                                    // Goto Next Record in map.dat
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Find map record By Matching name
int findmap(char *tmap) {

    int idx = 0;
    string temp1,temp2;
    MAPNAMEREC map;

    temp1 = (tmap);

    while(readm(&map,idx)) {
        temp2 = (map.name);
        if(temp1 == temp2) return(idx);
        idx++;
    }
    return(-1);
}

/*--------------------------------------------------------------------------------*/
// Function for Seeing if A map has already been loaded before
bool matchmap(char* name) {

    int index=-1;                            // Name Not Found
    index = findmap(name);
    if (index == -1) return false;
    return true;
}

/*--------------------------------------------------------------------------------*/
// Checks if map.dat file exists,  if not Creates it
bool mdataexists() {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\map.dat";
       #else
    path += "Data/map.dat";
       #endif

    FILE * stream;

    stream=fopen(path.c_str(),"rb+");
    if(stream == NULL) {
        stream=fopen(path.c_str(), "wb");   //open file Writing
        if(stream == NULL) {
            fprintf(stderr, "Error Creating map.dat!\n");
            return false;
        }
    }
    fclose(stream);
    return true;
}

#endif
