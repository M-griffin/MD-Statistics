#ifndef __FA26_H    /*  An extra safeguard to prevent this header from  */
#define __FA26_H    /*  being included twice in the same source file    */

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearplayerdata();                   // Clears Playersort Link List

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearlogdata(void);

/*--------------------------------------------------------------------------------*/
// Link List for Sorting Log Files by Name to Parse in Creation Order
void lognamesort(LOGNAME * log);

/*--------------------------------------------------------------------------------*/
// This Function Add New Players to the Link List #13 for Log Parsing
bool newplayerdata(string name);

/*--------------------------------------------------------------------------------*/
// Computes Weapons KILL Out of Total players Kills Percentage
double compwkillpercent1(long double wk,  // Weapon Kills
                         long double pk); // Player Kills

/*--------------------------------------------------------------------------------*/
// This Function Copy's All Player Data From Link List to Player.dat
void copyplayerdata();

/*--------------------------------------------------------------------------------*/
// STRING PARSING FUNCTIONS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Parses for Player Damage Received
void playerdamrec(string logline);

/*--------------------------------------------------------------------------------*/
// Parses for Player Damage Delt
void playerdamdelt(string logline);

/*--------------------------------------------------------------------------------*/
// Parses for Player Died
void playerdied(string logline);

/*--------------------------------------------------------------------------------*/
// Parses for New Map Started
void playerkill(string logline);

/*--------------------------------------------------------------------------------*/
// Parses for New Map Started
void mapstarted(string logline);

/*--------------------------------------------------------------------------------*/
// Parses for Team Joined
void joinedteam(string logline);

/*--------------------------------------------------------------------------------*/
// Parse & Process Log String and Sort in Data Structures For Statics Genepercentagen Later...
// For Half-Life FireArms v2.5
void proc1str(string logline);

/*--------------------------------------------------------------------------------*/
// Checks String from Log And Breaks up Multiple Log Lines Found in 1 String
// Half-Life = Firearms v2.5 [Checks for Begining of Log Stamp]
void checkstr(string logdata);

/*--------------------------------------------------------------------------------*/
// Read Log File And Send Strings for Testing and Spliting Before Parsing
int parselog(char * logname);

/*--------------------------------------------------------------------------------*/
// Setup Log Parsing
void resortlog();

/*--------------------------------------------------------------------------------*/
// Small Loop to Kick off Log Parsing
void runparse();

/*--------------------------------------------------------------------------------*/
// Reads for Log Files Then Index's them into Log.dat
void addlog();

/*--------------------------------------------------------------------------------*/
// Kicks off All Log Parsing Functions
void dologparsing();

#endif

