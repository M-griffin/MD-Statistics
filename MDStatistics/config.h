#ifndef __CONFIG_H    /*  An extra safeguard to prevent this header from  */
#define __CONFIG_H    /*  being included twice in the same source file    */

// Config.dat Functions

/*--------------------------------------------------------------------------------*/
// LOG.DAT Write - I/O Adds logname to Log File
int writecfg(CONFIG * cfg, int idx);

/*--------------------------------------------------------------------------------*/
// LOG.DAT Reads - I/O Read Any Log by Index Number
int readcfg(CONFIG * cfg, int idx);

/*--------------------------------------------------------------------------------*/
// Reads log.dat and gets Total number of Logs that have been loaded
int countcfg();

/*--------------------------------------------------------------------------------*/
// Find log record By Matching name
int findcfg(char *tcfg);

/*--------------------------------------------------------------------------------*/
// Function for Seeing if A Log has already been loaded before
bool matchcfg(char* name);

/*--------------------------------------------------------------------------------*/
// Checks if log.dat file exists,  if not Creates it
bool cfgdataexists();

// Config.cfg Functions

/*--------------------------------------------------------------------------------*/
// Checks if CONFIG.CFG file exists
bool configdataexists();

/*--------------------------------------------------------------------------------*/
// Creat Defauly Config File if None Exists
void createconfig();

/*--------------------------------------------------------------------------------*/
// Parses Config File Data
void checkcfg(string cfgdata);

/*--------------------------------------------------------------------------------*/
// Read Config File
void parseconfig();

#endif

