#ifndef __STATS_CPP    /*  An extra safeguard to prevent this header from  */
#define __STATS_CPP    /*  being included twice in the same source file    */

// This file Processes both the Rank and Players HTML Files, Also Computing Statistics

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

#include "structs.h"              // Player / Weapon / Linklist Structures
#include "LogFunc.h"
#include "PlayerFunc.h"           // Displaying Link list with Players
#include "Mapfunc.h"
#include "WeaponFunc.h"
#include "FA26.h"
#include "Stats.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN_AND_MEAN
#include <windows.h>
#include "wincon.h"
#endif

using namespace std;              // Standard C++ Namespace

/*--------------------------------------------------------------------------------*/
// GLOBALS - Link List's For Data Contianers
/*--------------------------------------------------------------------------------*/

struct ListItem12 *MyList12 = 0 ; // Holds Player Ranks .dat Data            PLAYERREC
struct ListItem14 *MyList14 = 0 ; // Holding All Player Data while Creating HTML Files    PLAYERREC
struct ListItem15 *MyList15 = 0 ; // Holding all Weapon Data While Calculating Stats    WEAPONREC
struct ListItem18 *MyList18 = 0 ; // Holding All Player Data while Creating HTML Files    PLAYERREC

/*--------------------------------------------------------------------------------*/
// LINK LISTS Data Sorting Functions & Memory Freeing Functions
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearplayercontainer() {

    struct ListItem14 *p,*next;
    if ( MyList14 == 0) return;

    for(p = MyList14 ; p !=0 ; p = next ) {
        next = p->next;
        delete (p);
    }
    MyList14 = 0; // Make sure that list point to 0 (Empty list)
}

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearprank2() {

    struct ListItem18 *p,*next;
    if ( MyList18 == 0) return;

    for(p = MyList18 ; p !=0 ; p = next ) {
        next = p->next;
        delete (p);
    }
    MyList18 = 0; // Make sure that list point to 0 (Empty list)
}

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearweaponcont() {

    struct ListItem15 *p,*next;
    if ( MyList15 == 0)    return;

    for(p = MyList15 ; p !=0 ; p = next ) {
        next = p->next;
        delete (p);
    }
    MyList15 = 0; // Make sure that list point to 0 (Empty list)
}

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearplayerrank() {

    struct ListItem12 *p,*next;
    if ( MyList12 == 0) return;

    for(p = MyList12 ; p !=0 ; p = next ) {
        next = p->next;
        delete (p);
    }
    MyList12 = 0; // Make sure that list point to 0 (Empty list)
}

/*--------------------------------------------------------------------------------*/
// This Function Holds All Player Data While Creating HTML Files
// Contains no Sorting of Player Records
void playerdatacontainer(PLAYERREC * player) {

    struct ListItem14 *last;
    string data;

    ListItem14 *item = new ListItem14;
    if( !item ) {
        cout << "Malloc Failed for holding Player Data\n";
        cout << "You do not have enough memory for this program!\n";
        exit(1);
    }

    item->player = (*player);
    item->next = 0;

    if ( MyList14 == 0 ) {  // If List is Empty, make this the first item
        MyList14 = item;
        return;
    }

    for( last = MyList14 ; last->next != 0 ; last = last->next );
    last->next = item;      // Append New Item to Last Item
    return;

}


/*--------------------------------------------------------------------------------*/
// This Function Holds All Weapon Data While Creating HTML Files
// Contains no Data Sorting
void weapondatacont(WEAPONREC * weapon) {

    struct ListItem15 *last;
    string data;

    ListItem15 *item = new ListItem15;
    if( !item ) {
        cout << "Malloc Failed for holding Player Data\n";
        cout << "You do not have enough memory for this program!\n";
        exit(1);
    }

    item->weapon = (*weapon);
    item->next = 0;

    if ( MyList15 == 0 ) {  // If List is Empty, make this the first item
        MyList15 = item;
        return;
    }

    for( last = MyList15 ; last->next != 0 ; last = last->next );
    last->next = item;      // Append New Item to Last Item
    return;
}

/*--------------------------------------------------------------------------------*/
// Sorting Functions for Rankings & Calculating Statistics
/*--------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------*/
// This Function Holds All Weapon Data While Creating HTML Files
void weaponkillsortcont(WEAPONREC * weapon) {

    struct ListItem15 *next;
    string data;

    ListItem15 *item = new ListItem15;
    if( !item ) {
        cout << "Malloc Failed for holding Player Data\n";
        cout << "You do not have enough memory for this program!\n";
        exit(1);
    }

    item->weapon = (*weapon);
    item->next = 0;

    if ( MyList15 == 0 ) {                  // If List is Empty, make this the first item
        MyList15 = item;
        return;
    }
    if((weapon->kills - MyList15->weapon.kills) > 0 ) {
        item->next = MyList15;
        MyList15 = item;
        return;
    }

    // Check to see if an item is inserted before the next item
    for ( next = MyList15 ; next->next != 0 ; next = next->next ) {
        if ((weapon->kills - next->next->weapon.kills) > 0 ) {
            // Insert Item before the next Item.
            item->next = next->next;
            next->next = item ;
            return;
        }
    }
    // There are no more Items ! Add to end
    next->next = item;
    return;
}

/*--------------------------------------------------------------------------------*/
// This Function Updates Players Statsics in the Link List
void addplayermapstats(PLAYERREC * player)
{
    struct ListItem12 *p;

    // Do Testing if player name is in list, Update it with New Data
    for ( p = MyList12 ; p != 0 ; p = p->next ) {
        if (strcmp(p->player.name,player->playername) == 0) {
            if (strcmp(p->player.name,player->playername) == 0) {

                p->player.kills         += player->redforce.player2.kills;
                p->player.deaths        += player->redforce.player2.deaths;
                p->player.sui           += player->redforce.player2.sui;
                p->player.damdelt       += player->redforce.player2.damdelt;
                p->player.damrec        += player->redforce.player2.damrec;
                p->player.dambleed      += player->redforce.player2.dambleed;

                p->player.kills         += player->blueforce.player2.kills;
                p->player.deaths        += player->blueforce.player2.deaths;
                p->player.sui            += player->blueforce.player2.sui;
                p->player.damdelt       += player->blueforce.player2.damdelt;
                p->player.damrec        += player->blueforce.player2.damrec;
                p->player.dambleed      += player->blueforce.player2.dambleed;

                p->player.weapon.m203.kills           += player->redforce.player2.weapon.m203.kills;
                p->player.weapon.famas.kills          += player->redforce.player2.weapon.famas.kills;
                p->player.weapon.g36e.kills           += player->redforce.player2.weapon.g36e.kills;
                p->player.weapon.benelli.kills        += player->redforce.player2.weapon.benelli.kills;
                p->player.weapon.saiga.kills          += player->redforce.player2.weapon.saiga.kills;
                p->player.weapon.m16.kills            += player->redforce.player2.weapon.m16.kills;
                p->player.weapon.ak47.kills           += player->redforce.player2.weapon.ak47.kills;
                p->player.weapon.m82.kills            += player->redforce.player2.weapon.m82.kills;
                p->player.weapon.bizon.kills          += player->redforce.player2.weapon.bizon.kills;
                p->player.weapon.knife.kills          += player->redforce.player2.weapon.knife.kills;
                p->player.weapon.coltgov.kills        += player->redforce.player2.weapon.coltgov.kills;
                p->player.weapon.ber92f.kills         += player->redforce.player2.weapon.ber92f.kills;
                p->player.weapon.ber93r.kills         += player->redforce.player2.weapon.ber93r.kills;
                p->player.weapon.desert.kills         += player->redforce.player2.weapon.desert.kills;
                p->player.weapon.anaconda.kills       += player->redforce.player2.weapon.anaconda.kills;
                p->player.weapon.stg24.kills          += player->redforce.player2.weapon.stg24.kills;
                p->player.weapon.claymore.kills       += player->redforce.player2.weapon.claymore.kills;
                p->player.weapon.sterling.kills       += player->redforce.player2.weapon.sterling.kills;
                p->player.weapon.mp5a5.kills          += player->redforce.player2.weapon.mp5a5.kills;
                p->player.weapon.g3a3.kills           += player->redforce.player2.weapon.g3a3.kills;
                p->player.weapon.m60.kills            += player->redforce.player2.weapon.m60.kills;
                p->player.weapon.m79.kills            += player->redforce.player2.weapon.m79.kills;
                p->player.weapon.frag.kills           += player->redforce.player2.weapon.frag.kills;
                p->player.weapon.uzi.kills            += player->redforce.player2.weapon.uzi.kills;
                p->player.weapon.pkm.kills            += player->redforce.player2.weapon.pkm.kills;
                p->player.weapon.ak74.kills           += player->redforce.player2.weapon.ak74.kills;
                p->player.weapon.svd.kills            += player->redforce.player2.weapon.svd.kills;
                p->player.weapon.gp25.kills           += player->redforce.player2.weapon.gp25.kills;
                p->player.weapon.ssg3000.kills        += player->redforce.player2.weapon.ssg3000.kills;
                p->player.weapon.weapmortar.kills     += player->redforce.player2.weapon.weapmortar.kills;
                p->player.weapon.spark_shower.kills   += player->redforce.player2.weapon.spark_shower.kills;
                p->player.weapon.monster_mortar.kills += player->redforce.player2.weapon.monster_mortar.kills;
                p->player.weapon.func_tank.kills      += player->redforce.player2.weapon.func_tank.kills;
                p->player.weapon.env_explosion.kills  += player->redforce.player2.weapon.env_explosion.kills;
                p->player.weapon.concussion.kills     += player->redforce.player2.weapon.concussion.kills;
                p->player.weapon.ammobox.kills        += player->redforce.player2.weapon.ammobox.kills;

                p->player.weapon.m203.kills           += player->blueforce.player2.weapon.m203.kills;
                p->player.weapon.famas.kills          += player->blueforce.player2.weapon.famas.kills;
                p->player.weapon.g36e.kills           += player->blueforce.player2.weapon.g36e.kills;
                p->player.weapon.benelli.kills        += player->blueforce.player2.weapon.benelli.kills;
                p->player.weapon.saiga.kills          += player->blueforce.player2.weapon.saiga.kills;
                p->player.weapon.m16.kills            += player->blueforce.player2.weapon.m16.kills;
                p->player.weapon.ak47.kills           += player->blueforce.player2.weapon.ak47.kills;
                p->player.weapon.m82.kills            += player->blueforce.player2.weapon.m82.kills;
                p->player.weapon.bizon.kills          += player->blueforce.player2.weapon.bizon.kills;
                p->player.weapon.knife.kills          += player->blueforce.player2.weapon.knife.kills;
                p->player.weapon.coltgov.kills        += player->blueforce.player2.weapon.coltgov.kills;
                p->player.weapon.ber92f.kills         += player->blueforce.player2.weapon.ber92f.kills;
                p->player.weapon.ber93r.kills         += player->blueforce.player2.weapon.ber93r.kills;
                p->player.weapon.desert.kills         += player->blueforce.player2.weapon.desert.kills;
                p->player.weapon.anaconda.kills       += player->blueforce.player2.weapon.anaconda.kills;
                p->player.weapon.stg24.kills          += player->blueforce.player2.weapon.stg24.kills;
                p->player.weapon.claymore.kills       += player->blueforce.player2.weapon.claymore.kills;
                p->player.weapon.sterling.kills       += player->blueforce.player2.weapon.sterling.kills;
                p->player.weapon.mp5a5.kills          += player->blueforce.player2.weapon.mp5a5.kills;
                p->player.weapon.g3a3.kills           += player->blueforce.player2.weapon.g3a3.kills;
                p->player.weapon.m60.kills            += player->blueforce.player2.weapon.m60.kills;
                p->player.weapon.m79.kills            += player->blueforce.player2.weapon.m79.kills;
                p->player.weapon.frag.kills           += player->blueforce.player2.weapon.frag.kills;
                p->player.weapon.uzi.kills            += player->blueforce.player2.weapon.uzi.kills;
                p->player.weapon.pkm.kills            += player->blueforce.player2.weapon.pkm.kills;
                p->player.weapon.ak74.kills           += player->blueforce.player2.weapon.ak74.kills;
                p->player.weapon.svd.kills            += player->blueforce.player2.weapon.svd.kills;
                p->player.weapon.gp25.kills           += player->blueforce.player2.weapon.gp25.kills;
                p->player.weapon.ssg3000.kills        += player->blueforce.player2.weapon.ssg3000.kills;
                p->player.weapon.weapmortar.kills     += player->blueforce.player2.weapon.weapmortar.kills;
                p->player.weapon.spark_shower.kills   += player->blueforce.player2.weapon.spark_shower.kills;
                p->player.weapon.monster_mortar.kills += player->blueforce.player2.weapon.monster_mortar.kills;
                p->player.weapon.func_tank.kills      += player->blueforce.player2.weapon.func_tank.kills;
                p->player.weapon.env_explosion.kills  += player->blueforce.player2.weapon.env_explosion.kills;
                p->player.weapon.concussion.kills     += player->blueforce.player2.weapon.concussion.kills;
                p->player.weapon.ammobox.kills        += player->blueforce.player2.weapon.ammobox.kills;

                p->player.weapon.m203.deaths           += player->redforce.player2.weapon.m203.deaths;
                p->player.weapon.famas.deaths          += player->redforce.player2.weapon.famas.deaths;
                p->player.weapon.g36e.deaths           += player->redforce.player2.weapon.g36e.deaths;
                p->player.weapon.benelli.deaths        += player->redforce.player2.weapon.benelli.deaths;
                p->player.weapon.saiga.deaths          += player->redforce.player2.weapon.saiga.deaths;
                p->player.weapon.m16.deaths            += player->redforce.player2.weapon.m16.deaths;
                p->player.weapon.ak47.deaths           += player->redforce.player2.weapon.ak47.deaths;
                p->player.weapon.m82.deaths            += player->redforce.player2.weapon.m82.deaths;
                p->player.weapon.bizon.deaths          += player->redforce.player2.weapon.bizon.deaths;
                p->player.weapon.knife.deaths          += player->redforce.player2.weapon.knife.deaths;
                p->player.weapon.coltgov.deaths        += player->redforce.player2.weapon.coltgov.deaths;
                p->player.weapon.ber92f.deaths         += player->redforce.player2.weapon.ber92f.deaths;
                p->player.weapon.ber93r.deaths         += player->redforce.player2.weapon.ber93r.deaths;
                p->player.weapon.desert.deaths         += player->redforce.player2.weapon.desert.deaths;
                p->player.weapon.anaconda.deaths       += player->redforce.player2.weapon.anaconda.deaths;
                p->player.weapon.stg24.deaths          += player->redforce.player2.weapon.stg24.deaths;
                p->player.weapon.claymore.deaths       += player->redforce.player2.weapon.claymore.deaths;
                p->player.weapon.sterling.deaths       += player->redforce.player2.weapon.sterling.deaths;
                p->player.weapon.mp5a5.deaths          += player->redforce.player2.weapon.mp5a5.deaths;
                p->player.weapon.g3a3.deaths           += player->redforce.player2.weapon.g3a3.deaths;
                p->player.weapon.m60.deaths            += player->redforce.player2.weapon.m60.deaths;
                p->player.weapon.m79.deaths            += player->redforce.player2.weapon.m79.deaths;
                p->player.weapon.frag.deaths           += player->redforce.player2.weapon.frag.deaths;
                p->player.weapon.uzi.deaths            += player->redforce.player2.weapon.uzi.deaths;
                p->player.weapon.pkm.deaths            += player->redforce.player2.weapon.pkm.deaths;
                p->player.weapon.ak74.deaths           += player->redforce.player2.weapon.ak74.deaths;
                p->player.weapon.svd.deaths            += player->redforce.player2.weapon.svd.deaths;
                p->player.weapon.gp25.deaths           += player->redforce.player2.weapon.gp25.deaths;
                p->player.weapon.ssg3000.deaths        += player->redforce.player2.weapon.ssg3000.deaths;
                p->player.weapon.weapmortar.deaths     += player->redforce.player2.weapon.weapmortar.deaths;
                p->player.weapon.spark_shower.deaths   += player->redforce.player2.weapon.spark_shower.deaths;
                p->player.weapon.monster_mortar.deaths += player->redforce.player2.weapon.monster_mortar.deaths;
                p->player.weapon.func_tank.deaths      += player->redforce.player2.weapon.func_tank.deaths;
                p->player.weapon.env_explosion.deaths  += player->redforce.player2.weapon.env_explosion.deaths;
                p->player.weapon.concussion.deaths     += player->redforce.player2.weapon.concussion.deaths;
                p->player.weapon.ammobox.deaths        += player->redforce.player2.weapon.ammobox.deaths;

                p->player.weapon.m203.deaths           += player->blueforce.player2.weapon.m203.deaths;
                p->player.weapon.famas.deaths          += player->blueforce.player2.weapon.famas.deaths;
                p->player.weapon.g36e.deaths           += player->blueforce.player2.weapon.g36e.deaths;
                p->player.weapon.benelli.deaths        += player->blueforce.player2.weapon.benelli.deaths;
                p->player.weapon.saiga.deaths          += player->blueforce.player2.weapon.saiga.deaths;
                p->player.weapon.m16.deaths            += player->blueforce.player2.weapon.m16.deaths;
                p->player.weapon.ak47.deaths           += player->blueforce.player2.weapon.ak47.deaths;
                p->player.weapon.m82.deaths            += player->blueforce.player2.weapon.m82.deaths;
                p->player.weapon.bizon.deaths          += player->blueforce.player2.weapon.bizon.deaths;
                p->player.weapon.knife.deaths          += player->blueforce.player2.weapon.knife.deaths;
                p->player.weapon.coltgov.deaths        += player->blueforce.player2.weapon.coltgov.deaths;
                p->player.weapon.ber92f.deaths         += player->blueforce.player2.weapon.ber92f.deaths;
                p->player.weapon.ber93r.deaths         += player->blueforce.player2.weapon.ber93r.deaths;
                p->player.weapon.desert.deaths         += player->blueforce.player2.weapon.desert.deaths;
                p->player.weapon.anaconda.deaths       += player->blueforce.player2.weapon.anaconda.deaths;
                p->player.weapon.stg24.deaths          += player->blueforce.player2.weapon.stg24.deaths;
                p->player.weapon.claymore.deaths       += player->blueforce.player2.weapon.claymore.deaths;
                p->player.weapon.sterling.deaths       += player->blueforce.player2.weapon.sterling.deaths;
                p->player.weapon.mp5a5.deaths          += player->blueforce.player2.weapon.mp5a5.deaths;
                p->player.weapon.g3a3.deaths           += player->blueforce.player2.weapon.g3a3.deaths;
                p->player.weapon.m60.deaths            += player->blueforce.player2.weapon.m60.deaths;
                p->player.weapon.m79.deaths            += player->blueforce.player2.weapon.m79.deaths;
                p->player.weapon.frag.deaths           += player->blueforce.player2.weapon.frag.deaths;
                p->player.weapon.uzi.deaths            += player->blueforce.player2.weapon.uzi.deaths;
                p->player.weapon.pkm.deaths            += player->blueforce.player2.weapon.pkm.deaths;
                p->player.weapon.ak74.deaths           += player->blueforce.player2.weapon.ak74.deaths;
                p->player.weapon.svd.deaths            += player->blueforce.player2.weapon.svd.deaths;
                p->player.weapon.gp25.deaths           += player->blueforce.player2.weapon.gp25.deaths;
                p->player.weapon.ssg3000.deaths        += player->blueforce.player2.weapon.ssg3000.deaths;
                p->player.weapon.weapmortar.deaths     += player->blueforce.player2.weapon.weapmortar.deaths;
                p->player.weapon.spark_shower.deaths   += player->blueforce.player2.weapon.spark_shower.deaths;
                p->player.weapon.monster_mortar.deaths += player->blueforce.player2.weapon.monster_mortar.deaths;
                p->player.weapon.func_tank.deaths      += player->blueforce.player2.weapon.func_tank.deaths;
                p->player.weapon.env_explosion.deaths  += player->blueforce.player2.weapon.env_explosion.deaths;
                p->player.weapon.concussion.deaths     += player->blueforce.player2.weapon.concussion.deaths;
                p->player.weapon.ammobox.deaths        += player->blueforce.player2.weapon.ammobox.deaths;

                p->player.weapon.m203.sui           += player->redforce.player2.weapon.m203.sui;
                p->player.weapon.famas.sui          += player->redforce.player2.weapon.famas.sui;
                p->player.weapon.g36e.sui           += player->redforce.player2.weapon.g36e.sui;
                p->player.weapon.benelli.sui        += player->redforce.player2.weapon.benelli.sui;
                p->player.weapon.saiga.sui          += player->redforce.player2.weapon.saiga.sui;
                p->player.weapon.m16.sui            += player->redforce.player2.weapon.m16.sui;
                p->player.weapon.ak47.sui           += player->redforce.player2.weapon.ak47.sui;
                p->player.weapon.m82.sui            += player->redforce.player2.weapon.m82.sui;
                p->player.weapon.bizon.sui          += player->redforce.player2.weapon.bizon.sui;
                p->player.weapon.knife.sui          += player->redforce.player2.weapon.knife.sui;
                p->player.weapon.coltgov.sui        += player->redforce.player2.weapon.coltgov.sui;
                p->player.weapon.ber92f.sui         += player->redforce.player2.weapon.ber92f.sui;
                p->player.weapon.ber93r.sui         += player->redforce.player2.weapon.ber93r.sui;
                p->player.weapon.desert.sui         += player->redforce.player2.weapon.desert.sui;
                p->player.weapon.anaconda.sui       += player->redforce.player2.weapon.anaconda.sui;
                p->player.weapon.stg24.sui          += player->redforce.player2.weapon.stg24.sui;
                p->player.weapon.claymore.sui       += player->redforce.player2.weapon.claymore.sui;
                p->player.weapon.sterling.sui       += player->redforce.player2.weapon.sterling.sui;
                p->player.weapon.mp5a5.sui          += player->redforce.player2.weapon.mp5a5.sui;
                p->player.weapon.g3a3.sui           += player->redforce.player2.weapon.g3a3.sui;
                p->player.weapon.m60.sui            += player->redforce.player2.weapon.m60.sui;
                p->player.weapon.m79.sui            += player->redforce.player2.weapon.m79.sui;
                p->player.weapon.frag.sui           += player->redforce.player2.weapon.frag.sui;
                p->player.weapon.uzi.sui            += player->redforce.player2.weapon.uzi.sui;
                p->player.weapon.pkm.sui            += player->redforce.player2.weapon.pkm.sui;
                p->player.weapon.ak74.sui           += player->redforce.player2.weapon.ak74.sui;
                p->player.weapon.svd.sui            += player->redforce.player2.weapon.svd.sui;
                p->player.weapon.gp25.sui           += player->redforce.player2.weapon.gp25.sui;
                p->player.weapon.ssg3000.sui        += player->redforce.player2.weapon.ssg3000.sui;
                p->player.weapon.weapmortar.sui     += player->redforce.player2.weapon.weapmortar.sui;
                p->player.weapon.spark_shower.sui   += player->redforce.player2.weapon.spark_shower.sui;
                p->player.weapon.monster_mortar.sui += player->redforce.player2.weapon.monster_mortar.sui;
                p->player.weapon.func_tank.sui      += player->redforce.player2.weapon.func_tank.sui;
                p->player.weapon.env_explosion.sui  += player->redforce.player2.weapon.env_explosion.sui;
                p->player.weapon.concussion.sui     += player->redforce.player2.weapon.concussion.sui;
                p->player.weapon.ammobox.sui        += player->redforce.player2.weapon.ammobox.sui;

                p->player.weapon.m203.sui           += player->blueforce.player2.weapon.m203.sui;
                p->player.weapon.famas.sui          += player->blueforce.player2.weapon.famas.sui;
                p->player.weapon.g36e.sui           += player->blueforce.player2.weapon.g36e.sui;
                p->player.weapon.benelli.sui        += player->blueforce.player2.weapon.benelli.sui;
                p->player.weapon.saiga.sui          += player->blueforce.player2.weapon.saiga.sui;
                p->player.weapon.m16.sui            += player->blueforce.player2.weapon.m16.sui;
                p->player.weapon.ak47.sui           += player->blueforce.player2.weapon.ak47.sui;
                p->player.weapon.m82.sui            += player->blueforce.player2.weapon.m82.sui;
                p->player.weapon.bizon.sui          += player->blueforce.player2.weapon.bizon.sui;
                p->player.weapon.knife.sui          += player->blueforce.player2.weapon.knife.sui;
                p->player.weapon.coltgov.sui        += player->blueforce.player2.weapon.coltgov.sui;
                p->player.weapon.ber92f.sui         += player->blueforce.player2.weapon.ber92f.sui;
                p->player.weapon.ber93r.sui         += player->blueforce.player2.weapon.ber93r.sui;
                p->player.weapon.desert.sui         += player->blueforce.player2.weapon.desert.sui;
                p->player.weapon.anaconda.sui       += player->blueforce.player2.weapon.anaconda.sui;
                p->player.weapon.stg24.sui          += player->blueforce.player2.weapon.stg24.sui;
                p->player.weapon.claymore.sui       += player->blueforce.player2.weapon.claymore.sui;
                p->player.weapon.sterling.sui       += player->blueforce.player2.weapon.sterling.sui;
                p->player.weapon.mp5a5.sui          += player->blueforce.player2.weapon.mp5a5.sui;
                p->player.weapon.g3a3.sui           += player->blueforce.player2.weapon.g3a3.sui;
                p->player.weapon.m60.sui            += player->blueforce.player2.weapon.m60.sui;
                p->player.weapon.m79.sui            += player->blueforce.player2.weapon.m79.sui;
                p->player.weapon.frag.sui           += player->blueforce.player2.weapon.frag.sui;
                p->player.weapon.uzi.sui            += player->blueforce.player2.weapon.uzi.sui;
                p->player.weapon.pkm.sui            += player->blueforce.player2.weapon.pkm.sui;
                p->player.weapon.ak74.sui           += player->blueforce.player2.weapon.ak74.sui;
                p->player.weapon.svd.sui            += player->blueforce.player2.weapon.svd.sui;
                p->player.weapon.gp25.sui           += player->blueforce.player2.weapon.gp25.sui;
                p->player.weapon.ssg3000.sui        += player->blueforce.player2.weapon.ssg3000.sui;
                p->player.weapon.weapmortar.sui     += player->blueforce.player2.weapon.weapmortar.sui;
                p->player.weapon.spark_shower.sui   += player->blueforce.player2.weapon.spark_shower.sui;
                p->player.weapon.monster_mortar.sui += player->blueforce.player2.weapon.monster_mortar.sui;
                p->player.weapon.func_tank.sui      += player->blueforce.player2.weapon.func_tank.sui;
                p->player.weapon.env_explosion.sui  += player->blueforce.player2.weapon.env_explosion.sui;
                p->player.weapon.concussion.sui     += player->blueforce.player2.weapon.concussion.sui;
                p->player.weapon.ammobox.sui        += player->blueforce.player2.weapon.ammobox.sui;

                p->player.weapon.m203.damdelt           += player->redforce.player2.weapon.m203.damdelt;
                p->player.weapon.famas.damdelt          += player->redforce.player2.weapon.famas.damdelt;
                p->player.weapon.g36e.damdelt           += player->redforce.player2.weapon.g36e.damdelt;
                p->player.weapon.benelli.damdelt        += player->redforce.player2.weapon.benelli.damdelt;
                p->player.weapon.saiga.damdelt          += player->redforce.player2.weapon.saiga.damdelt;
                p->player.weapon.m16.damdelt            += player->redforce.player2.weapon.m16.damdelt;
                p->player.weapon.ak47.damdelt           += player->redforce.player2.weapon.ak47.damdelt;
                p->player.weapon.m82.damdelt            += player->redforce.player2.weapon.m82.damdelt;
                p->player.weapon.bizon.damdelt          += player->redforce.player2.weapon.bizon.damdelt;
                p->player.weapon.knife.damdelt          += player->redforce.player2.weapon.knife.damdelt;
                p->player.weapon.coltgov.damdelt        += player->redforce.player2.weapon.coltgov.damdelt;
                p->player.weapon.ber92f.damdelt         += player->redforce.player2.weapon.ber92f.damdelt;
                p->player.weapon.ber93r.damdelt         += player->redforce.player2.weapon.ber93r.damdelt;
                p->player.weapon.desert.damdelt         += player->redforce.player2.weapon.desert.damdelt;
                p->player.weapon.anaconda.damdelt       += player->redforce.player2.weapon.anaconda.damdelt;
                p->player.weapon.stg24.damdelt          += player->redforce.player2.weapon.stg24.damdelt;
                p->player.weapon.claymore.damdelt       += player->redforce.player2.weapon.claymore.damdelt;
                p->player.weapon.sterling.damdelt       += player->redforce.player2.weapon.sterling.damdelt;
                p->player.weapon.mp5a5.damdelt          += player->redforce.player2.weapon.mp5a5.damdelt;
                p->player.weapon.g3a3.damdelt           += player->redforce.player2.weapon.g3a3.damdelt;
                p->player.weapon.m60.damdelt            += player->redforce.player2.weapon.m60.damdelt;
                p->player.weapon.m79.damdelt            += player->redforce.player2.weapon.m79.damdelt;
                p->player.weapon.frag.damdelt           += player->redforce.player2.weapon.frag.damdelt;
                p->player.weapon.uzi.damdelt            += player->redforce.player2.weapon.uzi.damdelt;
                p->player.weapon.pkm.damdelt            += player->redforce.player2.weapon.pkm.damdelt;
                p->player.weapon.ak74.damdelt           += player->redforce.player2.weapon.ak74.damdelt;
                p->player.weapon.svd.damdelt            += player->redforce.player2.weapon.svd.damdelt;
                p->player.weapon.gp25.damdelt           += player->redforce.player2.weapon.gp25.damdelt;
                p->player.weapon.ssg3000.damdelt        += player->redforce.player2.weapon.ssg3000.damdelt;
                p->player.weapon.weapmortar.damdelt     += player->redforce.player2.weapon.weapmortar.damdelt;
                p->player.weapon.spark_shower.damdelt   += player->redforce.player2.weapon.spark_shower.damdelt;
                p->player.weapon.monster_mortar.damdelt += player->redforce.player2.weapon.monster_mortar.damdelt;
                p->player.weapon.func_tank.damdelt      += player->redforce.player2.weapon.func_tank.damdelt;
                p->player.weapon.env_explosion.damdelt  += player->redforce.player2.weapon.env_explosion.damdelt;
                p->player.weapon.concussion.damdelt     += player->redforce.player2.weapon.concussion.damdelt;
                p->player.weapon.ammobox.damdelt        += player->redforce.player2.weapon.ammobox.damdelt;

                p->player.weapon.m203.damdelt           += player->blueforce.player2.weapon.m203.damdelt;
                p->player.weapon.famas.damdelt          += player->blueforce.player2.weapon.famas.damdelt;
                p->player.weapon.g36e.damdelt           += player->blueforce.player2.weapon.g36e.damdelt;
                p->player.weapon.benelli.damdelt        += player->blueforce.player2.weapon.benelli.damdelt;
                p->player.weapon.saiga.damdelt          += player->blueforce.player2.weapon.saiga.damdelt;
                p->player.weapon.m16.damdelt            += player->blueforce.player2.weapon.m16.damdelt;
                p->player.weapon.ak47.damdelt           += player->blueforce.player2.weapon.ak47.damdelt;
                p->player.weapon.m82.damdelt            += player->blueforce.player2.weapon.m82.damdelt;
                p->player.weapon.bizon.damdelt          += player->blueforce.player2.weapon.bizon.damdelt;
                p->player.weapon.knife.damdelt          += player->blueforce.player2.weapon.knife.damdelt;
                p->player.weapon.coltgov.damdelt        += player->blueforce.player2.weapon.coltgov.damdelt;
                p->player.weapon.ber92f.damdelt         += player->blueforce.player2.weapon.ber92f.damdelt;
                p->player.weapon.ber93r.damdelt         += player->blueforce.player2.weapon.ber93r.damdelt;
                p->player.weapon.desert.damdelt         += player->blueforce.player2.weapon.desert.damdelt;
                p->player.weapon.anaconda.damdelt       += player->blueforce.player2.weapon.anaconda.damdelt;
                p->player.weapon.stg24.damdelt          += player->blueforce.player2.weapon.stg24.damdelt;
                p->player.weapon.claymore.damdelt       += player->blueforce.player2.weapon.claymore.damdelt;
                p->player.weapon.sterling.damdelt       += player->blueforce.player2.weapon.sterling.damdelt;
                p->player.weapon.mp5a5.damdelt          += player->blueforce.player2.weapon.mp5a5.damdelt;
                p->player.weapon.g3a3.damdelt           += player->blueforce.player2.weapon.g3a3.damdelt;
                p->player.weapon.m60.damdelt            += player->blueforce.player2.weapon.m60.damdelt;
                p->player.weapon.m79.damdelt            += player->blueforce.player2.weapon.m79.damdelt;
                p->player.weapon.frag.damdelt           += player->blueforce.player2.weapon.frag.damdelt;
                p->player.weapon.uzi.damdelt            += player->blueforce.player2.weapon.uzi.damdelt;
                p->player.weapon.pkm.damdelt            += player->blueforce.player2.weapon.pkm.damdelt;
                p->player.weapon.ak74.damdelt           += player->blueforce.player2.weapon.ak74.damdelt;
                p->player.weapon.svd.damdelt            += player->blueforce.player2.weapon.svd.damdelt;
                p->player.weapon.gp25.damdelt           += player->blueforce.player2.weapon.gp25.damdelt;
                p->player.weapon.ssg3000.damdelt        += player->blueforce.player2.weapon.ssg3000.damdelt;
                p->player.weapon.weapmortar.damdelt     += player->blueforce.player2.weapon.weapmortar.damdelt;
                p->player.weapon.spark_shower.damdelt   += player->blueforce.player2.weapon.spark_shower.damdelt;
                p->player.weapon.monster_mortar.damdelt += player->blueforce.player2.weapon.monster_mortar.damdelt;
                p->player.weapon.func_tank.damdelt      += player->blueforce.player2.weapon.func_tank.damdelt;
                p->player.weapon.env_explosion.damdelt  += player->blueforce.player2.weapon.env_explosion.damdelt;
                p->player.weapon.concussion.damdelt     += player->blueforce.player2.weapon.concussion.damdelt;
                p->player.weapon.ammobox.damdelt        += player->blueforce.player2.weapon.ammobox.damdelt;

                p->player.weapon.m203.damrec           += player->redforce.player2.weapon.m203.damrec;
                p->player.weapon.famas.damrec          += player->redforce.player2.weapon.famas.damrec;
                p->player.weapon.g36e.damrec           += player->redforce.player2.weapon.g36e.damrec;
                p->player.weapon.benelli.damrec        += player->redforce.player2.weapon.benelli.damrec;
                p->player.weapon.saiga.damrec          += player->redforce.player2.weapon.saiga.damrec;
                p->player.weapon.m16.damrec            += player->redforce.player2.weapon.m16.damrec;
                p->player.weapon.ak47.damrec           += player->redforce.player2.weapon.ak47.damrec;
                p->player.weapon.m82.damrec            += player->redforce.player2.weapon.m82.damrec;
                p->player.weapon.bizon.damrec          += player->redforce.player2.weapon.bizon.damrec;
                p->player.weapon.knife.damrec          += player->redforce.player2.weapon.knife.damrec;
                p->player.weapon.coltgov.damrec        += player->redforce.player2.weapon.coltgov.damrec;
                p->player.weapon.ber92f.damrec         += player->redforce.player2.weapon.ber92f.damrec;
                p->player.weapon.ber93r.damrec         += player->redforce.player2.weapon.ber93r.damrec;
                p->player.weapon.desert.damrec         += player->redforce.player2.weapon.desert.damrec;
                p->player.weapon.anaconda.damrec       += player->redforce.player2.weapon.anaconda.damrec;
                p->player.weapon.stg24.damrec          += player->redforce.player2.weapon.stg24.damrec;
                p->player.weapon.claymore.damrec       += player->redforce.player2.weapon.claymore.damrec;
                p->player.weapon.sterling.damrec       += player->redforce.player2.weapon.sterling.damrec;
                p->player.weapon.mp5a5.damrec          += player->redforce.player2.weapon.mp5a5.damrec;
                p->player.weapon.g3a3.damrec           += player->redforce.player2.weapon.g3a3.damrec;
                p->player.weapon.m60.damrec            += player->redforce.player2.weapon.m60.damrec;
                p->player.weapon.m79.damrec            += player->redforce.player2.weapon.m79.damrec;
                p->player.weapon.frag.damrec           += player->redforce.player2.weapon.frag.damrec;
                p->player.weapon.uzi.damrec            += player->redforce.player2.weapon.uzi.damrec;
                p->player.weapon.pkm.damrec            += player->redforce.player2.weapon.pkm.damrec;
                p->player.weapon.ak74.damrec           += player->redforce.player2.weapon.ak74.damrec;
                p->player.weapon.svd.damrec            += player->redforce.player2.weapon.svd.damrec;
                p->player.weapon.gp25.damrec           += player->redforce.player2.weapon.gp25.damrec;
                p->player.weapon.ssg3000.damrec        += player->redforce.player2.weapon.ssg3000.damrec;
                p->player.weapon.weapmortar.damrec     += player->redforce.player2.weapon.weapmortar.damrec;
                p->player.weapon.spark_shower.damrec   += player->redforce.player2.weapon.spark_shower.damrec;
                p->player.weapon.monster_mortar.damrec += player->redforce.player2.weapon.monster_mortar.damrec;
                p->player.weapon.func_tank.damrec      += player->redforce.player2.weapon.func_tank.damrec;
                p->player.weapon.env_explosion.damrec  += player->redforce.player2.weapon.env_explosion.damrec;
                p->player.weapon.concussion.damrec     += player->redforce.player2.weapon.concussion.damrec;
                p->player.weapon.ammobox.damrec        += player->redforce.player2.weapon.ammobox.damrec;

                p->player.weapon.m203.damrec           += player->blueforce.player2.weapon.m203.damrec;
                p->player.weapon.famas.damrec          += player->blueforce.player2.weapon.famas.damrec;
                p->player.weapon.g36e.damrec           += player->blueforce.player2.weapon.g36e.damrec;
                p->player.weapon.benelli.damrec        += player->blueforce.player2.weapon.benelli.damrec;
                p->player.weapon.saiga.damrec          += player->blueforce.player2.weapon.saiga.damrec;
                p->player.weapon.m16.damrec            += player->blueforce.player2.weapon.m16.damrec;
                p->player.weapon.ak47.damrec           += player->blueforce.player2.weapon.ak47.damrec;
                p->player.weapon.m82.damrec            += player->blueforce.player2.weapon.m82.damrec;
                p->player.weapon.bizon.damrec          += player->blueforce.player2.weapon.bizon.damrec;
                p->player.weapon.knife.damrec          += player->blueforce.player2.weapon.knife.damrec;
                p->player.weapon.coltgov.damrec        += player->blueforce.player2.weapon.coltgov.damrec;
                p->player.weapon.ber92f.damrec         += player->blueforce.player2.weapon.ber92f.damrec;
                p->player.weapon.ber93r.damrec         += player->blueforce.player2.weapon.ber93r.damrec;
                p->player.weapon.desert.damrec         += player->blueforce.player2.weapon.desert.damrec;
                p->player.weapon.anaconda.damrec       += player->blueforce.player2.weapon.anaconda.damrec;
                p->player.weapon.stg24.damrec          += player->blueforce.player2.weapon.stg24.damrec;
                p->player.weapon.claymore.damrec       += player->blueforce.player2.weapon.claymore.damrec;
                p->player.weapon.sterling.damrec       += player->blueforce.player2.weapon.sterling.damrec;
                p->player.weapon.mp5a5.damrec          += player->blueforce.player2.weapon.mp5a5.damrec;
                p->player.weapon.g3a3.damrec           += player->blueforce.player2.weapon.g3a3.damrec;
                p->player.weapon.m60.damrec            += player->blueforce.player2.weapon.m60.damrec;
                p->player.weapon.m79.damrec            += player->blueforce.player2.weapon.m79.damrec;
                p->player.weapon.frag.damrec           += player->blueforce.player2.weapon.frag.damrec;
                p->player.weapon.uzi.damrec            += player->blueforce.player2.weapon.uzi.damrec;
                p->player.weapon.pkm.damrec            += player->blueforce.player2.weapon.pkm.damrec;
                p->player.weapon.ak74.damrec           += player->blueforce.player2.weapon.ak74.damrec;
                p->player.weapon.svd.damrec            += player->blueforce.player2.weapon.svd.damrec;
                p->player.weapon.gp25.damrec           += player->blueforce.player2.weapon.gp25.damrec;
                p->player.weapon.ssg3000.damrec        += player->blueforce.player2.weapon.ssg3000.damrec;
                p->player.weapon.weapmortar.damrec     += player->blueforce.player2.weapon.weapmortar.damrec;
                p->player.weapon.spark_shower.damrec   += player->blueforce.player2.weapon.spark_shower.damrec;
                p->player.weapon.monster_mortar.damrec += player->blueforce.player2.weapon.monster_mortar.damrec;
                p->player.weapon.func_tank.damrec      += player->blueforce.player2.weapon.func_tank.damrec;
                p->player.weapon.env_explosion.damrec  += player->blueforce.player2.weapon.env_explosion.damrec;
                p->player.weapon.concussion.damrec     += player->blueforce.player2.weapon.concussion.damrec;
                p->player.weapon.ammobox.damrec        += player->blueforce.player2.weapon.ammobox.damrec;
                return;
            }
        }
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// This Function Add New Players to the Link List #13 for Log Parsing
bool newmapdata(string name) {

    struct ListItem12 *p, *last;
    string data;
    for ( p = MyList12 ; p != 0 ; p = p->next ) {
        if (strcmp(p->player.name,name.c_str()) == 0) return false;
    }

    ListItem12 *item = new ListItem12;
    if( !item )    {
        cout << "Malloc Failed for holding Player Data\n";
        cout << "You do not have enough memory for this program!\n";
        exit(1);
    }

     memset(&item->player,0,sizeof(PLAYERREC2)); // Sets all Records to 0
    strcpy(item->player.name,name.c_str());
    item->next = 0;

    if ( MyList12 == 0 ) {  // If List is Empty, make this the first item
        MyList12 = item;
        return true;
    }

    for( last = MyList12 ; last->next != 0 ; last = last->next );
    last->next = item;      // Append New Item to Last Item
    return true;
}


/*--------------------------------------------------------------------------------*/
// Link List for Sorting By Player's Kills
// Sorts Players in Index.HTML
void killsort(PLAYERREC * player) {

    struct ListItem14 *next;
    string data;

    ListItem14 *item = new ListItem14;
    if( !item )    {
        cout << "Malloc Failed for holding Player Data\n";
        cout << "You do not have enough memory for this program!\n";
        exit(1);
    }

    // If it gets here, no Name Match was found, Add New Player to the Link List with Defaults
    // Creates Player And Sets Record's Defaults all to 0 in Memory.

    item->player = (*player);
    item->next = 0;

    if ( MyList14 == 0 ) {
        MyList14 = item;
        return;
    }

    if (TEAM == true) {
        // This is where Sorting takes place!
        // Check if the new item comes before the first item in old list
        if((player->redforce.player2.kills - MyList14->player.redforce.player2.kills) > 0 ) {
            item->next = MyList14;
            MyList14 = item;
            return;
        }
    }
    else {
        // This is where Sorting takes place!
        // Check if the new item comes before the first item in old list
        if((player->blueforce.player2.kills - MyList14->player.blueforce.player2.kills) > 0 ) {
            item->next = MyList14;
            MyList14 = item;
            return;
        }
    }
    // There are no more Items ! Add to end
    next->next = item;
    return;
}


/*--------------------------------------------------------------------------------*/
// Link List For Sorting PlayerRank.dat Players by Kills
// Sorts Players in Index.HTML
void rankkillsort(PLAYERREC2 * player) {

        struct ListItem12 *next;
        string data;

        ListItem12 *item = new ListItem12;
        if( !item )
        {
                cout << "Malloc Failed for holding Player Data\n";
                cout << "You do not have enough memory for this program!\n";
                exit(1);
        }

        // If it gets here, no Name Match was found, Add New Player to the Link List with Defaults
        // Creates Player And Sets Record's Defaults all to 0 in Memory.

        item->player = (*player);
    item->next = 0;

    if ( MyList12 == 0 ) {                  // If List is Empty, make this the first item
            MyList12 = item;
                return;
        }


    if((player->kills - MyList12->player.kills) > 0 ) {
        item->next = MyList12;
        MyList12 = item;
        return;
    }

    // Check to see if an item is inserted before the next item
    for ( next = MyList12 ; next->next != 0 ; next = next->next ) {
        if ((player->kills - next->next->player.kills) > 0 ) {
            // Insert Item before the next Item.
            item->next = next->next;
            next->next = item ;
            return;
        }
    }

    // There are no more Items ! Add to end
    next->next = item;
    return;
}

/*--------------------------------------------------------------------------------*/
// Link List For Sorting PlayerRank.dat Players by Kills
// Sorts Players in Index.HTML
void rankkillsort2(PLAYERREC2 * player) {

    struct ListItem18 *next;
    string data;

    ListItem18 *item = new ListItem18;
    if( !item )    {
        cout << "Malloc Failed for holding Player Data\n";
        cout << "You do not have enough memory for this program!\n";
        exit(1);
    }

    // If it gets here, no Name Match was found, Add New Player to the Link List with Defaults
    // Creates Player And Sets Record's Defaults all to 0 in Memory.

    item->player = (*player);
    strcpy(item->player.weapon.m203.name,"M-203");
    strcpy(item->player.weapon.famas.name,"FA-MAS");
    strcpy(item->player.weapon.g36e.name,"H&K G36E");
    strcpy(item->player.weapon.benelli.name,"BENELLI M3 SUPER 90 P");
    strcpy(item->player.weapon.saiga.name,"SAIGA 12K");
    strcpy(item->player.weapon.m16.name , "M-16A2");
    strcpy(item->player.weapon.ak47.name,"AK-47");
    strcpy(item->player.weapon.m82.name,"BARRET M82A1");
    strcpy(item->player.weapon.bizon.name, "BIZON-2");
    strcpy(item->player.weapon.knife.name , "COMBAT KNIFE");
    strcpy(item->player.weapon.coltgov.name ,"COLT 1911");
    strcpy(item->player.weapon.ber92f.name,"BERETTA 92F");
    strcpy(item->player.weapon.ber93r.name,"BERETTA 93R");
    strcpy(item->player.weapon.desert.name, "IMI DESERT EAGLE");
    strcpy(item->player.weapon.anaconda.name ,"COLT ANACONDA");
    strcpy(item->player.weapon.stg24.name,"STIELHANDGRANATE");
    strcpy(item->player.weapon.claymore.name,"M81 CLAYMORE");
    strcpy(item->player.weapon.sterling.name , "STERLING L2A3MK4");
    strcpy(item->player.weapon.mp5a5.name , "H&K MP5A2-MP5SD2");
    strcpy(item->player.weapon.g3a3.name ,"H&K G3A3");
    strcpy(item->player.weapon.m60.name,"M-60");
    strcpy(item->player.weapon.m79.name , "M-79");
    strcpy(item->player.weapon.frag.name ,"M61-FRAG GRENADE");
    strcpy(item->player.weapon.uzi.name, "IMI UZI");
    strcpy(item->player.weapon.pkm.name ,"PKM");
    strcpy(item->player.weapon.ak74.name , "AK-74");
    strcpy(item->player.weapon.svd.name ,"SVD DRAGUNOV");
    strcpy(item->player.weapon.gp25.name , "GP-25");
    strcpy(item->player.weapon.ssg3000.name , "SIG SSG-3000");
    strcpy(item->player.weapon.weapmortar.name,"MORTAR");
    strcpy(item->player.weapon.spark_shower.name ,"SPARK SHOWER");
    strcpy(item->player.weapon.monster_mortar.name, "MONSTER MORTAR");
    strcpy(item->player.weapon.func_tank.name , "TANK");
    strcpy(item->player.weapon.env_explosion.name,"EXPLOSION");
    strcpy(item->player.weapon.concussion.name ,"CONCUSSION GRENADE");
    strcpy(item->player.weapon.ammobox.name , "AMMO BOX");
    item->next = 0;

    if ( MyList18 == 0 ) {
        MyList18 = item;
        return;
    }
    if((player->kills - MyList18->player.kills) > 0 ) {
        item->next = MyList18;
        MyList18 = item;
        return;
    }
    // Check to see if an item is inserted before the next item
    for ( next = MyList18 ; next->next != 0 ; next = next->next ) {
        if ((player->kills - next->next->player.kills) > 0 ) {
            // Insert Item before the next Item.
            item->next = next->next;
            next->next = item ;
            return;
        }
    }
    // There are no more Items ! Add to end
    next->next = item;
    return;
}



/*--------------------------------------------------------------------------------*/
// Statistics Calculations
/*--------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------*/
// Computes Weapons KILL DEATH+SUICIDE RADIO
long GreatestCommonDivisor(long alpha,   // Kills
                           long beta) {  // Deaths

    alpha = abs(alpha);  // take absolute values of operands
    beta = abs(beta);

    if (beta == 0) return alpha;
    else {
        long remainder = alpha % beta;
        return GreatestCommonDivisor(beta, remainder);
    }
}

/*--------------------------------------------------------------------------------*/
// definition of Simplify() Converts fractions to it simpliest form
string simplify(long myNumerator,
                long myDenominator) {

    long gcd = GreatestCommonDivisor(myNumerator, myDenominator);
    if ((myNumerator || gcd) != 0) {
        myNumerator /= gcd;
        myDenominator /= gcd;
    }
    char temp[12]; // Holds Conversion from Int to String
    sprintf(temp, "%i : %i", myNumerator, myDenominator );
    string result = (temp);
    return result;
}


/*--------------------------------------------------------------------------------*/
// Computes Weapons KILL DEATH SUICIDE PERCENTAGE
double compstatspercent(long double wk,    // Weapon Kills     // Player Kills
                        long double wd,    // Weapon Deaths    // Player Deaths
                        long double ws) {  // Weapon sui       // Player sui

    double wkdp; // = 0;
    if ( wk < (wd + ws)) return (0.0);
    if ( wk + wd > 0 ) {  // Calculates Weapons Kill:Death Percentage w/ sui
        if (wd + ws == 0) return (100.0);
        else {  // Calculate Ratio
            wkdp = 100 * (wk / (wk + wd + ws)); // 0 - 100% Eficency
            return wkdp;
        }
    }
    else return (0.0);

}

/*--------------------------------------------------------------------------------*/
// Computes Weapons KILL Out of Total players Kills Percentage
double compwkillpercent(long double wk,   // Weapon Kills
                        long double pk) { // Player Kills

    double p = (0.0);
    if (pk == 0) return (0.0);
    if ( wk > 0 ) {
        if (wk == pk) return (100.0);
        else {                   // Calculate Ratio
            p = 100 * (wk / pk); // 0 - 100% Eficency
            return p;
        }
    }
    else return (0.0);
}


/*--------------------------------------------------------------------------------*/
// Computes Players & Weapons KILL DEATH SUICIDE PERCENTAGE And Assigns to Players Rec
// With Kill : Death Ratio / And New Attack Damage Statistics
void calcRankPlayerStats() {

    // Generates Player Ranking Data Files
    prankdataexists();

    // Handle to Link List Holding All Player Data
    struct ListItem18 *pl;
    // Handle to List List Holding All Weapon Data
    //struct ListItem15 *wp;

    long         pd      = 0;               // Player Deaths
    long         pf      = 0;               // Player Frags
    long         ps      = 0;               // Player Suicides
    double       kdp     = 0;               // Kill Death Percentage
    string       kdr;                       // Weapon Kill : Death Ratio
    string       dratio;                    // Player Damage Ratio
    // Weapons
    long         wk      = 0;               // Weapon Kills
    long         wd      = 0;               // Weapon Deaths
    long         ws      = 0;               // Weapon Suicides
    double       wkdp    = 0;               // Weapon Kill : Death : Suicide Percentage
    string       wkdr;                      // Weapon Kill : Death Ratio
    double       wpkills = 0;               // Weapon Percentage Kills
    string       wdratio;                   // Weapon Damage Ratio
    // Damage
    long         dd      = 0;               // Damage Delt
    long         dr      = 0;               // Damage Received

    // int widx  = 0; // Weapon Index for Calcing Weapon's Total Stats
    int rank  = 0;

    double p1 = 0,  // Top Percentage
           p2 = 0;  // Left Percentage

    // Do Testing if player name is in list, Update it with New Data
    for ( pl = MyList18 ; pl != 0 ; pl = pl->next ) {
        ++ rank;
        if (rank == MAXRANK+1) break;
        pl->player.rank = rank;

        clearallleft();
        p1 = compwkillpercent1(rank,MAXRANK);
        percenttop(p1);

        char text1[40] = "Create Player Ranks!";
        drawleft(text1,3,0);
        p2 = 0;
        percentleft(0);

        // Calc Player's Stats
        pf = pl->player.kills;                        // Gets #'s for Computing
        pd = pl->player.deaths;
        ps = pl->player.sui;
        dd = pl->player.damdelt;
        dr = pl->player.damrec;
        // Kill Percentage
        kdp = compstatspercent(pf,pd,ps);             // Compute KILL DEATH SUI PERCENTAGE
        pl->player.kdp = kdp;                         // Assign Kill Death Percentage
        // Kill : Death Ratio
        kdr = simplify(pf,pd);                        // Calc K:D Ratio
        strcpy(pl->player.kdr,kdr.c_str());           // Assings K:D Ratio
        // Damage Ratio
        dratio = simplify(dd,dr);
        strcpy(pl->player.dratio,dratio.c_str());     // Assings DD:DR Ratio

        // Player Statistics are Calulated here
        wk = pl->player.weapon.knife.kills;
        wd = pl->player.weapon.knife.deaths;
        ws = pl->player.weapon.knife.sui;
        wkdp = compstatspercent(wk,wd,ws);            // Compute Weapon Kill:D:S Percentage
        pl->player.weapon.knife.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.knife.kdr,wkdr.c_str());    // Computer Weapon K:D Ratio
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.knife.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.knife.damdelt;
        dr = pl->player.weapon.knife.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.knife.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.coltgov.kills;
        wd = pl->player.weapon.coltgov.deaths;
        ws = pl->player.weapon.coltgov.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.coltgov.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.coltgov.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.coltgov.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.coltgov.damdelt;
        dr = pl->player.weapon.coltgov.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.coltgov.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here

        wk = pl->player.weapon.ber92f.kills;
        wd = pl->player.weapon.ber92f.deaths;
        ws = pl->player.weapon.ber92f.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.ber92f.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.ber92f.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.ber92f.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.ber92f.damdelt;
        dr = pl->player.weapon.ber92f.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.ber92f.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.ber93r.kills;
        wd = pl->player.weapon.ber93r.deaths;
        ws = pl->player.weapon.ber93r.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.ber93r.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.ber93r.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.ber93r.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.ber93r.damdelt;
        dr = pl->player.weapon.ber93r.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.ber93r.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.anaconda.kills;
        wd = pl->player.weapon.anaconda.deaths;
        ws = pl->player.weapon.anaconda.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.anaconda.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.anaconda.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.anaconda.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.anaconda.damdelt;
        dr = pl->player.weapon.anaconda.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.anaconda.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.desert.kills;
        wd = pl->player.weapon.desert.deaths;
        ws = pl->player.weapon.desert.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.desert.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.desert.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.desert.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.desert.damdelt;
        dr = pl->player.weapon.desert.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.desert.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.benelli.kills;
        wd = pl->player.weapon.benelli.deaths;
        ws = pl->player.weapon.benelli.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.benelli.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.benelli.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.benelli.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.benelli.damdelt;
        dr = pl->player.weapon.benelli.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.benelli.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here

        wk = pl->player.weapon.saiga.kills;
        wd = pl->player.weapon.saiga.deaths;
        ws = pl->player.weapon.saiga.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.saiga.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.saiga.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.saiga.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.saiga.damdelt;
        dr = pl->player.weapon.saiga.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.saiga.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.mp5a5.kills;
        wd = pl->player.weapon.mp5a5.deaths;
        ws = pl->player.weapon.mp5a5.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.mp5a5.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.mp5a5.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.mp5a5.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.mp5a5.damdelt;
        dr = pl->player.weapon.mp5a5.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.mp5a5.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.sterling.kills;
        wd = pl->player.weapon.sterling.deaths;
        ws = pl->player.weapon.sterling.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.sterling.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.sterling.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.sterling.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.sterling.damdelt;
        dr = pl->player.weapon.sterling.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.sterling.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.bizon.kills;
        wd = pl->player.weapon.bizon.deaths;
        ws = pl->player.weapon.bizon.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.bizon.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.bizon.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.bizon.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.bizon.damdelt;
        dr = pl->player.weapon.bizon.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.bizon.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here

        wk = pl->player.weapon.ak47.kills;
        wd = pl->player.weapon.ak47.deaths;
        ws = pl->player.weapon.ak47.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.ak47.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.ak47.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.ak47.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.ak47.damdelt;
        dr = pl->player.weapon.ak47.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.ak47.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.famas.kills;
        wd = pl->player.weapon.famas.deaths;
        ws = pl->player.weapon.famas.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.famas.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.famas.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.famas.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.famas.damdelt;
        dr = pl->player.weapon.famas.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.famas.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.g3a3.kills;
        wd = pl->player.weapon.g3a3.deaths;
        ws = pl->player.weapon.g3a3.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.g3a3.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.g3a3.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.g3a3.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.g3a3.damdelt;
        dr = pl->player.weapon.g3a3.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.g3a3.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.g36e.kills;
        wd = pl->player.weapon.g36e.deaths;
        ws = pl->player.weapon.g36e.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.g36e.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.g36e.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.g36e.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.g36e.damdelt;
        dr = pl->player.weapon.g36e.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.g36e.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.m16.kills;
        wd = pl->player.weapon.m16.deaths;
        ws = pl->player.weapon.m16.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.m16.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.m16.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.m16.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.m16.damdelt;
        dr = pl->player.weapon.m16.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.m16.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.m82.kills;
        wd = pl->player.weapon.m82.deaths;
        ws = pl->player.weapon.m82.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.m82.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.m82.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.m82.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.m82.damdelt;
        dr = pl->player.weapon.m82.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.m82.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.m60.kills;
        wd = pl->player.weapon.m60.deaths;
        ws = pl->player.weapon.m60.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.m60.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.m60.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.m60.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.m60.damdelt;
        dr = pl->player.weapon.m60.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.m60.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.m79.kills;
        wd = pl->player.weapon.m79.deaths;
        ws = pl->player.weapon.m79.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.m79.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.m79.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.m79.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.m79.damdelt;
        dr = pl->player.weapon.m79.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.m79.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.claymore.kills;
        wd = pl->player.weapon.claymore.deaths;
        ws = pl->player.weapon.claymore.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.claymore.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.claymore.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.claymore.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.claymore.damdelt;
        dr = pl->player.weapon.claymore.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.claymore.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.frag.kills;
        wd = pl->player.weapon.frag.deaths;
        ws = pl->player.weapon.frag.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.frag.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.frag.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.frag.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.frag.damdelt;
        dr = pl->player.weapon.frag.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.frag.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.stg24.kills;
        wd = pl->player.weapon.stg24.deaths;
        ws = pl->player.weapon.stg24.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.stg24.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.stg24.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.stg24.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.stg24.damdelt;
        dr = pl->player.weapon.stg24.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.stg24.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.m203.kills;
        wd = pl->player.weapon.m203.deaths;
        ws = pl->player.weapon.m203.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.m203.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.m203.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.m203.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.m203.damdelt;
        dr = pl->player.weapon.m203.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.m203.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here

        wk = pl->player.weapon.uzi.kills;
        wd = pl->player.weapon.uzi.deaths;
        ws = pl->player.weapon.uzi.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.uzi.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.uzi.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.uzi.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.uzi.damdelt;
        dr = pl->player.weapon.uzi.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.uzi.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.pkm.kills;
        wd = pl->player.weapon.pkm.deaths;
        ws = pl->player.weapon.pkm.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.pkm.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.pkm.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.pkm.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.pkm.damdelt;
        dr = pl->player.weapon.pkm.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.pkm.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.ak74.kills;
        wd = pl->player.weapon.ak74.deaths;
        ws = pl->player.weapon.ak74.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.ak74.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.ak74.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.ak74.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.ak74.damdelt;
        dr = pl->player.weapon.ak74.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.ak74.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.svd.kills;
        wd = pl->player.weapon.svd.deaths;
        ws = pl->player.weapon.svd.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.svd.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.svd.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.svd.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.svd.damdelt;
        dr = pl->player.weapon.svd.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.svd.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.gp25.kills;
        wd = pl->player.weapon.gp25.deaths;
        ws = pl->player.weapon.gp25.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.gp25.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.gp25.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.gp25.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.gp25.damdelt;
        dr = pl->player.weapon.gp25.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.gp25.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.ssg3000.kills;
        wd = pl->player.weapon.ssg3000.deaths;
        ws = pl->player.weapon.ssg3000.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.ssg3000.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.ssg3000.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.ssg3000.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.ssg3000.damdelt;
        dr = pl->player.weapon.ssg3000.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.ssg3000.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.weapmortar.kills;
        wd = pl->player.weapon.weapmortar.deaths;
        ws = pl->player.weapon.weapmortar.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.weapmortar.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.weapmortar.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.weapmortar.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.weapmortar.damdelt;
        dr = pl->player.weapon.weapmortar.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.weapmortar.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.spark_shower.kills;
        wd = pl->player.weapon.spark_shower.deaths;
        ws = pl->player.weapon.spark_shower.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.spark_shower.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.spark_shower.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.spark_shower.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.spark_shower.damdelt;
        dr = pl->player.weapon.spark_shower.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.spark_shower.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.monster_mortar.kills;
        wd = pl->player.weapon.monster_mortar.deaths;
        ws = pl->player.weapon.monster_mortar.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.monster_mortar.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.monster_mortar.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.monster_mortar.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.monster_mortar.damdelt;
        dr = pl->player.weapon.monster_mortar.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.monster_mortar.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.func_tank.kills;
        wd = pl->player.weapon.func_tank.deaths;
        ws = pl->player.weapon.func_tank.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.func_tank.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.func_tank.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.func_tank.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.func_tank.damdelt;
        dr = pl->player.weapon.func_tank.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.func_tank.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.env_explosion.kills;
        wd = pl->player.weapon.env_explosion.deaths;
        ws = pl->player.weapon.env_explosion.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.env_explosion.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.env_explosion.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.env_explosion.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.env_explosion.damdelt;
        dr = pl->player.weapon.env_explosion.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.env_explosion.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here


        wk = pl->player.weapon.concussion.kills;
        wd = pl->player.weapon.concussion.deaths;
        ws = pl->player.weapon.concussion.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.concussion.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.concussion.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.concussion.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.concussion.damdelt;
        dr = pl->player.weapon.concussion.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.concussion.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here

        wk = pl->player.weapon.ammobox.kills;
        wd = pl->player.weapon.ammobox.deaths;
        ws = pl->player.weapon.ammobox.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.weapon.ammobox.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.weapon.ammobox.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.weapon.ammobox.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.weapon.ammobox.damdelt;
        dr = pl->player.weapon.ammobox.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.weapon.ammobox.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here

        addpridx(pl->player.name,rank-1);  // Adds to Index
        writeprank(&pl->player,rank-1);    // Write to Data file
        percentleft(100);
        char text3[40];
        sprintf(text3,"Completed OK! ");
        drawleft2(text3,9,0);
    }
    percenttop(100);
    return;
}


/*--------------------------------------------------------------------------------*/
// Computes Players & Weapons KILL DEATH SUICIDE PERCENTAGE And Assigns to Players Rec
// With Kill : Death Ratio / And New Attack Damage Statistics
void calcPlayerStats() {

    // Handle to Link List Holding All Player Data
    struct ListItem14 *pl;
    // Handle to List List Holding All Weapon Data
    struct ListItem15 *wp;

    long         pd      = 0;               // Player Deaths
    long         pf      = 0;               // Player weapon.kills
    long         ps      = 0;               // Player sui
    double       kdp     = 0;               // Kill Death Percentage
    string       kdr;                       // Weapon Kill : Death Ratio
    string       dratio;                    // Player Damage Ratio
    // Weapons
    long         wk      = 0;               // Weapon Kills
    long         wd      = 0;               // Weapon Deaths
    long         ws      = 0;               // Weapon sui
    double       wkdp    = 0;               // Weapon Kill : Death : Suicide Percentage
    string       wkdr;                      // Weapon Kill : Death Ratio
    double       wpkills = 0;               // Weapon Percentage Kills
    string       wdratio;                   // Weapon Damage Ratio
    // Damage
    long         dd      = 0;               // Damage Delt
    long         dr      = 0;               // Damage Received

    int widx  = 0; // Weapon Index for Calcing Weapon's Total Stats
    int count = 0; // Counter For ReWritting to Map Files

    // Do Testing if player name is in list, Update it with New Data
    for ( pl = MyList14 ; pl != 0 ; pl = pl->next ) {

        // Calc Player's Stats
        pf = pl->player.redforce.player2.kills;                        // Gets #'s for Computing
        pd = pl->player.redforce.player2.deaths;
        ps = pl->player.redforce.player2.sui;
        dd = pl->player.redforce.player2.damdelt;
        dr = pl->player.redforce.player2.damrec;
        // Kill Percentage
        kdp = compstatspercent(pf,pd,ps);             // Compute KILL DEATH SUI PERCENTAGE
        pl->player.redforce.player2.kdp = kdp;                         // Assign Kill Death Percentage
        // Kill : Death Ratio
        kdr = simplify(pf,pd);                        // Calc K:D Ratio
        strcpy(pl->player.redforce.player2.kdr,kdr.c_str());           // Assings K:D Ratio
        // Damage Ratio
        dratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.dratio,dratio.c_str());     // Assings DD:DR Ratio

        // Player Statistics are Calulated here
        wk = pl->player.redforce.player2.weapon.knife.kills;
        wd = pl->player.redforce.player2.weapon.knife.deaths;
        ws = pl->player.redforce.player2.weapon.knife.sui;
        wkdp = compstatspercent(wk,wd,ws);            // Compute Weapon Kill:D:S Percentage
        pl->player.redforce.player2.weapon.knife.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.knife.kdr,wkdr.c_str());    // Computer Weapon K:D Ratio
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.knife.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.knife.damdelt;
        dr = pl->player.redforce.player2.weapon.knife.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.knife.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.knife.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.coltgov.kills;
        wd = pl->player.redforce.player2.weapon.coltgov.deaths;
        ws = pl->player.redforce.player2.weapon.coltgov.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.coltgov.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.coltgov.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.coltgov.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.coltgov.damdelt;
        dr = pl->player.redforce.player2.weapon.coltgov.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.coltgov.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.coltgov.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.ber92f.kills;
        wd = pl->player.redforce.player2.weapon.ber92f.deaths;
        ws = pl->player.redforce.player2.weapon.ber92f.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.ber92f.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.ber92f.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.ber92f.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.ber92f.damdelt;
        dr = pl->player.redforce.player2.weapon.ber92f.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.ber92f.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.ber92f.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.ber93r.kills;
        wd = pl->player.redforce.player2.weapon.ber93r.deaths;
        ws = pl->player.redforce.player2.weapon.ber93r.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.ber93r.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.ber93r.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.ber93r.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.ber93r.damdelt;
        dr = pl->player.redforce.player2.weapon.ber93r.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.ber93r.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.ber93r.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.anaconda.kills;
        wd = pl->player.redforce.player2.weapon.anaconda.deaths;
        ws = pl->player.redforce.player2.weapon.anaconda.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.anaconda.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.anaconda.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.anaconda.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.anaconda.damdelt;
        dr = pl->player.redforce.player2.weapon.anaconda.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.anaconda.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.anaconda.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.desert.kills;
        wd = pl->player.redforce.player2.weapon.desert.deaths;
        ws = pl->player.redforce.player2.weapon.desert.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.desert.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.desert.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.desert.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.desert.damdelt;
        dr = pl->player.redforce.player2.weapon.desert.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.desert.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.desert.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.benelli.kills;
        wd = pl->player.redforce.player2.weapon.benelli.deaths;
        ws = pl->player.redforce.player2.weapon.benelli.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.benelli.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.benelli.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.benelli.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.benelli.damdelt;
        dr = pl->player.redforce.player2.weapon.benelli.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.benelli.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.benelli.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.saiga.kills;
        wd = pl->player.redforce.player2.weapon.saiga.deaths;
        ws = pl->player.redforce.player2.weapon.saiga.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.saiga.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.saiga.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.saiga.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.saiga.damdelt;
        dr = pl->player.redforce.player2.weapon.saiga.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.saiga.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.saiga.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.mp5a5.kills;
        wd = pl->player.redforce.player2.weapon.mp5a5.deaths;
        ws = pl->player.redforce.player2.weapon.mp5a5.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.mp5a5.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.mp5a5.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.mp5a5.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.mp5a5.damdelt;
        dr = pl->player.redforce.player2.weapon.mp5a5.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.mp5a5.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.mp5a5.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.sterling.kills;
        wd = pl->player.redforce.player2.weapon.sterling.deaths;
        ws = pl->player.redforce.player2.weapon.sterling.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.sterling.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.sterling.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.sterling.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.sterling.damdelt;
        dr = pl->player.redforce.player2.weapon.sterling.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.sterling.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.sterling.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;

            }
        }

        wk = pl->player.redforce.player2.weapon.bizon.kills;
        wd = pl->player.redforce.player2.weapon.bizon.deaths;
        ws = pl->player.redforce.player2.weapon.bizon.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.bizon.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.bizon.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.bizon.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.bizon.damdelt;
        dr = pl->player.redforce.player2.weapon.bizon.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.bizon.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.bizon.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.ak47.kills;
        wd = pl->player.redforce.player2.weapon.ak47.deaths;
        ws = pl->player.redforce.player2.weapon.ak47.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.ak47.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.ak47.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.ak47.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.ak47.damdelt;
        dr = pl->player.redforce.player2.weapon.ak47.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.ak47.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.ak47.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.famas.kills;
        wd = pl->player.redforce.player2.weapon.famas.deaths;
        ws = pl->player.redforce.player2.weapon.famas.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.famas.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.famas.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.famas.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.famas.damdelt;
        dr = pl->player.redforce.player2.weapon.famas.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.famas.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.famas.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.g3a3.kills;
        wd = pl->player.redforce.player2.weapon.g3a3.deaths;
        ws = pl->player.redforce.player2.weapon.g3a3.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.g3a3.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.g3a3.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.g3a3.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.g3a3.damdelt;
        dr = pl->player.redforce.player2.weapon.g3a3.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.g3a3.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.g3a3.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.g36e.kills;
        wd = pl->player.redforce.player2.weapon.g36e.deaths;
        ws = pl->player.redforce.player2.weapon.g36e.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.g36e.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.g36e.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.g36e.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.g36e.damdelt;
        dr = pl->player.redforce.player2.weapon.g36e.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.g36e.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.g36e.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.m16.kills;
        wd = pl->player.redforce.player2.weapon.m16.deaths;
        ws = pl->player.redforce.player2.weapon.m16.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.m16.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.m16.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.m16.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.m16.damdelt;
        dr = pl->player.redforce.player2.weapon.m16.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.m16.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.m16.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.m82.kills;
        wd = pl->player.redforce.player2.weapon.m82.deaths;
        ws = pl->player.redforce.player2.weapon.m82.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.m82.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.m82.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.m82.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.m82.damdelt;
        dr = pl->player.redforce.player2.weapon.m82.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.m82.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.m82.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.m60.kills;
        wd = pl->player.redforce.player2.weapon.m60.deaths;
        ws = pl->player.redforce.player2.weapon.m60.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.m60.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.m60.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.m60.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.m60.damdelt;
        dr = pl->player.redforce.player2.weapon.m60.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.m60.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.m60.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.m79.kills;
        wd = pl->player.redforce.player2.weapon.m79.deaths;
        ws = pl->player.redforce.player2.weapon.m79.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.m79.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.m79.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.m79.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.m79.damdelt;
        dr = pl->player.redforce.player2.weapon.m79.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.m79.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.m79.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.claymore.kills;
        wd = pl->player.redforce.player2.weapon.claymore.deaths;
        ws = pl->player.redforce.player2.weapon.claymore.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.claymore.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.claymore.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.claymore.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.claymore.damdelt;
        dr = pl->player.redforce.player2.weapon.claymore.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.claymore.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.claymore.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.frag.kills;
        wd = pl->player.redforce.player2.weapon.frag.deaths;
        ws = pl->player.redforce.player2.weapon.frag.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.frag.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.frag.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.frag.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.frag.damdelt;
        dr = pl->player.redforce.player2.weapon.frag.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.frag.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.frag.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.stg24.kills;
        wd = pl->player.redforce.player2.weapon.stg24.deaths;
        ws = pl->player.redforce.player2.weapon.stg24.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.stg24.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.stg24.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.stg24.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.stg24.damdelt;
        dr = pl->player.redforce.player2.weapon.stg24.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.stg24.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.stg24.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.m203.kills;
        wd = pl->player.redforce.player2.weapon.m203.deaths;
        ws = pl->player.redforce.player2.weapon.m203.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.m203.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.m203.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.m203.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.m203.damdelt;
        dr = pl->player.redforce.player2.weapon.m203.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.m203.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.m203.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.uzi.kills;
        wd = pl->player.redforce.player2.weapon.uzi.deaths;
        ws = pl->player.redforce.player2.weapon.uzi.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.uzi.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.uzi.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.uzi.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.uzi.damdelt;
        dr = pl->player.redforce.player2.weapon.uzi.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.uzi.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.uzi.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.pkm.kills;
        wd = pl->player.redforce.player2.weapon.pkm.deaths;
        ws = pl->player.redforce.player2.weapon.pkm.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.pkm.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.pkm.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.pkm.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.pkm.damdelt;
        dr = pl->player.redforce.player2.weapon.pkm.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.pkm.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.pkm.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.ak74.kills;
        wd = pl->player.redforce.player2.weapon.ak74.deaths;
        ws = pl->player.redforce.player2.weapon.ak74.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.ak74.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.ak74.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.ak74.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.ak74.damdelt;
        dr = pl->player.redforce.player2.weapon.ak74.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.ak74.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.ak74.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.svd.kills;
        wd = pl->player.redforce.player2.weapon.svd.deaths;
        ws = pl->player.redforce.player2.weapon.svd.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.svd.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.svd.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.svd.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.svd.damdelt;
        dr = pl->player.redforce.player2.weapon.svd.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.svd.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.svd.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.gp25.kills;
        wd = pl->player.redforce.player2.weapon.gp25.deaths;
        ws = pl->player.redforce.player2.weapon.gp25.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.gp25.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.gp25.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.gp25.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.gp25.damdelt;
        dr = pl->player.redforce.player2.weapon.gp25.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.gp25.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.gp25.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.ssg3000.kills;
        wd = pl->player.redforce.player2.weapon.ssg3000.deaths;
        ws = pl->player.redforce.player2.weapon.ssg3000.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.ssg3000.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.ssg3000.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.ssg3000.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.ssg3000.damdelt;
        dr = pl->player.redforce.player2.weapon.ssg3000.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.ssg3000.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.ssg3000.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.weapmortar.kills;
        wd = pl->player.redforce.player2.weapon.weapmortar.deaths;
        ws = pl->player.redforce.player2.weapon.weapmortar.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.weapmortar.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.weapmortar.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.weapmortar.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.weapmortar.damdelt;
        dr = pl->player.redforce.player2.weapon.weapmortar.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.weapmortar.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.weapmortar.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.spark_shower.kills;
        wd = pl->player.redforce.player2.weapon.spark_shower.deaths;
        ws = pl->player.redforce.player2.weapon.spark_shower.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.spark_shower.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.spark_shower.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.spark_shower.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.spark_shower.damdelt;
        dr = pl->player.redforce.player2.weapon.spark_shower.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.spark_shower.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.spark_shower.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.monster_mortar.kills;
        wd = pl->player.redforce.player2.weapon.monster_mortar.deaths;
        ws = pl->player.redforce.player2.weapon.monster_mortar.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.monster_mortar.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.monster_mortar.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.monster_mortar.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.monster_mortar.damdelt;
        dr = pl->player.redforce.player2.weapon.monster_mortar.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.monster_mortar.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.monster_mortar.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.func_tank.kills;
        wd = pl->player.redforce.player2.weapon.func_tank.deaths;
        ws = pl->player.redforce.player2.weapon.func_tank.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.func_tank.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.func_tank.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.func_tank.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.func_tank.damdelt;
        dr = pl->player.redforce.player2.weapon.func_tank.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.func_tank.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.func_tank.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.env_explosion.kills;
        wd = pl->player.redforce.player2.weapon.env_explosion.deaths;
        ws = pl->player.redforce.player2.weapon.env_explosion.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.env_explosion.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.env_explosion.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.env_explosion.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.env_explosion.damdelt;
        dr = pl->player.redforce.player2.weapon.env_explosion.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.env_explosion.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.env_explosion.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.concussion.kills;
        wd = pl->player.redforce.player2.weapon.concussion.deaths;
        ws = pl->player.redforce.player2.weapon.concussion.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.concussion.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.concussion.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.concussion.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.concussion.damdelt;
        dr = pl->player.redforce.player2.weapon.concussion.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.concussion.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.concussion.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.redforce.player2.weapon.ammobox.kills;
        wd = pl->player.redforce.player2.weapon.ammobox.deaths;
        ws = pl->player.redforce.player2.weapon.ammobox.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.redforce.player2.weapon.ammobox.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.redforce.player2.weapon.ammobox.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.redforce.player2.weapon.ammobox.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.redforce.player2.weapon.ammobox.damdelt;
        dr = pl->player.redforce.player2.weapon.ammobox.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.redforce.player2.weapon.ammobox.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.redforce.player2.weapon.ammobox.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }


        // Calculate Statistics for Blue Side...

        // Calc Player's Stats
        pf = pl->player.redforce.player2.kills;                        // Gets #'s for Computing
        pd = pl->player.blueforce.player2.deaths;
        ps = pl->player.blueforce.player2.sui;
        dd = pl->player.blueforce.player2.damdelt;
        dr = pl->player.blueforce.player2.damrec;
        // Kill Percentage
        kdp = compstatspercent(pf,pd,ps);             // Compute KILL DEATH SUI PERCENTAGE
        pl->player.blueforce.player2.kdp = kdp;                         // Assign Kill Death Percentage
        // Kill : Death Ratio
        kdr = simplify(pf,pd);                        // Calc K:D Ratio
        strcpy(pl->player.blueforce.player2.kdr,kdr.c_str());           // Assings K:D Ratio
        // Damage Ratio
        dratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.dratio,dratio.c_str());     // Assings DD:DR Ratio

        // Player Statistics are Calulated here
        wk = pl->player.blueforce.player2.weapon.knife.kills;
        wd = pl->player.blueforce.player2.weapon.knife.deaths;
        ws = pl->player.blueforce.player2.weapon.knife.sui;
        wkdp = compstatspercent(wk,wd,ws);            // Compute Weapon Kill:D:S Percentage
        pl->player.blueforce.player2.weapon.knife.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.knife.kdr,wkdr.c_str());    // Computer Weapon K:D Ratio
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.knife.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.knife.damdelt;
        dr = pl->player.blueforce.player2.weapon.knife.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.knife.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.knife.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.coltgov.kills;
        wd = pl->player.blueforce.player2.weapon.coltgov.deaths;
        ws = pl->player.blueforce.player2.weapon.coltgov.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.coltgov.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.coltgov.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.coltgov.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.coltgov.damdelt;
        dr = pl->player.blueforce.player2.weapon.coltgov.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.coltgov.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.coltgov.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.ber92f.kills;
        wd = pl->player.blueforce.player2.weapon.ber92f.deaths;
        ws = pl->player.blueforce.player2.weapon.ber92f.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.ber92f.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.ber92f.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.ber92f.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.ber92f.damdelt;
        dr = pl->player.blueforce.player2.weapon.ber92f.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.ber92f.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.ber92f.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.ber93r.kills;
        wd = pl->player.blueforce.player2.weapon.ber93r.deaths;
        ws = pl->player.blueforce.player2.weapon.ber93r.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.ber93r.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.ber93r.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.ber93r.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.ber93r.damdelt;
        dr = pl->player.blueforce.player2.weapon.ber93r.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.ber93r.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.ber93r.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.anaconda.kills;
        wd = pl->player.blueforce.player2.weapon.anaconda.deaths;
        ws = pl->player.blueforce.player2.weapon.anaconda.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.anaconda.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.anaconda.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.anaconda.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.anaconda.damdelt;
        dr = pl->player.blueforce.player2.weapon.anaconda.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.anaconda.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.anaconda.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.desert.kills;
        wd = pl->player.blueforce.player2.weapon.desert.deaths;
        ws = pl->player.blueforce.player2.weapon.desert.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.desert.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.desert.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.desert.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.desert.damdelt;
        dr = pl->player.blueforce.player2.weapon.desert.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.desert.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.desert.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.benelli.kills;
        wd = pl->player.blueforce.player2.weapon.benelli.deaths;
        ws = pl->player.blueforce.player2.weapon.benelli.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.benelli.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.benelli.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.benelli.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.benelli.damdelt;
        dr = pl->player.blueforce.player2.weapon.benelli.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.benelli.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.benelli.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.saiga.kills;
        wd = pl->player.blueforce.player2.weapon.saiga.deaths;
        ws = pl->player.blueforce.player2.weapon.saiga.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.saiga.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.saiga.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.saiga.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.saiga.damdelt;
        dr = pl->player.blueforce.player2.weapon.saiga.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.saiga.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.saiga.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.mp5a5.kills;
        wd = pl->player.blueforce.player2.weapon.mp5a5.deaths;
        ws = pl->player.blueforce.player2.weapon.mp5a5.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.mp5a5.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.mp5a5.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.mp5a5.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.mp5a5.damdelt;
        dr = pl->player.blueforce.player2.weapon.mp5a5.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.mp5a5.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.mp5a5.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.sterling.kills;
        wd = pl->player.blueforce.player2.weapon.sterling.deaths;
        ws = pl->player.blueforce.player2.weapon.sterling.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.sterling.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.sterling.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.sterling.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.sterling.damdelt;
        dr = pl->player.blueforce.player2.weapon.sterling.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.sterling.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.sterling.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;

            }
        }

        wk = pl->player.blueforce.player2.weapon.bizon.kills;
        wd = pl->player.blueforce.player2.weapon.bizon.deaths;
        ws = pl->player.blueforce.player2.weapon.bizon.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.bizon.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.bizon.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.bizon.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.bizon.damdelt;
        dr = pl->player.blueforce.player2.weapon.bizon.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.bizon.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.bizon.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.ak47.kills;
        wd = pl->player.blueforce.player2.weapon.ak47.deaths;
        ws = pl->player.blueforce.player2.weapon.ak47.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.ak47.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.ak47.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.ak47.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.ak47.damdelt;
        dr = pl->player.blueforce.player2.weapon.ak47.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.ak47.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.ak47.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.famas.kills;
        wd = pl->player.blueforce.player2.weapon.famas.deaths;
        ws = pl->player.blueforce.player2.weapon.famas.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.famas.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.famas.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.famas.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.famas.damdelt;
        dr = pl->player.blueforce.player2.weapon.famas.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.famas.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.famas.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.g3a3.kills;
        wd = pl->player.blueforce.player2.weapon.g3a3.deaths;
        ws = pl->player.blueforce.player2.weapon.g3a3.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.g3a3.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.g3a3.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.g3a3.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.g3a3.damdelt;
        dr = pl->player.blueforce.player2.weapon.g3a3.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.g3a3.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.g3a3.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.g36e.kills;
        wd = pl->player.blueforce.player2.weapon.g36e.deaths;
        ws = pl->player.blueforce.player2.weapon.g36e.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.g36e.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.g36e.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.g36e.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.g36e.damdelt;
        dr = pl->player.blueforce.player2.weapon.g36e.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.g36e.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.g36e.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.m16.kills;
        wd = pl->player.blueforce.player2.weapon.m16.deaths;
        ws = pl->player.blueforce.player2.weapon.m16.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.m16.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.m16.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.m16.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.m16.damdelt;
        dr = pl->player.blueforce.player2.weapon.m16.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.m16.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.m16.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.m82.kills;
        wd = pl->player.blueforce.player2.weapon.m82.deaths;
        ws = pl->player.blueforce.player2.weapon.m82.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.m82.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.m82.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.m82.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.m82.damdelt;
        dr = pl->player.blueforce.player2.weapon.m82.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.m82.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.m82.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.m60.kills;
        wd = pl->player.blueforce.player2.weapon.m60.deaths;
        ws = pl->player.blueforce.player2.weapon.m60.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.m60.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.m60.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.m60.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.m60.damdelt;
        dr = pl->player.blueforce.player2.weapon.m60.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.m60.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.m60.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.m79.kills;
        wd = pl->player.blueforce.player2.weapon.m79.deaths;
        ws = pl->player.blueforce.player2.weapon.m79.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.m79.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.m79.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.m79.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.m79.damdelt;
        dr = pl->player.blueforce.player2.weapon.m79.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.m79.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.m79.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.claymore.kills;
        wd = pl->player.blueforce.player2.weapon.claymore.deaths;
        ws = pl->player.blueforce.player2.weapon.claymore.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.claymore.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.claymore.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.claymore.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.claymore.damdelt;
        dr = pl->player.blueforce.player2.weapon.claymore.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.claymore.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.claymore.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.frag.kills;
        wd = pl->player.blueforce.player2.weapon.frag.deaths;
        ws = pl->player.blueforce.player2.weapon.frag.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.frag.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.frag.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.frag.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.frag.damdelt;
        dr = pl->player.blueforce.player2.weapon.frag.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.frag.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.frag.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.stg24.kills;
        wd = pl->player.blueforce.player2.weapon.stg24.deaths;
        ws = pl->player.blueforce.player2.weapon.stg24.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.stg24.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.stg24.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.stg24.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.stg24.damdelt;
        dr = pl->player.blueforce.player2.weapon.stg24.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.stg24.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.stg24.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.m203.kills;
        wd = pl->player.blueforce.player2.weapon.m203.deaths;
        ws = pl->player.blueforce.player2.weapon.m203.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.m203.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.m203.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.m203.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.m203.damdelt;
        dr = pl->player.blueforce.player2.weapon.m203.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.m203.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.m203.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.uzi.kills;
        wd = pl->player.blueforce.player2.weapon.uzi.deaths;
        ws = pl->player.blueforce.player2.weapon.uzi.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.uzi.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.uzi.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.uzi.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.uzi.damdelt;
        dr = pl->player.blueforce.player2.weapon.uzi.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.uzi.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.uzi.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.pkm.kills;
        wd = pl->player.blueforce.player2.weapon.pkm.deaths;
        ws = pl->player.blueforce.player2.weapon.pkm.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.pkm.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.pkm.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.pkm.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.pkm.damdelt;
        dr = pl->player.blueforce.player2.weapon.pkm.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.pkm.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.pkm.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.ak74.kills;
        wd = pl->player.blueforce.player2.weapon.ak74.deaths;
        ws = pl->player.blueforce.player2.weapon.ak74.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.ak74.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.ak74.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.ak74.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.ak74.damdelt;
        dr = pl->player.blueforce.player2.weapon.ak74.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.ak74.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.ak74.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.svd.kills;
        wd = pl->player.blueforce.player2.weapon.svd.deaths;
        ws = pl->player.blueforce.player2.weapon.svd.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.svd.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.svd.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.svd.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.svd.damdelt;
        dr = pl->player.blueforce.player2.weapon.svd.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.svd.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.svd.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.gp25.kills;
        wd = pl->player.blueforce.player2.weapon.gp25.deaths;
        ws = pl->player.blueforce.player2.weapon.gp25.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.gp25.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.gp25.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.gp25.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.gp25.damdelt;
        dr = pl->player.blueforce.player2.weapon.gp25.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.gp25.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.gp25.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.ssg3000.kills;
        wd = pl->player.blueforce.player2.weapon.ssg3000.deaths;
        ws = pl->player.blueforce.player2.weapon.ssg3000.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.ssg3000.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.ssg3000.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.ssg3000.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.ssg3000.damdelt;
        dr = pl->player.blueforce.player2.weapon.ssg3000.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.ssg3000.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.ssg3000.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.weapmortar.kills;
        wd = pl->player.blueforce.player2.weapon.weapmortar.deaths;
        ws = pl->player.blueforce.player2.weapon.weapmortar.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.weapmortar.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.weapmortar.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.weapmortar.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.weapmortar.damdelt;
        dr = pl->player.blueforce.player2.weapon.weapmortar.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.weapmortar.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.weapmortar.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.spark_shower.kills;
        wd = pl->player.blueforce.player2.weapon.spark_shower.deaths;
        ws = pl->player.blueforce.player2.weapon.spark_shower.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.spark_shower.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.spark_shower.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.spark_shower.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.spark_shower.damdelt;
        dr = pl->player.blueforce.player2.weapon.spark_shower.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.spark_shower.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.spark_shower.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.monster_mortar.kills;
        wd = pl->player.blueforce.player2.weapon.monster_mortar.deaths;
        ws = pl->player.blueforce.player2.weapon.monster_mortar.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.monster_mortar.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.monster_mortar.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.monster_mortar.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.monster_mortar.damdelt;
        dr = pl->player.blueforce.player2.weapon.monster_mortar.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.monster_mortar.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.monster_mortar.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.func_tank.kills;
        wd = pl->player.blueforce.player2.weapon.func_tank.deaths;
        ws = pl->player.blueforce.player2.weapon.func_tank.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.func_tank.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.func_tank.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.func_tank.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.func_tank.damdelt;
        dr = pl->player.blueforce.player2.weapon.func_tank.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.func_tank.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.func_tank.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.env_explosion.kills;
        wd = pl->player.blueforce.player2.weapon.env_explosion.deaths;
        ws = pl->player.blueforce.player2.weapon.env_explosion.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.env_explosion.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.env_explosion.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.env_explosion.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.env_explosion.damdelt;
        dr = pl->player.blueforce.player2.weapon.env_explosion.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.env_explosion.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.env_explosion.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.concussion.kills;
        wd = pl->player.blueforce.player2.weapon.concussion.deaths;
        ws = pl->player.blueforce.player2.weapon.concussion.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.concussion.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.concussion.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.concussion.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.concussion.damdelt;
        dr = pl->player.blueforce.player2.weapon.concussion.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.concussion.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.concussion.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }

        wk = pl->player.blueforce.player2.weapon.ammobox.kills;
        wd = pl->player.blueforce.player2.weapon.ammobox.deaths;
        ws = pl->player.blueforce.player2.weapon.ammobox.sui;
        wkdp = compstatspercent(wk,wd,ws);
        pl->player.blueforce.player2.weapon.ammobox.kdp = wkdp;
        wkdr = simplify(wk,wd);
        strcpy(pl->player.blueforce.player2.weapon.ammobox.kdr,wkdr.c_str());
        wpkills = compwkillpercent(wk,pf);
        pl->player.blueforce.player2.weapon.ammobox.pkills = wpkills;
        // Damage Ratio
        dd = pl->player.blueforce.player2.weapon.ammobox.damdelt;
        dr = pl->player.blueforce.player2.weapon.ammobox.damrec;
        wdratio = simplify(dd,dr);
        strcpy(pl->player.blueforce.player2.weapon.ammobox.dratio,wdratio.c_str()); // Assings DD:DR Ratio
        // Ongoing Total Weapon Statistics are Added Here
        for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
            if (strcmp(wp->weapon.name,pl->player.blueforce.player2.weapon.ammobox.name) == 0) {
                wp->weapon.kills   +=wk;
                wp->weapon.damdelt +=dd;
            }
        }
        writep(&pl->player,count);
        ++count;
    }
    return;
}


/*--------------------------------------------------------------------------------*/
/*// Reveices Player Weapons and Sorts by kills for Players.HTML
void calcweapons(PLAYERREC * player)
{
        // Add Weapons to Linklist and Sort Weapons for Each Player by Kills
        weaponkillsort(player->redforce.player2.weapon.knife.rank,       // Weapon Rank
                       player->redforce.player2.weapon.knife.name,       // Weapon Name
                       player->redforce.player2.weapon.knife.kills,      // Weapon Kills
                       player->redforce.player2.weapon.knife.deaths,     // Weapon Deaths
                       player->redforce.player2.weapon.knife.sui,        // Weapon sui
                       player->redforce.player2.weapon.knife.kdp,        // Weapon Kill Death Suicide Percentage
                       player->redforce.player2.weapon.knife.kdr,        // Weapon Kill : Death Ratio
                       player->redforce.player2.weapon.knife.pkills,
                       player->redforce.player2.weapon.knife.damdelt,
                       player->redforce.player2.weapon.knife.damrec,
                       player->redforce.player2.weapon.knife.dratio);

        weaponkillsort(player->redforce.player2.weapon.coltgov.rank,
                       player->redforce.player2.weapon.coltgov.name,
                       player->redforce.player2.weapon.coltgov.kills,
                       player->redforce.player2.weapon.coltgov.deaths,
                       player->redforce.player2.weapon.coltgov.sui,
                       player->redforce.player2.weapon.coltgov.kdp,
                       player->redforce.player2.weapon.coltgov.kdr,
                       player->redforce.player2.weapon.coltgov.pkills,
                       player->redforce.player2.weapon.coltgov.damdelt,
                       player->redforce.player2.weapon.coltgov.damrec,
                       player->redforce.player2.weapon.coltgov.dratio);

        weaponkillsort(player->redforce.player2.weapon.ber92f.rank,
                       player->redforce.player2.weapon.ber92f.name,
                       player->redforce.player2.weapon.ber92f.kills,
                       player->redforce.player2.weapon.ber92f.deaths,
                       player->redforce.player2.weapon.ber92f.sui,
                       player->redforce.player2.weapon.ber92f.kdp,
                       player->redforce.player2.weapon.ber92f.kdr,
                       player->redforce.player2.weapon.ber92f.pkills,
                       player->redforce.player2.weapon.ber92f.damdelt,
                       player->redforce.player2.weapon.ber92f.damrec,
                       player->redforce.player2.weapon.ber92f.dratio);

        weaponkillsort(player->redforce.player2.weapon.ber93r.rank,
                       player->redforce.player2.weapon.ber93r.name,
                       player->redforce.player2.weapon.ber93r.kills,
                       player->redforce.player2.weapon.ber93r.deaths,
                       player->redforce.player2.weapon.ber93r.sui,
                       player->redforce.player2.weapon.ber93r.kdp,
                       player->redforce.player2.weapon.ber93r.kdr,
                       player->redforce.player2.weapon.ber93r.pkills,
                       player->redforce.player2.weapon.ber93r.damdelt,
                       player->redforce.player2.weapon.ber93r.damrec,
                       player->redforce.player2.weapon.ber93r.dratio);

        weaponkillsort(player->redforce.player2.weapon.anaconda.rank,
                       player->redforce.player2.weapon.anaconda.name,
                       player->redforce.player2.weapon.anaconda.kills,
                       player->redforce.player2.weapon.anaconda.deaths,
                       player->redforce.player2.weapon.anaconda.sui,
                       player->redforce.player2.weapon.anaconda.kdp,
                       player->redforce.player2.weapon.anaconda.kdr,
                       player->redforce.player2.weapon.anaconda.pkills,
                       player->redforce.player2.weapon.anaconda.damdelt,
                       player->redforce.player2.weapon.anaconda.damrec,
                       player->redforce.player2.weapon.anaconda.dratio);

        weaponkillsort(player->redforce.player2.weapon.desert.rank,
                       player->redforce.player2.weapon.desert.name,
                       player->redforce.player2.weapon.desert.kills,
                       player->redforce.player2.weapon.desert.deaths,
                       player->redforce.player2.weapon.desert.sui,
                       player->redforce.player2.weapon.desert.kdp,
                       player->redforce.player2.weapon.desert.kdr,
                       player->redforce.player2.weapon.desert.pkills,
                       player->redforce.player2.weapon.desert.damdelt,
                       player->redforce.player2.weapon.desert.damrec,
                       player->redforce.player2.weapon.desert.dratio);

        weaponkillsort(player->redforce.player2.weapon.benelli.rank,
                       player->redforce.player2.weapon.benelli.name,
                       player->redforce.player2.weapon.benelli.kills,
                       player->redforce.player2.weapon.benelli.deaths,
                       player->redforce.player2.weapon.benelli.sui,
                       player->redforce.player2.weapon.benelli.kdp,
                       player->redforce.player2.weapon.benelli.kdr,
                       player->redforce.player2.weapon.benelli.pkills,
                       player->redforce.player2.weapon.benelli.damdelt,
                       player->redforce.player2.weapon.benelli.damrec,
                       player->redforce.player2.weapon.benelli.dratio);

        weaponkillsort(player->redforce.player2.weapon.saiga.rank,
                       player->redforce.player2.weapon.saiga.name,
                       player->redforce.player2.weapon.saiga.kills,
                       player->redforce.player2.weapon.saiga.deaths,
                       player->redforce.player2.weapon.saiga.sui,
                       player->redforce.player2.weapon.saiga.kdp,
                       player->redforce.player2.weapon.saiga.kdr,
                       player->redforce.player2.weapon.saiga.pkills,
                       player->redforce.player2.weapon.saiga.damdelt,
                       player->redforce.player2.weapon.saiga.damrec,
                       player->redforce.player2.weapon.saiga.dratio);

        weaponkillsort(player->redforce.player2.weapon.mp5a5.rank,
                       player->redforce.player2.weapon.mp5a5.name,
                       player->redforce.player2.weapon.mp5a5.kills,
                       player->redforce.player2.weapon.mp5a5.deaths,
                       player->redforce.player2.weapon.mp5a5.sui,
                       player->redforce.player2.weapon.mp5a5.kdp,
                       player->redforce.player2.weapon.mp5a5.kdr,
                       player->redforce.player2.weapon.mp5a5.pkills,
                       player->redforce.player2.weapon.mp5a5.damdelt,
                       player->redforce.player2.weapon.mp5a5.damrec,
                       player->redforce.player2.weapon.mp5a5.dratio);

        weaponkillsort(player->redforce.player2.weapon.sterling.rank,
                       player->redforce.player2.weapon.sterling.name,
                       player->redforce.player2.weapon.sterling.kills,
                       player->redforce.player2.weapon.sterling.deaths,
                       player->redforce.player2.weapon.sterling.sui,
                       player->redforce.player2.weapon.sterling.kdp,
                       player->redforce.player2.weapon.sterling.kdr,
                       player->redforce.player2.weapon.sterling.pkills,
                       player->redforce.player2.weapon.sterling.damdelt,
                       player->redforce.player2.weapon.sterling.damrec,
                       player->redforce.player2.weapon.sterling.dratio);

        weaponkillsort(player->redforce.player2.weapon.bizon.rank,
                       player->redforce.player2.weapon.bizon.name,
                       player->redforce.player2.weapon.bizon.kills,
                       player->redforce.player2.weapon.bizon.deaths,
                       player->redforce.player2.weapon.bizon.sui,
                       player->redforce.player2.weapon.bizon.kdp,
                       player->redforce.player2.weapon.bizon.kdr,
                       player->redforce.player2.weapon.bizon.pkills,
                       player->redforce.player2.weapon.bizon.damdelt,
                       player->redforce.player2.weapon.bizon.damrec,
                       player->redforce.player2.weapon.bizon.dratio);

        weaponkillsort(player->redforce.player2.weapon.ak47.rank,
                       player->redforce.player2.weapon.ak47.name,
                       player->redforce.player2.weapon.ak47.kills,
                       player->redforce.player2.weapon.ak47.deaths,
                       player->redforce.player2.weapon.ak47.sui,
                       player->redforce.player2.weapon.ak47.kdp,
                       player->redforce.player2.weapon.ak47.kdr,
                       player->redforce.player2.weapon.ak47.pkills,
                       player->redforce.player2.weapon.ak47.damdelt,
                       player->redforce.player2.weapon.ak47.damrec,
                       player->redforce.player2.weapon.ak47.dratio);

        weaponkillsort(player->redforce.player2.weapon.famas.rank,
                       player->redforce.player2.weapon.famas.name,
                       player->redforce.player2.weapon.famas.kills,
                       player->redforce.player2.weapon.famas.deaths,
                       player->redforce.player2.weapon.famas.sui,
                       player->redforce.player2.weapon.famas.kdp,
                       player->redforce.player2.weapon.famas.kdr,
                       player->redforce.player2.weapon.famas.pkills,
                       player->redforce.player2.weapon.famas.damdelt,
                       player->redforce.player2.weapon.famas.damrec,
                       player->redforce.player2.weapon.famas.dratio);

        weaponkillsort(player->redforce.player2.weapon.g3a3.rank,
                       player->redforce.player2.weapon.g3a3.name,
                       player->redforce.player2.weapon.g3a3.kills,
                       player->redforce.player2.weapon.g3a3.deaths,
                       player->redforce.player2.weapon.g3a3.sui,
                       player->redforce.player2.weapon.g3a3.kdp,
                       player->redforce.player2.weapon.g3a3.kdr,
                       player->redforce.player2.weapon.g3a3.pkills,
                       player->redforce.player2.weapon.g3a3.damdelt,
                       player->redforce.player2.weapon.g3a3.damrec,
                       player->redforce.player2.weapon.g3a3.dratio);

        weaponkillsort(player->redforce.player2.weapon.g36e.rank,
                       player->redforce.player2.weapon.g36e.name,
                       player->redforce.player2.weapon.g36e.kills,
                       player->redforce.player2.weapon.g36e.deaths,
                       player->redforce.player2.weapon.g36e.sui,
                       player->redforce.player2.weapon.g36e.kdp,
                       player->redforce.player2.weapon.g36e.kdr,
                       player->redforce.player2.weapon.g36e.pkills,
                       player->redforce.player2.weapon.g36e.damdelt,
                       player->redforce.player2.weapon.g36e.damrec,
                       player->redforce.player2.weapon.g36e.dratio);

        weaponkillsort(player->redforce.player2.weapon.m16.rank,
                       player->redforce.player2.weapon.m16.name,
                       player->redforce.player2.weapon.m16.kills,
                       player->redforce.player2.weapon.m16.deaths,
                       player->redforce.player2.weapon.m16.sui,
                       player->redforce.player2.weapon.m16.kdp,
                       player->redforce.player2.weapon.m16.kdr,
                       player->redforce.player2.weapon.m16.pkills,
                       player->redforce.player2.weapon.m16.damdelt,
                       player->redforce.player2.weapon.m16.damrec,
                       player->redforce.player2.weapon.m16.dratio);

        weaponkillsort(player->redforce.player2.weapon.m82.rank,
                       player->redforce.player2.weapon.m82.name,
                       player->redforce.player2.weapon.m82.kills,
                       player->redforce.player2.weapon.m82.deaths,
                       player->redforce.player2.weapon.m82.sui,
                       player->redforce.player2.weapon.m82.kdp,
                       player->redforce.player2.weapon.m82.kdr,
                       player->redforce.player2.weapon.m82.pkills,
                       player->redforce.player2.weapon.m82.damdelt,
                       player->redforce.player2.weapon.m82.damrec,
                       player->redforce.player2.weapon.m82.dratio);

        weaponkillsort(player->redforce.player2.weapon.m60.rank,
                       player->redforce.player2.weapon.m60.name,
                       player->redforce.player2.weapon.m60.kills,
                       player->redforce.player2.weapon.m60.deaths,
                       player->redforce.player2.weapon.m60.sui,
                       player->redforce.player2.weapon.m60.kdp,
                       player->redforce.player2.weapon.m60.kdr,
                       player->redforce.player2.weapon.m60.pkills,
                       player->redforce.player2.weapon.m60.damdelt,
                       player->redforce.player2.weapon.m60.damrec,
                       player->redforce.player2.weapon.m60.dratio);

        weaponkillsort(player->redforce.player2.weapon.m79.rank,
                       player->redforce.player2.weapon.m79.name,
                       player->redforce.player2.weapon.m79.kills,
                       player->redforce.player2.weapon.m79.deaths,
                       player->redforce.player2.weapon.m79.sui,
                       player->redforce.player2.weapon.m79.kdp,
                       player->redforce.player2.weapon.m79.kdr,
                       player->redforce.player2.weapon.m79.pkills,
                       player->redforce.player2.weapon.m79.damdelt,
                       player->redforce.player2.weapon.m79.damrec,
                       player->redforce.player2.weapon.m79.dratio);

        weaponkillsort(player->redforce.player2.weapon.claymore.rank,
                       player->redforce.player2.weapon.claymore.name,
                       player->redforce.player2.weapon.claymore.kills,
                       player->redforce.player2.weapon.claymore.deaths,
                       player->redforce.player2.weapon.claymore.sui,
                       player->redforce.player2.weapon.claymore.kdp,
                       player->redforce.player2.weapon.claymore.kdr,
                       player->redforce.player2.weapon.claymore.pkills,
                       player->redforce.player2.weapon.claymore.damdelt,
                       player->redforce.player2.weapon.claymore.damrec,
                       player->redforce.player2.weapon.claymore.dratio);

        weaponkillsort(player->redforce.player2.weapon.frag.rank,
                       player->redforce.player2.weapon.frag.name,
                       player->redforce.player2.weapon.frag.kills,
                       player->redforce.player2.weapon.frag.deaths,
                       player->redforce.player2.weapon.frag.sui,
                       player->redforce.player2.weapon.frag.kdp,
                       player->redforce.player2.weapon.frag.kdr,
                       player->redforce.player2.weapon.frag.pkills,
                       player->redforce.player2.weapon.frag.damdelt,
                       player->redforce.player2.weapon.frag.damrec,
                       player->redforce.player2.weapon.frag.dratio);

        weaponkillsort(player->redforce.player2.weapon.stg24.rank,
                       player->redforce.player2.weapon.stg24.name,
                       player->redforce.player2.weapon.stg24.kills,
                       player->redforce.player2.weapon.stg24.deaths,
                       player->redforce.player2.weapon.stg24.sui,
                       player->redforce.player2.weapon.stg24.kdp,
                       player->redforce.player2.weapon.stg24.kdr,
                       player->redforce.player2.weapon.stg24.pkills,
                       player->redforce.player2.weapon.stg24.damdelt,
                       player->redforce.player2.weapon.stg24.damrec,
                       player->redforce.player2.weapon.stg24.dratio);

        weaponkillsort(player->redforce.player2.weapon.m203.rank,
                       player->redforce.player2.weapon.m203.name,
                       player->redforce.player2.weapon.m203.kills,
                       player->redforce.player2.weapon.m203.deaths,
                       player->redforce.player2.weapon.m203.sui,
                       player->redforce.player2.weapon.m203.kdp,
                       player->redforce.player2.weapon.m203.kdr,
                       player->redforce.player2.weapon.m203.pkills,
                       player->redforce.player2.weapon.m203.damdelt,
                       player->redforce.player2.weapon.m203.damrec,
                       player->redforce.player2.weapon.m203.dratio);

        weaponkillsort(player->redforce.player2.weapon.uzi.rank,
                       player->redforce.player2.weapon.uzi.name,
                       player->redforce.player2.weapon.uzi.kills,
                       player->redforce.player2.weapon.uzi.deaths,
                       player->redforce.player2.weapon.uzi.sui,
                       player->redforce.player2.weapon.uzi.kdp,
                       player->redforce.player2.weapon.uzi.kdr,
                       player->redforce.player2.weapon.uzi.pkills,
                       player->redforce.player2.weapon.uzi.damdelt,
                       player->redforce.player2.weapon.uzi.damrec,
                       player->redforce.player2.weapon.uzi.dratio);

        weaponkillsort(player->redforce.player2.weapon.pkm.rank,
                       player->redforce.player2.weapon.pkm.name,
                       player->redforce.player2.weapon.pkm.kills,
                       player->redforce.player2.weapon.pkm.deaths,
                       player->redforce.player2.weapon.pkm.sui,
                       player->redforce.player2.weapon.pkm.kdp,
                       player->redforce.player2.weapon.pkm.kdr,
                       player->redforce.player2.weapon.pkm.pkills,
                       player->redforce.player2.weapon.pkm.damdelt,
                       player->redforce.player2.weapon.pkm.damrec,
                       player->redforce.player2.weapon.pkm.dratio);

        weaponkillsort(player->redforce.player2.weapon.ak74.rank,
                       player->redforce.player2.weapon.ak74.name,
                       player->redforce.player2.weapon.ak74.kills,
                       player->redforce.player2.weapon.ak74.deaths,
                       player->redforce.player2.weapon.ak74.sui,
                       player->redforce.player2.weapon.ak74.kdp,
                       player->redforce.player2.weapon.ak74.kdr,
                       player->redforce.player2.weapon.ak74.pkills,
                       player->redforce.player2.weapon.ak74.damdelt,
                       player->redforce.player2.weapon.ak74.damrec,
                       player->redforce.player2.weapon.ak74.dratio);

        weaponkillsort(player->redforce.player2.weapon.svd.rank,
                       player->redforce.player2.weapon.svd.name,
                       player->redforce.player2.weapon.svd.kills,
                       player->redforce.player2.weapon.svd.deaths,
                       player->redforce.player2.weapon.svd.sui,
                       player->redforce.player2.weapon.svd.kdp,
                       player->redforce.player2.weapon.svd.kdr,
                       player->redforce.player2.weapon.svd.pkills,
                       player->redforce.player2.weapon.svd.damdelt,
                       player->redforce.player2.weapon.svd.damrec,
                       player->redforce.player2.weapon.svd.dratio);

        weaponkillsort(player->redforce.player2.weapon.gp25.rank,
                       player->redforce.player2.weapon.gp25.name,
                       player->redforce.player2.weapon.gp25.kills,
                       player->redforce.player2.weapon.gp25.deaths,
                       player->redforce.player2.weapon.gp25.sui,
                       player->redforce.player2.weapon.gp25.kdp,
                       player->redforce.player2.weapon.gp25.kdr,
                       player->redforce.player2.weapon.gp25.pkills,
                       player->redforce.player2.weapon.gp25.damdelt,
                       player->redforce.player2.weapon.gp25.damrec,
                       player->redforce.player2.weapon.gp25.dratio);

        weaponkillsort(player->redforce.player2.weapon.ssg3000.rank,
                       player->redforce.player2.weapon.ssg3000.name,
                       player->redforce.player2.weapon.ssg3000.kills,
                       player->redforce.player2.weapon.ssg3000.deaths,
                       player->redforce.player2.weapon.ssg3000.sui,
                       player->redforce.player2.weapon.ssg3000.kdp,
                       player->redforce.player2.weapon.ssg3000.kdr,
                       player->redforce.player2.weapon.ssg3000.pkills,
                       player->redforce.player2.weapon.ssg3000.damdelt,
                       player->redforce.player2.weapon.ssg3000.damrec,
                       player->redforce.player2.weapon.ssg3000.dratio);

        weaponkillsort(player->redforce.player2.weapon.weapmortar.rank,
                       player->redforce.player2.weapon.weapmortar.name,
                       player->redforce.player2.weapon.weapmortar.kills,
                       player->redforce.player2.weapon.weapmortar.deaths,
                       player->redforce.player2.weapon.weapmortar.sui,
                       player->redforce.player2.weapon.weapmortar.kdp,
                       player->redforce.player2.weapon.weapmortar.kdr,
                       player->redforce.player2.weapon.weapmortar.pkills,
                       player->redforce.player2.weapon.weapmortar.damdelt,
                       player->redforce.player2.weapon.weapmortar.damrec,
                       player->redforce.player2.weapon.weapmortar.dratio);

        weaponkillsort(player->redforce.player2.weapon.spark_shower.rank,
                       player->redforce.player2.weapon.spark_shower.name,
                       player->redforce.player2.weapon.spark_shower.kills,
                       player->redforce.player2.weapon.spark_shower.deaths,
                       player->redforce.player2.weapon.spark_shower.sui,
                       player->redforce.player2.weapon.spark_shower.kdp,
                       player->redforce.player2.weapon.spark_shower.kdr,
                       player->redforce.player2.weapon.spark_shower.pkills,
                       player->redforce.player2.weapon.spark_shower.damdelt,
                       player->redforce.player2.weapon.spark_shower.damrec,
                       player->redforce.player2.weapon.spark_shower.dratio);

        weaponkillsort(player->redforce.player2.weapon.monster_mortar.rank,
                       player->redforce.player2.weapon.monster_mortar.name,
                       player->redforce.player2.weapon.monster_mortar.kills,
                       player->redforce.player2.weapon.monster_mortar.deaths,
                       player->redforce.player2.weapon.monster_mortar.sui,
                       player->redforce.player2.weapon.monster_mortar.kdp,
                       player->redforce.player2.weapon.monster_mortar.kdr,
                       player->redforce.player2.weapon.monster_mortar.pkills,
                       player->redforce.player2.weapon.monster_mortar.damdelt,
                       player->redforce.player2.weapon.monster_mortar.damrec,
                       player->redforce.player2.weapon.monster_mortar.dratio);

        weaponkillsort(player->redforce.player2.weapon.func_tank.rank,
                       player->redforce.player2.weapon.func_tank.name,
                       player->redforce.player2.weapon.func_tank.kills,
                       player->redforce.player2.weapon.func_tank.deaths,
                       player->redforce.player2.weapon.func_tank.sui,
                       player->redforce.player2.weapon.func_tank.kdp,
                       player->redforce.player2.weapon.func_tank.kdr,
                       player->redforce.player2.weapon.func_tank.pkills,
                       player->redforce.player2.weapon.func_tank.damdelt,
                       player->redforce.player2.weapon.func_tank.damrec,
                       player->redforce.player2.weapon.func_tank.dratio);

        weaponkillsort(player->redforce.player2.weapon.env_explosion.rank,
                       player->redforce.player2.weapon.env_explosion.name,
                       player->redforce.player2.weapon.env_explosion.kills,
                       player->redforce.player2.weapon.env_explosion.deaths,
                       player->redforce.player2.weapon.env_explosion.sui,
                       player->redforce.player2.weapon.env_explosion.kdp,
                       player->redforce.player2.weapon.env_explosion.kdr,
                       player->redforce.player2.weapon.env_explosion.pkills,
                       player->redforce.player2.weapon.env_explosion.damdelt,
                       player->redforce.player2.weapon.env_explosion.damrec,
                       player->redforce.player2.weapon.env_explosion.dratio);

        weaponkillsort(player->redforce.player2.weapon.concussion.rank,
                       player->redforce.player2.weapon.concussion.name,
                       player->redforce.player2.weapon.concussion.kills,
                       player->redforce.player2.weapon.concussion.deaths,
                       player->redforce.player2.weapon.concussion.sui,
                       player->redforce.player2.weapon.concussion.kdp,
                       player->redforce.player2.weapon.concussion.kdr,
                       player->redforce.player2.weapon.concussion.pkills,
                       player->redforce.player2.weapon.concussion.damdelt,
                       player->redforce.player2.weapon.concussion.damrec,
                       player->redforce.player2.weapon.concussion.dratio);

        weaponkillsort(player->redforce.player2.weapon.ammobox.rank,
                       player->redforce.player2.weapon.ammobox.name,
                       player->redforce.player2.weapon.ammobox.kills,
                       player->redforce.player2.weapon.ammobox.deaths,
                       player->redforce.player2.weapon.ammobox.sui,
                       player->redforce.player2.weapon.ammobox.kdp,
                       player->redforce.player2.weapon.ammobox.kdr,
                       player->redforce.player2.weapon.ammobox.pkills,
                       player->redforce.player2.weapon.ammobox.damdelt,
                       player->redforce.player2.weapon.ammobox.damrec,
                       player->redforce.player2.weapon.ammobox.dratio);


    // Add Weapons to Linklist and Sort Weapons for Each Player by Kills
        weaponkillsort(player->blueforce.player2.weapon.knife.rank,       // Weapon Rank
                       player->blueforce.player2.weapon.knife.name,       // Weapon Name
                       player->blueforce.player2.weapon.knife.kills,      // Weapon Kills
                       player->blueforce.player2.weapon.knife.deaths,     // Weapon Deaths
                       player->blueforce.player2.weapon.knife.sui,        // Weapon sui
                       player->blueforce.player2.weapon.knife.kdp,        // Weapon Kill Death Suicide Percentage
                       player->blueforce.player2.weapon.knife.kdr,        // Weapon Kill : Death Ratio
                       player->blueforce.player2.weapon.knife.pkills,
                       player->blueforce.player2.weapon.knife.damdelt,
                       player->blueforce.player2.weapon.knife.damrec,
                       player->blueforce.player2.weapon.knife.dratio);

        weaponkillsort(player->blueforce.player2.weapon.coltgov.rank,
                       player->blueforce.player2.weapon.coltgov.name,
                       player->blueforce.player2.weapon.coltgov.kills,
                       player->blueforce.player2.weapon.coltgov.deaths,
                       player->blueforce.player2.weapon.coltgov.sui,
                       player->blueforce.player2.weapon.coltgov.kdp,
                       player->blueforce.player2.weapon.coltgov.kdr,
                       player->blueforce.player2.weapon.coltgov.pkills,
                       player->blueforce.player2.weapon.coltgov.damdelt,
                       player->blueforce.player2.weapon.coltgov.damrec,
                       player->blueforce.player2.weapon.coltgov.dratio);

        weaponkillsort(player->blueforce.player2.weapon.ber92f.rank,
                       player->blueforce.player2.weapon.ber92f.name,
                       player->blueforce.player2.weapon.ber92f.kills,
                       player->blueforce.player2.weapon.ber92f.deaths,
                       player->blueforce.player2.weapon.ber92f.sui,
                       player->blueforce.player2.weapon.ber92f.kdp,
                       player->blueforce.player2.weapon.ber92f.kdr,
                       player->blueforce.player2.weapon.ber92f.pkills,
                       player->blueforce.player2.weapon.ber92f.damdelt,
                       player->blueforce.player2.weapon.ber92f.damrec,
                       player->blueforce.player2.weapon.ber92f.dratio);

        weaponkillsort(player->blueforce.player2.weapon.ber93r.rank,
                       player->blueforce.player2.weapon.ber93r.name,
                       player->blueforce.player2.weapon.ber93r.kills,
                       player->blueforce.player2.weapon.ber93r.deaths,
                       player->blueforce.player2.weapon.ber93r.sui,
                       player->blueforce.player2.weapon.ber93r.kdp,
                       player->blueforce.player2.weapon.ber93r.kdr,
                       player->blueforce.player2.weapon.ber93r.pkills,
                       player->blueforce.player2.weapon.ber93r.damdelt,
                       player->blueforce.player2.weapon.ber93r.damrec,
                       player->blueforce.player2.weapon.ber93r.dratio);

        weaponkillsort(player->blueforce.player2.weapon.anaconda.rank,
                       player->blueforce.player2.weapon.anaconda.name,
                       player->blueforce.player2.weapon.anaconda.kills,
                       player->blueforce.player2.weapon.anaconda.deaths,
                       player->blueforce.player2.weapon.anaconda.sui,
                       player->blueforce.player2.weapon.anaconda.kdp,
                       player->blueforce.player2.weapon.anaconda.kdr,
                       player->blueforce.player2.weapon.anaconda.pkills,
                       player->blueforce.player2.weapon.anaconda.damdelt,
                       player->blueforce.player2.weapon.anaconda.damrec,
                       player->blueforce.player2.weapon.anaconda.dratio);

        weaponkillsort(player->blueforce.player2.weapon.desert.rank,
                       player->blueforce.player2.weapon.desert.name,
                       player->blueforce.player2.weapon.desert.kills,
                       player->blueforce.player2.weapon.desert.deaths,
                       player->blueforce.player2.weapon.desert.sui,
                       player->blueforce.player2.weapon.desert.kdp,
                       player->blueforce.player2.weapon.desert.kdr,
                       player->blueforce.player2.weapon.desert.pkills,
                       player->blueforce.player2.weapon.desert.damdelt,
                       player->blueforce.player2.weapon.desert.damrec,
                       player->blueforce.player2.weapon.desert.dratio);

        weaponkillsort(player->blueforce.player2.weapon.benelli.rank,
                       player->blueforce.player2.weapon.benelli.name,
                       player->blueforce.player2.weapon.benelli.kills,
                       player->blueforce.player2.weapon.benelli.deaths,
                       player->blueforce.player2.weapon.benelli.sui,
                       player->blueforce.player2.weapon.benelli.kdp,
                       player->blueforce.player2.weapon.benelli.kdr,
                       player->blueforce.player2.weapon.benelli.pkills,
                       player->blueforce.player2.weapon.benelli.damdelt,
                       player->blueforce.player2.weapon.benelli.damrec,
                       player->blueforce.player2.weapon.benelli.dratio);

        weaponkillsort(player->blueforce.player2.weapon.saiga.rank,
                       player->blueforce.player2.weapon.saiga.name,
                       player->blueforce.player2.weapon.saiga.kills,
                       player->blueforce.player2.weapon.saiga.deaths,
                       player->blueforce.player2.weapon.saiga.sui,
                       player->blueforce.player2.weapon.saiga.kdp,
                       player->blueforce.player2.weapon.saiga.kdr,
                       player->blueforce.player2.weapon.saiga.pkills,
                       player->blueforce.player2.weapon.saiga.damdelt,
                       player->blueforce.player2.weapon.saiga.damrec,
                       player->blueforce.player2.weapon.saiga.dratio);

        weaponkillsort(player->blueforce.player2.weapon.mp5a5.rank,
                       player->blueforce.player2.weapon.mp5a5.name,
                       player->blueforce.player2.weapon.mp5a5.kills,
                       player->blueforce.player2.weapon.mp5a5.deaths,
                       player->blueforce.player2.weapon.mp5a5.sui,
                       player->blueforce.player2.weapon.mp5a5.kdp,
                       player->blueforce.player2.weapon.mp5a5.kdr,
                       player->blueforce.player2.weapon.mp5a5.pkills,
                       player->blueforce.player2.weapon.mp5a5.damdelt,
                       player->blueforce.player2.weapon.mp5a5.damrec,
                       player->blueforce.player2.weapon.mp5a5.dratio);

        weaponkillsort(player->blueforce.player2.weapon.sterling.rank,
                       player->blueforce.player2.weapon.sterling.name,
                       player->blueforce.player2.weapon.sterling.kills,
                       player->blueforce.player2.weapon.sterling.deaths,
                       player->blueforce.player2.weapon.sterling.sui,
                       player->blueforce.player2.weapon.sterling.kdp,
                       player->blueforce.player2.weapon.sterling.kdr,
                       player->blueforce.player2.weapon.sterling.pkills,
                       player->blueforce.player2.weapon.sterling.damdelt,
                       player->blueforce.player2.weapon.sterling.damrec,
                       player->blueforce.player2.weapon.sterling.dratio);

        weaponkillsort(player->blueforce.player2.weapon.bizon.rank,
                       player->blueforce.player2.weapon.bizon.name,
                       player->blueforce.player2.weapon.bizon.kills,
                       player->blueforce.player2.weapon.bizon.deaths,
                       player->blueforce.player2.weapon.bizon.sui,
                       player->blueforce.player2.weapon.bizon.kdp,
                       player->blueforce.player2.weapon.bizon.kdr,
                       player->blueforce.player2.weapon.bizon.pkills,
                       player->blueforce.player2.weapon.bizon.damdelt,
                       player->blueforce.player2.weapon.bizon.damrec,
                       player->blueforce.player2.weapon.bizon.dratio);

        weaponkillsort(player->blueforce.player2.weapon.ak47.rank,
                       player->blueforce.player2.weapon.ak47.name,
                       player->blueforce.player2.weapon.ak47.kills,
                       player->blueforce.player2.weapon.ak47.deaths,
                       player->blueforce.player2.weapon.ak47.sui,
                       player->blueforce.player2.weapon.ak47.kdp,
                       player->blueforce.player2.weapon.ak47.kdr,
                       player->blueforce.player2.weapon.ak47.pkills,
                       player->blueforce.player2.weapon.ak47.damdelt,
                       player->blueforce.player2.weapon.ak47.damrec,
                       player->blueforce.player2.weapon.ak47.dratio);

        weaponkillsort(player->blueforce.player2.weapon.famas.rank,
                       player->blueforce.player2.weapon.famas.name,
                       player->blueforce.player2.weapon.famas.kills,
                       player->blueforce.player2.weapon.famas.deaths,
                       player->blueforce.player2.weapon.famas.sui,
                       player->blueforce.player2.weapon.famas.kdp,
                       player->blueforce.player2.weapon.famas.kdr,
                       player->blueforce.player2.weapon.famas.pkills,
                       player->blueforce.player2.weapon.famas.damdelt,
                       player->blueforce.player2.weapon.famas.damrec,
                       player->blueforce.player2.weapon.famas.dratio);

        weaponkillsort(player->blueforce.player2.weapon.g3a3.rank,
                       player->blueforce.player2.weapon.g3a3.name,
                       player->blueforce.player2.weapon.g3a3.kills,
                       player->blueforce.player2.weapon.g3a3.deaths,
                       player->blueforce.player2.weapon.g3a3.sui,
                       player->blueforce.player2.weapon.g3a3.kdp,
                       player->blueforce.player2.weapon.g3a3.kdr,
                       player->blueforce.player2.weapon.g3a3.pkills,
                       player->blueforce.player2.weapon.g3a3.damdelt,
                       player->blueforce.player2.weapon.g3a3.damrec,
                       player->blueforce.player2.weapon.g3a3.dratio);

        weaponkillsort(player->blueforce.player2.weapon.g36e.rank,
                       player->blueforce.player2.weapon.g36e.name,
                       player->blueforce.player2.weapon.g36e.kills,
                       player->blueforce.player2.weapon.g36e.deaths,
                       player->blueforce.player2.weapon.g36e.sui,
                       player->blueforce.player2.weapon.g36e.kdp,
                       player->blueforce.player2.weapon.g36e.kdr,
                       player->blueforce.player2.weapon.g36e.pkills,
                       player->blueforce.player2.weapon.g36e.damdelt,
                       player->blueforce.player2.weapon.g36e.damrec,
                       player->blueforce.player2.weapon.g36e.dratio);

        weaponkillsort(player->blueforce.player2.weapon.m16.rank,
                       player->blueforce.player2.weapon.m16.name,
                       player->blueforce.player2.weapon.m16.kills,
                       player->blueforce.player2.weapon.m16.deaths,
                       player->blueforce.player2.weapon.m16.sui,
                       player->blueforce.player2.weapon.m16.kdp,
                       player->blueforce.player2.weapon.m16.kdr,
                       player->blueforce.player2.weapon.m16.pkills,
                       player->blueforce.player2.weapon.m16.damdelt,
                       player->blueforce.player2.weapon.m16.damrec,
                       player->blueforce.player2.weapon.m16.dratio);

        weaponkillsort(player->blueforce.player2.weapon.m82.rank,
                       player->blueforce.player2.weapon.m82.name,
                       player->blueforce.player2.weapon.m82.kills,
                       player->blueforce.player2.weapon.m82.deaths,
                       player->blueforce.player2.weapon.m82.sui,
                       player->blueforce.player2.weapon.m82.kdp,
                       player->blueforce.player2.weapon.m82.kdr,
                       player->blueforce.player2.weapon.m82.pkills,
                       player->blueforce.player2.weapon.m82.damdelt,
                       player->blueforce.player2.weapon.m82.damrec,
                       player->blueforce.player2.weapon.m82.dratio);

        weaponkillsort(player->blueforce.player2.weapon.m60.rank,
                       player->blueforce.player2.weapon.m60.name,
                       player->blueforce.player2.weapon.m60.kills,
                       player->blueforce.player2.weapon.m60.deaths,
                       player->blueforce.player2.weapon.m60.sui,
                       player->blueforce.player2.weapon.m60.kdp,
                       player->blueforce.player2.weapon.m60.kdr,
                       player->blueforce.player2.weapon.m60.pkills,
                       player->blueforce.player2.weapon.m60.damdelt,
                       player->blueforce.player2.weapon.m60.damrec,
                       player->blueforce.player2.weapon.m60.dratio);

        weaponkillsort(player->blueforce.player2.weapon.m79.rank,
                       player->blueforce.player2.weapon.m79.name,
                       player->blueforce.player2.weapon.m79.kills,
                       player->blueforce.player2.weapon.m79.deaths,
                       player->blueforce.player2.weapon.m79.sui,
                       player->blueforce.player2.weapon.m79.kdp,
                       player->blueforce.player2.weapon.m79.kdr,
                       player->blueforce.player2.weapon.m79.pkills,
                       player->blueforce.player2.weapon.m79.damdelt,
                       player->blueforce.player2.weapon.m79.damrec,
                       player->blueforce.player2.weapon.m79.dratio);

        weaponkillsort(player->blueforce.player2.weapon.claymore.rank,
                       player->blueforce.player2.weapon.claymore.name,
                       player->blueforce.player2.weapon.claymore.kills,
                       player->blueforce.player2.weapon.claymore.deaths,
                       player->blueforce.player2.weapon.claymore.sui,
                       player->blueforce.player2.weapon.claymore.kdp,
                       player->blueforce.player2.weapon.claymore.kdr,
                       player->blueforce.player2.weapon.claymore.pkills,
                       player->blueforce.player2.weapon.claymore.damdelt,
                       player->blueforce.player2.weapon.claymore.damrec,
                       player->blueforce.player2.weapon.claymore.dratio);

        weaponkillsort(player->blueforce.player2.weapon.frag.rank,
                       player->blueforce.player2.weapon.frag.name,
                       player->blueforce.player2.weapon.frag.kills,
                       player->blueforce.player2.weapon.frag.deaths,
                       player->blueforce.player2.weapon.frag.sui,
                       player->blueforce.player2.weapon.frag.kdp,
                       player->blueforce.player2.weapon.frag.kdr,
                       player->blueforce.player2.weapon.frag.pkills,
                       player->blueforce.player2.weapon.frag.damdelt,
                       player->blueforce.player2.weapon.frag.damrec,
                       player->blueforce.player2.weapon.frag.dratio);

        weaponkillsort(player->blueforce.player2.weapon.stg24.rank,
                       player->blueforce.player2.weapon.stg24.name,
                       player->blueforce.player2.weapon.stg24.kills,
                       player->blueforce.player2.weapon.stg24.deaths,
                       player->blueforce.player2.weapon.stg24.sui,
                       player->blueforce.player2.weapon.stg24.kdp,
                       player->blueforce.player2.weapon.stg24.kdr,
                       player->blueforce.player2.weapon.stg24.pkills,
                       player->blueforce.player2.weapon.stg24.damdelt,
                       player->blueforce.player2.weapon.stg24.damrec,
                       player->blueforce.player2.weapon.stg24.dratio);

        weaponkillsort(player->blueforce.player2.weapon.m203.rank,
                       player->blueforce.player2.weapon.m203.name,
                       player->blueforce.player2.weapon.m203.kills,
                       player->blueforce.player2.weapon.m203.deaths,
                       player->blueforce.player2.weapon.m203.sui,
                       player->blueforce.player2.weapon.m203.kdp,
                       player->blueforce.player2.weapon.m203.kdr,
                       player->blueforce.player2.weapon.m203.pkills,
                       player->blueforce.player2.weapon.m203.damdelt,
                       player->blueforce.player2.weapon.m203.damrec,
                       player->blueforce.player2.weapon.m203.dratio);

        weaponkillsort(player->blueforce.player2.weapon.uzi.rank,
                       player->blueforce.player2.weapon.uzi.name,
                       player->blueforce.player2.weapon.uzi.kills,
                       player->blueforce.player2.weapon.uzi.deaths,
                       player->blueforce.player2.weapon.uzi.sui,
                       player->blueforce.player2.weapon.uzi.kdp,
                       player->blueforce.player2.weapon.uzi.kdr,
                       player->blueforce.player2.weapon.uzi.pkills,
                       player->blueforce.player2.weapon.uzi.damdelt,
                       player->blueforce.player2.weapon.uzi.damrec,
                       player->blueforce.player2.weapon.uzi.dratio);

        weaponkillsort(player->blueforce.player2.weapon.pkm.rank,
                       player->blueforce.player2.weapon.pkm.name,
                       player->blueforce.player2.weapon.pkm.kills,
                       player->blueforce.player2.weapon.pkm.deaths,
                       player->blueforce.player2.weapon.pkm.sui,
                       player->blueforce.player2.weapon.pkm.kdp,
                       player->blueforce.player2.weapon.pkm.kdr,
                       player->blueforce.player2.weapon.pkm.pkills,
                       player->blueforce.player2.weapon.pkm.damdelt,
                       player->blueforce.player2.weapon.pkm.damrec,
                       player->blueforce.player2.weapon.pkm.dratio);

        weaponkillsort(player->blueforce.player2.weapon.ak74.rank,
                       player->blueforce.player2.weapon.ak74.name,
                       player->blueforce.player2.weapon.ak74.kills,
                       player->blueforce.player2.weapon.ak74.deaths,
                       player->blueforce.player2.weapon.ak74.sui,
                       player->blueforce.player2.weapon.ak74.kdp,
                       player->blueforce.player2.weapon.ak74.kdr,
                       player->blueforce.player2.weapon.ak74.pkills,
                       player->blueforce.player2.weapon.ak74.damdelt,
                       player->blueforce.player2.weapon.ak74.damrec,
                       player->blueforce.player2.weapon.ak74.dratio);

        weaponkillsort(player->blueforce.player2.weapon.svd.rank,
                       player->blueforce.player2.weapon.svd.name,
                       player->blueforce.player2.weapon.svd.kills,
                       player->blueforce.player2.weapon.svd.deaths,
                       player->blueforce.player2.weapon.svd.sui,
                       player->blueforce.player2.weapon.svd.kdp,
                       player->blueforce.player2.weapon.svd.kdr,
                       player->blueforce.player2.weapon.svd.pkills,
                       player->blueforce.player2.weapon.svd.damdelt,
                       player->blueforce.player2.weapon.svd.damrec,
                       player->blueforce.player2.weapon.svd.dratio);

        weaponkillsort(player->blueforce.player2.weapon.gp25.rank,
                       player->blueforce.player2.weapon.gp25.name,
                       player->blueforce.player2.weapon.gp25.kills,
                       player->blueforce.player2.weapon.gp25.deaths,
                       player->blueforce.player2.weapon.gp25.sui,
                       player->blueforce.player2.weapon.gp25.kdp,
                       player->blueforce.player2.weapon.gp25.kdr,
                       player->blueforce.player2.weapon.gp25.pkills,
                       player->blueforce.player2.weapon.gp25.damdelt,
                       player->blueforce.player2.weapon.gp25.damrec,
                       player->blueforce.player2.weapon.gp25.dratio);

        weaponkillsort(player->blueforce.player2.weapon.ssg3000.rank,
                       player->blueforce.player2.weapon.ssg3000.name,
                       player->blueforce.player2.weapon.ssg3000.kills,
                       player->blueforce.player2.weapon.ssg3000.deaths,
                       player->blueforce.player2.weapon.ssg3000.sui,
                       player->blueforce.player2.weapon.ssg3000.kdp,
                       player->blueforce.player2.weapon.ssg3000.kdr,
                       player->blueforce.player2.weapon.ssg3000.pkills,
                       player->blueforce.player2.weapon.ssg3000.damdelt,
                       player->blueforce.player2.weapon.ssg3000.damrec,
                       player->blueforce.player2.weapon.ssg3000.dratio);

        weaponkillsort(player->blueforce.player2.weapon.weapmortar.rank,
                       player->blueforce.player2.weapon.weapmortar.name,
                       player->blueforce.player2.weapon.weapmortar.kills,
                       player->blueforce.player2.weapon.weapmortar.deaths,
                       player->blueforce.player2.weapon.weapmortar.sui,
                       player->blueforce.player2.weapon.weapmortar.kdp,
                       player->blueforce.player2.weapon.weapmortar.kdr,
                       player->blueforce.player2.weapon.weapmortar.pkills,
                       player->blueforce.player2.weapon.weapmortar.damdelt,
                       player->blueforce.player2.weapon.weapmortar.damrec,
                       player->blueforce.player2.weapon.weapmortar.dratio);

        weaponkillsort(player->blueforce.player2.weapon.spark_shower.rank,
                       player->blueforce.player2.weapon.spark_shower.name,
                       player->blueforce.player2.weapon.spark_shower.kills,
                       player->blueforce.player2.weapon.spark_shower.deaths,
                       player->blueforce.player2.weapon.spark_shower.sui,
                       player->blueforce.player2.weapon.spark_shower.kdp,
                       player->blueforce.player2.weapon.spark_shower.kdr,
                       player->blueforce.player2.weapon.spark_shower.pkills,
                       player->blueforce.player2.weapon.spark_shower.damdelt,
                       player->blueforce.player2.weapon.spark_shower.damrec,
                       player->blueforce.player2.weapon.spark_shower.dratio);

        weaponkillsort(player->blueforce.player2.weapon.monster_mortar.rank,
                       player->blueforce.player2.weapon.monster_mortar.name,
                       player->blueforce.player2.weapon.monster_mortar.kills,
                       player->blueforce.player2.weapon.monster_mortar.deaths,
                       player->blueforce.player2.weapon.monster_mortar.sui,
                       player->blueforce.player2.weapon.monster_mortar.kdp,
                       player->blueforce.player2.weapon.monster_mortar.kdr,
                       player->blueforce.player2.weapon.monster_mortar.pkills,
                       player->blueforce.player2.weapon.monster_mortar.damdelt,
                       player->blueforce.player2.weapon.monster_mortar.damrec,
                       player->blueforce.player2.weapon.monster_mortar.dratio);

        weaponkillsort(player->blueforce.player2.weapon.func_tank.rank,
                       player->blueforce.player2.weapon.func_tank.name,
                       player->blueforce.player2.weapon.func_tank.kills,
                       player->blueforce.player2.weapon.func_tank.deaths,
                       player->blueforce.player2.weapon.func_tank.sui,
                       player->blueforce.player2.weapon.func_tank.kdp,
                       player->blueforce.player2.weapon.func_tank.kdr,
                       player->blueforce.player2.weapon.func_tank.pkills,
                       player->blueforce.player2.weapon.func_tank.damdelt,
                       player->blueforce.player2.weapon.func_tank.damrec,
                       player->blueforce.player2.weapon.func_tank.dratio);

        weaponkillsort(player->blueforce.player2.weapon.env_explosion.rank,
                       player->blueforce.player2.weapon.env_explosion.name,
                       player->blueforce.player2.weapon.env_explosion.kills,
                       player->blueforce.player2.weapon.env_explosion.deaths,
                       player->blueforce.player2.weapon.env_explosion.sui,
                       player->blueforce.player2.weapon.env_explosion.kdp,
                       player->blueforce.player2.weapon.env_explosion.kdr,
                       player->blueforce.player2.weapon.env_explosion.pkills,
                       player->blueforce.player2.weapon.env_explosion.damdelt,
                       player->blueforce.player2.weapon.env_explosion.damrec,
                       player->blueforce.player2.weapon.env_explosion.dratio);

        weaponkillsort(player->blueforce.player2.weapon.concussion.rank,
                       player->blueforce.player2.weapon.concussion.name,
                       player->blueforce.player2.weapon.concussion.kills,
                       player->blueforce.player2.weapon.concussion.deaths,
                       player->blueforce.player2.weapon.concussion.sui,
                       player->blueforce.player2.weapon.concussion.kdp,
                       player->blueforce.player2.weapon.concussion.kdr,
                       player->blueforce.player2.weapon.concussion.pkills,
                       player->blueforce.player2.weapon.concussion.damdelt,
                       player->blueforce.player2.weapon.concussion.damrec,
                       player->blueforce.player2.weapon.concussion.dratio);

        weaponkillsort(player->blueforce.player2.weapon.ammobox.rank,
                       player->blueforce.player2.weapon.ammobox.name,
                       player->blueforce.player2.weapon.ammobox.kills,
                       player->blueforce.player2.weapon.ammobox.deaths,
                       player->blueforce.player2.weapon.ammobox.sui,
                       player->blueforce.player2.weapon.ammobox.kdp,
                       player->blueforce.player2.weapon.ammobox.kdr,
                       player->blueforce.player2.weapon.ammobox.pkills,
                       player->blueforce.player2.weapon.ammobox.damdelt,
                       player->blueforce.player2.weapon.ammobox.damrec,
                       player->blueforce.player2.weapon.ammobox.dratio);

        return;
}


/*--------------------------------------------------------------------------------*/
/*// Reveices Player Weapons and Sorts by kills for Players.HTML
void calcweapons(PLAYERREC * player)
{
        // Add Weapons to Linklist and Sort Weapons for Each Player by Kills
        weaponkillsort(player->redforce.player2.weapon.knife.rank,       // Weapon Rank
                       player->redforce.player2.weapon.knife.name,       // Weapon Name
                       player->redforce.player2.weapon.knife.kills,      // Weapon Kills
                       player->redforce.player2.weapon.knife.deaths,     // Weapon Deaths
                       player->redforce.player2.weapon.knife.sui,        // Weapon sui
                       player->redforce.player2.weapon.knife.kdp,        // Weapon Kill Death Suicide Percentage
                       player->redforce.player2.weapon.knife.kdr,        // Weapon Kill : Death Ratio
                       player->redforce.player2.weapon.knife.pkills,
                       player->redforce.player2.weapon.knife.damdelt,
                       player->redforce.player2.weapon.knife.damrec,
                       player->redforce.player2.weapon.knife.dratio);

        weaponkillsort(player->redforce.player2.weapon.coltgov.rank,
                       player->redforce.player2.weapon.coltgov.name,
                       player->redforce.player2.weapon.coltgov.kills,
                       player->redforce.player2.weapon.coltgov.deaths,
                       player->redforce.player2.weapon.coltgov.sui,
                       player->redforce.player2.weapon.coltgov.kdp,
                       player->redforce.player2.weapon.coltgov.kdr,
                       player->redforce.player2.weapon.coltgov.pkills,
                       player->redforce.player2.weapon.coltgov.damdelt,
                       player->redforce.player2.weapon.coltgov.damrec,
                       player->redforce.player2.weapon.coltgov.dratio);

        weaponkillsort(player->redforce.player2.weapon.ber92f.rank,
                       player->redforce.player2.weapon.ber92f.name,
                       player->redforce.player2.weapon.ber92f.kills,
                       player->redforce.player2.weapon.ber92f.deaths,
                       player->redforce.player2.weapon.ber92f.sui,
                       player->redforce.player2.weapon.ber92f.kdp,
                       player->redforce.player2.weapon.ber92f.kdr,
                       player->redforce.player2.weapon.ber92f.pkills,
                       player->redforce.player2.weapon.ber92f.damdelt,
                       player->redforce.player2.weapon.ber92f.damrec,
                       player->redforce.player2.weapon.ber92f.dratio);

        weaponkillsort(player->redforce.player2.weapon.ber93r.rank,
                       player->redforce.player2.weapon.ber93r.name,
                       player->redforce.player2.weapon.ber93r.kills,
                       player->redforce.player2.weapon.ber93r.deaths,
                       player->redforce.player2.weapon.ber93r.sui,
                       player->redforce.player2.weapon.ber93r.kdp,
                       player->redforce.player2.weapon.ber93r.kdr,
                       player->redforce.player2.weapon.ber93r.pkills,
                       player->redforce.player2.weapon.ber93r.damdelt,
                       player->redforce.player2.weapon.ber93r.damrec,
                       player->redforce.player2.weapon.ber93r.dratio);

        weaponkillsort(player->redforce.player2.weapon.anaconda.rank,
                       player->redforce.player2.weapon.anaconda.name,
                       player->redforce.player2.weapon.anaconda.kills,
                       player->redforce.player2.weapon.anaconda.deaths,
                       player->redforce.player2.weapon.anaconda.sui,
                       player->redforce.player2.weapon.anaconda.kdp,
                       player->redforce.player2.weapon.anaconda.kdr,
                       player->redforce.player2.weapon.anaconda.pkills,
                       player->redforce.player2.weapon.anaconda.damdelt,
                       player->redforce.player2.weapon.anaconda.damrec,
                       player->redforce.player2.weapon.anaconda.dratio);

        weaponkillsort(player->redforce.player2.weapon.desert.rank,
                       player->redforce.player2.weapon.desert.name,
                       player->redforce.player2.weapon.desert.kills,
                       player->redforce.player2.weapon.desert.deaths,
                       player->redforce.player2.weapon.desert.sui,
                       player->redforce.player2.weapon.desert.kdp,
                       player->redforce.player2.weapon.desert.kdr,
                       player->redforce.player2.weapon.desert.pkills,
                       player->redforce.player2.weapon.desert.damdelt,
                       player->redforce.player2.weapon.desert.damrec,
                       player->redforce.player2.weapon.desert.dratio);

        weaponkillsort(player->redforce.player2.weapon.desert.rank,
                       player->redforce.player2.weapon.desert.name,
                       player->redforce.player2.weapon.desert.kills,
                       player->redforce.player2.weapon.desert.deaths,
                       player->redforce.player2.weapon.desert.sui,
                       player->redforce.player2.weapon.desert.kdp,
                       player->redforce.player2.weapon.desert.kdr,
                       player->redforce.player2.weapon.desert.pkills,
                       player->redforce.player2.weapon.desert.damdelt,
                       player->redforce.player2.weapon.desert.damrec,
                       player->redforce.player2.weapon.desert.dratio);

        weaponkillsort(player->redforce.player2.weapon.saiga.rank,
                       player->redforce.player2.weapon.saiga.name,
                       player->redforce.player2.weapon.saiga.kills,
                       player->redforce.player2.weapon.saiga.deaths,
                       player->redforce.player2.weapon.saiga.sui,
                       player->redforce.player2.weapon.saiga.kdp,
                       player->redforce.player2.weapon.saiga.kdr,
                       player->redforce.player2.weapon.saiga.pkills,
                       player->redforce.player2.weapon.saiga.damdelt,
                       player->redforce.player2.weapon.saiga.damrec,
                       player->redforce.player2.weapon.saiga.dratio);

        weaponkillsort(player->redforce.player2.weapon.mp5a5.rank,
                       player->redforce.player2.weapon.mp5a5.name,
                       player->redforce.player2.weapon.mp5a5.kills,
                       player->redforce.player2.weapon.mp5a5.deaths,
                       player->redforce.player2.weapon.mp5a5.sui,
                       player->redforce.player2.weapon.mp5a5.kdp,
                       player->redforce.player2.weapon.mp5a5.kdr,
                       player->redforce.player2.weapon.mp5a5.pkills,
                       player->redforce.player2.weapon.mp5a5.damdelt,
                       player->redforce.player2.weapon.mp5a5.damrec,
                       player->redforce.player2.weapon.mp5a5.dratio);

        weaponkillsort(player->redforce.player2.weapon.sterling.rank,
                       player->redforce.player2.weapon.sterling.name,
                       player->redforce.player2.weapon.sterling.kills,
                       player->redforce.player2.weapon.sterling.deaths,
                       player->redforce.player2.weapon.sterling.sui,
                       player->redforce.player2.weapon.sterling.kdp,
                       player->redforce.player2.weapon.sterling.kdr,
                       player->redforce.player2.weapon.sterling.pkills,
                       player->redforce.player2.weapon.sterling.damdelt,
                       player->redforce.player2.weapon.sterling.damrec,
                       player->redforce.player2.weapon.sterling.dratio);

        weaponkillsort(player->redforce.player2.weapon.bizon.rank,
                       player->redforce.player2.weapon.bizon.name,
                       player->redforce.player2.weapon.bizon.kills,
                       player->redforce.player2.weapon.bizon.deaths,
                       player->redforce.player2.weapon.bizon.sui,
                       player->redforce.player2.weapon.bizon.kdp,
                       player->redforce.player2.weapon.bizon.kdr,
                       player->redforce.player2.weapon.bizon.pkills,
                       player->redforce.player2.weapon.bizon.damdelt,
                       player->redforce.player2.weapon.bizon.damrec,
                       player->redforce.player2.weapon.bizon.dratio);

        weaponkillsort(player->redforce.player2.weapon.ak47.rank,
                       player->redforce.player2.weapon.ak47.name,
                       player->redforce.player2.weapon.ak47.kills,
                       player->redforce.player2.weapon.ak47.deaths,
                       player->redforce.player2.weapon.ak47.sui,
                       player->redforce.player2.weapon.ak47.kdp,
                       player->redforce.player2.weapon.ak47.kdr,
                       player->redforce.player2.weapon.ak47.pkills,
                       player->redforce.player2.weapon.ak47.damdelt,
                       player->redforce.player2.weapon.ak47.damrec,
                       player->redforce.player2.weapon.ak47.dratio);

        weaponkillsort(player->redforce.player2.weapon.famas.rank,
                       player->redforce.player2.weapon.famas.name,
                       player->redforce.player2.weapon.famas.kills,
                       player->redforce.player2.weapon.famas.deaths,
                       player->redforce.player2.weapon.famas.sui,
                       player->redforce.player2.weapon.famas.kdp,
                       player->redforce.player2.weapon.famas.kdr,
                       player->redforce.player2.weapon.famas.pkills,
                       player->redforce.player2.weapon.famas.damdelt,
                       player->redforce.player2.weapon.famas.damrec,
                       player->redforce.player2.weapon.famas.dratio);

        weaponkillsort(player->redforce.player2.weapon.g3a3.rank,
                       player->redforce.player2.weapon.g3a3.name,
                       player->redforce.player2.weapon.g3a3.kills,
                       player->redforce.player2.weapon.g3a3.deaths,
                       player->redforce.player2.weapon.g3a3.sui,
                       player->redforce.player2.weapon.g3a3.kdp,
                       player->redforce.player2.weapon.g3a3.kdr,
                       player->redforce.player2.weapon.g3a3.pkills,
                       player->redforce.player2.weapon.g3a3.damdelt,
                       player->redforce.player2.weapon.g3a3.damrec,
                       player->redforce.player2.weapon.g3a3.dratio);

        weaponkillsort(player->redforce.player2.weapon.g36e.rank,
                       player->redforce.player2.weapon.g36e.name,
                       player->redforce.player2.weapon.g36e.kills,
                       player->redforce.player2.weapon.g36e.deaths,
                       player->redforce.player2.weapon.g36e.sui,
                       player->redforce.player2.weapon.g36e.kdp,
                       player->redforce.player2.weapon.g36e.kdr,
                       player->redforce.player2.weapon.g36e.pkills,
                       player->redforce.player2.weapon.g36e.damdelt,
                       player->redforce.player2.weapon.g36e.damrec,
                       player->redforce.player2.weapon.g36e.dratio);

        weaponkillsort(player->redforce.player2.weapon.m16.rank,
                       player->redforce.player2.weapon.m16.name,
                       player->redforce.player2.weapon.m16.kills,
                       player->redforce.player2.weapon.m16.deaths,
                       player->redforce.player2.weapon.m16.sui,
                       player->redforce.player2.weapon.m16.kdp,
                       player->redforce.player2.weapon.m16.kdr,
                       player->redforce.player2.weapon.m16.pkills,
                       player->redforce.player2.weapon.m16.damdelt,
                       player->redforce.player2.weapon.m16.damrec,
                       player->redforce.player2.weapon.m16.dratio);

        weaponkillsort(player->redforce.player2.weapon.m82.rank,
                       player->redforce.player2.weapon.m82.name,
                       player->redforce.player2.weapon.m82.kills,
                       player->redforce.player2.weapon.m82.deaths,
                       player->redforce.player2.weapon.m82.sui,
                       player->redforce.player2.weapon.m82.kdp,
                       player->redforce.player2.weapon.m82.kdr,
                       player->redforce.player2.weapon.m82.pkills,
                       player->redforce.player2.weapon.m82.damdelt,
                       player->redforce.player2.weapon.m82.damrec,
                       player->redforce.player2.weapon.m82.dratio);

        weaponkillsort(player->redforce.player2.weapon.m60.rank,
                       player->redforce.player2.weapon.m60.name,
                       player->redforce.player2.weapon.m60.kills,
                       player->redforce.player2.weapon.m60.deaths,
                       player->redforce.player2.weapon.m60.sui,
                       player->redforce.player2.weapon.m60.kdp,
                       player->redforce.player2.weapon.m60.kdr,
                       player->redforce.player2.weapon.m60.pkills,
                       player->redforce.player2.weapon.m60.damdelt,
                       player->redforce.player2.weapon.m60.damrec,
                       player->redforce.player2.weapon.m60.dratio);

        weaponkillsort(player->redforce.player2.weapon.m79.rank,
                       player->redforce.player2.weapon.m79.name,
                       player->redforce.player2.weapon.m79.kills,
                       player->redforce.player2.weapon.m79.deaths,
                       player->redforce.player2.weapon.m79.sui,
                       player->redforce.player2.weapon.m79.kdp,
                       player->redforce.player2.weapon.m79.kdr,
                       player->redforce.player2.weapon.m79.pkills,
                       player->redforce.player2.weapon.m79.damdelt,
                       player->redforce.player2.weapon.m79.damrec,
                       player->redforce.player2.weapon.m79.dratio);

        weaponkillsort(player->redforce.player2.weapon.claymore.rank,
                       player->redforce.player2.weapon.claymore.name,
                       player->redforce.player2.weapon.claymore.kills,
                       player->redforce.player2.weapon.claymore.deaths,
                       player->redforce.player2.weapon.claymore.sui,
                       player->redforce.player2.weapon.claymore.kdp,
                       player->redforce.player2.weapon.claymore.kdr,
                       player->redforce.player2.weapon.claymore.pkills,
                       player->redforce.player2.weapon.claymore.damdelt,
                       player->redforce.player2.weapon.claymore.damrec,
                       player->redforce.player2.weapon.claymore.dratio);

        weaponkillsort(player->redforce.player2.weapon.frag.rank,
                       player->redforce.player2.weapon.frag.name,
                       player->redforce.player2.weapon.frag.kills,
                       player->redforce.player2.weapon.frag.deaths,
                       player->redforce.player2.weapon.frag.sui,
                       player->redforce.player2.weapon.frag.kdp,
                       player->redforce.player2.weapon.frag.kdr,
                       player->redforce.player2.weapon.frag.pkills,
                       player->redforce.player2.weapon.frag.damdelt,
                       player->redforce.player2.weapon.frag.damrec,
                       player->redforce.player2.weapon.frag.dratio);

        weaponkillsort(player->redforce.player2.weapon.stg24.rank,
                       player->redforce.player2.weapon.stg24.name,
                       player->redforce.player2.weapon.stg24.kills,
                       player->redforce.player2.weapon.stg24.deaths,
                       player->redforce.player2.weapon.stg24.sui,
                       player->redforce.player2.weapon.stg24.kdp,
                       player->redforce.player2.weapon.stg24.kdr,
                       player->redforce.player2.weapon.stg24.pkills,
                       player->redforce.player2.weapon.stg24.damdelt,
                       player->redforce.player2.weapon.stg24.damrec,
                       player->redforce.player2.weapon.stg24.dratio);

        weaponkillsort(player->redforce.player2.weapon.m203.rank,
                       player->redforce.player2.weapon.m203.name,
                       player->redforce.player2.weapon.m203.kills,
                       player->redforce.player2.weapon.m203.deaths,
                       player->redforce.player2.weapon.m203.sui,
                       player->redforce.player2.weapon.m203.kdp,
                       player->redforce.player2.weapon.m203.kdr,
                       player->redforce.player2.weapon.m203.pkills,
                       player->redforce.player2.weapon.m203.damdelt,
                       player->redforce.player2.weapon.m203.damrec,
                       player->redforce.player2.weapon.m203.dratio);

        weaponkillsort(player->redforce.player2.weapon.uzi.rank,
                       player->redforce.player2.weapon.uzi.name,
                       player->redforce.player2.weapon.uzi.kills,
                       player->redforce.player2.weapon.uzi.deaths,
                       player->redforce.player2.weapon.uzi.sui,
                       player->redforce.player2.weapon.uzi.kdp,
                       player->redforce.player2.weapon.uzi.kdr,
                       player->redforce.player2.weapon.uzi.pkills,
                       player->redforce.player2.weapon.uzi.damdelt,
                       player->redforce.player2.weapon.uzi.damrec,
                       player->redforce.player2.weapon.uzi.dratio);

        weaponkillsort(player->redforce.player2.weapon.pkm.rank,
                       player->redforce.player2.weapon.pkm.name,
                       player->redforce.player2.weapon.pkm.kills,
                       player->redforce.player2.weapon.pkm.deaths,
                       player->redforce.player2.weapon.pkm.sui,
                       player->redforce.player2.weapon.pkm.kdp,
                       player->redforce.player2.weapon.pkm.kdr,
                       player->redforce.player2.weapon.pkm.pkills,
                       player->redforce.player2.weapon.pkm.damdelt,
                       player->redforce.player2.weapon.pkm.damrec,
                       player->redforce.player2.weapon.pkm.dratio);

        weaponkillsort(player->redforce.player2.weapon.ak74.rank,
                       player->redforce.player2.weapon.ak74.name,
                       player->redforce.player2.weapon.ak74.kills,
                       player->redforce.player2.weapon.ak74.deaths,
                       player->redforce.player2.weapon.ak74.sui,
                       player->redforce.player2.weapon.ak74.kdp,
                       player->redforce.player2.weapon.ak74.kdr,
                       player->redforce.player2.weapon.ak74.pkills,
                       player->redforce.player2.weapon.ak74.damdelt,
                       player->redforce.player2.weapon.ak74.damrec,
                       player->redforce.player2.weapon.ak74.dratio);

        weaponkillsort(player->redforce.player2.weapon.svd.rank,
                       player->redforce.player2.weapon.svd.name,
                       player->redforce.player2.weapon.svd.kills,
                       player->redforce.player2.weapon.svd.deaths,
                       player->redforce.player2.weapon.svd.sui,
                       player->redforce.player2.weapon.svd.kdp,
                       player->redforce.player2.weapon.svd.kdr,
                       player->redforce.player2.weapon.svd.pkills,
                       player->redforce.player2.weapon.svd.damdelt,
                       player->redforce.player2.weapon.svd.damrec,
                       player->redforce.player2.weapon.svd.dratio);

        weaponkillsort(player->redforce.player2.weapon.gp25.rank,
                       player->redforce.player2.weapon.gp25.name,
                       player->redforce.player2.weapon.gp25.kills,
                       player->redforce.player2.weapon.gp25.deaths,
                       player->redforce.player2.weapon.gp25.sui,
                       player->redforce.player2.weapon.gp25.kdp,
                       player->redforce.player2.weapon.gp25.kdr,
                       player->redforce.player2.weapon.gp25.pkills,
                       player->redforce.player2.weapon.gp25.damdelt,
                       player->redforce.player2.weapon.gp25.damrec,
                       player->redforce.player2.weapon.gp25.dratio);

        weaponkillsort(player->redforce.player2.weapon.ssg3000.rank,
                       player->redforce.player2.weapon.ssg3000.name,
                       player->redforce.player2.weapon.ssg3000.kills,
                       player->redforce.player2.weapon.ssg3000.deaths,
                       player->redforce.player2.weapon.ssg3000.sui,
                       player->redforce.player2.weapon.ssg3000.kdp,
                       player->redforce.player2.weapon.ssg3000.kdr,
                       player->redforce.player2.weapon.ssg3000.pkills,
                       player->redforce.player2.weapon.ssg3000.damdelt,
                       player->redforce.player2.weapon.ssg3000.damrec,
                       player->redforce.player2.weapon.ssg3000.dratio);

        weaponkillsort(player->redforce.player2.weapon.weapmortar.rank,
                       player->redforce.player2.weapon.weapmortar.name,
                       player->redforce.player2.weapon.weapmortar.kills,
                       player->redforce.player2.weapon.weapmortar.deaths,
                       player->redforce.player2.weapon.weapmortar.sui,
                       player->redforce.player2.weapon.weapmortar.kdp,
                       player->redforce.player2.weapon.weapmortar.kdr,
                       player->redforce.player2.weapon.weapmortar.pkills,
                       player->redforce.player2.weapon.weapmortar.damdelt,
                       player->redforce.player2.weapon.weapmortar.damrec,
                       player->redforce.player2.weapon.weapmortar.dratio);

        weaponkillsort(player->redforce.player2.weapon.spark_shower.rank,
                       player->redforce.player2.weapon.spark_shower.name,
                       player->redforce.player2.weapon.spark_shower.kills,
                       player->redforce.player2.weapon.spark_shower.deaths,
                       player->redforce.player2.weapon.spark_shower.sui,
                       player->redforce.player2.weapon.spark_shower.kdp,
                       player->redforce.player2.weapon.spark_shower.kdr,
                       player->redforce.player2.weapon.spark_shower.pkills,
                       player->redforce.player2.weapon.spark_shower.damdelt,
                       player->redforce.player2.weapon.spark_shower.damrec,
                       player->redforce.player2.weapon.spark_shower.dratio);

        weaponkillsort(player->redforce.player2.weapon.monster_mortar.rank,
                       player->redforce.player2.weapon.monster_mortar.name,
                       player->redforce.player2.weapon.monster_mortar.kills,
                       player->redforce.player2.weapon.monster_mortar.deaths,
                       player->redforce.player2.weapon.monster_mortar.sui,
                       player->redforce.player2.weapon.monster_mortar.kdp,
                       player->redforce.player2.weapon.monster_mortar.kdr,
                       player->redforce.player2.weapon.monster_mortar.pkills,
                       player->redforce.player2.weapon.monster_mortar.damdelt,
                       player->redforce.player2.weapon.monster_mortar.damrec,
                       player->redforce.player2.weapon.monster_mortar.dratio);

        weaponkillsort(player->redforce.player2.weapon.func_tank.rank,
                       player->redforce.player2.weapon.func_tank.name,
                       player->redforce.player2.weapon.func_tank.kills,
                       player->redforce.player2.weapon.func_tank.deaths,
                       player->redforce.player2.weapon.func_tank.sui,
                       player->redforce.player2.weapon.func_tank.kdp,
                       player->redforce.player2.weapon.func_tank.kdr,
                       player->redforce.player2.weapon.func_tank.pkills,
                       player->redforce.player2.weapon.func_tank.damdelt,
                       player->redforce.player2.weapon.func_tank.damrec,
                       player->redforce.player2.weapon.func_tank.dratio);

        weaponkillsort(player->redforce.player2.weapon.env_explosion.rank,
                       player->redforce.player2.weapon.env_explosion.name,
                       player->redforce.player2.weapon.env_explosion.kills,
                       player->redforce.player2.weapon.env_explosion.deaths,
                       player->redforce.player2.weapon.env_explosion.sui,
                       player->redforce.player2.weapon.env_explosion.kdp,
                       player->redforce.player2.weapon.env_explosion.kdr,
                       player->redforce.player2.weapon.env_explosion.pkills,
                       player->redforce.player2.weapon.env_explosion.damdelt,
                       player->redforce.player2.weapon.env_explosion.damrec,
                       player->redforce.player2.weapon.env_explosion.dratio);

        weaponkillsort(player->redforce.player2.weapon.concussion.rank,
                       player->redforce.player2.weapon.concussion.name,
                       player->redforce.player2.weapon.concussion.kills,
                       player->redforce.player2.weapon.concussion.deaths,
                       player->redforce.player2.weapon.concussion.sui,
                       player->redforce.player2.weapon.concussion.kdp,
                       player->redforce.player2.weapon.concussion.kdr,
                       player->redforce.player2.weapon.concussion.pkills,
                       player->redforce.player2.weapon.concussion.damdelt,
                       player->redforce.player2.weapon.concussion.damrec,
                       player->redforce.player2.weapon.concussion.dratio);

        weaponkillsort(player->redforce.player2.weapon.ammobox.rank,
                       player->redforce.player2.weapon.ammobox.name,
                       player->redforce.player2.weapon.ammobox.kills,
                       player->redforce.player2.weapon.ammobox.deaths,
                       player->redforce.player2.weapon.ammobox.sui,
                       player->redforce.player2.weapon.ammobox.kdp,
                       player->redforce.player2.weapon.ammobox.kdr,
                       player->redforce.player2.weapon.ammobox.pkills,
                       player->redforce.player2.weapon.ammobox.damdelt,
                       player->redforce.player2.weapon.ammobox.damrec,
                       player->redforce.player2.weapon.ammobox.dratio);
    return;
}

/*--------------------------------------------------------------------------------*/
// Copys from Link List to Weapon.dat
void writeweapondc() {

    struct ListItem15 *wp;

    int tidx  = 0;// Temp Index - Counter
    for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
        writew(&wp->weapon,tidx);
        ++tidx;
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Adds All Weapons to Link List for Stat Calculations
void setupweapondc() {

    WEAPONREC weapon;

    int tidx  = 0;
    int total = 0;
    total = countweapons();

    // This Loops Filles up the Link List with all Weapons
    while (tidx != total) {
        readw(&weapon,tidx);           // Loads Weapon form Dat for Weapon Name
        weapondatacont(&weapon);       // Add Weapons To Container
        ++tidx;
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Gets Players from Map.dats and Loads them into Memory for Fast Statistics Calcs
void getplayerlist() {

    MAPNAMEREC map;
    PLAYERREC  player;

    strcpy(CURRMAP,MAPNAME);

    int mapidx = 0;
    int totalmaps = countmaps();

    double p1 = 0,  // Top Percentage Bar
           p2 = 0;  // Left Percentage Bar

    while(readm(&map,mapidx)) {
        clearallleft();
        strcpy(MAPNAME,map.name);
        p1 = compwkillpercent1(mapidx,totalmaps);
        percenttop(p1);

        char text1[40];
        sprintf(text1,"Scan: %s ", MAPNAME);
        drawleft(text1,3,0);

        int Total = countpidx();
        int idx = 0;

        while(readp(&player,idx)) {
            p2 = compwkillpercent1(idx,Total);
            percentleft(p2);
            playerdatacontainer(&player);
            idx++;
        }

        calcPlayerStats();
        // Current Process Completed
        percentleft(100);

        char text3[40];
        sprintf(text3,"Completed OK! ");
        drawleft2(text3,9,0);
        ++mapidx;
        clearplayercontainer();  // Clears Link List

        #ifdef _WIN32
        Sleep(1000);
        #else
        system("sleep 1s");
        #endif
    }
    percenttop(100);
    strcpy(MAPNAME,CURRMAP);
    return;
}

/*--------------------------------------------------------------------------------*/
// Gets Players from Map.dats and Loads them into Memory for Fast Statistics Calcs
void getplayerlist2() {

    MAPNAMEREC map;
    PLAYERREC  player;

    strcpy(CURRMAP,MAPNAME);

    int mapidx = 0;
    int totalmaps = countmaps();

    double p1 = 0,  // Top Percentage Bar
           p2 = 0;  // Right PErcentage Bar

    struct ListItem14 *pl;

    while(readm(&map,mapidx)) {
        strcpy(MAPNAME,map.name);
        clearallright();
        p1 = compwkillpercent1(mapidx,totalmaps);
        percenttop(p1);

        char text1[40];
        sprintf(text1,"Scan: %s ", MAPNAME);
        drawright(text1,3,0);

        int Total = countpidx();
        int idx = 0;

        while(readp(&player,idx)) {
            p2 = compwkillpercent1(idx,Total);
            percentright(p2);
            playerdatacontainer(&player);
            idx++;
        }

        // Do Testing if player name is in list, Update it with New Data
        for ( pl = MyList14 ; pl != 0 ; pl = pl->next ) {
            // Kick off Copy Function Here
            newmapdata(pl->player.playername);
            addplayermapstats(&pl->player);
        }
        calcPlayerStats();  // Calculate Statistics
        percentright(100);

        char text3[40];
        sprintf(text3,"Completed OK! ");
        drawright2(text3,9,0);

        ++mapidx;
        clearplayercontainer();  // Clears Link List

        #ifdef _WIN32
        Sleep(1000);
        #else
        system("sleep 1s");
        #endif
    }
    percenttop(100);
    strcpy(MAPNAME,CURRMAP); // Reset Original Map Settings
    return;
}


/*--------------------------------------------------------------------------------*/
// Gets Player from Playerrank.dat and Setups Link List
void getplayerlist3() {

    PLAYERREC2  player;

    struct ListItem12 *pl;

    for ( pl = MyList12 ; pl != 0 ; pl = pl->next ) { rankkillsort2(&pl->player); }
    clearplayerrank();
    calcRankPlayerStats();  // Creates PlayerRank.dat
    clearprank2();          //clear List 18
    return;
}

/*--------------------------------------------------------------------------------*/
// Gets Player from Playerrank.dat and Setups Link List
void getweaponlist3() {

    WEAPONREC weapon;

    struct ListItem15 *wp;

    int Total = countweapons();
    int idx = 0;

    double p1 = 0,  // Top Percentage Bar
           p2 = 0;  // Right PErcentage Bar

    while(readw(&weapon,idx)) {
        weaponkillsortcont(&weapon);
        idx++;
    }

    int rank = 0;
    // Do Testing if player name is in list, Update it with New Data
    for ( wp = MyList15 ; wp != 0 ; wp = wp->next ) {
        // Kick off Copy Function Here
        clearallright();
        p1 = compwkillpercent1(rank,Total);
        percenttop(p1);

        char text1[40] = "Create Weapon Ranks!";
        drawright(text1,3,0);
          ++rank;
        wp->weapon.rank = rank;
        writew(&wp->weapon,rank-1);
        percentright(100);
        char text3[40];
        sprintf(text3,"Completed OK! ");
        drawright2(text3,9,0);
    }
    percenttop(100);
    clearweaponcont();
    return;
}

/*--------------------------------------------------------------------------------*/
// This Function will setups Player Statistics Calculations
void dostatcacl() {

     // Sets up and Creates Playerrank.dat
    createweapons();   // Creats Weapons.dat
    setupweapondc();   // Setup Weapons.dat

    clearall();        // Clear ALL GUI for Fresh Start
    char title[100] = "Calculating Player Statistics Per Map . . .";
    drawtop(title,11,0,18);
    getplayerlist();   // Sets up Player Rankings and Creates Playerrank.dat
    writeweapondc();   // Writes Overall Weapon Stats to Weapon.dat
    clearweaponcont(); // After Stat Calculations Clear #15 From Memory

    percenttop(100);

    #ifdef _WIN32
    Sleep(1000);
    #else
    system("sleep 1s");
    #endif

    clearall();
    char title2[100] = "Calculating Overall Player Statistics . . .";
    drawtop(title2,11,0,18);
    getplayerlist2();  // Setup up for Adding Red / Blue Statistics Togeter for Player Totals
    prankdataexists(); // Create Rank.dat for Holding Indivdual Player Totals

     percenttop(100);

    #ifdef _WIN32
    Sleep(1000);
    #else
    system("sleep 1s");
    #endif

    clearall();
    char title3[100] = "Calculating Rankings for Overall Players . . .";
    drawtop(title3,11,0,17);
     getplayerlist3(); // Setup up for Adding Red / Blue Statistics Togeter for Player Totals

    percenttop(100);

    #ifdef _WIN32
    Sleep(1000);
    #else
    system("sleep 1s");
    #endif

     clearall();
     char title4[100] = "Calculating Rankings for Overall Weapons . . .";
     drawtop(title4,11,0,17);
     wdataexists();
    getweaponlist3(); // Create Weapon.dat for Holding Weapon Rankings

    percenttop(100);

    #ifdef _WIN32
    Sleep(1000);
    #else
    system("sleep 1s");
    #endif
    return;
}


#endif
