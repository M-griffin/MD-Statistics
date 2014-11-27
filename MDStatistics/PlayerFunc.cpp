#ifndef __PLAYERFUNCT_CPP    /*  An extra safeguard to prevent this header from  */
#define __PLAYERFUNCT_CPP    /*  being included twice in the same source file    */

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN_AND_MEAN
#include "wincon.h"
#include "windows.h"
#endif

#include "Stats.h"
#include "structs.h"
#include "Mapfunc.h"
#include "PlayerFunc.h"

using namespace std;            // Standard C++ Namespace

/*--------------------------------------------------------------------------------*/
// GLOBALS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Link list for Faster Player Purging
struct ListItem14 *List14 = 0;

/*--------------------------------------------------------------------------------*/
// LINKLIST Functions for Faster Player Purging
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearList14(void) {

    struct ListItem14 *p,*next;
    if ( List14 == 0) return;

    for(p = List14 ; p !=0 ; p = next ) {
        next = p->next;
        delete (p);
    }
    List14 = 0;
    return;
}


/*--------------------------------------------------------------------------------*/
// MAPNAME.IDX FUNCTIONS - Indexing of Player Data
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// MAPNAME.IDX Write - Indexes of Each Data file for Faster Searching
int writepidx(PLAYERRECIDX * player, int idx) {

    string path = PATH;
    string map = MAPNAME;

      #ifdef _WIN32
    path += "Data\\"+map+".idx";
       #else
      path += "Data/"+map+".idx";
       #endif

    FILE * stream;
    int x=0;

    stream=fopen(path.c_str(),"rb+");         // file test
    if(stream == NULL){
        stream=fopen(path.c_str(), "wb"); // open file Writing
        if(stream == NULL) {
            cout << "Error Creating " << MAPNAME << ".idx!" << endl;
            return x;
        }
    }
    if(fseek(stream,(long)idx*sizeof(PLAYERRECIDX),SEEK_SET)==0)
        x = fwrite(player,sizeof(PLAYERRECIDX),1,stream);
    fclose(stream);
    return x;
}


/*--------------------------------------------------------------------------------*/
// MAPNAME.DAT Reads - Indexes of Each Data file for Faster Searching
int readpidx(PLAYERRECIDX * player, int idx) {

    string path = PATH;
    string map  = MAPNAME;

    #ifdef _WIN32
    path += "Data\\"+map+".idx";
       #else
      path += "Data/"+map+".idx";
       #endif

    int x;

    FILE * stream;

    stream = fopen(path.c_str(),"rb+");
    if(stream == NULL) {
        stream=fopen(path.c_str(), "wb");   // open file Writing
        if(stream == NULL) {
            cout << "Error Creating " << MAPNAME << ".idx!" << endl;
            return false;
        }
    }
    fclose(stream);

    stream = fopen(path.c_str(), "rb");
    if(fseek(stream,(long)idx*sizeof(PLAYERRECIDX),SEEK_SET)==0)
        x = fread(player,sizeof(PLAYERRECIDX),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// Reads player.dat and gets Total number of Players that have been loaded
int countpidx() {

    int i = 0;
    PLAYERRECIDX player;

    while(readpidx(&player,i++));
    if(i < 1)    i=-1;
    else        i--;
    return(i);
}

/*--------------------------------------------------------------------------------*/
// Find Player record By Matching name - Gets player Index
int findpidx(char * tplayer) {

    int idx=0;
    string temp1, temp2;
    PLAYERRECIDX player;

    temp1 = (tplayer);

    while(readpidx(&player,idx)) {
        temp2 = (player.name);
        if(temp1 == temp2) return(idx);
        idx++;
    }
    return(-1); // Return Record Not Found
}


/*--------------------------------------------------------------------------------*/
// Function Check if Name already exists in Player.dat
bool matchpidx(char * name) {

    int index =- 1;
    index = findpidx(name);
    if (index == -1) return false;
    else return true;
}


/*--------------------------------------------------------------------------------*/
// Checks if Player.dat file exists,  if not Creates it
bool pidxdataexists() {

    string path = PATH;
    string map  = MAPNAME;

    #ifdef _WIN32
    path +="Data\\"+map+".idx";
       #else
      path +="Data/"+map+".idx";
       #endif

    FILE * stream;

    stream=fopen(path.c_str(),"rb+");
    if(stream == NULL) {
        stream=fopen(path.c_str(), "wb");
        if(stream == NULL) {
            fprintf(stderr, "Error Creating MapName.idx!\n");
            return false;
        }
    }
    fclose(stream);
    return true;
}

/*--------------------------------------------------------------------------------*/
// Adds Index
void addpidx(char * name, int idx) {

    PLAYERRECIDX player;
    strcpy(player.name,name);
    player.index = idx;
    writepidx(&player,idx);
    return;
}


/*--------------------------------------------------------------------------------*/
// MAPNAME.DAT FUNCTIONS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// MAPNAME.DAT Write - I/O Adds logname to Log File
int writep(PLAYERREC * player, int idx) {

    string path = PATH;
    string map = MAPNAME;

      #ifdef _WIN32
    path += "Data\\"+map+".dat";
       #else
      path += "Data/"+map+".dat";
       #endif

    FILE * stream;
    int x=0;

    stream=fopen(path.c_str(),"rb+");         // file test
    if(stream == NULL){
        stream=fopen(path.c_str(), "wb"); // open file Writing
        if(stream == NULL) {
            cout << "Error Creating " << MAPNAME << ".dat!" << endl;
            return x;
        }
    }
    if(fseek(stream,(long)idx*sizeof(PLAYERREC),SEEK_SET)==0)
        x = fwrite(player,sizeof(PLAYERREC),1,stream);
    fclose(stream);
    return x;
}



/*--------------------------------------------------------------------------------*/
// PLAYERNAME.DAT Reads - I/O Read Any Log by Index Number
int readp(PLAYERREC * player, int idx) {

    string path = PATH;
    string map  = MAPNAME;

    #ifdef _WIN32
    path += "Data\\"+map+".dat";
       #else
      path += "Data/"+map+".dat";
       #endif

    int x;
    FILE * stream;

    stream = fopen(path.c_str(),"rb+");
    if(stream == NULL) {
        stream=fopen(path.c_str(), "wb");   // open file Writing
        if(stream == NULL) {
            cout << "Error Creating " << MAPNAME << ".dat!" << endl;
            return false;
        }
    }
    fclose(stream);

    stream = fopen(path.c_str(), "rb");
    if(fseek(stream,(long)idx*sizeof(PLAYERREC),SEEK_SET)==0)
        x = fread(player,sizeof(PLAYERREC),1,stream);
    fclose(stream);
    return x;
}


/*--------------------------------------------------------------------------------*/
// Select and Save User Data to Temp file
void save_player_temp(PLAYERREC * player) {

    struct ListItem14 *last;

    ListItem14 *item = new ListItem14;
    if( !item ) {
        cout << "Malloc Failed for holding Player Data\n";
        cout << "You do not have enough memory for this program!\n";
        exit(1);
    }

    item->player = (*player);
    item->next = 0;

    if ( List14 == 0 ) {  // If List is Empty, make this the first item
        List14 = item;
        return;
    }

    for( last = List14 ; last->next != 0 ; last = last->next );
    last->next = item;
    return;
}


/*--------------------------------------------------------------------------------*/
// Grabs information form Temp and Puts into Normal.. Then Deletes Temp File
void restore_player_data() {

    struct ListItem14 *p;
    string path = PATH,
       temp0, temp1,
       map = MAPNAME;

    #ifdef _WIN32
    temp0 = path+"Data\\"+map+".idx";
    temp1 = path+"Data\\"+map+".dat";
       #else
    temp0 = path+"Data/"+map+".idx";
      temp1 = path+"Data/"+map+".dat";
       #endif

    remove(temp0.c_str()); // Deletes Original MAPNAME.IDX
    remove(temp1.c_str()); // Deletes Original MAPNAME.DAT

    int i = 0;
    for ( p = List14 ; p != 0 ; p = p->next ) {
        p->player.index = i;
          addpidx(p->player.playername,i);     // Recreates index to match dat file
          writep(&p->player,i);                // Writes Temp.dat Data to 'New' Mapname.dat
        ++i;
    }
    clearList14();
    return;
}

/*--------------------------------------------------------------------------------*/
// Purges Players with 0 Kills and 0 Damage Delt in all MAP Data Files
void delplayer() {

    clearall();          // GUI Refresh
    char title[50] = "Removing Players with No Statistics . . . ";
    drawtop(title,11,0,19);

    MAPNAMEREC map;       // Handle to Map Struct
    PLAYERREC  player;      // Handle to Player Struct

    //struct ListItem13 *p;     // List13 For Faster Player Purging

    strcpy(CURRMAP,MAPNAME);  // Get Current Map Name

    int      mapidx       = 0, // Map Index for Current Map
            idx              = 0, // Player Index in Current Map
            count         = 0, // New Player Index
            total        = 0, // Total Players in Current Map
            totalmaps    = countmaps(), // Total # Of Maps
            totalplayers = 0; // New Total Players After all Purging

    double  p1 = 0, // Top Percentage
            p2 = 0; // Left Perfectage

    long    Totalkills   = 0;

    string  name;            // Handle to Players Name
    char    rtext[20]={0};   // GUI Text
    char    rtext2[20]={0};  // GUI Text

    while(mapidx != totalmaps) {
          clearallleft();
        // Draw and Setup Percentage Bar
        p1 = compwkillpercent1(mapidx,totalmaps);
        if (p1 > 99) p1 = 95; // Don't show 100 till finished!
        percenttop(p1);
        // Get Current / Next Map
        readm(&map,mapidx);
        strcpy(MAPNAME,map.name);

         idx   = 0;
        count = 0;
        total = countpidx();

        // Draw Update to GUI
        sprintf(rtext,"Map: %s",MAPNAME);
         drawleft(rtext,3,0);

        while(readp(&player,idx)){
            totalplayers = countpidx();
            p2 = compwkillpercent1(idx,totalplayers);
            percentleft(p2);

            // Add up users total kills for Both Teams
            Totalkills  = 0;
            Totalkills  = player.redforce.player2.kills + player.blueforce.player2.kills;

            // Remove any Users with Freshmeat in their name!
            name = '\0';
            name = player.playername;

            //Name Not Found... and Not 0 Kills...
            if (name.find("reshmeat",0) == -1) {
                // Make Sure Player has Kills to be Registered
                if (Totalkills != 0) {
                    save_player_temp(&player);
                    ++count;
                }
            }
            memset(&player,0,sizeof(PLAYERREC));
            ++idx;
        }
        ++mapidx;
        restore_player_data();

        total = countpidx();
        percentleft(100);
        sprintf(rtext2,"%i of %i Removed!",totalplayers - total,totalplayers);
        drawleft2(rtext2,9,0);

        // Pause GUI for 1 Second
        #ifdef _WIN32
        Sleep(1000);
        #else
        system("sleep 1s");
        #endif
    }
    percenttop(100);
    #ifdef _WIN32
    Sleep(1000);
    #else
    system("sleep 1s");
       #endif
    return;
}

/*--------------------------------------------------------------------------------*/
// Add New Playername to STRUCTURE AND player.dat
void addplayer(char * name) {

        PLAYERREC player;

        if(pdataexists() == false) {
                cout << "Can't Generate MapName.dat for Holding Player Data...";
                exit(1);   // Exit Program if Error Occurs
        }

        if(pidxdataexists() == false) {
                cout << "Can't Generate MapName.idx for Holding Player Data...";
                exit(1);   // Exit Program if Error Occurs
        }

        int idx = countpidx();

        strcpy(player.playername, name);

        // Adds LogName to Database log.dat
        if (matchpidx(player.playername) != true) {

        addpidx(name,idx);  // Add Player Name for Indexing

        memset(&player,0,sizeof(PLAYERREC));
        strcpy(player.playername, name);
        player.index = idx;
        player.rank  = 0;

        strcpy(player.redforce.player2.weapon.m203.name, "M-203");
        strcpy(player.redforce.player2.weapon.famas.name, "FA-MAS");
        strcpy(player.redforce.player2.weapon.g36e.name, "H&K G36E");
        strcpy(player.redforce.player2.weapon.benelli.name, "BENELLI M3 SUPER 90 P");
        strcpy(player.redforce.player2.weapon.saiga.name, "SAIGA 12K");
        strcpy(player.redforce.player2.weapon.m16.name, "M-16A2");
        strcpy(player.redforce.player2.weapon.ak47.name, "AK-47");
        strcpy(player.redforce.player2.weapon.m82.name, "BARRET M82A1");
        strcpy(player.redforce.player2.weapon.bizon.name, "BIZON-2");
        strcpy(player.redforce.player2.weapon.knife.name, "COMBAT KNIFE");
        strcpy(player.redforce.player2.weapon.coltgov.name, "COLT 1911");
        strcpy(player.redforce.player2.weapon.ber92f.name, "BERETTA 92F");
        strcpy(player.redforce.player2.weapon.ber93r.name, "BERETTA 93R");
        strcpy(player.redforce.player2.weapon.desert.name, "IMI DESERT EAGLE");
        strcpy(player.redforce.player2.weapon.anaconda.name, "COLT ANACONDA");
        strcpy(player.redforce.player2.weapon.stg24.name, "STIELHANDGRANATE");
        strcpy(player.redforce.player2.weapon.claymore.name, "M81 CLAYMORE");
        strcpy(player.redforce.player2.weapon.sterling.name, "STERLING L2A3MK4");
        strcpy(player.redforce.player2.weapon.mp5a5.name, "H&K MP5A2-MP5SD2");
        strcpy(player.redforce.player2.weapon.g3a3.name, "H&K G3A3");
        strcpy(player.redforce.player2.weapon.m60.name, "M-60");
        strcpy(player.redforce.player2.weapon.m79.name, "M-79");
        strcpy(player.redforce.player2.weapon.uzi.name, "IMI UZI");
        strcpy(player.redforce.player2.weapon.pkm.name, "PKM");
        strcpy(player.redforce.player2.weapon.ak74.name, "AK-74");
        strcpy(player.redforce.player2.weapon.svd.name, "SVD DRAGUNOV");
        strcpy(player.redforce.player2.weapon.gp25.name, "GP-25");
        strcpy(player.redforce.player2.weapon.ssg3000.name, "SIG SSG-3000");
        strcpy(player.redforce.player2.weapon.frag.name, "M61-FRAG GRENADE");
        strcpy(player.redforce.player2.weapon.weapmortar.name, "MORTAR");
        strcpy(player.redforce.player2.weapon.spark_shower.name, "SPARK SHOWER");
        strcpy(player.redforce.player2.weapon.monster_mortar.name, "MONSTER MORTAR");
        strcpy(player.redforce.player2.weapon.func_tank.name, "TANK");
        strcpy(player.redforce.player2.weapon.env_explosion.name, "EXPLOSION");
        strcpy(player.redforce.player2.weapon.concussion.name, "CONCUSSION GRENADE");
        strcpy(player.redforce.player2.weapon.ammobox.name, "AMMO BOX");

        strcpy(player.blueforce.player2.weapon.m203.name, "M-203");
        strcpy(player.blueforce.player2.weapon.famas.name, "FA-MAS");
        strcpy(player.blueforce.player2.weapon.g36e.name, "H&K G36E");
        strcpy(player.blueforce.player2.weapon.benelli.name, "BENELLI M3 SUPER 90 P");
        strcpy(player.blueforce.player2.weapon.saiga.name, "SAIGA 12K");
        strcpy(player.blueforce.player2.weapon.m16.name, "M-16A2");
        strcpy(player.blueforce.player2.weapon.ak47.name, "AK-47");
        strcpy(player.blueforce.player2.weapon.m82.name, "BARRET M82A1");
        strcpy(player.blueforce.player2.weapon.bizon.name, "BIZON-2");
        strcpy(player.blueforce.player2.weapon.knife.name, "COMBAT KNIFE");
        strcpy(player.blueforce.player2.weapon.coltgov.name, "COLT 1911");
        strcpy(player.blueforce.player2.weapon.ber92f.name, "BERETTA 92F");
        strcpy(player.blueforce.player2.weapon.ber93r.name, "BERETTA 93R");
        strcpy(player.blueforce.player2.weapon.desert.name, "IMI DESERT EAGLE");
        strcpy(player.blueforce.player2.weapon.anaconda.name, "COLT ANACONDA");
        strcpy(player.blueforce.player2.weapon.stg24.name, "STIELHANDGRANATE");
        strcpy(player.blueforce.player2.weapon.claymore.name, "M81 CLAYMORE");
        strcpy(player.blueforce.player2.weapon.sterling.name, "STERLING L2A3MK4");
        strcpy(player.blueforce.player2.weapon.mp5a5.name, "H&K MP5A2-MP5SD2");
        strcpy(player.blueforce.player2.weapon.g3a3.name, "H&K G3A3");
        strcpy(player.blueforce.player2.weapon.m60.name, "M-60");
        strcpy(player.blueforce.player2.weapon.m79.name, "M-79");
        strcpy(player.blueforce.player2.weapon.uzi.name, "IMI UZI");
        strcpy(player.blueforce.player2.weapon.pkm.name, "PKM");
        strcpy(player.blueforce.player2.weapon.ak74.name, "AK-74");
        strcpy(player.blueforce.player2.weapon.svd.name, "SVD DRAGUNOV");
        strcpy(player.blueforce.player2.weapon.gp25.name, "GP-25");
        strcpy(player.blueforce.player2.weapon.ssg3000.name, "SIG SSG-3000");
        strcpy(player.blueforce.player2.weapon.frag.name, "M61-FRAG GRENADE");
        strcpy(player.blueforce.player2.weapon.weapmortar.name, "MORTAR");
        strcpy(player.blueforce.player2.weapon.spark_shower.name, "SPARK SHOWER");
        strcpy(player.blueforce.player2.weapon.monster_mortar.name, "MONSTER MORTAR");
        strcpy(player.blueforce.player2.weapon.func_tank.name, "TANK");
        strcpy(player.blueforce.player2.weapon.env_explosion.name, "EXPLOSION");
        strcpy(player.blueforce.player2.weapon.concussion.name, "CONCUSSION GRENADE");
        strcpy(player.blueforce.player2.weapon.ammobox.name, "AMMO BOX");
        writep(&player,idx);  // Writes Defaults to *Mapname*.dat
        return;
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Checks if Player.dat file exists,  if not Creates it
bool pdataexists() {

    string path = PATH;
    string map  = MAPNAME;

    #ifdef _WIN32
    path +="Data\\"+map+".dat";
       #else
      path +="Data/"+map+".dat";
       #endif

    FILE * stream;

    stream=fopen(path.c_str(),"rb+");
    if(stream == NULL) {
        stream=fopen(path.c_str(), "wb");
        if(stream == NULL) {
            fprintf(stderr, "Error Creating MapName.dat!\n");
            return false;
        }
    }
    fclose(stream);
    return true;
}


/*--------------------------------------------------------------------------------*/
// PLAYERRANK.IDX FUNCTIONS - Indexing of Playerrank.dat
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// PLAYERRANK.IDX Write
int writepridx(PLAYERREC2IDX * player, int idx) {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\playerrank.idx";
       #else
      path += "Data/playerrank.idx";
       #endif

    FILE *stream;
    int x=0;

    stream=fopen(path.c_str(),"rb+");         // file test
    if(stream == NULL){
        stream=fopen(path.c_str(), "wb"); // open file Writing
        if(stream == NULL) {
            fprintf(stderr, "Error Creating playerrank.idx!\n");
            return x;
        }
    }
    if(fseek(stream,(long)idx*sizeof(PLAYERREC2IDX),SEEK_SET)==0)
        x = fwrite(player,sizeof(PLAYERREC2IDX),1,stream);
    fclose(stream);
    return x;
}


/*--------------------------------------------------------------------------------*/
//  PLAYERRANK.IDX Reads - I/O Read Any Log by Index Number
int readpridx(PLAYERREC2IDX * player, int idx) {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\playerrank.idx";
       #else
      path += "Data/playerrank.idx";
       #endif

    int x;

    FILE * stream = fopen(path.c_str(), "rb");
    if(fseek(stream,(long)idx*sizeof(PLAYERREC2IDX),SEEK_SET)==0)
        x = fread(player,sizeof(PLAYERREC2IDX),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// Reads player.dat and gets Total number of Players that have been loaded
int countpridx() {

    int i = 0;
    PLAYERREC2IDX player;

    while(readpridx(&player,i++));
    if(i < 1)    i = -1;
    else        i--;
    return(i);
}

/*--------------------------------------------------------------------------------*/
// Find Player record By Matching name - Gets player Index
int findpridx(char * tplayer) {

    int idx = 0;
    string temp1, temp2;
    PLAYERREC2IDX player;

    temp1 = (tplayer);

    while(readpridx(&player,idx)){
        temp2 = (player.name);
        if(temp1 == temp2) return(idx);
        idx++;
    }
    return(-1);
}


/*--------------------------------------------------------------------------------*/
// Function Check if Name already exists in Player.dat
bool matchpridx(char * name) {

    int index=-1;
    index = findpridx(name);
    if (index == -1) return false;
    else return true;
}


/*--------------------------------------------------------------------------------*/
// Checks if PlayerRank.idx file exists,  if not Creates it
bool pridxdataexists() {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\playerrank.idx";
       #else
      path += "Data/playerrank.idx";
       #endif

    FILE * stream;

    stream=fopen(path.c_str(),"rb+");
    if(stream == NULL) {
        stream=fopen(path.c_str(), "wb");
        if(stream == NULL) {
            fprintf(stderr, "Error Creating playerrank.idx!\n");
            return false;
        }
    }
    fclose(stream);
    return true;
}

/*--------------------------------------------------------------------------------*/
// Adds Index
void addpridx(char * name, int idx) {

    PLAYERREC2IDX player;
    strcpy(player.name,name);
    player.index = idx;
    writepridx(&player,idx);
    return;
}


/*--------------------------------------------------------------------------------*/
// PLAYERRANK.DAT FUNCTIONS Contains totals from all map files for overall stats
/*--------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------*/
// PLAYER.DAT Write - I/O Adds logname to Log File
int writeprank(PLAYERREC2 * player, int idx) {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\playerrank.dat";
       #else
    path += "Data/playerrank.dat";
       #endif

    FILE *stream;
    int x=0;

    stream=fopen(path.c_str(),"rb+");         // file test
    if(stream == NULL){
        stream=fopen(path.c_str(), "wb"); // open file Writing
        if(stream == NULL) {
            fprintf(stderr, "Error Creating Player2.dat!\n");
            return x;
        }
    }
    if(fseek(stream,(long)idx*sizeof(PLAYERREC2),SEEK_SET)==0)
        x = fwrite(player,sizeof(PLAYERREC2),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// PLAYER.DAT Reads - I/O Read Any Log by Index Number
int readprank(PLAYERREC2 * player, int idx) {

    string path = PATH;

    #ifdef _LINUX
      path += "Data/playerrank.dat";
       #endif

    #ifdef _WIN32
    path += "Data\\playerrank.dat";
       #endif

    int x;

    FILE * stream = fopen(path.c_str(), "rb");
    if(fseek(stream,(long)idx*sizeof(PLAYERREC2),SEEK_SET)==0)
        x = fread(player,sizeof(PLAYERREC2),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// Checks if PlayerRank.dat file exists,  if not Creates it
bool prankdataexists() {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\playerrank.dat";
       #else
      path += "Data/playerrank.dat";
       #endif

    FILE * stream;

    stream=fopen(path.c_str(),"rb+");
    if(stream == NULL) {
        stream=fopen(path.c_str(), "wb");
        if(stream == NULL) {
            fprintf(stderr, "Error Creating playerrank.dat!\n");
            return false;
        }
    }
    fclose(stream);
    return true;
}

#endif
