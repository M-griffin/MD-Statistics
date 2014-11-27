#ifndef __LOGFUNCT_CPP    /*  An extra safeguard to prevent this header from  */
#define __LOGFUNCT_CPP    /*  being included twice in the same source file    */


// This file is the basic i/o for LOG.DAT and hold all Log File Names

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

#include "structs.h"
#include "LogFunc.h"

using namespace std;

 /*--------------------------------------------------------------------------------*/
// LOG.DAT FUNCTIONS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// LOG.DAT Write - I/O Adds logname to Log File
int write(LOGNAME * log, int idx) {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\log.dat";
       #else
    path += "Data/log.dat";
       #endif

    FILE *stream;
    int x=0;

    stream=fopen(path.c_str(),"rb+");         // file test
    if(stream == NULL) {
        stream=fopen(path.c_str(), "wb"); // open file Writing
        if(stream == NULL) {
            fprintf(stderr, "Error Creating Log.dat!\n");
            return x;
        }
    }
    if(fseek(stream,(int)idx*sizeof(LOGNAME),SEEK_SET)==0)
         x = fwrite(log,sizeof(LOGNAME),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// LOG.DAT Reads - I/O Read Any Log by Index Number
int read(LOGNAME * log, int idx) {

    int x;

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\log.dat";
       #else
    path += "Data/log.dat";
       #endif

    FILE * stream = fopen(path.c_str(), "rb");
    if(fseek(stream,(int)idx*sizeof(LOGNAME),SEEK_SET)==0)
        x = fread(log,sizeof(LOGNAME),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// Reads log.dat and gets Total number of Logs that have been loaded
int countlogs() {

    int i = 0;
    LOGNAME log;

    while(read(&log,i++));
    if(i<1)    i=-1;
    else    i--;
    return(i);
}

/*--------------------------------------------------------------------------------*/
// Lists ALL Users By Name from user.dat
void listlogs() {

    LOGNAME log;
    int idx;
    idx = 0;
    printf("\nListing all Logs Processed!\n");
    while(read(&log,idx)){
        cout << "#" << idx+1 << "\t Log: " << log.name << endl;
        idx++;
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Find log record By Matching name
int findlog(char *tlog) {

    int idx=0;                               // Start Searching at Record 0
    string temp1,temp2;
    LOGNAME log;                             // Handle to Log Structure

    temp1 = (tlog);

    while(read(&log,idx)) {             // Loop Tests Each record in log.dat
        temp2 = (log.name);                  // Get Current Name from Record
        if(temp1 == temp2) {         // Compare Current Record Name with Input Name
            return(idx);         // Return Index of Matched Name if Found
        }
        idx++;                           // Goto Next Record in Log.dat
    }
    return(-1);                              // Return Record Not Found
}

/*--------------------------------------------------------------------------------*/
// Function for Seeing if A Log has already been loaded before
bool matchlog(char* name) {

    int index = -1;                 // Name Not Found
    while(index == -1) {            // if not match stay in loop
    index = findlog(name);    // if match get record index
        if (index == -1)
        return false;           // No Match Found
    }
    return true;                    // Found a Match
}

/*--------------------------------------------------------------------------------*/
// Checks if log.dat file exists,  if not Creates it
bool dataexists() {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\log.dat";
       #else
    path += "Data/log.dat";
       #endif

    FILE * stream;

    stream=fopen(path.c_str(),"rb+");
    if(stream == NULL) {
        stream=fopen(path.c_str(), "wb");   //open file Writing
        if(stream == NULL) {
            fprintf(stderr, "Error Creating log.dat!\n");
            return false;
        }
    }
    fclose(stream);
    return true;
}

#endif
