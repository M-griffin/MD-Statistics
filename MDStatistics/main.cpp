/*

    .mD.Statistics
    Half Life Log Parser & HTML Statistics Generation (c) Michael Griffin .2002. / .2003.
    For Half Life FireArms Mod v2.6
    MrMisticismo@hotmail.com

    [Developed and Compiled on Borland C++ Builder 5.5 & 6, Visual C++ 6.0 SP5 & DevC++]
    [Developed and Compiles with g++ 2.95.3 Ported for Linux 1/8/03]

------------------- [Created starting with FA version 2.5] --------------------------------------------------------------------------------------------

03/26/02 - Started Basic Structure
03/29/02 - Not Keeping Track.. Building Log Dat Functions / Started Praser
03/30/02 - Finished Basic Log Praser and String Conversion... Working on
		 - Setting up Player Structure and Sorting Data from Strings
03/31/02 - Left off on proc1str();  And Player.dat File Creation Completed
		 - Setup Basic Index of all Player Names found from "connected" in log
		 - Completed scan for Kill and Asigns A kill for Player
04/01/02 - Completed Death And Kill Total's for Each Player
04/02/02 - Working on Link List Creation for Sorting Players.. Kills, Rank. Etc..
04/10/02 - Research and Testing Link List for sorting...  Hehe
04/11/02 - Link List Working and sorting by both Names in Alphebtic, and By # of Kill
04/12/02 - Thanks to Tim for the _getcwd(); Added that in to Replace Argv[0] System Path
		 - Working on Weapon Names and Number of Kills Per Weapon Structure
		 - Fixed And Completed Kill Death + Suicide Percentage

04/12/02 - Breaking up strings of log lines is broken...  gota put some checking in... :(
		   substring is not working correctly... ???? ARGHHHHHHHHH Can't do weapons till
		   This String Problem is fixed!!! :(

04/15/02 - Fixed Function for Breaking up Strings!!!  WOW that was anoying!!!!
		 - Getting Back to work on Weapon Structure, Stats for Each Player
04/16/02 - Complete Records for Each Weapon Name with Description / Kills & Death per.. each
		 - Creating Function to Add Kills and Deaths Per Weapon
		 - Fixed Suicides to Ignore Non-Valid Suicide Deaths.. Switching Teams.. etc..
04/17/02 - Added Suicide Counts for Each weapon... Later Killed Self with this weapon the most... =)
		 - Removed Index from WEAPONREC...  No Need to Index them... Since they are saved
		 - With PLAYERREC...
04/18/02 - Started making HTML Templates for Statistics, Also Working on Weapon
		   Kill.Death.Suicide Percentage aswell.
		 - Completed Weapon KILL DEATH SUICIDE PERCENTAGE Function!! Argh!! Lots of work
		 - And All Player Percentages have been fixed as well 0 - 100..  no Negative Values.
		 - Broke off the Percentages into a single function / Should do the same later
		 - For Weapon Parsing .. Naaaaaa..  hehe =)  If i'm bored :)
04/19/02 - Finished Basic HTML Templates for Rank and Player Statistics
04/20/02 - Created Link List for Sorting Modified HTML and Writing to File
		 - Working on Html Variable Fills and Replacement for each stat, Rank.html
		 - Finished Player Rank HTML file.. Starting on Second Player Stats.html
04/21/02 - Finished PlayerStats HTML files for Weapons for Each Player Stats..
		 - Completed Pre-Release Build 1 =)  Woooooo Hooooo  OMG i'm tired.!!
04/23/02 - Strings now being repalced when source is compiles in Vc++ 6, Borland 5.5
		 - DevC++ File i/o is not writing correctly for Output of HTML files.. Crazy..
		 - Program Runs perfectly in Borland C++ Builder 6 Only...  This is on Winxp,
		 - Testing on Win NT 4 also.. :(..
		-- Breaking Up File Into Seperate Headers and .Cpp's.. Over 4000 lines is a lot to
		   Go though back and forth in the same file when writing new shit.. =)
04/24/02 - Fixed and Correct String.Find(); Function which was killing the program in Visual
		   C++ And Borland BCB5 Free..  Dev C++ is still choking on File i/o  To hell with DevC++.
		   Next Going to Break Weapons File into 5 Files for Sorting Colums /rows of Weapons Like
		   The Player Ranks are Sorted..
04/25/02 - Re-Writting Link List for HTML PlayerStats.  Read in Once into Memory then keep
		   Parsing from copy in memory instead of reading file each time.. should help make a little
		   bit faster processing.
		 - Created Greatest Common Demonator for Kill Death Ratio, Look into Textout() File I/O
		   functions for Faster C++ I/O...
04/26/02 - Finished Added K:D Ratio in.. And Completed rewritting Rank HTML Templaes.. Next working on
		   adding K:D Ratio to PlayerStats, And Fixing Percentage bar graph.  Then will start to re-write
		   to order the weapons in in PlayerStats by Most Kills
		 - Finished Creating new PlayerStats.HTML Template, Will rewrite again for Ranking of Weapons..
		 - Completed Pre-Release Build 2.
04/30/02 - Found Bug in Program.. Player Names with only 1 Character ie Playername: o does not
		   have weapon statistics added to the player.dat.  Currently Tracking it down.
05/02/02 - Fixed Bug!! With Playername being only 1 Character - YAYAYAYAY *spits on computer*
		 - Change Output of Player stats from playername.html to rank.html..
05/04/02 - Creating Weapon Linklist for sorting weapons by name, Also Creating Weapon Names
		   for each instance.
		 - Added Weapon Name Completed.  And Total Weapon Kills per each weapon.
		   Program function to use these next... Completed Weapon Link List for Sorting
		   Weapons by Kills.
		 - Started Neck Read & CheckHTMLplayer Functions / Need to Finish New Template also.
		-- Completed New Player And Weapon Sorting HTML... phewwwwwwww....
05/05/02 - Completed Build 3, Starting on Build 4...
05/06/02 - Converted Player Processing from Read each time from disk, to Read one time into
		   Link Lists then cycle through processing..  Hopefully a little faster... =)
		   Next Will start working on New Weapon Percentage, Converted tkills to pkills
		   for New Percentage..
		 - Cleaned Up source Code and Removed Functions no longer in Use and ones for testing
05/09/02 - Completed Kill Percentage for Weapons.. This is new Percentage of Weapon kills out
		 - of Users total Kills.  Started working on new HTML Templates and also about to start
		   on Seperate Overall Weapon Statistics.
05/13/02 - Working on New Play Stat Templates, Fixed Percentage Bars, Now adding Weapon
		   Pictures...
05/14/02 - Re-Wrote File Structure again, and Broke up Log Parsing into FA25.cpp to Seperate
		   it for when Firearms 2.6 is released.  Also Fixed and Created Global PATH..
05/15/02 - Started Creating Seperate Weapon statistics, And Weapon.dat with WeaponFunc.cpp
05/16/02 - Not Much to Wrtie Down, doing a Tun of Coding and Re-writting for Weapon HTML Statistics..
		   it's going to be Twice as complicated as the Player Ranks and Player Weapon Statistcis..
05/21/02 - Completed Indivdual Weapon Statistics HTML Files and Coding,  Next Making Template
		   for Weapon Rankings, And code clean up.  Version 2.6 of Fire Arms released over the
		   weekend.  Need to setup a server and get some new log files and update program.
05/22/02 - Doing some minor code clean up
05/28/02 - Completed Weapon.html for Weapon Ranking, Going to Clean Up ALL HTML a bit also...
		 - Add in Weapon Kill Percentage of Total Kills for Weapon Rankings
		 - Completed Kill Percentage for Weapon.. Starting on NEW HTML files... =)
05/28/02 - Completed v2.5 Player Rankings, Players Stats with Weapon's, Weapon Ranking
		 - and Weapon Rankings with Players Kills for wach Weapon.  Starting on 2.6 Update.

------------------- [CONVERSION TO 2.6 HISTORY STARTS HERE] ---------------------------------------------------------------------------------------------

06/04/02 - Converting Weapons to 2.6 Log Format.. Complete Conversion of FA25.Cpp to FA26.Cpp
		   Struct.h Updated, HTML1.cpp Updated, HTML2.cpp Updated, PlayerFunct.cpp Updated.
		   Finishing up on FA26.cpp Updates for String Conversion to Find Weapons Correctly.
		   Updated WeaponFunct.cpp..  Weapon Updating Complete.  Next Need New Updated Pic's
		   And HTML for New Weapons...
06/05/02 - Created Function to Purge Players with No Kills or Statics from Player.dat..
06/06/02 - Make Sure to Add "weapmortor" to weapons ... Also Fix BUG with <PLAYERNAME>
		 - Did some Code Cleanup,, Added Weapons - weapmortar, spark_shower,  now need to
		 - modify link lists and HTML parser for Attack Damage to be added in...  along with
		 - some of the calculation functions.. *FOUND* Damage Scoring BUG!! Not Choping Strings Correctly.
		 - Must be re-worked.. also double check the Weapon Kills/ Deaths Suicides.. might be doing the same!!!
06/07/02 - Finished Updated Damage Statistics for all HTML Templates.. Thinknig adding Bleeding Damage..
		 - Added All New Weapons, as Well as Bleeding Damage Tracking as well..  Need to Rework All
		 - HTML Now.. as Well as Fix the Time so everything is Time Stamped with the same time..
		 - Also .. Created Footer for Bottom of all HTML Files..
06/11/02 - Finished Update All HTML and Conversion to FA2.6  Released 1st Public Build
06/12/02 - Working on Config File for # Of Players Ranked in HTML..
06/13/02 - Finished Basic Config File..  Impliments New Log Path, and # Of Players for Ranking,
		   All Setup and Working..  Finish Weapon Player Ranks Tomorrow in log file..
06/14/02 - Added HTML Path from writtin out HTML file..  Also New Templat Directory.. to Seperate
		 - Template files from those that get generated.   Release Build 6.8 With new config.
06/15/02 - Starting working on New Link list in Memory to Hold player data while parsing log
		 - this should speed everything up 10x or more.. =)) if i get it right.. hehe
06/16/02 - Finished rewritting Log Parser to gather Data in memory,  Sped up 100x faster!!!
06/17/02 - Added Some Extra Error Checking to Make Sure Program doesn't crash with crazy windows
		   Errors when no logs or player data exists to generate Stats From.
		 - Also Fixed a few path problems with dataexists functions for Dat files.
06/27/02 - Fixed Memory Leak YIPPIE!!   No Working on a couple minor speed up, and some
		 - extra log parsing information, what log file is being parsed etc...
		 - Updated All Link Lists in HTML1 to 'new & delete'
		 - Fixed Visual C++ Build by replacing time() with GetTimeFormat() & GetDateFormat()
06/29/02 - Working on Rewriting calculation for speed up, Load All Players into memory and
		   Then Calculate Stats,, Also will try this for HTML Creation to speed that up also.
06/30/02 - Sped Up Every Function for Writing Out HTML Files.. Left Out Putting ALL players
		   into link list for Writting out Weapon Ranks, Might Be a Little To Much Memory.
		   Will run a test later on it.
		 - Next Maybe Speed up Calculation of Statistics.. But Runs Great for Now.
		 - Broke off HTML Tempaltes into a Seperate Folder
07/08/02 - Fixed Log Parsing Log problem, added \r into log file for splitting log lines
		 - Also added log line counting to remove last line of log file if it is bad.
		 - Build 7.4 ...
07/09/02 - Finished All Speed Optimization for Calculations and HTML speed up, the whole program
		   Now flies like a bastard.. WOW  even on a P2-400 it takes like useer 10 seconds for everything
		   and this is just will a couple log files..  Build 7.5.. =)
07/10/02 - Restructing Log Handeling, Sorting Log Names in Order to Process Logs in Order
		   For Proper / cloest to possiable map tracting from 1 log to the next...
		 - Redesigned Output for User End.. + Lots of Code Clean up
07/12/02 - Setup Map Structures and new Config.dat Structure to Hold Current Map for Next Log Parsing run
		 - Have Globals set for Map. now just have to setup Players Stats to Maps and Save to Map Data file
07/14/02 - Finished udateing and spliting log parsing into Seperate dat's for each map.
	 	   Next just need to sorta it and output.. and creat new HTML for maps..
		 - Moved All Data Files to a [Data] Directory for clearner program layout
07/16/02 - Breaking up Source, Adding New Stats.Cpp and Maps.Cpp for Extra Processing
07/18/02 - Fixed Problem in Data files.. Needed to 0 out variables before saving or
		   adding / subtracting.. etc..
		 - Now need to Setup PlayerRankCalcStats..  So it Calculcated all those statistics
		   Then program should be able to run almost where it left off..
		 - Fixed Up to Player Rankings, Now have to Kick off Weapon Sorting - Finished!!
		 - Starting on Player Rankings HTML
07/19/02 - Finished Converting Player Ranks and Player Statistics HTML, No Fixing HTML Templates.
		 - Fixed up config file and Tamplate to hold Server/Admin Names Ip and Web Addreses.. etc.
		 - Need to Fix Bug, IMI DESERT EAGLE 2 times in Player Weapon Rankings. =(
07/20/02 - Added New Console.cpp and Console.h for New Console Functino to Change Text Color,
	 	   Cursor Position for a Better User Interface.. =)
07/21/02 - Finished New Inferface.. Looks Great, will add Percentage later...
		 - Finished Fixing up All Templates and Weapon HTML Files Build .87
08/07/02 - Working on Percentage Complete for each process..
		 - Completed Percentage for Log parsing and saving only.
08/13/02 - Reworking PlayerRank.dat system.. putting into Link List before writes..
08/18/02 - Still Reworking PlayerRank.dat
		 - Finished Ranks, Everything is working again.. YAY

------------------- Compiler Fixes ---------------------------------------------------------------------------------------------

11/25/02 - Updated all c++ Read/Write from .data() to .c_str, Previouslu
		   was only compiling on Borland C++ Builder 6, Now will compile on all
		   C++ Compiles Again, Visual C++ and Dev++ (Main Working Enviroment now)
		 - Changed all Globals from String to Char[] for Compatibilty
		 - Fixed for Linux Compatibility with Character Arrays,
		   For full need to Replace Time and Directory Functions
		 - Removes all Players with Freshmeat in Name!
		 - Changeing Cout to Prinf for proper Console display
		 - Build 91

11/26/02 - Fixed Config file recreation if missing, ofstream::out | ofstream::trunc
	 	   and fixed the path setup aswell.
		 - Fixed some more overlooks on paths with data files, and replace more cout's
		   with printf's
		 - Also fixed some Percentag's Goof's on Display. And more HTML Output
		   Path's.  Weird that it was working the way it was..  hmmmm
		 - Fixed more i/o functions with fclose in them causing program to exit!
		   When file was not opened in first place!
		 - Build 92

		 - Need to add extra conio.h from linux for console interface! should also rip out
		   all conio.h functions being used and added to console.cpp / h to make faster.
		 - also need to replease direct.h with io.h for current working dir.
		 - Also Need to Remove String Conversions in Parsing, no longer String
		   So don't have to convert to Char Arrays anymore!! :))

11/27/02 - Making some minor Code Optimizations and Cleaning up the comments!
	 	 - EXE Optimized 17k by removing all = 0's to Memset(Struct) for Big Functions!
	 	 - Build 93

11/28/02 - Reworking for new Temples of Player Rankings
	 	 - Build 94

11/29/02 - Added Sleep()'s to help kill off the constant 100% CPU useage,  will add
	   	   a variable to the confile to set the delay manually for people who aren't
		   worried about cpu usage.. ;) Build 95
		 - A bite more of code cleaning up.  Weeeeeeeeeeeeeeeeeeee

01/07/03 - Moved to Linux Platform, going through major re-write of complete program :)

01/08/03 - Log Parsing Ported over, finishing player statistics

		 - Everything is Converted Over to Linux, Percentages arn't working with the conversion
		   from double to long.  And time.h needs to repleace windows api time functions.

01/09/03 - Complete Full Ports of Windows and Linux with same source code. Phewwwwwww
		 - Will rework GUI later for ansi in both windows and linux, Starting to work
	   	   on new map code. Sleep()'s only done in Linux at the moment

01/10/03 - Adding new Windows Console Functions and handling, Wincon.cpp, a seperate one
	   	   will be created for linux's console output as well.

01/22/03 - Cleaning up some Functions and getting ready for map processing.

01/24/03 - Adding IDX files for each MAPNAME.DAT for Indexing of Player data,
	       This should help make searching and reading and writing of data files a
		   bit faster. - Working Great, Has double the speed of Log Data Saving,
		   as well as player purging.
		 - Make an IDX of the Playerrank also for faster processing in Stats and HTML
		 - Code Cleanup and Removed a few functions that were not being used anymore.

01/25/03 - Reworking Parsing of Log Data, Removing extra function work and breaking off
	   	   The String parsing to update the user data directly / faster!
		 - Finished Rewritting the reparsing, optimized about 2k of exe and it's a lot
		   more workable now.

01/30/03 - Fixed bugs in parsing code that wasn't registering damage received.
	 	 - Also re-write of the purging code for players,  now purges correctly
	   	   only players with freshmeat and players with 0 kills on a map.
		 - Added extra GUI clearing functions... Clear All, Clear all Right / Left

01/31/03 - Reworking Player Rankings with new Tamplates, Also Multiple index.html
	   	   For Rankings per Statistics.

02/01/03 - Reworked Temp dat functions.  Instead of Writtting to Temp file and then
	   	   Renaming temp.  All data is copied to Link List. then Saved to remove
	       Unnessary Processing.

02/04/03 - Finished NEW GUI for all processes.  Need a little tweaking but all the
		   Work and complicated shit is out of the way.  :)  Yippie.

03/01/03 - Added Ansi Parsing code for GUI to replace call to GUI.com
		   broke up startup checks and functions into program_init()
		 - Rewrote the HTML Ranks output to use streaming instead of link lists.

03/02/03 - Reformatting all code and cleanup from 8 tabs to 4



   *Overview. Program Reads all Log Files. Puts LOG Names into a Log.dat Index's them.
    Logs files are only read once then Stats Are generated and placed into Player.dat for each player
    New Logs Files append new stats to each player in Player.dat... Program is ongoing
    stats can be reset by deleteing the player.dat and keeping the log.dat, old log
    files will not be re-read then, as long as the log.dat isn't deleted. Weapons .dat
    will contain all stats for each weapons including kills per weapon.  Don't forget to Add Player Victum
    Stats... =)  And A few Extra's That Phychostats has.  But the Complicate Stuff Can Wait till after b
    basic build and program are completed...

   **Warning Half aSleep When Writting Comments..  Lots of Typo's.. hehe :p

*/

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++  - All Libraries are Defined in "Structs.h"


// Linux Specific Headers
#ifdef _LINUX
#include <unistd.h>		// CWD
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN_AND_MEAN
#include <windows.h>
#include "wincon.h"
#endif

#include "ansi.h"		// Ansi Parser for GUI
#include "structs.h"            // Loads all Globals
#include "config.h"             // Load Config File
#include "Mapfunc.h"		// Map Function / Not Completed Yet!
#include "LogFunc.h"            // Loads LOG.DAT File i/o
#include "PlayerFunc.h"         // Loads PLAYER.DAT File i/o
#include "WeaponFunc.h"         // Loads WEAPON.DAT File i/o
#include "FA26.h"               // Firearms Log File Parsing Functions
#include "Stats.h"              // Statistics Calculations
#include "Html1.h"              // Player Ranks and Player Weapons
#include "Html2.h"              // Indivual Weapon And Weapon Ranking HTML Creation

using namespace std;            // Standard C++ Namespace

/*--------------------------------------------------------------------------------*/
// Globals - Extern in Structs.h
/*--------------------------------------------------------------------------------*/

char 	PATH[255];		// Global Path
long 	MAXRANK = 0;		// Max # of Players in Player Rankings
long 	MAXWEAPONRANK = 0; 	// Max # of Players in Weapon Rankings
char 	LOGPATH[255];     	// Log File Path
char 	HTMLPATH[255];    	// HTML Output Path

char 	szDateFormat[128];	// System Date
char 	szTimeFormat[128];	// System Time
char 	MAPNAME[30];	 	// Current Map
char 	NEWMAP[30];	 	// Test for New Map
char 	CURRMAP[30]; 	 	// Current Map (During Processing)
bool 	TEAM = true;	 	// 0 true = Red / 1 False = Blue



/*--------------------------------------------------------------------------------*/
// MAIN PROGRAM ENTRANCE
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Program Initalization
void program_init() {

	CONFIG cfg;   // Handle to Current Map Name

	// Do Error Checking if CONFIG.CFG File exists, if not creates it
	if(configdataexists() == false) createconfig(); // Creates Config with Default Settings

	// Open and Read Config file
	parseconfig();

	// Check if Log Path was set, of not use Default!
	if (strcmp(LOGPATH, "NONE") == 0 ) strcpy(LOGPATH,PATH);

	// Check if HTML Path was set, of not use Default!
	if (strcmp(HTMLPATH, "NONE") == 0) strcpy(HTMLPATH,PATH);

	// Create Config.dat
	if(cfgdataexists() == false) {
		char text1[40] = "Can't Create config.dat! ";
		drawleft(text1,12,0);
		#ifdef _WIN32
		system("pause");
		#endif
		exit(1);   // Exit Program if Error Occurs
	}

	if (countcfg() == 0) strcpy(MAPNAME, "unknown");
	else {
		readcfg(&cfg,0);
		strcpy(MAPNAME,cfg.currmap);
	}

	// Setup Log Parsing
	strcpy(NEWMAP,MAPNAME);

	// Do Error Checking if Log.dat File exists, if not creates it
	if(dataexists() == false) {
		char text1[40] = "Can't Create log.dat! ";
		drawleft(text1,12,0);
		#ifdef _WIN32
		system("pause");
		#endif
		exit(1);   // Exit Program if Error Occurs
	}

        // Do Error Checking if Weapon.dat File exists, if not creates it
	if(wdataexists() == false) {
		char text1[40] = "Can't Create Weapon.dat! ";
		drawleft(text1,12,0);
		#ifdef _WIN32
		system("pause");
		#endif
		exit(1);   // Exit Program if Error Occurs
	}

	// Do Error Checking if Weapon.dat File exists, if not creates it
	if(mdataexists() == false) {
		char text1[40] = "Can't Create Map.dat! ";
		drawleft(text1,12,0);
		#ifdef _WIN32
		system("pause");
		#endif
		exit(1);   // Exit Program if Error Occurs
	}

	#ifdef _WIN32
	// Display Program GUI
	char gui[255];
	sprintf (gui,"%sGUI.ANS",PATH);
	system("cls");
	ansiparse( gui );
	#endif
	return;
}



/*--------------------------------------------------------------------------------*/
// Main - Testing of All Functions
int main(int argc, char *argv[]) {

	// Setup Global Path in Structs.h
    char arg[255];
  	strcpy(arg,argv[0]);
	int num;

	#ifdef _WIN32
	// Get And Set Program Path
	memset(&PATH,0,255);
	for (int i = 0; ;i++) { // Count for Romoval of ExeName with Path
		if (arg[i] == '\0') break;
		if (arg[i] == '\\') num = i;
	}
	for (int i = 0; i < num+1 ; i++) {
		PATH[i] = arg[i];
	}
 	SetCurrentDirectory(PATH);
    #else
	// Get And Set Program Path
	memset(&PATH,0,255);
	for (int i = 0; ;i++) { // Count for Romoval of ExeName with Path
		if (arg[i] == '\0') break;
		if (arg[i] == '/') num = i;
	}
	for (int i = 0; i < num+1 ; i++) {
		PATH[i] = arg[i];
	}
    #endif

	program_init(); // Initalize all setup proceedures

	#ifdef _WIN32
	GetTimeFormat( LOCALE_SYSTEM_DEFAULT, 0, NULL, NULL, szTimeFormat, 50 );
	GetDateFormat( LOCALE_SYSTEM_DEFAULT, 0, NULL, NULL, szDateFormat, 50 );
	SetConsoleTitle(" .mD.Statistics For Firearms Mod v2.6 [Alpha] Release - Webpage Statistics");
	//system("GUI.COM"); // Kick off GUI Interface...
   	#else
   	// Add Linux Time here.. Still missing from Linux Port.
	system("clear");
	//System("cat GUI.ANS");    - Not yet Implimented a GUI for Linux - Text Only!
	printf("\n+----------------------------------------------------------------+\n");
	printf("| .mD.Statistics For Firearms Mod v2.6 : [Build 0.1.1.1] 3/02/03 |\n");
	printf("| (c) 2002-2003 Michael Griffin (Webpage Statistics Generator)   |\n");
	printf("+----------------------------------------------------------------+\n\n");
	#endif

	// Start Program Operations here, Parsing of Log Files
	dologparsing();

        // Error Checking if any Log files are avial to be read..
	if (countlogs() == 0) {
		char text1[40] = "No log files found! ";
		drawleft(text1,12,0);
		#ifdef _WIN32
		system("pause");
		#endif
		return 0;
	}

	// Handle to Current Map Name
	CONFIG cfg;
	strcpy(cfg.currmap,NEWMAP);
	writecfg(&cfg,0);

	// Kick off rest of program's processes
	delplayer();            // Removes Player's with 0 Kills From Rankings

	dostatcacl();           // Do Player Stat Calculations

	doplayersrankHTML();    // Process Player Rankings Index.html
	doplayersHTML();        // Processes Individual Player Statistics with Weapons Stats

	doweaponHTML();         // Processes Weapon Rankings, And Indivdual Weapons Statistics
	clearwkillsort();       // Clears Link List for Weapon Sorting And Ranks calcwrank(); =)
	doweaponrankHTML();     // Process for Weapon Rankings Weapon.HTML

   	string tpath = PATH;

	clearall();

	#ifdef _WIN32
	char text2[40];
	sprintf(text2,"Started: [%s]",szTimeFormat );
	drawleft(text2,3,0);

	GetTimeFormat( LOCALE_SYSTEM_DEFAULT, 0, NULL, NULL, szTimeFormat, 50 );
	char text4[40];
	sprintf(text2,"Ended:   [%s]\n\n",szTimeFormat );
	drawleft2(text2,3,0);
	system("pause");
        string temp0 = tpath+"Data\\playerrank.dat";
  	string temp1 = tpath+"Data\\playerrank.idx";
   	#else
	string temp0 = tpath+"Data/playerrank.dat";
  	string temp1 = tpath+"Data/playerrank.idx";
  	#endif

	// Removes Playerrank files for refresh.
	remove(temp0.c_str());
	remove(temp1.c_str());
	return 0;
}
/*--------------------------------------------------------------------------------*/
