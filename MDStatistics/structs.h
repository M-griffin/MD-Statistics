#ifndef __STRUCTS_H    /*  An extra safeguard to prevent this header from  */
#define __STRUCTS_H    /*  being included twice in the same source file    */

// This file is the basic GLOBAL File, it contains all Libraries that will be used as
// well as structures for all data types used in this program

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++
// This File loads all Headers and is the main Global File

#include <iostream>             // C++ I/o   For Cin / Cout ... - Global
#include <stdio.h>              // C Standard I/o - Global
#include <stdlib.h>             // strtod()  String to Double...
#include <string>               // C++ String Library - Globlal
#include <fstream>              // Files Streams C++ - Global
#include <cstdlib>              // abs() - LinkList.h

using namespace std;

/*--------------------------------------------------------------------------------*/
// GLOBALS
/*--------------------------------------------------------------------------------*/

// Config File Globals
extern char   PATH[255];        // Global Path
extern long   MAXRANK;          // Max # of Players in Player Rankings
extern long   MAXWEAPONRANK;    // Max # of Players in Weapon Rankings
extern char   LOGPATH[255];     // Log File Path
extern char   HTMLPATH[255];    // HTML Output Path
extern char   SERVERNAME[255];  // HTML Server Name
extern char   SERVERIP[255];    // Server IP Address
extern char   WEBPAGE[255];     // Server Web Page
extern char   ADMINNAME[255];   // Admin Name
extern char   ADMINEMAIL[255];  // Admin Email

// Program Globlas
extern char szDateFormat[128];  // System Date
extern char szTimeFormat[128];  // System Time
extern char MAPNAME[30];        // Current Map
extern char NEWMAP[30];         // Test for New Map
extern char CURRMAP[30];        // Current Map (During Processing)
extern bool TEAM;               // 0 False = Red / 1 True = Blue


/*--------------------------------------------------------------------------------*/
// STRUCTURES
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Structure Holds All Log FileNames
typedef struct
{
    char   currmap[30];      // Current Map Name
} CONFIG;


/*--------------------------------------------------------------------------------*/
// Structure Holds All Log FileNames
typedef struct
{
    // Still Thinking of How to Set this up with each weapon name
    // Then Kills per each weapon
    int    index;             // Weapon Index
    int    rank;              // Weapon Rank
    char   name[30];          // Weapon Name
    long   kills;             // Kills with this Weapon
    long   deaths;            // Deaths by this Weapon
    long   sui;               // Suicides with this weapon
    double kdp;               // Weapon Kill Death Sui Percentage
    char   kdr[10];           // Kill Death Ratio
    double pkills;            // Weapons Percentage Kills
    long   damdelt;           // Damage Delt by this Weapon
    long   damrec;            // Damage Reveiced by This Weapon
    char   dratio[10];        // Damage Ratio
} WEAPONREC;


/*--------------------------------------------------------------------------------*/
// Structure Holds Basic Map Stats
typedef struct
{
    WEAPONREC knife;          // COMBAT KNIFE
    WEAPONREC coltgov;        // COLT 1911 (.45 ACP-SA)
    WEAPONREC ber92f;         // BERETTA 92F (9mm SA-SIL)
    WEAPONREC ber93r;         // BERETTA 93R (9mm SA-3RB)
    WEAPONREC anaconda;       // COLT ANACONDA (.44 RV SA-SCP)
    WEAPONREC desert;         // DESERT EAGLE (.50 AE-SA)
    WEAPONREC benelli;        // BENELLI M1 (TAC 12-Gauge)
    WEAPONREC saiga;          // SAIGA 12K (Automatic Shotgun)
    WEAPONREC mp5a5;          // H&K MP5A5 (9mm TAC SMG)
    WEAPONREC sterling;       // Sterling SMG (9mm LC)
    WEAPONREC bizon;          // BIZON SMG (9mm HCM-SMG)
    WEAPONREC ak47;           // AK-47 (7.62mm AR-BT)
    WEAPONREC famas;          // FA-MAS (5.56 AR-TAC)
    WEAPONREC g3a3;           // H&K G3 (7.62 TAC AR-LCM)
    WEAPONREC g36e;           // G36E (5.56 NATO AR-SCP)
    WEAPONREC m16;            // M-16A2 (5.56 AR-GL)
    WEAPONREC m82;            // BARRET M82A1 (.50 A-T SR-SCP)
    WEAPONREC m60;            // M-60 (7.62 HCM-MG)
    WEAPONREC m203;           // M203
    WEAPONREC m79;            // M-79 (40mm GL)
    WEAPONREC claymore;       // CLAYMORE (Land Mine)
    WEAPONREC frag;           // M-61 FRAGMENTATION GRENADE
    WEAPONREC stg24;          // STIELHANDGRANATE
    WEAPONREC uzi;
    WEAPONREC pkm;
    WEAPONREC ak74;
    WEAPONREC svd;
    WEAPONREC gp25;
    WEAPONREC ssg3000;
    // Special Weapon Items...
    WEAPONREC weapmortar;
    WEAPONREC spark_shower;
    WEAPONREC monster_mortar;
    WEAPONREC func_tank;
    WEAPONREC env_explosion;
    WEAPONREC concussion;
    WEAPONREC ammobox;
    // Special Not Being Used at the Moment
    // WEAPONREC bodyque;
    // WEAPONREC game_player_hurt;
    // WEAPONREC trigger_hurt;
    // WEAPONREC world;
    // WEAPONREC worldspawn;

    // Map / Team Statistics
} WEAPONSTRUCT;


/*--------------------------------------------------------------------------------*/
// Structure Holds All Player Names in Log File
typedef struct
{
    // Basic Player Statistics
    int          index;            // Player Index in Data File
    int          rank;             // Players Rank
    char         name[30];         // Player Name
    long         kills;            // Kills
    long         deaths;           // # of Times Killed
    long         sui;              // # of Times Player has killed Self
    double       kdp;              // Kill Death Percentage
    char         kdr[10];          // Kill Death Ratio
    long         damdelt;          // Damage delt to Other Players
    long         damrec;           // Damage Received from Other Players
    char         dratio[10];       // Players Damage Ratio, Inflicted / Received
    long         dambleed;         // Bleeding Damage
    WEAPONSTRUCT weapon;           // Weapon Statistics
} PLAYERREC2;

/*--------------------------------------------------------------------------------*/
// Indexing for PLAYERREC - For Faster Lookup's
typedef struct
{
    int          index;            // Player Index in PLAYERREC
    char         name[30];         // Player Name
    //long         wonid;            // Players Wonid - Not implimented yet
} PLAYERREC2IDX;



/*--------------------------------------------------------------------------------*/
// Structure Holds Basic Map Stats
typedef struct
{
    PLAYERREC2 player2;
    // Player's Team / Map Statistics
} MAPREC;

/*--------------------------------------------------------------------------------*/
// Structure Holds All Player Names in Log File
typedef struct
{
    char         mapname[30];      // Map Name
    MAPREC         redforce;       // Statistics for Red Team on This Map
    MAPREC         blueforce;      // Statistics for Blue Team on this map
    int          index;            // Player Index in Data File
    int          rank;             // Players Rank
    char         playername[30];   // Player Name
    long         kills;            // Kills
    long         deaths;           // # of Times Killed
    long         sui;              // # of Times Player has killed Self
    double       kdp;              // Kill Death Percentage
    char         kdr[10];          // Kill Death Ratio
    long         damdelt;          // Damage delt to Other Players
    long         damrec;           // Damage Received from Other Players
    char         dratio[10];       // Players Damage Ratio, Inflicted / Received
    long         dambleed;         // Bleeding Damage
} PLAYERREC;

/*--------------------------------------------------------------------------------*/
// Indexing for PLAYERREC - For Faster Lookup's
typedef struct
{
    int          index;            // Player Index in PLAYERREC
    char         name[30];         // Player Name
    //long         wonid;            // Players Wonid - Not implimented yet
} PLAYERRECIDX;

/*--------------------------------------------------------------------------------*/
// Structure Holds All Log FileNames
typedef struct
{
    int  index;             // Logname Index in Data File
    char name[30];          // Logname
} LOGNAME;

/*--------------------------------------------------------------------------------*/
// Structure Holds All Log FileNames
typedef struct
{
    int  index;             // mapname Index in Data File
    char name[30];          // mapname
} MAPNAMEREC;


/*--------------------------------------------------------------------------------*/
// Link List for Sorting Players by Kills
struct ListItem
{
    int       index;            // Player Index
    int       rank;             // Player Rank
    char      name[30];         // Player Name
    long      frags;            // Kills
    long      deaths;           // # of Times Killed
    long      suicides;         // # of Times Player has killed Self
    double    kdp;              // Kill Death Percentage
    char      kdr[10];          // Kill Death Ratio
    long      damdelt;          // Damage delt to Other Players
    long      damrec;           // Damage Received from Other Players
    char      dratio[10];       // Players Damage Ratio, Inflicted / Received
    long      dambleed;         // Bleeding Damage
    struct ListItem *next;
};

/*--------------------------------------------------------------------------------*/
/*// Link List for Sorting HTML OUTPUT - Rank's.html
struct ListItem2
{
        char html[400];
        struct ListItem2 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Sorting HTML OUTPUT - Playername's.html
struct ListItem3
{
    char html[400];
    struct ListItem3 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Sorting Player Weapons By Kills Player.HTML
struct ListItem4
{
    int       rank;             // Weapon Rank
    char      name[30];         // Weapon Name
    long      kills;            // Kills with this..
    long      deaths;           // # of Times Killed by this ...
    long      sui;              // # of Times Player has killed Self by this...
    double    kdp;              // Kill Death Percentage
    char      kdr[10];          // Kill Death Ratio
    double    pkills;           // Weapons Percentage Kills
    long      damdelt;          // Damage delt to Other Players
    long      damrec;           // Damage Received from Other Players
    char      dratio[10];       // Players Damage Ratio, Inflicted / Received
    struct ListItem4 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Sorting HTML OUTPUT - PlayerTop.HTML
struct ListItem5
{
    char html[400];
    struct ListItem5 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Sorting HTML OUTPUT - PlayerRow1.HTML
struct ListItem6
{
    char html[400];
    struct ListItem6 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Sorting HTML OUTPUT - PlayerRow2.HTML
struct ListItem7
{
    char html[400];
    struct ListItem7 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Sorting HTML OUTPUT - PlayerTop.HTML
struct ListItem8
{
    char html[400];
    struct ListItem8 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Sorting HTML OUTPUT - PlayerRow1.HTML
struct ListItem9
{
    char html[400];
    struct ListItem9 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Sorting HTML OUTPUT - PlayerRow2.HTML
struct ListItem10
{
    char html[400];
    struct ListItem10 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Sorting Player Weapons By Kills Weapons.html
struct ListItem11
{
    int       rank;             // Weapon Rank
    char      name[30];         // Weapon Name
    long      kills;            // Kills with this..
    long      damdelt;          // Damage delt to Other Players
    struct ListItem11 *next;
};


/*--------------------------------------------------------------------------------*/
// Link List for Holding all Players during log parsing until write to player.dat
struct ListItem13
{

    PLAYERREC player;
    struct ListItem13 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Holding all Players Data Faster Statistics Generation
struct ListItem14
{
    PLAYERREC player;
    struct ListItem14 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Playerrank.dat and Getting Overall Players Ranks and Stats
struct ListItem12
{
    PLAYERREC2 player;
    struct ListItem12 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Playerrank.dat and Getting Overall Players Ranks and Stats
struct ListItem18
{
    PLAYERREC2 player;
    struct ListItem18 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Holding all Weapon Data Faster HTML Creation
struct ListItem15
{
    WEAPONREC weapon;
    struct ListItem15 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Holding Log Files names and Sorting in Creation Order
struct ListItem16
{
    LOGNAME log;
    struct ListItem16 *next;
};

/*--------------------------------------------------------------------------------*/
// Link List for Holding Log Files names and Sorting in Creation Order
struct ListItem17
{
    MAPNAMEREC map;
    struct ListItem17 *next;
};

#endif
