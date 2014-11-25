#ifndef __LOGFUNCT_H    /*  An extra safeguard to prevent this header from  */
#define __LOGFUNCT_H    /*  being included twice in the same source file    */

/*--------------------------------------------------------------------------------*/
// LOG.DAT FUNCTIONS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// LOG.DAT Write - I/O Adds logname to Log File
int write(LOGNAME * log, int idx);


/*--------------------------------------------------------------------------------*/
// LOG.DAT Reads - I/O Read Any Log by Index Number
int read(LOGNAME * log, int idx);


/*--------------------------------------------------------------------------------*/
// Reads log.dat and gets Total number of Logs that have been loaded
int countlogs();

/*--------------------------------------------------------------------------------*/
// Lists ALL Users By Name from user.dat
void listlogs();


/*--------------------------------------------------------------------------------*/
// Find log record By Matching name
int findlog(char *tlog);


/*--------------------------------------------------------------------------------*/
// Function for Seeing if A Log has already been loaded before
bool matchlog(char* name);


/*--------------------------------------------------------------------------------*/
// Checks if log.dat file exists,  if not Creates it
bool dataexists();

#endif

