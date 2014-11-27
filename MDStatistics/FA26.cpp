#ifndef __FA26_CPP    /*  An extra safeguard to prevent this header from  */
#define __FA26_CPP    /*  being included twice in the same source file    */

// Main Log Parser..

// This file Processes All Log Files for File Arms v2.6 and Files Structures with Data
// For Processing and Computing Statistics

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

#ifdef _LINUX
#include <sys/types.h>
#include <dirent.h>
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN_AND_MEAN
#include <windows.h>
#include "wincon.h"
#endif

#include "structs.h"     // Player / Weapon / Linklist Structures
#include "PlayerFunc.h"  // Displaying Link list with Players
#include "LogFunc.h"
#include "Mapfunc.h"
#include "FA26.h"

using namespace std;     // Standard C++ Namespace

/*--------------------------------------------------------------------------------*/
// FIREARMS v2.6 LOG PROCESSING FUNCTIONS
/*--------------------------------------------------------------------------------*/

struct ListItem13 *MyList13 = 0 ; // hold all Player Data in memory while parsing logs
struct ListItem16 *MyList16 = 0 ; // Sorting log Names by Creattion

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearplayerdata(void) {

    struct ListItem13 *p,*next;
    if ( MyList13 == 0) return;

    for(p = MyList13 ; p !=0 ; p = next ) {
        next = p->next;
        delete (p);
    }
    MyList13 = 0;
    return;
}


/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearlogdata(void) {

    struct ListItem16 *p, *next;
    if ( MyList16 == 0) return;

    for(p = MyList16 ; p !=0 ; p = next ) {
        next = p->next;
        delete (p);
    }
    MyList16 = 0;
    return;
}


/*--------------------------------------------------------------------------------*/
// Link List for Sorting Log Files by Name to Parse in Creation Order
void lognamesort(LOGNAME * log) {

    struct ListItem16 *next;
    ListItem16 *Item = new ListItem16;

    if ( !Item ) {
        printf ("Malloc Failed \n");
        return;
    }

    Item->log = (*log);
    Item->next = 0;

    if ( MyList16 == 0 ) {
        MyList16 = Item;
        return;
    }

    // Check if the new item comes before the first item in old list
    if(strcmp(log->name,MyList16->log.name) < 0 ) {
        Item->next = MyList16;
        MyList16 = Item;
        return;
    }

    // Check to see if an item is inserted before the next item
    for ( next = MyList16 ; next->next != 0 ; next = next->next ) {
        if (strcmp (log->name, next->next->log.name) < 0 ) {
            // Insert Item before the next Item.
            Item->next = next->next;
            next->next = Item ;
            return;
        }
    }
    // There are no more names ! Add to end
    next->next = Item;
    return;
}


/*--------------------------------------------------------------------------------*/
// PLAYER DATA SORTING
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// This Function Add New Players to the Link List #13 for Log Parsing
bool newplayerdata(string name) {

    struct ListItem13 *p, *last;
    string data;
    for ( p = MyList13 ; p != 0 ; p = p->next ) {
        if (strcmp(p->player.playername,name.c_str()) == 0) return true;
    }

    ListItem13 *item = new ListItem13;
    if( !item ) {
        cout << "Malloc Failed for holding Player Data\n";
        cout << "You do not have enough memory for this program!\n";
        exit(1);
    }

    // If it gets here, no Name Match was found, Add New Player to the Link List with Defaults
    // Creates Player And Sets Record's Defaults all to 0 in Memory.
    memset(&item->player,0,sizeof(PLAYERREC)); // Sets all Records to 0
    strcpy(item->player.playername,name.c_str());
    item->next = 0;

    if ( MyList13 == 0 ) {  // If List is Empty, make this the first item
        MyList13 = item;
        return false;
    }

    for( last = MyList13 ; last->next != 0 ; last = last->next );

    last->next = item;      // Append New Item to Last Item
    return false;
}

/*--------------------------------------------------------------------------------*/
// Percentage bar / For Gui During Processing
double compwkillpercent1(long double wk, long double pk) {

    double p = (0.0);

    if (pk == 0) return (0.0);
    if ( wk > 0 ) {
        if (wk == pk) return (100.0);
        else {
            p = 100 * (wk / pk);
            return p;
        }
    }
    return (0.0);
}

/*--------------------------------------------------------------------------------*/
// This Function Copy's All Player Data From Link List to MAPNAME.DAT
void copyplayerdata() {

    PLAYERREC player;
    MAPNAMEREC map;

    struct ListItem13 *p;
     int tempidx, idx;

    double p1       = 0;
    char   p2[5];
    long   counter  = 0,
           recCount = 0;

    // for Percentage
    for ( p = MyList13 ; p != 0 ; p = p->next ) { ++recCount; }

    clearpercentright();

    // Do Testing if player name is in list, Update it with New Data
    for ( p = MyList13 ; p != 0 ; p = p->next ) {

        addplayer(p->player.playername);
        idx = findpidx(p->player.playername);
        readp(&player,idx);
        ++counter;
        p1 = compwkillpercent1(counter,recCount);

        // Percentage Bar
        percentright(p1);

        // Red Force
        player.redforce.player2.kills                 += p->player.redforce.player2.kills;
        player.redforce.player2.deaths                += p->player.redforce.player2.deaths;
        player.redforce.player2.sui                   += p->player.redforce.player2.sui;
        player.redforce.player2.damdelt               += p->player.redforce.player2.damdelt;
        player.redforce.player2.damrec                += p->player.redforce.player2.damrec;
        player.redforce.player2.dambleed              += p->player.redforce.player2.dambleed;

        player.redforce.player2.weapon.m203.kills            += p->player.redforce.player2.weapon.m203.kills;
        player.redforce.player2.weapon.famas.kills           += p->player.redforce.player2.weapon.famas.kills;
        player.redforce.player2.weapon.g36e.kills            += p->player.redforce.player2.weapon.g36e.kills;
        player.redforce.player2.weapon.benelli.kills         += p->player.redforce.player2.weapon.benelli.kills;
        player.redforce.player2.weapon.saiga.kills           += p->player.redforce.player2.weapon.saiga.kills;
        player.redforce.player2.weapon.m16.kills             += p->player.redforce.player2.weapon.m16.kills;
        player.redforce.player2.weapon.ak47.kills            += p->player.redforce.player2.weapon.ak47.kills;
        player.redforce.player2.weapon.m82.kills             += p->player.redforce.player2.weapon.m82.kills;
        player.redforce.player2.weapon.bizon.kills           += p->player.redforce.player2.weapon.bizon.kills;
        player.redforce.player2.weapon.knife.kills           += p->player.redforce.player2.weapon.knife.kills;
        player.redforce.player2.weapon.coltgov.kills         += p->player.redforce.player2.weapon.coltgov.kills;
        player.redforce.player2.weapon.ber92f.kills          += p->player.redforce.player2.weapon.ber92f.kills;
        player.redforce.player2.weapon.ber93r.kills          += p->player.redforce.player2.weapon.ber93r.kills;
        player.redforce.player2.weapon.desert.kills          += p->player.redforce.player2.weapon.desert.kills;
        player.redforce.player2.weapon.anaconda.kills        += p->player.redforce.player2.weapon.anaconda.kills;
        player.redforce.player2.weapon.stg24.kills           += p->player.redforce.player2.weapon.stg24.kills;
        player.redforce.player2.weapon.claymore.kills        += p->player.redforce.player2.weapon.claymore.kills;
        player.redforce.player2.weapon.sterling.kills        += p->player.redforce.player2.weapon.sterling.kills;
        player.redforce.player2.weapon.mp5a5.kills           += p->player.redforce.player2.weapon.mp5a5.kills;
        player.redforce.player2.weapon.g3a3.kills            += p->player.redforce.player2.weapon.g3a3.kills;
        player.redforce.player2.weapon.m60.kills             += p->player.redforce.player2.weapon.m60.kills;
        player.redforce.player2.weapon.m79.kills             += p->player.redforce.player2.weapon.m79.kills;
        player.redforce.player2.weapon.frag.kills            += p->player.redforce.player2.weapon.frag.kills;
        player.redforce.player2.weapon.uzi.kills             += p->player.redforce.player2.weapon.uzi.kills;
        player.redforce.player2.weapon.pkm.kills             += p->player.redforce.player2.weapon.pkm.kills;
        player.redforce.player2.weapon.ak74.kills            += p->player.redforce.player2.weapon.ak74.kills;
        player.redforce.player2.weapon.svd.kills             += p->player.redforce.player2.weapon.svd.kills;
        player.redforce.player2.weapon.gp25.kills            += p->player.redforce.player2.weapon.gp25.kills;
        player.redforce.player2.weapon.ssg3000.kills         += p->player.redforce.player2.weapon.ssg3000.kills;
        player.redforce.player2.weapon.weapmortar.kills      += p->player.redforce.player2.weapon.weapmortar.kills;
        player.redforce.player2.weapon.spark_shower.kills    += p->player.redforce.player2.weapon.spark_shower.kills;
        player.redforce.player2.weapon.monster_mortar.kills  += p->player.redforce.player2.weapon.monster_mortar.kills;
        player.redforce.player2.weapon.func_tank.kills       += p->player.redforce.player2.weapon.func_tank.kills;
        player.redforce.player2.weapon.env_explosion.kills   += p->player.redforce.player2.weapon.env_explosion.kills;
        player.redforce.player2.weapon.concussion.kills      += p->player.redforce.player2.weapon.concussion.kills;
        player.redforce.player2.weapon.ammobox.kills         += p->player.redforce.player2.weapon.ammobox.kills;

        player.redforce.player2.weapon.m203.deaths           += p->player.redforce.player2.weapon.m203.deaths;
        player.redforce.player2.weapon.famas.deaths          += p->player.redforce.player2.weapon.famas.deaths;
        player.redforce.player2.weapon.g36e.deaths           += p->player.redforce.player2.weapon.g36e.deaths;
        player.redforce.player2.weapon.benelli.deaths        += p->player.redforce.player2.weapon.benelli.deaths;
        player.redforce.player2.weapon.saiga.deaths          += p->player.redforce.player2.weapon.saiga.deaths;
        player.redforce.player2.weapon.m16.deaths            += p->player.redforce.player2.weapon.m16.deaths;
        player.redforce.player2.weapon.ak47.deaths           += p->player.redforce.player2.weapon.ak47.deaths;
        player.redforce.player2.weapon.m82.deaths            += p->player.redforce.player2.weapon.m82.deaths;
        player.redforce.player2.weapon.bizon.deaths          += p->player.redforce.player2.weapon.bizon.deaths;
        player.redforce.player2.weapon.knife.deaths          += p->player.redforce.player2.weapon.knife.deaths;
        player.redforce.player2.weapon.coltgov.deaths        += p->player.redforce.player2.weapon.coltgov.deaths;
        player.redforce.player2.weapon.ber92f.deaths         += p->player.redforce.player2.weapon.ber92f.deaths;
        player.redforce.player2.weapon.ber93r.deaths         += p->player.redforce.player2.weapon.ber93r.deaths;
        player.redforce.player2.weapon.desert.deaths         += p->player.redforce.player2.weapon.desert.deaths;
        player.redforce.player2.weapon.anaconda.deaths       += p->player.redforce.player2.weapon.anaconda.deaths;
        player.redforce.player2.weapon.stg24.deaths          += p->player.redforce.player2.weapon.stg24.deaths;
        player.redforce.player2.weapon.claymore.deaths       += p->player.redforce.player2.weapon.claymore.deaths;
        player.redforce.player2.weapon.sterling.deaths       += p->player.redforce.player2.weapon.sterling.deaths;
        player.redforce.player2.weapon.mp5a5.deaths          += p->player.redforce.player2.weapon.mp5a5.deaths;
        player.redforce.player2.weapon.g3a3.deaths           += p->player.redforce.player2.weapon.g3a3.deaths;
        player.redforce.player2.weapon.m60.deaths            += p->player.redforce.player2.weapon.m60.deaths;
        player.redforce.player2.weapon.m79.deaths            += p->player.redforce.player2.weapon.m79.deaths;
        player.redforce.player2.weapon.frag.deaths           += p->player.redforce.player2.weapon.frag.deaths;
        player.redforce.player2.weapon.uzi.deaths            += p->player.redforce.player2.weapon.uzi.deaths;
        player.redforce.player2.weapon.pkm.deaths            += p->player.redforce.player2.weapon.pkm.deaths;
        player.redforce.player2.weapon.ak74.deaths           += p->player.redforce.player2.weapon.ak74.deaths;
        player.redforce.player2.weapon.svd.deaths            += p->player.redforce.player2.weapon.svd.deaths;
        player.redforce.player2.weapon.gp25.deaths           += p->player.redforce.player2.weapon.gp25.deaths;
        player.redforce.player2.weapon.ssg3000.deaths        += p->player.redforce.player2.weapon.ssg3000.deaths;
        player.redforce.player2.weapon.weapmortar.deaths     += p->player.redforce.player2.weapon.weapmortar.deaths;
        player.redforce.player2.weapon.spark_shower.deaths   += p->player.redforce.player2.weapon.spark_shower.deaths;
        player.redforce.player2.weapon.monster_mortar.deaths += p->player.redforce.player2.weapon.monster_mortar.deaths;
        player.redforce.player2.weapon.func_tank.deaths      += p->player.redforce.player2.weapon.func_tank.deaths;
        player.redforce.player2.weapon.env_explosion.deaths  += p->player.redforce.player2.weapon.env_explosion.deaths;
        player.redforce.player2.weapon.concussion.deaths     += p->player.redforce.player2.weapon.concussion.deaths;
        player.redforce.player2.weapon.ammobox.deaths        += p->player.redforce.player2.weapon.ammobox.deaths;

        player.redforce.player2.weapon.m203.sui              += p->player.redforce.player2.weapon.m203.sui;
        player.redforce.player2.weapon.famas.sui             += p->player.redforce.player2.weapon.famas.sui;
        player.redforce.player2.weapon.g36e.sui              += p->player.redforce.player2.weapon.g36e.sui;
        player.redforce.player2.weapon.benelli.sui           += p->player.redforce.player2.weapon.benelli.sui;
        player.redforce.player2.weapon.saiga.sui             += p->player.redforce.player2.weapon.saiga.sui;
        player.redforce.player2.weapon.m16.sui               += p->player.redforce.player2.weapon.m16.sui;
        player.redforce.player2.weapon.ak47.sui              += p->player.redforce.player2.weapon.ak47.sui;
        player.redforce.player2.weapon.m82.sui               += p->player.redforce.player2.weapon.m82.sui;
        player.redforce.player2.weapon.bizon.sui             += p->player.redforce.player2.weapon.bizon.sui;
        player.redforce.player2.weapon.knife.sui             += p->player.redforce.player2.weapon.knife.sui;
        player.redforce.player2.weapon.coltgov.sui           += p->player.redforce.player2.weapon.coltgov.sui;
        player.redforce.player2.weapon.ber92f.sui            += p->player.redforce.player2.weapon.ber92f.sui;
        player.redforce.player2.weapon.ber93r.sui            += p->player.redforce.player2.weapon.ber93r.sui;
        player.redforce.player2.weapon.desert.sui            += p->player.redforce.player2.weapon.desert.sui;
        player.redforce.player2.weapon.anaconda.sui          += p->player.redforce.player2.weapon.anaconda.sui;
        player.redforce.player2.weapon.stg24.sui             += p->player.redforce.player2.weapon.stg24.sui;
        player.redforce.player2.weapon.claymore.sui          += p->player.redforce.player2.weapon.claymore.sui;
        player.redforce.player2.weapon.sterling.sui          += p->player.redforce.player2.weapon.sterling.sui;
        player.redforce.player2.weapon.mp5a5.sui             += p->player.redforce.player2.weapon.mp5a5.sui;
        player.redforce.player2.weapon.g3a3.sui              += p->player.redforce.player2.weapon.g3a3.sui;
        player.redforce.player2.weapon.m60.sui               += p->player.redforce.player2.weapon.m60.sui;
        player.redforce.player2.weapon.m79.sui               += p->player.redforce.player2.weapon.m79.sui;
        player.redforce.player2.weapon.frag.sui              += p->player.redforce.player2.weapon.frag.sui;
        player.redforce.player2.weapon.uzi.sui               += p->player.redforce.player2.weapon.uzi.sui;
        player.redforce.player2.weapon.pkm.sui               += p->player.redforce.player2.weapon.pkm.sui;
        player.redforce.player2.weapon.ak74.sui              += p->player.redforce.player2.weapon.ak74.sui;
        player.redforce.player2.weapon.svd.sui               += p->player.redforce.player2.weapon.svd.sui;
        player.redforce.player2.weapon.gp25.sui              += p->player.redforce.player2.weapon.gp25.sui;
        player.redforce.player2.weapon.ssg3000.sui           += p->player.redforce.player2.weapon.ssg3000.sui;
        player.redforce.player2.weapon.weapmortar.sui        += p->player.redforce.player2.weapon.weapmortar.sui;
        player.redforce.player2.weapon.spark_shower.sui      += p->player.redforce.player2.weapon.spark_shower.sui;
        player.redforce.player2.weapon.monster_mortar.sui    += p->player.redforce.player2.weapon.monster_mortar.sui;
        player.redforce.player2.weapon.func_tank.sui         += p->player.redforce.player2.weapon.func_tank.sui;
        player.redforce.player2.weapon.env_explosion.sui     += p->player.redforce.player2.weapon.env_explosion.sui;
        player.redforce.player2.weapon.concussion.sui        += p->player.redforce.player2.weapon.concussion.sui;
        player.redforce.player2.weapon.ammobox.sui           += p->player.redforce.player2.weapon.ammobox.sui;

        player.redforce.player2.weapon.m203.damdelt          += p->player.redforce.player2.weapon.m203.damdelt;
        player.redforce.player2.weapon.famas.damdelt         += p->player.redforce.player2.weapon.famas.damdelt;
        player.redforce.player2.weapon.g36e.damdelt          += p->player.redforce.player2.weapon.g36e.damdelt;
        player.redforce.player2.weapon.benelli.damdelt       += p->player.redforce.player2.weapon.benelli.damdelt;
        player.redforce.player2.weapon.saiga.damdelt         += p->player.redforce.player2.weapon.saiga.damdelt;
        player.redforce.player2.weapon.m16.damdelt           += p->player.redforce.player2.weapon.m16.damdelt;
        player.redforce.player2.weapon.ak47.damdelt          += p->player.redforce.player2.weapon.ak47.damdelt;
        player.redforce.player2.weapon.m82.damdelt           += p->player.redforce.player2.weapon.m82.damdelt;
        player.redforce.player2.weapon.bizon.damdelt         += p->player.redforce.player2.weapon.bizon.damdelt;
        player.redforce.player2.weapon.knife.damdelt         += p->player.redforce.player2.weapon.knife.damdelt;
        player.redforce.player2.weapon.coltgov.damdelt       += p->player.redforce.player2.weapon.coltgov.damdelt;
        player.redforce.player2.weapon.ber92f.damdelt        += p->player.redforce.player2.weapon.ber92f.damdelt;
        player.redforce.player2.weapon.ber93r.damdelt        += p->player.redforce.player2.weapon.ber93r.damdelt;
        player.redforce.player2.weapon.desert.damdelt        += p->player.redforce.player2.weapon.desert.damdelt;
        player.redforce.player2.weapon.anaconda.damdelt      += p->player.redforce.player2.weapon.anaconda.damdelt;
        player.redforce.player2.weapon.stg24.damdelt         += p->player.redforce.player2.weapon.stg24.damdelt;
        player.redforce.player2.weapon.claymore.damdelt      += p->player.redforce.player2.weapon.claymore.damdelt;
        player.redforce.player2.weapon.sterling.damdelt      += p->player.redforce.player2.weapon.sterling.damdelt;
        player.redforce.player2.weapon.mp5a5.damdelt         += p->player.redforce.player2.weapon.mp5a5.damdelt;
        player.redforce.player2.weapon.g3a3.damdelt          += p->player.redforce.player2.weapon.g3a3.damdelt;
        player.redforce.player2.weapon.m60.damdelt           += p->player.redforce.player2.weapon.m60.damdelt;
        player.redforce.player2.weapon.m79.damdelt           += p->player.redforce.player2.weapon.m79.damdelt;
        player.redforce.player2.weapon.frag.damdelt          += p->player.redforce.player2.weapon.frag.damdelt;
        player.redforce.player2.weapon.uzi.damdelt           += p->player.redforce.player2.weapon.uzi.damdelt;
        player.redforce.player2.weapon.pkm.damdelt           += p->player.redforce.player2.weapon.pkm.damdelt;
        player.redforce.player2.weapon.ak74.damdelt          += p->player.redforce.player2.weapon.ak74.damdelt;
        player.redforce.player2.weapon.svd.damdelt           += p->player.redforce.player2.weapon.svd.damdelt;
        player.redforce.player2.weapon.gp25.damdelt          += p->player.redforce.player2.weapon.gp25.damdelt;
        player.redforce.player2.weapon.ssg3000.damdelt       += p->player.redforce.player2.weapon.ssg3000.damdelt;
        player.redforce.player2.weapon.weapmortar.damdelt    += p->player.redforce.player2.weapon.weapmortar.damdelt;
        player.redforce.player2.weapon.spark_shower.damdelt  += p->player.redforce.player2.weapon.spark_shower.damdelt;
        player.redforce.player2.weapon.monster_mortar.damdelt+= p->player.redforce.player2.weapon.monster_mortar.damdelt;
        player.redforce.player2.weapon.func_tank.damdelt     += p->player.redforce.player2.weapon.func_tank.damdelt;
        player.redforce.player2.weapon.env_explosion.damdelt += p->player.redforce.player2.weapon.env_explosion.damdelt;
        player.redforce.player2.weapon.concussion.damdelt    += p->player.redforce.player2.weapon.concussion.damdelt;
        player.redforce.player2.weapon.ammobox.damdelt       += p->player.redforce.player2.weapon.ammobox.damdelt;

        player.redforce.player2.weapon.m203.damrec           += p->player.redforce.player2.weapon.m203.damrec;
        player.redforce.player2.weapon.famas.damrec          += p->player.redforce.player2.weapon.famas.damrec;
        player.redforce.player2.weapon.g36e.damrec           += p->player.redforce.player2.weapon.g36e.damrec;
        player.redforce.player2.weapon.benelli.damrec        += p->player.redforce.player2.weapon.benelli.damrec;
        player.redforce.player2.weapon.saiga.damrec          += p->player.redforce.player2.weapon.saiga.damrec;
        player.redforce.player2.weapon.m16.damrec            += p->player.redforce.player2.weapon.m16.damrec;
        player.redforce.player2.weapon.ak47.damrec           += p->player.redforce.player2.weapon.ak47.damrec;
        player.redforce.player2.weapon.m82.damrec            += p->player.redforce.player2.weapon.m82.damrec;
        player.redforce.player2.weapon.bizon.damrec          += p->player.redforce.player2.weapon.bizon.damrec;
        player.redforce.player2.weapon.knife.damrec          += p->player.redforce.player2.weapon.knife.damrec;
        player.redforce.player2.weapon.coltgov.damrec        += p->player.redforce.player2.weapon.coltgov.damrec;
        player.redforce.player2.weapon.ber92f.damrec         += p->player.redforce.player2.weapon.ber92f.damrec;
        player.redforce.player2.weapon.ber93r.damrec         += p->player.redforce.player2.weapon.ber93r.damrec;
        player.redforce.player2.weapon.desert.damrec         += p->player.redforce.player2.weapon.desert.damrec;
        player.redforce.player2.weapon.anaconda.damrec       += p->player.redforce.player2.weapon.anaconda.damrec;
        player.redforce.player2.weapon.stg24.damrec          += p->player.redforce.player2.weapon.stg24.damrec;
        player.redforce.player2.weapon.claymore.damrec       += p->player.redforce.player2.weapon.claymore.damrec;
        player.redforce.player2.weapon.sterling.damrec       += p->player.redforce.player2.weapon.sterling.damrec;
        player.redforce.player2.weapon.mp5a5.damrec          += p->player.redforce.player2.weapon.mp5a5.damrec;
        player.redforce.player2.weapon.g3a3.damrec           += p->player.redforce.player2.weapon.g3a3.damrec;
        player.redforce.player2.weapon.m60.damrec            += p->player.redforce.player2.weapon.m60.damrec;
        player.redforce.player2.weapon.m79.damrec            += p->player.redforce.player2.weapon.m79.damrec;
        player.redforce.player2.weapon.frag.damrec           += p->player.redforce.player2.weapon.frag.damrec;
        player.redforce.player2.weapon.uzi.damrec            += p->player.redforce.player2.weapon.uzi.damrec;
        player.redforce.player2.weapon.pkm.damrec            += p->player.redforce.player2.weapon.pkm.damrec;
        player.redforce.player2.weapon.ak74.damrec           += p->player.redforce.player2.weapon.ak74.damrec;
        player.redforce.player2.weapon.svd.damrec            += p->player.redforce.player2.weapon.svd.damrec;
        player.redforce.player2.weapon.gp25.damrec           += p->player.redforce.player2.weapon.gp25.damrec;
        player.redforce.player2.weapon.ssg3000.damrec        += p->player.redforce.player2.weapon.ssg3000.damrec;
        player.redforce.player2.weapon.weapmortar.damrec     += p->player.redforce.player2.weapon.weapmortar.damrec;
        player.redforce.player2.weapon.spark_shower.damrec   += p->player.redforce.player2.weapon.spark_shower.damrec;
        player.redforce.player2.weapon.monster_mortar.damrec += p->player.redforce.player2.weapon.monster_mortar.damrec;
        player.redforce.player2.weapon.func_tank.damrec      += p->player.redforce.player2.weapon.func_tank.damrec;
        player.redforce.player2.weapon.env_explosion.damrec  += p->player.redforce.player2.weapon.env_explosion.damrec;
        player.redforce.player2.weapon.concussion.damrec     += p->player.redforce.player2.weapon.concussion.damrec;
        player.redforce.player2.weapon.ammobox.damrec        += p->player.redforce.player2.weapon.ammobox.damrec;


        // Blue Force
        player.blueforce.player2.kills                 += p->player.blueforce.player2.kills;
        player.blueforce.player2.deaths                += p->player.blueforce.player2.deaths;
        player.blueforce.player2.sui                   += p->player.blueforce.player2.sui;
        player.blueforce.player2.damdelt               += p->player.blueforce.player2.damdelt;
        player.blueforce.player2.damrec                += p->player.blueforce.player2.damrec;
        player.blueforce.player2.dambleed              += p->player.blueforce.player2.dambleed;

        player.blueforce.player2.weapon.m203.kills            += p->player.blueforce.player2.weapon.m203.kills;
        player.blueforce.player2.weapon.famas.kills           += p->player.blueforce.player2.weapon.famas.kills;
        player.blueforce.player2.weapon.g36e.kills            += p->player.blueforce.player2.weapon.g36e.kills;
        player.blueforce.player2.weapon.benelli.kills         += p->player.blueforce.player2.weapon.benelli.kills;
        player.blueforce.player2.weapon.saiga.kills           += p->player.blueforce.player2.weapon.saiga.kills;
        player.blueforce.player2.weapon.m16.kills             += p->player.blueforce.player2.weapon.m16.kills;
        player.blueforce.player2.weapon.ak47.kills            += p->player.blueforce.player2.weapon.ak47.kills;
        player.blueforce.player2.weapon.m82.kills             += p->player.blueforce.player2.weapon.m82.kills;
        player.blueforce.player2.weapon.bizon.kills           += p->player.blueforce.player2.weapon.bizon.kills;
        player.blueforce.player2.weapon.knife.kills           += p->player.blueforce.player2.weapon.knife.kills;
        player.blueforce.player2.weapon.coltgov.kills         += p->player.blueforce.player2.weapon.coltgov.kills;
        player.blueforce.player2.weapon.ber92f.kills          += p->player.blueforce.player2.weapon.ber92f.kills;
        player.blueforce.player2.weapon.ber93r.kills          += p->player.blueforce.player2.weapon.ber93r.kills;
        player.blueforce.player2.weapon.desert.kills          += p->player.blueforce.player2.weapon.desert.kills;
        player.blueforce.player2.weapon.anaconda.kills        += p->player.blueforce.player2.weapon.anaconda.kills;
        player.blueforce.player2.weapon.stg24.kills           += p->player.blueforce.player2.weapon.stg24.kills;
        player.blueforce.player2.weapon.claymore.kills        += p->player.blueforce.player2.weapon.claymore.kills;
        player.blueforce.player2.weapon.sterling.kills        += p->player.blueforce.player2.weapon.sterling.kills;
        player.blueforce.player2.weapon.mp5a5.kills           += p->player.blueforce.player2.weapon.mp5a5.kills;
        player.blueforce.player2.weapon.g3a3.kills            += p->player.blueforce.player2.weapon.g3a3.kills;
        player.blueforce.player2.weapon.m60.kills             += p->player.blueforce.player2.weapon.m60.kills;
        player.blueforce.player2.weapon.m79.kills             += p->player.blueforce.player2.weapon.m79.kills;
        player.blueforce.player2.weapon.frag.kills            += p->player.blueforce.player2.weapon.frag.kills;
        player.blueforce.player2.weapon.uzi.kills             += p->player.blueforce.player2.weapon.uzi.kills;
        player.blueforce.player2.weapon.pkm.kills             += p->player.blueforce.player2.weapon.pkm.kills;
        player.blueforce.player2.weapon.ak74.kills            += p->player.blueforce.player2.weapon.ak74.kills;
        player.blueforce.player2.weapon.svd.kills             += p->player.blueforce.player2.weapon.svd.kills;
        player.blueforce.player2.weapon.gp25.kills            += p->player.blueforce.player2.weapon.gp25.kills;
        player.blueforce.player2.weapon.ssg3000.kills         += p->player.blueforce.player2.weapon.ssg3000.kills;
        player.blueforce.player2.weapon.weapmortar.kills      += p->player.blueforce.player2.weapon.weapmortar.kills;
        player.blueforce.player2.weapon.spark_shower.kills    += p->player.blueforce.player2.weapon.spark_shower.kills;
        player.blueforce.player2.weapon.monster_mortar.kills  += p->player.blueforce.player2.weapon.monster_mortar.kills;
        player.blueforce.player2.weapon.func_tank.kills       += p->player.blueforce.player2.weapon.func_tank.kills;
        player.blueforce.player2.weapon.env_explosion.kills   += p->player.blueforce.player2.weapon.env_explosion.kills;
        player.blueforce.player2.weapon.concussion.kills      += p->player.blueforce.player2.weapon.concussion.kills;
        player.blueforce.player2.weapon.ammobox.kills         += p->player.blueforce.player2.weapon.ammobox.kills;

        player.blueforce.player2.weapon.m203.deaths           += p->player.blueforce.player2.weapon.m203.deaths;
        player.blueforce.player2.weapon.famas.deaths          += p->player.blueforce.player2.weapon.famas.deaths;
        player.blueforce.player2.weapon.g36e.deaths           += p->player.blueforce.player2.weapon.g36e.deaths;
        player.blueforce.player2.weapon.benelli.deaths        += p->player.blueforce.player2.weapon.benelli.deaths;
        player.blueforce.player2.weapon.saiga.deaths          += p->player.blueforce.player2.weapon.saiga.deaths;
        player.blueforce.player2.weapon.m16.deaths            += p->player.blueforce.player2.weapon.m16.deaths;
        player.blueforce.player2.weapon.ak47.deaths           += p->player.blueforce.player2.weapon.ak47.deaths;
        player.blueforce.player2.weapon.m82.deaths            += p->player.blueforce.player2.weapon.m82.deaths;
        player.blueforce.player2.weapon.bizon.deaths          += p->player.blueforce.player2.weapon.bizon.deaths;
        player.blueforce.player2.weapon.knife.deaths          += p->player.blueforce.player2.weapon.knife.deaths;
        player.blueforce.player2.weapon.coltgov.deaths        += p->player.blueforce.player2.weapon.coltgov.deaths;
        player.blueforce.player2.weapon.ber92f.deaths         += p->player.blueforce.player2.weapon.ber92f.deaths;
        player.blueforce.player2.weapon.ber93r.deaths         += p->player.blueforce.player2.weapon.ber93r.deaths;
        player.blueforce.player2.weapon.desert.deaths         += p->player.blueforce.player2.weapon.desert.deaths;
        player.blueforce.player2.weapon.anaconda.deaths       += p->player.blueforce.player2.weapon.anaconda.deaths;
        player.blueforce.player2.weapon.stg24.deaths          += p->player.blueforce.player2.weapon.stg24.deaths;
        player.blueforce.player2.weapon.claymore.deaths       += p->player.blueforce.player2.weapon.claymore.deaths;
        player.blueforce.player2.weapon.sterling.deaths       += p->player.blueforce.player2.weapon.sterling.deaths;
        player.blueforce.player2.weapon.mp5a5.deaths          += p->player.blueforce.player2.weapon.mp5a5.deaths;
        player.blueforce.player2.weapon.g3a3.deaths           += p->player.blueforce.player2.weapon.g3a3.deaths;
        player.blueforce.player2.weapon.m60.deaths            += p->player.blueforce.player2.weapon.m60.deaths;
        player.blueforce.player2.weapon.m79.deaths            += p->player.blueforce.player2.weapon.m79.deaths;
        player.blueforce.player2.weapon.frag.deaths           += p->player.blueforce.player2.weapon.frag.deaths;
        player.blueforce.player2.weapon.uzi.deaths            += p->player.blueforce.player2.weapon.uzi.deaths;
        player.blueforce.player2.weapon.pkm.deaths            += p->player.blueforce.player2.weapon.pkm.deaths;
        player.blueforce.player2.weapon.ak74.deaths           += p->player.blueforce.player2.weapon.ak74.deaths;
        player.blueforce.player2.weapon.svd.deaths            += p->player.blueforce.player2.weapon.svd.deaths;
        player.blueforce.player2.weapon.gp25.deaths           += p->player.blueforce.player2.weapon.gp25.deaths;
        player.blueforce.player2.weapon.ssg3000.deaths        += p->player.blueforce.player2.weapon.ssg3000.deaths;
        player.blueforce.player2.weapon.weapmortar.deaths     += p->player.blueforce.player2.weapon.weapmortar.deaths;
        player.blueforce.player2.weapon.spark_shower.deaths   += p->player.blueforce.player2.weapon.spark_shower.deaths;
        player.blueforce.player2.weapon.monster_mortar.deaths += p->player.blueforce.player2.weapon.monster_mortar.deaths;
        player.blueforce.player2.weapon.func_tank.deaths      += p->player.blueforce.player2.weapon.func_tank.deaths;
        player.blueforce.player2.weapon.env_explosion.deaths  += p->player.blueforce.player2.weapon.env_explosion.deaths;
        player.blueforce.player2.weapon.concussion.deaths     += p->player.blueforce.player2.weapon.concussion.deaths;
        player.blueforce.player2.weapon.ammobox.deaths        += p->player.blueforce.player2.weapon.ammobox.deaths;

        player.blueforce.player2.weapon.m203.sui              += p->player.blueforce.player2.weapon.m203.sui;
        player.blueforce.player2.weapon.famas.sui             += p->player.blueforce.player2.weapon.famas.sui;
        player.blueforce.player2.weapon.g36e.sui              += p->player.blueforce.player2.weapon.g36e.sui;
        player.blueforce.player2.weapon.benelli.sui           += p->player.blueforce.player2.weapon.benelli.sui;
        player.blueforce.player2.weapon.saiga.sui             += p->player.blueforce.player2.weapon.saiga.sui;
        player.blueforce.player2.weapon.m16.sui               += p->player.blueforce.player2.weapon.m16.sui;
        player.blueforce.player2.weapon.ak47.sui              += p->player.blueforce.player2.weapon.ak47.sui;
        player.blueforce.player2.weapon.m82.sui               += p->player.blueforce.player2.weapon.m82.sui;
        player.blueforce.player2.weapon.bizon.sui             += p->player.blueforce.player2.weapon.bizon.sui;
        player.blueforce.player2.weapon.knife.sui             += p->player.blueforce.player2.weapon.knife.sui;
        player.blueforce.player2.weapon.coltgov.sui           += p->player.blueforce.player2.weapon.coltgov.sui;
        player.blueforce.player2.weapon.ber92f.sui            += p->player.blueforce.player2.weapon.ber92f.sui;
        player.blueforce.player2.weapon.ber93r.sui            += p->player.blueforce.player2.weapon.ber93r.sui;
        player.blueforce.player2.weapon.desert.sui            += p->player.blueforce.player2.weapon.desert.sui;
        player.blueforce.player2.weapon.anaconda.sui          += p->player.blueforce.player2.weapon.anaconda.sui;
        player.blueforce.player2.weapon.stg24.sui             += p->player.blueforce.player2.weapon.stg24.sui;
        player.blueforce.player2.weapon.claymore.sui          += p->player.blueforce.player2.weapon.claymore.sui;
        player.blueforce.player2.weapon.sterling.sui          += p->player.blueforce.player2.weapon.sterling.sui;
        player.blueforce.player2.weapon.mp5a5.sui             += p->player.blueforce.player2.weapon.mp5a5.sui;
        player.blueforce.player2.weapon.g3a3.sui              += p->player.blueforce.player2.weapon.g3a3.sui;
        player.blueforce.player2.weapon.m60.sui               += p->player.blueforce.player2.weapon.m60.sui;
        player.blueforce.player2.weapon.m79.sui               += p->player.blueforce.player2.weapon.m79.sui;
        player.blueforce.player2.weapon.frag.sui              += p->player.blueforce.player2.weapon.frag.sui;
        player.blueforce.player2.weapon.uzi.sui               += p->player.blueforce.player2.weapon.uzi.sui;
        player.blueforce.player2.weapon.pkm.sui               += p->player.blueforce.player2.weapon.pkm.sui;
        player.blueforce.player2.weapon.ak74.sui              += p->player.blueforce.player2.weapon.ak74.sui;
        player.blueforce.player2.weapon.svd.sui               += p->player.blueforce.player2.weapon.svd.sui;
        player.blueforce.player2.weapon.gp25.sui              += p->player.blueforce.player2.weapon.gp25.sui;
        player.blueforce.player2.weapon.ssg3000.sui           += p->player.blueforce.player2.weapon.ssg3000.sui;
        player.blueforce.player2.weapon.weapmortar.sui        += p->player.blueforce.player2.weapon.weapmortar.sui;
        player.blueforce.player2.weapon.spark_shower.sui      += p->player.blueforce.player2.weapon.spark_shower.sui;
        player.blueforce.player2.weapon.monster_mortar.sui    += p->player.blueforce.player2.weapon.monster_mortar.sui;
        player.blueforce.player2.weapon.func_tank.sui         += p->player.blueforce.player2.weapon.func_tank.sui;
        player.blueforce.player2.weapon.env_explosion.sui     += p->player.blueforce.player2.weapon.env_explosion.sui;
        player.blueforce.player2.weapon.concussion.sui        += p->player.blueforce.player2.weapon.concussion.sui;
        player.blueforce.player2.weapon.ammobox.sui           += p->player.blueforce.player2.weapon.ammobox.sui;

        player.blueforce.player2.weapon.m203.damdelt          += p->player.blueforce.player2.weapon.m203.damdelt;
        player.blueforce.player2.weapon.famas.damdelt         += p->player.blueforce.player2.weapon.famas.damdelt;
        player.blueforce.player2.weapon.g36e.damdelt          += p->player.blueforce.player2.weapon.g36e.damdelt;
        player.blueforce.player2.weapon.benelli.damdelt       += p->player.blueforce.player2.weapon.benelli.damdelt;
        player.blueforce.player2.weapon.saiga.damdelt         += p->player.blueforce.player2.weapon.saiga.damdelt;
        player.blueforce.player2.weapon.m16.damdelt           += p->player.blueforce.player2.weapon.m16.damdelt;
        player.blueforce.player2.weapon.ak47.damdelt          += p->player.blueforce.player2.weapon.ak47.damdelt;
        player.blueforce.player2.weapon.m82.damdelt           += p->player.blueforce.player2.weapon.m82.damdelt;
        player.blueforce.player2.weapon.bizon.damdelt         += p->player.blueforce.player2.weapon.bizon.damdelt;
        player.blueforce.player2.weapon.knife.damdelt         += p->player.blueforce.player2.weapon.knife.damdelt;
        player.blueforce.player2.weapon.coltgov.damdelt       += p->player.blueforce.player2.weapon.coltgov.damdelt;
        player.blueforce.player2.weapon.ber92f.damdelt        += p->player.blueforce.player2.weapon.ber92f.damdelt;
        player.blueforce.player2.weapon.ber93r.damdelt        += p->player.blueforce.player2.weapon.ber93r.damdelt;
        player.blueforce.player2.weapon.desert.damdelt        += p->player.blueforce.player2.weapon.desert.damdelt;
        player.blueforce.player2.weapon.anaconda.damdelt      += p->player.blueforce.player2.weapon.anaconda.damdelt;
        player.blueforce.player2.weapon.stg24.damdelt         += p->player.blueforce.player2.weapon.stg24.damdelt;
        player.blueforce.player2.weapon.claymore.damdelt      += p->player.blueforce.player2.weapon.claymore.damdelt;
        player.blueforce.player2.weapon.sterling.damdelt      += p->player.blueforce.player2.weapon.sterling.damdelt;
        player.blueforce.player2.weapon.mp5a5.damdelt         += p->player.blueforce.player2.weapon.mp5a5.damdelt;
        player.blueforce.player2.weapon.g3a3.damdelt          += p->player.blueforce.player2.weapon.g3a3.damdelt;
        player.blueforce.player2.weapon.m60.damdelt           += p->player.blueforce.player2.weapon.m60.damdelt;
        player.blueforce.player2.weapon.m79.damdelt           += p->player.blueforce.player2.weapon.m79.damdelt;
        player.blueforce.player2.weapon.frag.damdelt          += p->player.blueforce.player2.weapon.frag.damdelt;
        player.blueforce.player2.weapon.uzi.damdelt           += p->player.blueforce.player2.weapon.uzi.damdelt;
        player.blueforce.player2.weapon.pkm.damdelt           += p->player.blueforce.player2.weapon.pkm.damdelt;
        player.blueforce.player2.weapon.ak74.damdelt          += p->player.blueforce.player2.weapon.ak74.damdelt;
        player.blueforce.player2.weapon.svd.damdelt           += p->player.blueforce.player2.weapon.svd.damdelt;
        player.blueforce.player2.weapon.gp25.damdelt          += p->player.blueforce.player2.weapon.gp25.damdelt;
        player.blueforce.player2.weapon.ssg3000.damdelt       += p->player.blueforce.player2.weapon.ssg3000.damdelt;
        player.blueforce.player2.weapon.weapmortar.damdelt    += p->player.blueforce.player2.weapon.weapmortar.damdelt;
        player.blueforce.player2.weapon.spark_shower.damdelt  += p->player.blueforce.player2.weapon.spark_shower.damdelt;
        player.blueforce.player2.weapon.monster_mortar.damdelt+= p->player.blueforce.player2.weapon.monster_mortar.damdelt;
        player.blueforce.player2.weapon.func_tank.damdelt     += p->player.blueforce.player2.weapon.func_tank.damdelt;
        player.blueforce.player2.weapon.env_explosion.damdelt += p->player.blueforce.player2.weapon.env_explosion.damdelt;
        player.blueforce.player2.weapon.concussion.damdelt    += p->player.blueforce.player2.weapon.concussion.damdelt;
        player.blueforce.player2.weapon.ammobox.damdelt       += p->player.blueforce.player2.weapon.ammobox.damdelt;

        player.blueforce.player2.weapon.m203.damrec           += p->player.blueforce.player2.weapon.m203.damrec;
        player.blueforce.player2.weapon.famas.damrec          += p->player.blueforce.player2.weapon.famas.damrec;
        player.blueforce.player2.weapon.g36e.damrec           += p->player.blueforce.player2.weapon.g36e.damrec;
        player.blueforce.player2.weapon.benelli.damrec        += p->player.blueforce.player2.weapon.benelli.damrec;
        player.blueforce.player2.weapon.saiga.damrec          += p->player.blueforce.player2.weapon.saiga.damrec;
        player.blueforce.player2.weapon.m16.damrec            += p->player.blueforce.player2.weapon.m16.damrec;
        player.blueforce.player2.weapon.ak47.damrec           += p->player.blueforce.player2.weapon.ak47.damrec;
        player.blueforce.player2.weapon.m82.damrec            += p->player.blueforce.player2.weapon.m82.damrec;
        player.blueforce.player2.weapon.bizon.damrec          += p->player.blueforce.player2.weapon.bizon.damrec;
        player.blueforce.player2.weapon.knife.damrec          += p->player.blueforce.player2.weapon.knife.damrec;
        player.blueforce.player2.weapon.coltgov.damrec        += p->player.blueforce.player2.weapon.coltgov.damrec;
        player.blueforce.player2.weapon.ber92f.damrec         += p->player.blueforce.player2.weapon.ber92f.damrec;
        player.blueforce.player2.weapon.ber93r.damrec         += p->player.blueforce.player2.weapon.ber93r.damrec;
        player.blueforce.player2.weapon.desert.damrec         += p->player.blueforce.player2.weapon.desert.damrec;
        player.blueforce.player2.weapon.anaconda.damrec       += p->player.blueforce.player2.weapon.anaconda.damrec;
        player.blueforce.player2.weapon.stg24.damrec          += p->player.blueforce.player2.weapon.stg24.damrec;
        player.blueforce.player2.weapon.claymore.damrec       += p->player.blueforce.player2.weapon.claymore.damrec;
        player.blueforce.player2.weapon.sterling.damrec       += p->player.blueforce.player2.weapon.sterling.damrec;
        player.blueforce.player2.weapon.mp5a5.damrec          += p->player.blueforce.player2.weapon.mp5a5.damrec;
        player.blueforce.player2.weapon.g3a3.damrec           += p->player.blueforce.player2.weapon.g3a3.damrec;
        player.blueforce.player2.weapon.m60.damrec            += p->player.blueforce.player2.weapon.m60.damrec;
        player.blueforce.player2.weapon.m79.damrec            += p->player.blueforce.player2.weapon.m79.damrec;
        player.blueforce.player2.weapon.frag.damrec           += p->player.blueforce.player2.weapon.frag.damrec;
        player.blueforce.player2.weapon.uzi.damrec            += p->player.blueforce.player2.weapon.uzi.damrec;
        player.blueforce.player2.weapon.pkm.damrec            += p->player.blueforce.player2.weapon.pkm.damrec;
        player.blueforce.player2.weapon.ak74.damrec           += p->player.blueforce.player2.weapon.ak74.damrec;
        player.blueforce.player2.weapon.svd.damrec            += p->player.blueforce.player2.weapon.svd.damrec;
        player.blueforce.player2.weapon.gp25.damrec           += p->player.blueforce.player2.weapon.gp25.damrec;
        player.blueforce.player2.weapon.ssg3000.damrec        += p->player.blueforce.player2.weapon.ssg3000.damrec;
        player.blueforce.player2.weapon.weapmortar.damrec     += p->player.blueforce.player2.weapon.weapmortar.damrec;
        player.blueforce.player2.weapon.spark_shower.damrec   += p->player.blueforce.player2.weapon.spark_shower.damrec;
        player.blueforce.player2.weapon.monster_mortar.damrec += p->player.blueforce.player2.weapon.monster_mortar.damrec;
        player.blueforce.player2.weapon.func_tank.damrec      += p->player.blueforce.player2.weapon.func_tank.damrec;
        player.blueforce.player2.weapon.env_explosion.damrec  += p->player.blueforce.player2.weapon.env_explosion.damrec;
        player.blueforce.player2.weapon.concussion.damrec     += p->player.blueforce.player2.weapon.concussion.damrec;
        player.blueforce.player2.weapon.ammobox.damrec        += p->player.blueforce.player2.weapon.ammobox.damrec;

        writep(&player,idx);
    }

    clearplayerdata();  // Remove Player Link List Data From Memory

    // Current Process Completed
    percentright(100);

    // Keep Track of All Map Names to Map.dat
    if(!matchmap(MAPNAME)) {
        tempidx = countmaps();
        map.index = tempidx;
        strcpy(map.name,NEWMAP);
        writem(&map,tempidx);
    }
    if(!matchmap(NEWMAP)) {
        tempidx = countmaps();
        map.index = tempidx;
        strcpy(map.name,NEWMAP);
        writem(&map,tempidx);
    }
    return;
}


/*--------------------------------------------------------------------------------*/
// STRING PARSING FUNCTIONS
/*--------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------*/
// Parses for Player Damage Received
void playerdamrec(string logline) {

    struct ListItem13 *p;

    string temp = logline, temp1, temp2, dtemp;
    char temp3[30]={0};

      int    st1  = -1,
        st2  = -1,
        id1  = -1,
        id3  = -1,
        id4  = -1,
        id5  = -1,
        id6  = -1,
        ct   =  0;

    // Start Splitting string for Second Player's Name After "attacked"
    st1 = temp.find("\"", 0);                // Getting Starting of Name
    st2 = temp.find("<", st1 +2);            // Getting Ending of Name
    ++st1;                                    // Incirment to get rid of "
    temp2 = temp.substr(st1,st2);            // Splits String / Sometimes leaves to much at end
    ct = st2 - st1;                           // Gets Name Length
    if (temp2.length() > ct)                  // Check for Proper Name Length
            temp2.erase(ct,temp2.size());     // Erase Any Extra Character at the end
    strcpy(temp3,temp2.c_str());              // Converts String to c string

     // Do Testing if player name is in list, Update it with New Data
     for ( p = MyList13 ; p != 0 ; p = p->next ) {
        if (strcmp(p->player.playername,temp3) == 0) {
            // Gets Weapon Name
            id3 = temp.find("with \"", 0);
            temp1 = temp.substr(id3+6,temp.length());
            id4 = temp1.find("\"",0);
            if (id4 != -1) temp1.erase(id4,temp1.length());
              // Gets Damage Amount
              id5 = temp.find("damage", 0);
            dtemp = temp.substr(id5+8,temp.length());
            id6 = dtemp.find("\"",0);
            if (id6 != -1) dtemp.erase(id6,id6+3);
            long dmg;
            dmg = atol(dtemp.c_str());

            if( temp.find("<Red Force>", 0) != -1) {
                 TEAM = true;

                if (temp1 == "player") {
                    return;  // Bleding Damage
                }
                else if (temp1 == "weapon_knife") {
                    p->player.redforce.player2.weapon.knife.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_coltgov") {
                    p->player.redforce.player2.weapon.coltgov.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_ber92f") {
                    p->player.redforce.player2.weapon.ber92f.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_ber93r") {
                    p->player.redforce.player2.weapon.ber93r.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_anaconda") {
                    p->player.redforce.player2.weapon.anaconda.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_desert") {
                    p->player.redforce.player2.weapon.desert.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_benelli") {
                    p->player.redforce.player2.weapon.benelli.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_saiga") {
                    p->player.redforce.player2.weapon.saiga.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_mp5a5") {
                    p->player.redforce.player2.weapon.mp5a5.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_sterling") {
                    p->player.redforce.player2.weapon.sterling.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_bizon") {
                    p->player.redforce.player2.weapon.bizon.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_ak47") {
                    p->player.redforce.player2.weapon.ak47.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_famas") {
                    p->player.redforce.player2.weapon.famas.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_g3a3") {
                    p->player.redforce.player2.weapon.g3a3.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_g36e") {
                    p->player.redforce.player2.weapon.g36e.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_m16") {
                    p->player.redforce.player2.weapon.m16.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_m203") {
                    p->player.redforce.player2.weapon.m203.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_m82") {
                    p->player.redforce.player2.weapon.m82.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_m60") {
                    p->player.redforce.player2.weapon.m60.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_m79") {
                    p->player.redforce.player2.weapon.m79.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "item_claymore") {
                    p->player.redforce.player2.weapon.claymore.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "item_frag") {
                    p->player.redforce.player2.weapon.frag.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "item_stg24") {
                    p->player.redforce.player2.weapon.stg24.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_uzi") {
                    p->player.redforce.player2.weapon.uzi.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_pkm") {
                    p->player.redforce.player2.weapon.pkm.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_ak74") {
                    p->player.redforce.player2.weapon.ak74.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_svd") {
                    p->player.redforce.player2.weapon.svd.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_gp25") {
                    p->player.redforce.player2.weapon.gp25.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_ssg3000") {
                    p->player.redforce.player2.weapon.ssg3000.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapmortar") {
                    p->player.redforce.player2.weapon.weapmortar.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "spark_shower") {
                    p->player.redforce.player2.weapon.spark_shower.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "monster_mortar") {
                    p->player.redforce.player2.weapon.monster_mortar.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "func_tank") {
                    p->player.redforce.player2.weapon.func_tank.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "env_explosion") {
                    p->player.redforce.player2.weapon.env_explosion.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "concussion") {
                    p->player.redforce.player2.weapon.concussion.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
                else if (temp1 == "ammobox") {
                    p->player.redforce.player2.weapon.ammobox.damrec += dmg;
                    p->player.redforce.player2.damrec += dmg;
                }
            }
            else {
                    TEAM = false;
                if (temp1 == "player") {
                    return;  // Bleding Damage
                }
                else if (temp1 == "weapon_knife") {
                    p->player.blueforce.player2.weapon.knife.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_coltgov") {
                    p->player.blueforce.player2.weapon.coltgov.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_ber92f") {
                    p->player.blueforce.player2.weapon.ber92f.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_ber93r") {
                    p->player.blueforce.player2.weapon.ber93r.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_anaconda") {
                    p->player.blueforce.player2.weapon.anaconda.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_desert") {
                    p->player.blueforce.player2.weapon.desert.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_benelli") {
                    p->player.blueforce.player2.weapon.benelli.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_saiga") {
                    p->player.blueforce.player2.weapon.saiga.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_mp5a5") {
                    p->player.blueforce.player2.weapon.mp5a5.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_sterling") {
                    p->player.blueforce.player2.weapon.sterling.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_bizon") {
                    p->player.blueforce.player2.weapon.bizon.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_ak47") {
                    p->player.blueforce.player2.weapon.ak47.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_famas") {
                    p->player.blueforce.player2.weapon.famas.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_g3a3") {
                    p->player.blueforce.player2.weapon.g3a3.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_g36e") {
                    p->player.blueforce.player2.weapon.g36e.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_m16") {
                    p->player.blueforce.player2.weapon.m16.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_m203") {
                    p->player.blueforce.player2.weapon.m203.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_m82") {
                    p->player.blueforce.player2.weapon.m82.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_m60") {
                    p->player.blueforce.player2.weapon.m60.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_m79") {
                    p->player.blueforce.player2.weapon.m79.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "item_claymore") {
                    p->player.blueforce.player2.weapon.claymore.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "item_frag") {
                    p->player.blueforce.player2.weapon.frag.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "item_stg24") {
                    p->player.blueforce.player2.weapon.stg24.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_uzi") {
                    p->player.blueforce.player2.weapon.uzi.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_pkm") {
                    p->player.blueforce.player2.weapon.pkm.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_ak74") {
                    p->player.blueforce.player2.weapon.ak74.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_svd") {
                    p->player.blueforce.player2.weapon.svd.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_gp25") {
                    p->player.blueforce.player2.weapon.gp25.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapon_ssg3000") {
                    p->player.blueforce.player2.weapon.ssg3000.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "weapmortar") {
                    p->player.blueforce.player2.weapon.weapmortar.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "spark_shower") {
                    p->player.blueforce.player2.weapon.spark_shower.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "monster_mortar") {
                    p->player.blueforce.player2.weapon.monster_mortar.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "func_tank") {
                    p->player.blueforce.player2.weapon.func_tank.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "env_explosion") {
                    p->player.blueforce.player2.weapon.env_explosion.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "concussion") {
                    p->player.blueforce.player2.weapon.concussion.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
                else if (temp1 == "ammobox") {
                    p->player.blueforce.player2.weapon.ammobox.damrec += dmg;
                    p->player.blueforce.player2.damrec += dmg;
                }
               } // End Else
            return;
        } // End IF
    }// End for
    newplayerdata(temp2);
    playerdamrec(temp);
}

/*--------------------------------------------------------------------------------*/
// Parses for Player Damage Delt Out
void playerdamdelt(string logline) {

    struct ListItem13 *p;

    string temp = logline, temp1, temp2, dtemp;
    char temp3[30]={0};

      int    st1  = -1,
        st2  = -1,
        id1  = -1,
        id3  = -1,
        id4  = -1,
        id5  = -1,
        id6  = -1,
        ct   =  0;

    // Get Player Name First & Make Sure it Exists before assigning Damage
    st1 = temp.find("\"", 0);
    st2 = temp.find("<", st1 +2);
    ++st1;
    temp2 = temp.substr(st1,st2);
    ct = st2 - st1;
    if (temp2.length() > ct)
        temp2.erase(ct,temp2.length());
    strcpy(temp3,temp2.c_str());

    // Do Testing if player name is in list, Update it with New Data
    for ( p = MyList13 ; p != 0 ; p = p->next ) {
        if (strcmp(p->player.playername,temp3) == 0) {
            // Gets Weapon Name
            id3 = temp.find("with \"", 0);
            temp1 = temp.substr(id3+6,temp.length());
            id4 = temp1.find("\"",0);
            if (id4 != -1) {
                temp1.erase(id4,temp1.length());
            }
            // Gets Damage Amount
            id5 = temp.find("damage", 0);
            dtemp = temp.substr(id5+8,temp.length());
            id6 = dtemp.find("\"",0);
            if (id6 != -1) {
                    dtemp.erase(id6,id6+3);
            }

            // Convert String (Damage) to Double for Processing
            long dmg;
            dmg = atol(dtemp.c_str());

            if( temp.find("<Red Force>", 0) != -1) {
                TEAM = true;

                if (temp1 == "player") {
                    p->player.redforce.player2.dambleed +=dmg;
                }
                else if (temp1 == "weapon_knife") {
                    p->player.redforce.player2.weapon.knife.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_coltgov") {
                    p->player.redforce.player2.weapon.coltgov.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_ber92f") {
                    p->player.redforce.player2.weapon.ber92f.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_ber93r") {
                    p->player.redforce.player2.weapon.ber93r.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_anaconda") {
                    p->player.redforce.player2.weapon.anaconda.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_desert") {
                    p->player.redforce.player2.weapon.desert.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_benelli") {
                    p->player.redforce.player2.weapon.benelli.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_saiga") {
                    p->player.redforce.player2.weapon.saiga.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_mp5a5") {
                    p->player.redforce.player2.weapon.mp5a5.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_sterling") {
                    p->player.redforce.player2.weapon.sterling.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_bizon") {
                    p->player.redforce.player2.weapon.bizon.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_ak47") {
                    p->player.redforce.player2.weapon.ak47.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_famas") {
                    p->player.redforce.player2.weapon.famas.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_g3a3") {
                    p->player.redforce.player2.weapon.g3a3.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_g36e") {
                    p->player.redforce.player2.weapon.g36e.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_m16") {
                    p->player.redforce.player2.weapon.m16.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_m203") {
                    p->player.redforce.player2.weapon.m203.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_m82") {
                    p->player.redforce.player2.weapon.m82.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_m60") {
                    p->player.redforce.player2.weapon.m60.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_m79") {
                    p->player.redforce.player2.weapon.m79.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "item_claymore") {
                    p->player.redforce.player2.weapon.claymore.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "item_frag") {
                    p->player.redforce.player2.weapon.frag.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "item_stg24") {
                    p->player.redforce.player2.weapon.stg24.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_uzi") {
                    p->player.redforce.player2.weapon.uzi.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_pkm") {
                    p->player.redforce.player2.weapon.pkm.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_ak74") {
                    p->player.redforce.player2.weapon.ak74.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_svd") {
                    p->player.redforce.player2.weapon.svd.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_gp25") {
                    p->player.redforce.player2.weapon.gp25.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_ssg3000") {
                    p->player.redforce.player2.weapon.ssg3000.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapmortar") {
                    p->player.redforce.player2.weapon.weapmortar.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "spark_shower") {
                    p->player.redforce.player2.weapon.spark_shower.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "monster_mortar") {
                    p->player.redforce.player2.weapon.monster_mortar.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "func_tank") {
                    p->player.redforce.player2.weapon.func_tank.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "env_explosion") {
                    p->player.redforce.player2.weapon.env_explosion.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "concussion") {
                    p->player.redforce.player2.weapon.concussion.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
                else if (temp1 == "ammobox") {
                    p->player.redforce.player2.weapon.ammobox.damdelt += dmg;
                    p->player.redforce.player2.damdelt += dmg;
                }
            }
            else {
                TEAM = false;
                if (temp1 == "player") {
                    p->player.blueforce.player2.dambleed +=dmg;
                }
                else if (temp1 == "weapon_knife") {
                    p->player.blueforce.player2.weapon.knife.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_coltgov") {
                    p->player.blueforce.player2.weapon.coltgov.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_ber92f") {
                    p->player.blueforce.player2.weapon.ber92f.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_ber93r") {
                    p->player.blueforce.player2.weapon.ber93r.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_anaconda") {
                    p->player.blueforce.player2.weapon.anaconda.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_desert") {
                    p->player.blueforce.player2.weapon.desert.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_benelli") {
                    p->player.blueforce.player2.weapon.benelli.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_saiga") {
                    p->player.blueforce.player2.weapon.saiga.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_mp5a5") {
                    p->player.blueforce.player2.weapon.mp5a5.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_sterling") {
                    p->player.blueforce.player2.weapon.sterling.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_bizon") {
                    p->player.blueforce.player2.weapon.bizon.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_ak47") {
                    p->player.blueforce.player2.weapon.ak47.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_famas") {
                    p->player.blueforce.player2.weapon.famas.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_g3a3") {
                    p->player.blueforce.player2.weapon.g3a3.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_g36e") {
                    p->player.blueforce.player2.weapon.g36e.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_m16") {
                    p->player.blueforce.player2.weapon.m16.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_m203") {
                    p->player.blueforce.player2.weapon.m203.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_m82") {
                    p->player.blueforce.player2.weapon.m82.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_m60") {
                    p->player.blueforce.player2.weapon.m60.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_m79") {
                    p->player.blueforce.player2.weapon.m79.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "item_claymore") {
                    p->player.blueforce.player2.weapon.claymore.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "item_frag") {
                    p->player.blueforce.player2.weapon.frag.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "item_stg24") {
                    p->player.blueforce.player2.weapon.stg24.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_uzi") {
                    p->player.blueforce.player2.weapon.uzi.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_pkm") {
                    p->player.blueforce.player2.weapon.pkm.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_ak74") {
                    p->player.blueforce.player2.weapon.ak74.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_svd") {
                    p->player.blueforce.player2.weapon.svd.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_gp25") {
                    p->player.blueforce.player2.weapon.gp25.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapon_ssg3000") {
                    p->player.blueforce.player2.weapon.ssg3000.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "weapmortar") {
                    p->player.blueforce.player2.weapon.weapmortar.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "spark_shower") {
                    p->player.blueforce.player2.weapon.spark_shower.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "monster_mortar") {
                    p->player.blueforce.player2.weapon.monster_mortar.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "func_tank") {
                    p->player.blueforce.player2.weapon.func_tank.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "env_explosion") {
                    p->player.blueforce.player2.weapon.env_explosion.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "concussion") {
                    p->player.blueforce.player2.weapon.concussion.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }
                else if (temp1 == "ammobox") {
                    p->player.blueforce.player2.weapon.ammobox.damdelt += dmg;
                    p->player.blueforce.player2.damdelt += dmg;
                }

            } // End Else
            return;
        }// indif
    }// End for
    newplayerdata(temp2);
    playerdamdelt(temp);

}

/*--------------------------------------------------------------------------------*/
// Parses for Player Suicide
void playersuicide(string logline) {

    struct ListItem13 *p;

    string temp = logline, temp1, temp2;
    char temp3[30]={0};

      int    st1  = -1,
        st2  = -1,
        id1  = -1,
        id3  = -1,
        id4  = -1,
        ct   =  0;

    // Check for Valid Suicide, if These are Found. Skip Processing. Invalid!
    // Or Suicide not with a Registered Weapon - Version 2.5, not Sure about 2.6

    if (temp.find("worldspawn",   0) != -1) return;
    if (temp.find("world",           0) != -1) return;
    if (temp.find("trigger_hurt", 0) != -1) return;

    //-----------------------------------------//
    // Get Player Name First & Make Sure it Exists before assigning a Suicide
    st1 = temp.find("\"", 0);
    st2 = temp.find("<", st1 +2);
    ++st1;
    temp2 = temp.substr(st1,st2);
    ct = st2 - st1;
    if (temp2.length() > ct)
        temp2.erase(ct,temp2.length());
    strcpy(temp3,temp2.c_str());

    // Do Testing if player name is in list, Update it with New Data
    for ( p = MyList13 ; p != 0 ; p = p->next ) {
        if (strcmp(p->player.playername,temp3) == 0) {

             id3 = temp.find("with \"", 0);
            temp1 = temp.substr(id3+6,temp.length()); // Cut Weapon
            id4 = temp1.find("\"",2);
            if (id4 != -1) {
                temp1.erase(id4,id4+2); // remove last chars "
            }

             if( temp.find("<Red Force>", 0) != -1) {
                 TEAM = true;
                  p->player.redforce.player2.sui += 1;

                  if (temp1 == "knife") {
                    p->player.redforce.player2.weapon.knife.sui += 1;
                }
                else if (temp1 == "coltgov") {
                    p->player.redforce.player2.weapon.coltgov.sui +=1;
                }
                else if (temp1 == "ber92f") {
                    p->player.redforce.player2.weapon.ber92f.sui +=1;
                }
                else if (temp1 == "ber93r") {
                    p->player.redforce.player2.weapon.ber93r.sui +=1;
                }
                else if (temp1 == "anaconda") {
                    p->player.redforce.player2.weapon.anaconda.sui +=1;
                }
                else if (temp1 == "desert") {
                    p->player.redforce.player2.weapon.desert.sui +=1;
                }
                else if (temp1 == "benelli") {
                    p->player.redforce.player2.weapon.benelli.sui +=1;
                }
                else if (temp1 == "saiga") {
                    p->player.redforce.player2.weapon.saiga.sui +=1;
                }
                else if (temp1 == "mp5a5") {
                    p->player.redforce.player2.weapon.mp5a5.sui +=1;
                }
                else if (temp1 == "sterling") {
                    p->player.redforce.player2.weapon.sterling.sui +=1;
                }
                else if (temp1 == "bizon") {
                    p->player.redforce.player2.weapon.bizon.sui +=1;
                }
                else if (temp1 == "ak47") {
                    p->player.redforce.player2.weapon.ak47.sui +=1;
                }
                else if (temp1 == "famas") {
                    p->player.redforce.player2.weapon.famas.sui +=1;
                }
                else if (temp1 == "g3a3") {
                    p->player.redforce.player2.weapon.g3a3.sui +=1;
                }
                else if (temp1 == "g36e") {
                    p->player.redforce.player2.weapon.g36e.sui +=1;
                }
                else if (temp1 == "m16") {
                    p->player.redforce.player2.weapon.m16.sui +=1;
                }
                else if (temp1 == "m203") {
                    p->player.redforce.player2.weapon.m203.sui +=1;
                }
                else if (temp1 == "m82") {
                    p->player.redforce.player2.weapon.m82.sui +=1;
                }
                else if (temp1 == "m60") {
                    p->player.redforce.player2.weapon.m60.sui +=1;
                }
                else if (temp1 == "m79") {
                    p->player.redforce.player2.weapon.m79.sui +=1;
                }
                else if (temp1 == "claymore") {
                    p->player.redforce.player2.weapon.claymore.sui +=1;
                }
                else if (temp1 == "frag") {
                    p->player.redforce.player2.weapon.frag.sui +=1;
                }
                else if (temp1 == "stg24") {
                    p->player.redforce.player2.weapon.stg24.sui +=1;
                }
                else if (temp1 == "uzi") {
                    p->player.redforce.player2.weapon.uzi.sui +=1;
                }
                else if (temp1 == "pkm") {
                    p->player.redforce.player2.weapon.pkm.sui +=1;
                }
                else if (temp1 == "ak74") {
                    p->player.redforce.player2.weapon.ak74.sui +=1;
                }
                else if (temp1 == "svd") {
                    p->player.redforce.player2.weapon.svd.sui +=1;
                }
                else if (temp1 == "gp25") {
                    p->player.redforce.player2.weapon.gp25.sui +=1;
                }
                else if (temp1 == "ssg3000") {
                    p->player.redforce.player2.weapon.ssg3000.sui +=1;
                }
                else if (temp1 == "weapmortar") {
                    p->player.redforce.player2.weapon.weapmortar.sui +=1;
                }
                else if (temp1 == "spark_shower") {
                    p->player.redforce.player2.weapon.spark_shower.sui +=1;
                }
                else if (temp1 == "monster_mortar") {
                    p->player.redforce.player2.weapon.monster_mortar.sui +=1;
                }
                else if (temp1 == "func_tank") {
                    p->player.redforce.player2.weapon.func_tank.sui +=1;
                }
                else if (temp1 == "env_explosion") {
                    p->player.redforce.player2.weapon.env_explosion.sui +=1;
                }
                else if (temp1 == "concussion") {
                    p->player.redforce.player2.weapon.concussion.sui +=1;
                }
                else if (temp1 == "ammobox") {
                    p->player.redforce.player2.weapon.ammobox.sui +=1;
                }
            }
            else {
                TEAM = false;
                p->player.blueforce.player2.sui += 1;

                if (temp1 == "knife") {
                    p->player.blueforce.player2.weapon.knife.sui += 1;
                }
                else if (temp1 == "coltgov") {
                    p->player.blueforce.player2.weapon.coltgov.sui +=1;
                }
                else if (temp1 == "ber92f") {
                    p->player.blueforce.player2.weapon.ber92f.sui +=1;
                }
                else if (temp1 == "ber93r") {
                    p->player.blueforce.player2.weapon.ber93r.sui +=1;
                }
                else if (temp1 == "anaconda") {
                    p->player.blueforce.player2.weapon.anaconda.sui +=1;
                }
                else if (temp1 == "desert") {
                    p->player.blueforce.player2.weapon.desert.sui +=1;
                }
                else if (temp1 == "benelli") {
                    p->player.blueforce.player2.weapon.benelli.sui +=1;
                }
                else if (temp1 == "saiga") {
                    p->player.blueforce.player2.weapon.saiga.sui +=1;
                }
                else if (temp1 == "mp5a5") {
                    p->player.blueforce.player2.weapon.mp5a5.sui +=1;
                }
                else if (temp1 == "sterling") {
                    p->player.blueforce.player2.weapon.sterling.sui +=1;
                }
                else if (temp1 == "bizon") {
                    p->player.blueforce.player2.weapon.bizon.sui +=1;
                }
                else if (temp1 == "ak47") {
                    p->player.blueforce.player2.weapon.ak47.sui +=1;
                }
                else if (temp1 == "famas") {
                    p->player.blueforce.player2.weapon.famas.sui +=1;
                }
                else if (temp1 == "g3a3") {
                    p->player.blueforce.player2.weapon.g3a3.sui +=1;
                }
                else if (temp1 == "g36e") {
                    p->player.blueforce.player2.weapon.g36e.sui +=1;
                }
                else if (temp1 == "m16") {
                    p->player.blueforce.player2.weapon.m16.sui +=1;
                }
                else if (temp1 == "m203") {
                    p->player.blueforce.player2.weapon.m203.sui +=1;
                }
                else if (temp1 == "m82") {
                    p->player.blueforce.player2.weapon.m82.sui +=1;
                }
                else if (temp1 == "m60") {
                    p->player.blueforce.player2.weapon.m60.sui +=1;
                }
                else if (temp1 == "m79") {
                    p->player.blueforce.player2.weapon.m79.sui +=1;
                }
                else if (temp1 == "claymore") {
                    p->player.blueforce.player2.weapon.claymore.sui +=1;
                }
                else if (temp1 == "frag") {
                    p->player.blueforce.player2.weapon.frag.sui +=1;
                }
                else if (temp1 == "stg24") {
                    p->player.blueforce.player2.weapon.stg24.sui +=1;
                }
                else if (temp1 == "uzi") {
                    p->player.blueforce.player2.weapon.uzi.sui +=1;
                }
                else if (temp1 == "pkm") {
                    p->player.blueforce.player2.weapon.pkm.sui +=1;
                }
                else if (temp1 == "ak74") {
                    p->player.blueforce.player2.weapon.ak74.sui +=1;
                }
                else if (temp1 == "svd") {
                    p->player.blueforce.player2.weapon.svd.sui +=1;
                }
                else if (temp1 == "gp25") {
                    p->player.blueforce.player2.weapon.gp25.sui +=1;
                }
                else if (temp1 == "ssg3000") {
                    p->player.blueforce.player2.weapon.ssg3000.sui +=1;
                }
                else if (temp1 == "weapmortar") {
                    p->player.blueforce.player2.weapon.weapmortar.sui +=1;
                }
                else if (temp1 == "spark_shower") {
                    p->player.blueforce.player2.weapon.spark_shower.sui +=1;
                }
                else if (temp1 == "monster_mortar") {
                    p->player.blueforce.player2.weapon.monster_mortar.sui +=1;
                }
                else if (temp1 == "func_tank") {
                    p->player.blueforce.player2.weapon.func_tank.sui +=1;
                }
                else if (temp1 == "env_explosion") {
                    p->player.blueforce.player2.weapon.env_explosion.sui +=1;
                }
                else if (temp1 == "concussion") {
                    p->player.blueforce.player2.weapon.concussion.sui +=1;
                }
                else if (temp1 == "ammobox") {
                    p->player.blueforce.player2.weapon.ammobox.sui +=1;
                }
            }
              return;
        } // End of IF
    } // End of For
    newplayerdata(temp2);
    playersuicide(temp);
}


/*--------------------------------------------------------------------------------*/
// Parses for Player Died
void playerdied(string logline) {

     struct ListItem13 *p;

    string temp = logline, temp1, temp2;
    char temp3[30]={0};

      int    st1  = -1,
        st2  = -1,
        id1  = -1,
        id3  = -1,
        id4  = -1,
        ct   =  0;

     // Start Splitting string for Second Player's Name After "Killed"
    st1 = temp.find("\"", 0);                      // Getting Starting of Name
    st2 = temp.find("<", st1 +2);                  // Getting Ending of Name

    ++st1;                                          // Incirment to get rid of "
    temp2 = temp.substr(st1,st2);                  // Splits String / Sometimes leaves to much at end
    ct = st2 - st1;                                 // Gets Name Length
    if (temp2.length() > ct)                        // Check for Proper Name Length
        temp2.erase(ct,temp2.size());           // Erase Any Extra Character at the end
    strcpy(temp3,temp2.c_str());                    // Converts String to c string

    // Do Testing if player name is in list, Update it with New Data
    for ( p = MyList13 ; p != 0 ; p = p->next ) {
        if (strcmp(p->player.playername,temp3) == 0) {

            id3 = temp.find("with \"", 0);             // Research for Weapon (Quciker)
            temp1 = temp.substr(id3+6,temp.length());  // Cut Weapon
            id4 = temp1.find("\"",2);
            if (id4 != -1) {
                temp1.erase(id4,id4+2);            // remove last chars "
            }

            if( temp.find("<Red Force>", 0) != -1) {
                TEAM = true;
                p->player.redforce.player2.deaths += 1;

                if (temp1 == "knife") {
                    p->player.redforce.player2.weapon.knife.deaths += 1;
                }
                else if (temp1 == "coltgov") {
                    p->player.redforce.player2.weapon.coltgov.deaths +=1;
                }
                else if (temp1 == "ber92f") {
                    p->player.redforce.player2.weapon.ber92f.deaths +=1;
                }
                else if (temp1 == "ber93r") {
                    p->player.redforce.player2.weapon.ber93r.deaths +=1;
                }
                else if (temp1 == "anaconda") {
                    p->player.redforce.player2.weapon.anaconda.deaths +=1;
                }
                else if (temp1 == "desert") {
                    p->player.redforce.player2.weapon.desert.deaths +=1;
                }
                else if (temp1 == "benelli") {
                    p->player.redforce.player2.weapon.benelli.deaths +=1;
                }
                else if (temp1 == "saiga") {
                    p->player.redforce.player2.weapon.saiga.deaths +=1;
                }
                else if (temp1 == "mp5a5") {
                    p->player.redforce.player2.weapon.mp5a5.deaths +=1;
                }
                else if (temp1 == "sterling") {
                    p->player.redforce.player2.weapon.sterling.deaths +=1;
                }
                else if (temp1 == "bizon") {
                    p->player.redforce.player2.weapon.bizon.deaths +=1;
                }
                else if (temp1 == "ak47") {
                    p->player.redforce.player2.weapon.ak47.deaths +=1;
                }
                else if (temp1 == "famas") {
                    p->player.redforce.player2.weapon.famas.deaths +=1;
                }
                else if (temp1 == "g3a3") {
                    p->player.redforce.player2.weapon.g3a3.deaths +=1;
                }
                else if (temp1 == "g36e") {
                    p->player.redforce.player2.weapon.g36e.deaths +=1;
                }
                else if (temp1 == "m16") {
                    p->player.redforce.player2.weapon.m16.deaths +=1;
                }
                else if (temp1 == "m203") {
                    p->player.redforce.player2.weapon.m203.deaths +=1;
                }
                else if (temp1 == "m82") {
                    p->player.redforce.player2.weapon.m82.deaths +=1;
                }
                else if (temp1 == "m60") {
                    p->player.redforce.player2.weapon.m60.deaths +=1;
                }
                else if (temp1 == "m79") {
                    p->player.redforce.player2.weapon.m79.deaths +=1;
                }
                else if (temp1 == "claymore") {
                    p->player.redforce.player2.weapon.claymore.deaths +=1;
                }
                else if (temp1 == "frag") {
                    p->player.redforce.player2.weapon.frag.deaths +=1;
                }
                else if (temp1 == "stg24") {
                    p->player.redforce.player2.weapon.stg24.deaths +=1;
                }
                else if (temp1 == "uzi") {
                    p->player.redforce.player2.weapon.uzi.deaths +=1;
                }
                else if (temp1 == "pkm") {
                    p->player.redforce.player2.weapon.pkm.deaths +=1;
                }
                else if (temp1 == "ak74") {
                    p->player.redforce.player2.weapon.ak74.deaths +=1;
                }
                else if (temp1 == "svd") {
                    p->player.redforce.player2.weapon.svd.deaths +=1;
                }
                else if (temp1 == "gp25") {
                    p->player.redforce.player2.weapon.gp25.deaths +=1;
                }
                else if (temp1 == "ssg3000") {
                    p->player.redforce.player2.weapon.ssg3000.deaths +=1;
                }
                else if (temp1 == "weapmortar") {
                    p->player.redforce.player2.weapon.weapmortar.deaths +=1;
                }
                else if (temp1 == "spark_shower") {
                    p->player.redforce.player2.weapon.spark_shower.deaths +=1;
                }
                else if (temp1 == "monster_mortar") {
                    p->player.redforce.player2.weapon.monster_mortar.deaths +=1;
                }
                else if (temp1 == "func_tank") {
                    p->player.redforce.player2.weapon.func_tank.deaths +=1;
                }
                else if (temp1 == "env_explosion") {
                    p->player.redforce.player2.weapon.env_explosion.deaths +=1;
                }
                else if (temp1 == "concussion") {
                    p->player.redforce.player2.weapon.concussion.deaths +=1;
                }
                else if (temp1 == "ammobox") {
                    p->player.redforce.player2.weapon.ammobox.deaths +=1;
                }
               }
              else {
                  TEAM = false;
                  p->player.blueforce.player2.deaths += 1;
                  if (temp1 == "knife") {
                      p->player.blueforce.player2.weapon.knife.deaths += 1;
                }
                else if (temp1 == "coltgov") {
                    p->player.blueforce.player2.weapon.coltgov.deaths +=1;
                }
                else if (temp1 == "ber92f") {
                    p->player.blueforce.player2.weapon.ber92f.deaths +=1;
                }
                else if (temp1 == "ber93r") {
                    p->player.blueforce.player2.weapon.ber93r.deaths +=1;
                }
                else if (temp1 == "anaconda") {
                    p->player.blueforce.player2.weapon.anaconda.deaths +=1;
                }
                else if (temp1 == "desert") {
                    p->player.blueforce.player2.weapon.desert.deaths +=1;
                }
                else if (temp1 == "benelli") {
                    p->player.blueforce.player2.weapon.benelli.deaths +=1;
                }
                else if (temp1 == "saiga") {
                    p->player.blueforce.player2.weapon.saiga.deaths +=1;
                }
                else if (temp1 == "mp5a5") {
                    p->player.blueforce.player2.weapon.mp5a5.deaths +=1;
                }
                else if (temp1 == "sterling") {
                    p->player.blueforce.player2.weapon.sterling.deaths +=1;
                }
                else if (temp1 == "bizon") {
                    p->player.blueforce.player2.weapon.bizon.deaths +=1;
                }
                else if (temp1 == "ak47") {
                    p->player.blueforce.player2.weapon.ak47.deaths +=1;
                }
                else if (temp1 == "famas") {
                    p->player.blueforce.player2.weapon.famas.deaths +=1;
                }
                else if (temp1 == "g3a3") {
                    p->player.blueforce.player2.weapon.g3a3.deaths +=1;
                }
                else if (temp1 == "g36e") {
                    p->player.blueforce.player2.weapon.g36e.deaths +=1;
                }
                else if (temp1 == "m16") {
                    p->player.blueforce.player2.weapon.m16.deaths +=1;
                }
                else if (temp1 == "m203") {
                    p->player.blueforce.player2.weapon.m203.deaths +=1;
                }
                else if (temp1 == "m82") {
                    p->player.blueforce.player2.weapon.m82.deaths +=1;
                }
                else if (temp1 == "m60") {
                    p->player.blueforce.player2.weapon.m60.deaths +=1;
                }
                else if (temp1 == "m79") {
                    p->player.blueforce.player2.weapon.m79.deaths +=1;
                }
                else if (temp1 == "claymore") {
                    p->player.blueforce.player2.weapon.claymore.deaths +=1;
                }
                else if (temp1 == "frag") {
                    p->player.blueforce.player2.weapon.frag.deaths +=1;
                }
                else if (temp1 == "stg24") {
                    p->player.blueforce.player2.weapon.stg24.deaths +=1;
                }
                else if (temp1 == "uzi") {
                    p->player.blueforce.player2.weapon.uzi.deaths +=1;
                }
                else if (temp1 == "pkm") {
                    p->player.blueforce.player2.weapon.pkm.deaths +=1;
                }
                else if (temp1 == "ak74") {
                    p->player.blueforce.player2.weapon.ak74.deaths +=1;
                }
                else if (temp1 == "svd") {
                    p->player.blueforce.player2.weapon.svd.deaths +=1;
                }
                else if (temp1 == "gp25") {
                    p->player.blueforce.player2.weapon.gp25.deaths +=1;
                }
                else if (temp1 == "ssg3000") {
                    p->player.blueforce.player2.weapon.ssg3000.deaths +=1;
                }
                else if (temp1 == "weapmortar") {
                    p->player.blueforce.player2.weapon.weapmortar.deaths +=1;
                }
                else if (temp1 == "spark_shower") {
                    p->player.blueforce.player2.weapon.spark_shower.deaths +=1;
                }
                else if (temp1 == "monster_mortar") {
                    p->player.blueforce.player2.weapon.monster_mortar.deaths +=1;
                }
                else if (temp1 == "func_tank") {
                    p->player.blueforce.player2.weapon.func_tank.deaths +=1;
                }
                else if (temp1 == "env_explosion") {
                    p->player.blueforce.player2.weapon.env_explosion.deaths +=1;
                }
                else if (temp1 == "concussion") {
                    p->player.blueforce.player2.weapon.concussion.deaths +=1;
                }
                else if (temp1 == "ammobox") {
                    p->player.blueforce.player2.weapon.ammobox.deaths +=1;
                }
               } // End Else
            return;
        } // End IF
    }// End for
    newplayerdata(temp2);
    playerdied(temp);
}


/*--------------------------------------------------------------------------------*/
// Parses for Player Kill
void playerkill(string logline) {

    struct ListItem13 *p;

    string temp = logline, temp1, temp2;
    char temp3[30]={0};

      int    st1  = -1,
        st2  = -1,
        id1  = -1,
        id3  = -1,
        id4  = -1,
        ct   =  0;

      // Start by getting Player's Name
       st1 = temp.find("\"", 0);                  // Getting Starting of Name
       st2 = temp.find("<", st1 +2);              // Getting Ending of Name
       ++st1;                                     // Incirment to get rid of "
    temp2 = temp.substr(st1,st2);              // Splits String / Sometimes leaves to much at end
    ct = st2 - st1;                            // Gets Name Length
    if (temp2.length() > ct)                   // Check for Proper Name Length
            temp2.erase(ct,temp2.length());
    strcpy(temp3,temp2.c_str());

    // Do Testing if player name is in list, Update it with New Data
    for ( p = MyList13 ; p != 0 ; p = p->next ) {
        if (strcmp(p->player.playername,temp3) == 0) {

            id3 = -1;
            id4 = -1;

            id3 = temp.find("with \"", 0);              // Research for Weapon (Quciker)
            temp1 = temp.substr(id3+6,temp.length());   // Cut Weapon
            id4 = temp1.find("\"",2);
            if (id4 != -1) {
                    temp1.erase(id4,id4+2);             // remove last chars "
            }

              if( temp.find("<Red Force>", 0) != -1) {
                  TEAM = true;
                 p->player.redforce.player2.kills += 1;

                   if (temp1 == "knife") {
                    p->player.redforce.player2.weapon.knife.kills += 1;
                }
                else if (temp1 == "coltgov") {
                    p->player.redforce.player2.weapon.coltgov.kills +=1;
                }
                else if (temp1 == "ber92f") {
                    p->player.redforce.player2.weapon.ber92f.kills +=1;
                }
                else if (temp1 == "ber93r") {
                    p->player.redforce.player2.weapon.ber93r.kills +=1;
                }
                else if (temp1 == "anaconda") {
                    p->player.redforce.player2.weapon.anaconda.kills +=1;
                }
                else if (temp1 == "desert") {
                    p->player.redforce.player2.weapon.desert.kills +=1;
                }
                else if (temp1 == "benelli") {
                    p->player.redforce.player2.weapon.benelli.kills +=1;
                }
                else if (temp1 == "saiga") {
                    p->player.redforce.player2.weapon.saiga.kills +=1;
                }
                else if (temp1 == "mp5a5") {
                    p->player.redforce.player2.weapon.mp5a5.kills +=1;
                }
                else if (temp1 == "sterling") {
                    p->player.redforce.player2.weapon.sterling.kills +=1;
                }
                else if (temp1 == "bizon") {
                    p->player.redforce.player2.weapon.bizon.kills +=1;
                }
                else if (temp1 == "ak47") {
                    p->player.redforce.player2.weapon.ak47.kills +=1;
                }
                else if (temp1 == "famas") {
                    p->player.redforce.player2.weapon.famas.kills +=1;
                }
                else if (temp1 == "g3a3") {
                    p->player.redforce.player2.weapon.g3a3.kills +=1;
                }
                else if (temp1 == "g36e") {
                    p->player.redforce.player2.weapon.g36e.kills +=1;
                }
                else if (temp1 == "m16") {
                    p->player.redforce.player2.weapon.m16.kills +=1;
                }
                else if (temp1 == "m203") {
                    p->player.redforce.player2.weapon.m203.kills +=1;
                }
                else if (temp1 == "m82") {
                    p->player.redforce.player2.weapon.m82.kills +=1;
                }
                else if (temp1 == "m60") {
                    p->player.redforce.player2.weapon.m60.kills +=1;
                }
                else if (temp1 == "m79") {
                    p->player.redforce.player2.weapon.m79.kills +=1;
                }
                else if (temp1 == "claymore") {
                    p->player.redforce.player2.weapon.claymore.kills +=1;
                }
                else if (temp1 == "frag") {
                    p->player.redforce.player2.weapon.frag.kills +=1;
                }
                else if (temp1 == "stg24") {
                    p->player.redforce.player2.weapon.stg24.kills +=1;
                }
                else if (temp1 == "uzi") {
                    p->player.redforce.player2.weapon.uzi.kills +=1;
                }
                else if (temp1 == "pkm") {
                    p->player.redforce.player2.weapon.pkm.kills +=1;
                }
                else if (temp1 == "ak74") {
                    p->player.redforce.player2.weapon.ak74.kills +=1;
                }
                else if (temp1 == "svd") {
                    p->player.redforce.player2.weapon.svd.kills +=1;
                }
                else if (temp1 == "gp25") {
                    p->player.redforce.player2.weapon.gp25.kills +=1;
                }
                else if (temp1 == "ssg3000") {
                    p->player.redforce.player2.weapon.ssg3000.kills +=1;
                }
                else if (temp1 == "weapmortar") {
                    p->player.redforce.player2.weapon.weapmortar.kills +=1;
                }
                else if (temp1 == "spark_shower") {
                    p->player.redforce.player2.weapon.spark_shower.kills +=1;
                }
                else if (temp1 == "monster_mortar") {
                    p->player.redforce.player2.weapon.monster_mortar.kills +=1;
                }
                else if (temp1 == "func_tank") {
                    p->player.redforce.player2.weapon.func_tank.kills +=1;
                }
                else if (temp1 == "env_explosion") {
                    p->player.redforce.player2.weapon.env_explosion.kills +=1;
                }
                else if (temp1 == "concussion") {
                    p->player.redforce.player2.weapon.concussion.kills +=1;
                }
                else if (temp1 == "ammobox") {
                    p->player.redforce.player2.weapon.ammobox.kills +=1;
                }
            }
            else {
                TEAM = false;
                p->player.blueforce.player2.kills += 1;
                if (temp1 == "knife") {
                    p->player.blueforce.player2.weapon.knife.kills += 1;
                }
                else if (temp1 == "coltgov") {
                    p->player.blueforce.player2.weapon.coltgov.kills +=1;
                }
                else if (temp1 == "ber92f") {
                    p->player.blueforce.player2.weapon.ber92f.kills +=1;
                }
                else if (temp1 == "ber93r") {
                    p->player.blueforce.player2.weapon.ber93r.kills +=1;
                }
                else if (temp1 == "anaconda") {
                    p->player.blueforce.player2.weapon.anaconda.kills +=1;
                }
                else if (temp1 == "desert") {
                    p->player.blueforce.player2.weapon.desert.kills +=1;
                }
                else if (temp1 == "benelli") {
                    p->player.blueforce.player2.weapon.benelli.kills +=1;
                }
                else if (temp1 == "saiga") {
                    p->player.blueforce.player2.weapon.saiga.kills +=1;
                }
                else if (temp1 == "mp5a5") {
                    p->player.blueforce.player2.weapon.mp5a5.kills +=1;
                }
                else if (temp1 == "sterling") {
                    p->player.blueforce.player2.weapon.sterling.kills +=1;
                }
                else if (temp1 == "bizon") {
                    p->player.blueforce.player2.weapon.bizon.kills +=1;
                }
                else if (temp1 == "ak47") {
                    p->player.blueforce.player2.weapon.ak47.kills +=1;
                }
                else if (temp1 == "famas") {
                    p->player.blueforce.player2.weapon.famas.kills +=1;
                }
                else if (temp1 == "g3a3") {
                    p->player.blueforce.player2.weapon.g3a3.kills +=1;
                }
                else if (temp1 == "g36e") {
                    p->player.blueforce.player2.weapon.g36e.kills +=1;
                }
                else if (temp1 == "m16") {
                    p->player.blueforce.player2.weapon.m16.kills +=1;
                }
                else if (temp1 == "m203") {
                    p->player.blueforce.player2.weapon.m203.kills +=1;
                }
                else if (temp1 == "m82") {
                    p->player.blueforce.player2.weapon.m82.kills +=1;
                }
                else if (temp1 == "m60") {
                    p->player.blueforce.player2.weapon.m60.kills +=1;
                }
                else if (temp1 == "m79") {
                    p->player.blueforce.player2.weapon.m79.kills +=1;
                }
                else if (temp1 == "claymore") {
                    p->player.blueforce.player2.weapon.claymore.kills +=1;
                }
                else if (temp1 == "frag") {
                    p->player.blueforce.player2.weapon.frag.kills +=1;
                }
                else if (temp1 == "stg24") {
                    p->player.blueforce.player2.weapon.stg24.kills +=1;
                }
                else if (temp1 == "uzi") {
                    p->player.blueforce.player2.weapon.uzi.kills +=1;
                }
                else if (temp1 == "pkm") {
                    p->player.blueforce.player2.weapon.pkm.kills +=1;
                }
                else if (temp1 == "ak74") {
                    p->player.blueforce.player2.weapon.ak74.kills +=1;
                }
                else if (temp1 == "svd") {
                    p->player.blueforce.player2.weapon.svd.kills +=1;
                }
                else if (temp1 == "gp25") {
                    p->player.blueforce.player2.weapon.gp25.kills +=1;
                }
                else if (temp1 == "ssg3000") {
                    p->player.blueforce.player2.weapon.ssg3000.kills +=1;
                }
                else if (temp1 == "weapmortar") {
                    p->player.blueforce.player2.weapon.weapmortar.kills +=1;
                }
                else if (temp1 == "spark_shower") {
                    p->player.blueforce.player2.weapon.spark_shower.kills +=1;
                }
                else if (temp1 == "monster_mortar") {
                    p->player.blueforce.player2.weapon.monster_mortar.kills +=1;
                }
                else if (temp1 == "func_tank") {
                    p->player.blueforce.player2.weapon.func_tank.kills +=1;
                }
                else if (temp1 == "env_explosion") {
                    p->player.blueforce.player2.weapon.env_explosion.kills +=1;
                }
                else if (temp1 == "concussion") {
                    p->player.blueforce.player2.weapon.concussion.kills +=1;
                }
                else if (temp1 == "ammobox") {
                    p->player.blueforce.player2.weapon.ammobox.kills +=1;
                }
            }
            return;
        } //End IF
    } // End for
    // Name Not Found, Create new and Re-Add Statistic
    newplayerdata(temp2);
    playerkill(temp);
}



/*--------------------------------------------------------------------------------*/
// Parses for New Map Started
void mapstarted(string logline) {

    CONFIG         cfg;  // Handle to Current Map

     struct ListItem13 *p;
    string temp = logline,temp2;
    char temp3[30]={0};

      int    st1 = -1,
           st2 = -1,
        ct  =  0;

      // Start by getting Map Name
       st1 = temp.find("\"", 0);                  // Getting Starting of Name
    st2 = temp.find("\"", st1 +2);             // Getting Ending of Name
    ++st1;                                     // Incirment to get rid of "
    temp2 = temp.substr(st1,st2);              // Splits String / Sometimes leaves to much at end
    ct = st2 - st1;                            // Gets Name Length
    if (temp2.length() > ct)                   // Check for Proper Name Length
        temp2.erase(ct,temp2.length());    // Erase Any Extra Character at the end
    strcpy(NEWMAP,temp2.c_str());
    strcpy(cfg.currmap,temp2.c_str());
    return;
}


/*--------------------------------------------------------------------------------*/
// Parses for Team Joined
void joinedteam(string logline) {

    struct ListItem13 *p;
    string temp = logline,temp2;
    char temp3[30]={0};

      int    st1 = -1,
        st2 = -1,
        ct  =  0;

      // Start by getting Player's Name
       st1 = temp.find("\"", 0);
       st2 = temp.find("<", st1 +2);
       ++st1;
    temp2 = temp.substr(st1,st2);
    ct = st2 - st1;
    if (temp2.length() > ct)
        temp2.erase(ct,temp2.length());
    strcpy(temp3,temp2.c_str());

    // Do Testing if player name is in list, Update it with New Data
    for ( p = MyList13 ; p != 0 ; p = p->next ) {
        if (strcmp(p->player.playername,temp3) == 0) {
            st1 = -1;
            st2 = -1;

            if( temp.find("<Red Force>", 0) != -1) {
                TEAM = true;
                //p->player.blueforce.player2.joins += 1;
            }
            else {
                TEAM = false;
                //p->player.redforce.player2.joins += 1;
            }
            return;
        }
    }
    // Name Not Found, Create new and Add Statistic
    newplayerdata(temp2);
    joinedteam(temp);
}


/*--------------------------------------------------------------------------------*/
// Parses Each String and Breaks up the Data and Sorts into Link List Data Structures
void proc1str(string logline) {

    // Test for Current Map
    if(strcmp(NEWMAP,MAPNAME)!=0 ){
        strcpy(MAPNAME,NEWMAP);
    }

    string temp  = logline;        // Temp Container

    // iTEMS NOT BEING TRACKED, sKIP TO SPEED UP PROCESSING
    if(temp.find("[META]", 0) != -1) {
            return;
    }
    else if(temp.find("[ADMIN]", 0) != -1) {
            return;
    }
    else if(temp.find("Rcon: \"", 0) != -1) {
            return;
    }
    else if(temp.find("say \"", 0) != -1) {
            return;
    }
    else if(temp.find("say_team \"", 0) != -1) {
            return;
    }
    else if(temp.find("Server cvar \"", 0) != -1) {
            return;
    }
    else if(temp.find("Server say \"", 0) != -1) {
            return;
    }
    else if(temp.find("triggered \"", 0) != -1) {
            return;
    }
    else if(temp.find("\" connected", 0) != -1) {
            return;
    }
    else if(temp.find("\" disconnected", 0) != -1) {
            return;
    }


    //---------------------------------------------------------//
    // If these Substrings are found start processing

    //---------------------------------------------------------//
    // Start Inexding Found Elements in Sting

    /*
    id1 = temp.find("connected,", 0);                       // Checking for Connection
    if(id1 != -1) {
            memset(&player,0,sizeof(PLAYERREC));            // Clear Structure from memory
            // Get Players Name
            st1 = temp.find("\"", 0);                       // Getting Starting of Name
            st2 = temp.find("<", st1 +2);                   // Getting Ending of Name
            ++st1;                                          // Incirment to get rid of "
            temp2 = temp.substr(st1,st2);                   // Splits String / Sometimes leaves to much at end
            ct = st2 - st1;                                 // Gets Name Length
            if (temp2.length() > ct)                        // Check for Proper Name Length
                    temp2.erase(ct,temp2.length());         // Erase Any Extra Character at the end
            strcpy(temp3,temp2.c_str());                    // Converts String to c string
            strcpy(player.name,temp3);
            exists = newplayerdata(temp3);
            if(exists == true) {
                    // No need to create it if it exists Here
                    //updateplayerdata(&player);
            }
            memset(&player,0,sizeof(PLAYERREC));
            //addplayer(temp3);
            return;
    }  */

    if(temp.find("joined team \"", 0) != -1) {
        joinedteam(temp);
        return;
    }
    else if(temp.find("Started map \"", 0) != -1) {
        mapstarted(temp); // Sets Current Map
        return;
    }
    else if(temp.find("killed \"", 0) != -1) {
        playerkill(temp); // Registers The Players Kill
        // Cut String and send Second part for processing
        // of who received the Death
        int id1 = 0;
        string temp1;
        id1 = temp.find("killed \"", 0);
        temp1 = temp.substr(id1+7,temp.length());
        playerdied(temp1); // Registed a Death for This Other Player
        return;
    }
    else if(temp.find("committed suicide", 0) != -1) {
        playersuicide(temp); // Registers player killed himself
        return;
    }
    else if(temp.find("attacked \"", 0) != -1) {
        playerdamdelt(temp); // Registers Damage Delt
        // Cut String and send Second part for processing
        // of who received the damage
        int id1 = 0;
        string temp1;
        id1 = temp.find("attacked \"", 0);
        temp1 = temp.substr(id1+9,temp.length());
        playerdamrec(temp1);  // Registers Damaged Received
        return;
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Breaks up Multiple Log Lines Found in 1 String before String Conversions
void checkstr(string logdata) {

    string temp = logdata;                  // Temp Container for Processing
    string temp2;                           // Container for Broken Up Strings

    int id1 = -1;                           // String Position for "L " Begining of Log Entry
    int id2 =  0;                           // ID2 is used becasue some Strings have multiple Log Lines,

    id1 = temp.find("L ", 0);               // Find the Begining of Each Log Line
    while (id1 != string::npos) {           // Not End of String
        id2 = id1;                      // place in temp container
        // \r catchs the line, carriage return for multi lines is 1 string
        // Mainly a fix for Linux log files
        id1 = temp.find("\rL ", id2 +1);  // Find the Begining of Each Log Line

        if(id1 == -1 && id2 == 0) {
            proc1str(temp);                               // Process String
            return;
        }
        if(id1 != -1 && id2 == 0) {  // First Instance of Manylines
            temp2 = temp.substr(id2,id1);                 // Splits String
            proc1str(temp2);                              // Proceses String
            continue;
        }
        if(id1 != -1 && id2 != 0) { // Remaining Instances on Manylines (Middle Lines)
            temp2 = temp.substr(id2,id1);                 // Splits String
            // Break into 1 Single Line,
            temp2.erase(id1-id2,temp2.length());          // FIX FOR SPLIT!!!
            proc1str(temp2);                              // Processes String
            continue;
        }
        if(id1 == -1 && id2 != 0) { // Chops off Last Line from string of many lines
            temp2 = temp.substr(id2,temp.length());       // Splits String
            proc1str(temp2);                              // Process String
            return;
        }
    }
    return;
}


/*--------------------------------------------------------------------------------*/
// LOG PARSING FUNCTIONS
/*--------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------*/
// Read Log File And Send Strings for Testing and Spliting Before Parsing
int parselog(char * logname) {

    string name;
    name = logname;
    name = LOGPATH+name;

    clearpercentleft();

    // Variable for Counting Number of lines in the file
    // This is being used to skip / Ignore the last line in the Log file when reading
    long recCount = 0;
    int c = 0;

    FILE *File=NULL;
    if (!(File=fopen(name.c_str(),"r"))) {
        // if access to the file itself is denied.
        char text1[40] = "Unable to Read Log File! ";
        drawleft(text1,12,0);
        char text2[40];
        strcpy(text2,name.c_str());
        drawleft2(text2,12,0);
        return (-5); // Returns -5 Showing that the file was in error, or Not Found.
                     // This Error Return is not handeled yet..
    }

    while((c = getc(File)) != EOF) {
        if(c == '\n') ++recCount;
        else if(c == '\r') ++recCount;
    }
    fclose(File);

    long counter;
    counter = 0;

    // Start Log Parsing Here Using C++ File I/O
    ifstream inStream;   // Handle to File Stream
    inStream.open( name.c_str() );

    if (!inStream.is_open()) {
        char text1[40] = "Unable to Read Log File! ";
        drawleft(text1,12,0);
        char text2[40];
        strcpy(text2,name.c_str());
        drawright(text2,12,0);
        return (-5); // Returns -5 Showing that the file was in error, or Not Found.
                     // This Error Return is not handeled yet..
    }

    clearallleft();

    char text1[40];
    sprintf(text1,"Parsing: %s ",logname);
    drawleft(text1,3,0);

    string logdata; // Holds Each Line Read in from the Log File

    double p1;
    char   p2[5];
    // tests if a valid file was found to read from

    for (;;) {
        getline(inStream,logdata);  // Gets line from log till '\n' & Stores in string
        checkstr(logdata);
        ++counter;                  // Prase's the string And splits for Processin
        // Skip Last Line in Log File to Prevent Bad Log's and Errors
        if(counter == recCount) break;
        if(counter == recCount / 2) percentleft(67);
        if(inStream.eof()) break;   // End of File Break
    }
    inStream.close();

    percentleft(100);
    char text3[40];
    sprintf(text3,"Completed OK! ");
    drawleft2(text3,9,0);

    clearallright();

    #ifdef _WIN32
    Sleep(1000);
    #else
    system("sleep 1s");
    #endif

    char text2[40];
    sprintf(text2,"Saving: %s ",logname);
    drawright(text2,3,0);

    copyplayerdata();   // Copy Player Data from Memory to Mapname.dat
    percentright(100);  // Send 100% to GUI

    char text4[40];
    sprintf(text4,"Completed OK! ");
    drawright2(text4,9,0);

    #ifdef _WIN32
    Sleep(1000);
    #else
    system("sleep 1s");
    #endif

    clearallleft();
    clearplayerdata();  // Remove Player Link List Data From Memory

    return 0;
}

/*--------------------------------------------------------------------------------*/
// Setup Log Parsing, Throw Names in Link List for Sorting in Creation Order
void resortlog() {

    // Takes Already processed logs from .Dat, Sorts them with the rest of the
    // Logs files, then copies old and New ones to Dat file in Proper Ordering.
    LOGNAME log;

    int total = countlogs();
    int idx   = 0;

    while (read(&log,idx)) {
    lognamesort(&log);
        ++idx;
    }

    struct ListItem16 *lg;
    int tidx  = 0;

    for ( lg = MyList16 ; lg != 0 ; lg = lg->next ) {
        lg->log.index = tidx;
        write(&lg->log,tidx);
        ++tidx;
    }
    clearlogdata();
    return;
}


/*--------------------------------------------------------------------------------*/
// Small Loop to Kick off Log Parsing
void runparse() {

    // Parses only New Logs
    struct ListItem16 *lg;

    if(MyList16 == 0) return;

    double total = 0,
           count = 0,
           p1    = 0;

    for ( lg = MyList16 ; lg != 0 ; lg = lg->next ) { ++total; }

    for ( lg = MyList16 ; lg != 0 ; lg = lg->next ) {
        ++count;
        p1 = compwkillpercent1(count,total);
        if (p1 == 100) p1 = 95;
        percenttop(p1);
        parselog(lg->log.name);
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Reads for Log Files Then Index's them into Log.dat And Parses them..
void addlog()
{

    LOGNAME      log;

    // Windows 32 Files / Folder Read Function
    #ifdef _WIN32
    WIN32_FIND_DATA wfd;   // File Structure
    HANDLE          h;     // Handle to File
    int             idx;

    SetCurrentDirectory(LOGPATH);

    h = FindFirstFile("l*.log", &wfd);
    if(h != INVALID_HANDLE_VALUE) {
        strcpy(log.name,wfd.cFileName);
        log.index = idx;
        if (matchlog(log.name) != true) lognamesort(&log);
    }
    while(FindNextFile(h, &wfd)) {
        idx = countlogs();
        strcpy(log.name,wfd.cFileName);
        log.index = idx;
        if (matchlog(log.name) != true) lognamesort(&log);
    }
    FindClose(h);
    SetCurrentDirectory(PATH);

    #else //efdef _LINUX
       int          idx;

    DIR * dir = opendir(LOGPATH);

    struct dirent **namelist;
    int n;
    string lname;

    n = scandir(".", &namelist, 0, alphasort);
    if (n < 0) perror("scandir");
    else {
        while(n--) {
            idx = countlogs();
            if (namelist[n]->d_name[0] == 'L') {
                lname = (namelist[n]->d_name);
                //st1 = -1;
                if (lname.find(".log") != -1) {
                    log.index = idx;
                    strcpy(log.name,lname.c_str());
                    // If Log is In Database, Skip it
                    if (matchlog(log.name) != true) {
                        lognamesort(&log);
                    }
                }
            }
            free(namelist[n]);
        }
    }
    free(namelist);
    closedir(dir);
       #endif

    return;
}


/*--------------------------------------------------------------------------------*/
// Kicks off All Log Parsing Functions
void dologparsing() {

    addlog();               // Adds Log to Link List, And checks if in Log.dat

    // Draws The Title for the Current Process
    char title[100] = "Parsing Server Log Files . . .";
    drawtop(title,11,0,24);

      runparse();             // Kicks off Log Parsing. With logs in Link List *NEW*
    resortlog();            // Grabs all Logs from Dat and Sorts them all Saves back to Log.dat
    percenttop(100);

    #ifdef _WIN32
    Sleep(1000);
    #else
    system("sleep 1s");
    #endif

    return;
}

#endif

