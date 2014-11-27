#ifndef __HTML2_CPP    /*  An extra safeguard to prevent this header from  */
#define __HTML2_CPP    /*  being included twice in the same source file    */

// This file Processes Indivual Weapon Statistics HTML Files & Weapons Ranking

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN_AND_MEAN
#include <windows.h>
#include "wincon.h"
#endif

#include "structs.h"              // Player / Weapon / Linklist Structures
#include "LogFunc.h"
#include "PlayerFunc.h"           // Displaying Link list with Players
#include "WeaponFunc.h"
#include "FA26.h"
#include "Html2.h"


using namespace std;              // Standard C++ Namespace

/*--------------------------------------------------------------------------------*/
// GLOBALS - Link List's
/*--------------------------------------------------------------------------------*/


struct ListItem3  *MYLIST3  = 0 ; // PlayerStats Write Out
struct ListItem4  *MYLIST4  = 0 ; // Weapon Rankings

struct ListItem5  *MYLIST5  = 0 ; // WeaponTOP.html    & WeaponRankTop.html
struct ListItem6  *MYLIST6  = 0 ; // WeaponROW-1.HTML  & WeaponRankRow-1.html
struct ListItem7  *MYLIST7  = 0 ; // WeaponROW-2.HTML  & WeaponRankRow-2.html

struct ListItem8  *MYLIST8  = 0 ; // WeaponPTOP.HTML
struct ListItem9  *MYLIST9  = 0 ; // WeaponPROW-1.HTML
struct ListItem10 *MYLIST10 = 0 ; // WeaponPROW-2.HTML
struct ListItem11 *MYLIST11 = 0 ; // Sort Players For Top Kills By "This" Weapon
struct ListItem12 *MYLIST12 = 0 ; // Add All Player Data into Link List For Faster HTML Creation
struct ListItem15 *MYLIST15 = 0 ; // Add All Weapon Data into Link List For Faster HTML Creation

/*--------------------------------------------------------------------------------*/
// LINK LISTS Data Sorting Functions
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearweaponcontainer(void) {

    struct ListItem15 *p,*next;
    if ( MYLIST15 == 0) return;

    for(p = MYLIST15 ; p !=0 ; p = next ) {
        next = p->next;
        delete (p);
    }
    MYLIST15 = 0;
}


/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearplayercont(void) {

    struct ListItem15 *p,*next;
    if ( MYLIST15 == 0) return;

    for(p = MYLIST15 ; p !=0 ; p = next ) {
    next = p->next;
        delete (p);
    }
    MYLIST15 = 0;
}

/*--------------------------------------------------------------------------------*/
// This Function Holds All Weapon Data While Creating HTML Files
void weapondatacontainer(WEAPONREC * weapon) {

    struct ListItem15 *last;
    string data;

    ListItem15 *item = new ListItem15;
    if( !item )
    {
        cout << "Malloc Failed for holding Player Data\n";
        cout << "You do not have enough memory for this program!\n";
        exit(1);
    }

    item->weapon = (*weapon);
    item->next = 0;

    if ( MYLIST15 == 0 ) {
        MYLIST15 = item;
        return;
    }

    for( last = MYLIST15 ; last->next != 0 ; last = last->next );
    last->next = item;
    return;
}


/*--------------------------------------------------------------------------------*/
// This Function Holds All Player Data While Creating HTML Files
void playerdatacont(PLAYERREC2 * player) {

    struct ListItem12 *last;
    string data;

    ListItem12 *item = new ListItem12;
    if( !item )
    {
        cout << "Malloc Failed for holding Player Data\n";
        cout << "You do not have enough memory for this program!\n";
        exit(1);
    }

    item->player = (*player);
    item->next = 0;

    if ( MYLIST12 == 0 ) {
        MYLIST12 = item;
        return;
    }

    for( last = MYLIST12 ; last->next != 0 ; last = last->next );
    last->next = item;
    return;
}


/*--------------------------------------------------------------------------------*/
// Link List Sorting Weapons By Kills, and Assigns Ranks
void wkillsort(int rank,         // Weapon Rank
               char * name,      // Weapon Name
               long   kills,     // Weapon Kills
               long   damdelt) { // Damage Caused with this weapon

    struct ListItem4 *Item, *next;
    Item = (struct ListItem4 *) malloc(sizeof(struct ListItem4));
    if ( Item==0 ) {
        printf ("Malloc Failed \n");
        return;
    }

    // Store Weapon Information into List
    Item->rank = rank;
    strcpy(Item->name,name);
    Item->kills = kills;
    Item->damdelt = damdelt;
    Item->next = 0;

    if ( MYLIST4 == 0 ) {
        MYLIST4 = Item;
        return;
    }

    // This is where Sorting takes place!
    // Check if the new item comes before the first item in old list
    if((kills - MYLIST4->kills) > 0 ) {
        Item->next = MYLIST4;
        MYLIST4 = Item;
        return;
    }

    // Check to see if an item is inserted before the next item
    for ( next = MYLIST4 ; next->next != 0 ; next = next->next ) {
        if ((kills - next->next->kills) > 0 ) {
            // Insert Item before the next Item.
            Item->next = next->next;
            next->next = Item ;
            return;
        }
    }
    next->next = Item;
    return;
}

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearwkillsort(void) {

    struct ListItem4 *p,*next;
    if ( MYLIST4 == 0) return;

    for(p = MYLIST4 ; p !=0 ; p = next ) {
        next = p->next;
        free ( p );
    }
    MYLIST4 = 0;
}

/*--------------------------------------------------------------------------------*/
// Runs Though Weapon.dat and Sorts Ky Kills Into Link List, Then Sets Rank
void calcwrank() {

    WEAPONREC weapon;
    int idx = 0;
    int total = countweapons();

    // Linklist and Sort Weapons by Kills
    while (idx != total) {
        readw(&weapon,idx);          // Loads Weapon form Dat for Weapon Name
        // Add Weapons to Linklist and Sort Weapons for Each Player by Kills
        wkillsort(weapon.rank,       // Weapon Rank
                  weapon.name,       // Weapon Name
                  weapon.kills,      // Weapon Kills
                  weapon.damdelt);   // Damage caused with this weapon
        ++idx;
    }

    // Runs though Link List and Sets RANK for Each Weapon
    // And Resets Weapon.dat With Order of Sorted Link List
    struct ListItem4 *p;
    int rank = 0;
    int tidx = 0;
    for ( p = MYLIST4 ; p != 0 ; p = p->next ) {
        readw(&weapon,tidx);
        p->rank = ++rank;
        weapon.rank = p->rank;
        strcpy(weapon.name, p->name);
        weapon.kills = p->kills;
        weapon.damdelt = p->damdelt;
        writew(&weapon,tidx);
        ++tidx;
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Take Current Player and Weapon INformation, Puts into Link List and Ranks Ky Kills
void wprank1(int    rank,     // Players Rank
             char * name,     // Players Name
             long   kills,
             long   damdelt) {

    // Make Sure Players With 0 Kills don't get added to link list
    if(kills == 0) return;

    struct ListItem11 *Item, *next;
    Item = (struct ListItem11 *) malloc(sizeof(struct ListItem11));
    if ( Item==0 ) {
        printf ("Malloc Failed \n");
        return;
    }

    // Store Weapon Information into List
    Item->rank = rank;
    strcpy(Item->name,name);
    Item->kills = kills;
    Item->damdelt = damdelt;
    Item->next = 0;

    if ( MYLIST11 == 0 ) {
        MYLIST11 = Item;
        return;
    }

    // This is where Sorting takes place!
    // Check if the new item comes before the first item in old list
    if((kills - MYLIST11->kills) > 0 ) {
        Item->next = MYLIST11;
        MYLIST11 = Item;
        return;
    }

    // Check to see if an item is inserted before the next item
    for ( next = MYLIST11 ; next->next != 0 ; next = next->next ) {
        if ((kills - next->next->kills) > 0 ) {
            // Insert Item before the next Item.
            Item->next = next->next;
            next->next = Item ;
            return;
        }
    }
    // There are no more Items ! Add to end
    next->next = Item;
    return;
}

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearwprank1() {

    struct ListItem11 *p,*next;
    if ( MYLIST11 == 0) {
        return;
    }

    for(p = MYLIST11 ; p !=0 ; p = next ) {
        next = p->next;
        free ( p );
    }
    MYLIST11 = 0;
}

/*--------------------------------------------------------------------------------*/
// Calculates Top Players Per Each Weapon - Send Players to LL to be Sorted by Kills
void topweaponplayers(PLAYERREC2 * player,  // Handle to Player
                       char      * name) {  // Weapon Name

    // Test If Name is Already in List, if it is.. Skip it...
    struct ListItem11 *p11; // TOP PLAYERS FOR THIS WEAPON

    // Do Testing if player name is not in list, Update it with New Data
    for ( p11 = MYLIST11 ; p11 != 0 ; p11 = p11->next ) {
        if (strcmp(p11->name, player->name) == 0) return;
    }


    if (strcmp(name,player->weapon.knife.name) == 0) {
        wprank1(player->rank,                     // Player Rank
                player->name,                     // Player Name
                player->weapon.knife.kills,       // Weapon Kills
                player->weapon.knife.damdelt);    // Weapon Damage
        return;
    }
    else if (strcmp(name,player->weapon.coltgov.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.coltgov.kills,
                player->weapon.coltgov.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.ber92f.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.ber92f.kills,
                player->weapon.ber92f.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.ber93r.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.ber93r.kills,
                player->weapon.ber93r.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.anaconda.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.anaconda.kills,
                player->weapon.anaconda.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.desert.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.desert.kills,
                player->weapon.desert.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.benelli.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.benelli.kills,
                player->weapon.benelli.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.saiga.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.saiga.kills,
                player->weapon.saiga.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.mp5a5.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.mp5a5.kills,
                player->weapon.mp5a5.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.sterling.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.sterling.kills,
                player->weapon.sterling.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.bizon.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.bizon.kills,
                player->weapon.bizon.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.ak47.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.ak47.kills,
                player->weapon.ak47.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.famas.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.famas.kills,
                player->weapon.famas.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.g3a3.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.g3a3.kills,
                player->weapon.g3a3.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.g36e.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.g36e.kills,
                player->weapon.g36e.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.m16.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.m16.kills,
                player->weapon.m16.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.m82.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.m82.kills,
                player->weapon.m82.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.m60.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.m60.kills,
                player->weapon.m60.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.m79.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.m79.kills,
                player->weapon.m79.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.claymore.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.claymore.kills,
                player->weapon.claymore.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.frag.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.frag.kills,
                player->weapon.frag.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.stg24.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.stg24.kills,
                player->weapon.stg24.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.m203.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.m203.kills,
                player->weapon.m203.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.uzi.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.uzi.kills,
                player->weapon.uzi.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.pkm.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.pkm.kills,
                player->weapon.pkm.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.ak74.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.ak74.kills,
                player->weapon.ak74.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.svd.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.svd.kills,
                player->weapon.svd.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.gp25.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.gp25.kills,
                player->weapon.gp25.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.ssg3000.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.ssg3000.kills,
                player->weapon.ssg3000.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.weapmortar.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.weapmortar.kills,
                player->weapon.weapmortar.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.spark_shower.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.spark_shower.kills,
                player->weapon.spark_shower.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.monster_mortar.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.monster_mortar.kills,
                player->weapon.monster_mortar.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.func_tank.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.func_tank.kills,
                player->weapon.func_tank.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.env_explosion.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.env_explosion.kills,
                player->weapon.env_explosion.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.concussion.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.concussion.kills,
                player->weapon.concussion.damdelt);
        return;
    }
    else if (strcmp(name,player->weapon.ammobox.name) == 0) {
        wprank1(player->rank,
                player->name,
                player->weapon.ammobox.kills,
                player->weapon.ammobox.damdelt);
        return;
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Calculates Top Players Per Each Weapon - Send Players to LL to be Sorted by Kills
/*void topweaponplayers(PLAYERREC2 * player,  // Handle to Player
                       char      * name)    // Weapon Name
{
        // Test If Name is Already in List, if it is.. Skip it...
        struct ListItem11 *p11; // TOP PLAYERS FOR THIS WEAPON

        // Do Testing if player name is not in list, Update it with New Data
        for ( p11 = MYLIST11 ; p11 != 0 ; p11 = p11->next ) {
                if (strcmp(p11->name, player->playername) == 0) {
                return;
                }
        }

    if (TEAM == false) {

        if (strcmp(name,player->redforce.player2.weapon.knife.name) == 0) {
                wprank1(player->rank,                     // Player Rank
                        player->playername,                     // Player Name
                        player->redforce.player2.weapon.knife.kills,
                        player->redforce.player2.weapon.knife.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.coltgov.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.coltgov.kills,
                        player->redforce.player2.weapon.coltgov.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.ber92f.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.ber92f.kills,
                        player->redforce.player2.weapon.ber92f.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.ber93r.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.ber93r.kills,
                        player->redforce.player2.weapon.ber93r.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.anaconda.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.anaconda.kills,
                        player->redforce.player2.weapon.anaconda.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.desert.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.desert.kills,
                        player->redforce.player2.weapon.desert.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.benelli.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.benelli.kills,
                        player->redforce.player2.weapon.benelli.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.saiga.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.saiga.kills,
                        player->redforce.player2.weapon.saiga.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.mp5a5.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.mp5a5.kills,
                        player->redforce.player2.weapon.mp5a5.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.sterling.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.sterling.kills,
                        player->redforce.player2.weapon.sterling.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.bizon.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.bizon.kills,
                        player->redforce.player2.weapon.bizon.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.ak47.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.ak47.kills,
                        player->redforce.player2.weapon.ak47.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.famas.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.famas.kills,
                        player->redforce.player2.weapon.famas.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.g3a3.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.g3a3.kills,
                        player->redforce.player2.weapon.g3a3.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.g36e.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.g36e.kills,
                        player->redforce.player2.weapon.g36e.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.m16.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.m16.kills,
                        player->redforce.player2.weapon.m16.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.m82.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.m82.kills,
                        player->redforce.player2.weapon.m82.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.m60.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.m60.kills,
                        player->redforce.player2.weapon.m60.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.m79.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.m79.kills,
                        player->redforce.player2.weapon.m79.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.claymore.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.claymore.kills,
                        player->redforce.player2.weapon.claymore.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.frag.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.frag.kills,
                        player->redforce.player2.weapon.frag.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.stg24.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.stg24.kills,
                        player->redforce.player2.weapon.stg24.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.m203.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.m203.kills,
                        player->redforce.player2.weapon.m203.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.uzi.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.uzi.kills,
                        player->redforce.player2.weapon.uzi.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.pkm.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.pkm.kills,
                        player->redforce.player2.weapon.pkm.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.ak74.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.ak74.kills,
                        player->redforce.player2.weapon.ak74.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.svd.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.svd.kills,
                        player->redforce.player2.weapon.svd.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.gp25.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.gp25.kills,
                        player->redforce.player2.weapon.gp25.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.ssg3000.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.ssg3000.kills,
                        player->redforce.player2.weapon.ssg3000.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.weapmortar.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.weapmortar.kills,
                        player->redforce.player2.weapon.weapmortar.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.spark_shower.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.spark_shower.kills,
                        player->redforce.player2.weapon.spark_shower.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.monster_mortar.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.monster_mortar.kills,
                        player->redforce.player2.weapon.monster_mortar.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.func_tank.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.func_tank.kills,
                        player->redforce.player2.weapon.func_tank.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.env_explosion.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.env_explosion.kills,
                        player->redforce.player2.weapon.env_explosion.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.concussion.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.concussion.kills,
                        player->redforce.player2.weapon.concussion.damdelt);
                        return;
        }
        else if (strcmp(name,player->redforce.player2.weapon.ammobox.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->redforce.player2.weapon.ammobox.kills,
                        player->redforce.player2.weapon.ammobox.damdelt);
                        return;
        }

    }
    else {


    if (strcmp(name,player->blueforce.player2.weapon.knife.name) == 0) {
                wprank1(player->rank,                     // Player Rank
                        player->playername,                     // Player Name
                        player->blueforce.player2.weapon.knife.kills,
                        player->blueforce.player2.weapon.knife.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.coltgov.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.coltgov.kills,
                        player->blueforce.player2.weapon.coltgov.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.ber92f.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.ber92f.kills,
                        player->blueforce.player2.weapon.ber92f.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.ber93r.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.ber93r.kills,
                        player->blueforce.player2.weapon.ber93r.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.anaconda.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.anaconda.kills,
                        player->blueforce.player2.weapon.anaconda.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.desert.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.desert.kills,
                        player->blueforce.player2.weapon.desert.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.benelli.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.benelli.kills,
                        player->blueforce.player2.weapon.benelli.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.saiga.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.saiga.kills,
                        player->blueforce.player2.weapon.saiga.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.mp5a5.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.mp5a5.kills,
                        player->blueforce.player2.weapon.mp5a5.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.sterling.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.sterling.kills,
                        player->blueforce.player2.weapon.sterling.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.bizon.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.bizon.kills,
                        player->blueforce.player2.weapon.bizon.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.ak47.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.ak47.kills,
                        player->blueforce.player2.weapon.ak47.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.famas.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.famas.kills,
                        player->blueforce.player2.weapon.famas.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.g3a3.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.g3a3.kills,
                        player->blueforce.player2.weapon.g3a3.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.g36e.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.g36e.kills,
                        player->blueforce.player2.weapon.g36e.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.m16.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.m16.kills,
                        player->blueforce.player2.weapon.m16.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.m82.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.m82.kills,
                        player->blueforce.player2.weapon.m82.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.m60.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.m60.kills,
                        player->blueforce.player2.weapon.m60.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.m79.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.m79.kills,
                        player->blueforce.player2.weapon.m79.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.claymore.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.claymore.kills,
                        player->blueforce.player2.weapon.claymore.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.frag.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.frag.kills,
                        player->blueforce.player2.weapon.frag.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.stg24.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.stg24.kills,
                        player->blueforce.player2.weapon.stg24.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.m203.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.m203.kills,
                        player->blueforce.player2.weapon.m203.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.uzi.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.uzi.kills,
                        player->blueforce.player2.weapon.uzi.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.pkm.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.pkm.kills,
                        player->blueforce.player2.weapon.pkm.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.ak74.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.ak74.kills,
                        player->blueforce.player2.weapon.ak74.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.svd.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.svd.kills,
                        player->blueforce.player2.weapon.svd.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.gp25.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.gp25.kills,
                        player->blueforce.player2.weapon.gp25.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.ssg3000.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.ssg3000.kills,
                        player->blueforce.player2.weapon.ssg3000.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.weapmortar.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.weapmortar.kills,
                        player->blueforce.player2.weapon.weapmortar.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.spark_shower.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.spark_shower.kills,
                        player->blueforce.player2.weapon.spark_shower.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.monster_mortar.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.monster_mortar.kills,
                        player->blueforce.player2.weapon.monster_mortar.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.func_tank.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.func_tank.kills,
                        player->blueforce.player2.weapon.func_tank.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.env_explosion.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.env_explosion.kills,
                        player->blueforce.player2.weapon.env_explosion.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.concussion.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.concussion.kills,
                        player->blueforce.player2.weapon.concussion.damdelt);
                        return;
        }
        else if (strcmp(name,player->blueforce.player2.weapon.ammobox.name) == 0) {
                wprank1(player->rank,
                        player->playername,
                        player->blueforce.player2.weapon.ammobox.kills,
                        player->blueforce.player2.weapon.ammobox.damdelt);
                        return;
        }
    } // End of Else


        return;
}
/*


/*--------------------------------------------------------------------------------*/
// PARSE HTML FILE TEMPLATES AND OUTPUT STATISTICS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void RemoveWeaponHTML(void) {

        struct ListItem5 *p5,*next5;       // List 5
        struct ListItem6 *p6,*next6;       // List 6
        struct ListItem7 *p7,*next7;       // List 7

        struct ListItem8 *p8,*next8;       // List 8
        struct ListItem9 *p9,*next9;       // List 9
        struct ListItem10 *p10,*next10;    // List 10

        // Clear List 5
        if ( MYLIST5 != 0) {
            for(p5 = MYLIST5 ; p5 !=0 ; p5 = next5 ) {
                next5 = p5->next;
                free ( p5 );
            }
            MYLIST5 = 0;
        }
        if ( MYLIST6 != 0) {
            for(p6 = MYLIST6 ; p6 !=0 ; p6 = next6 ) {
                next6 = p6->next;
                free ( p6 );
            }
            MYLIST6 = 0;
        }

        // Clear List 7
        if ( MYLIST7 != 0) {
            for(p7 = MYLIST7 ; p7 !=0 ; p7 = next7 ) {
                next7 = p7->next;
                free ( p7 );
            }
            MYLIST7 = 0;
        }
        if ( MYLIST8 != 0) {
            for(p8 = MYLIST8 ; p8 !=0 ; p8 = next8 ) {
                next8 = p8->next;
                free ( p8 );
            }
            MYLIST8 = 0;
        }
        if ( MYLIST9 != 0) {
            for(p9 = MYLIST9 ; p9 !=0 ; p9 = next9 ) {
                next9 = p9->next;
                free ( p9 );
            }
            MYLIST9 = 0;
        }
        if ( MYLIST10 != 0) {
            for(p10 = MYLIST10 ; p10 !=0 ; p10 = next10 ) {
                next10 = p10->next;
                free ( p10 );
            }
            MYLIST10 = 0;
        }
        return;
}


/*--------------------------------------------------------------------------------*/
// Write out the HTML FILE from Link List
void writeHTMLweapon(char* tweapon) {

    char temp[355];
    sprintf(temp, "%s%s.html", HTMLPATH,tweapon);
    string name = (temp);

    struct ListItem3 *p;

    ofstream outStream2;
    outStream2.open( name.c_str(), ofstream::out | ofstream::trunc );
    if (!outStream2.is_open()) {
        cout << "\n\nError creating Weapon.html for Writing " << name <<endl;
        clearHTMLweapon();
        return;
    }

    for ( p= MYLIST3 ; p != 0 ; p = p->next ) {
        outStream2 << p->html << endl;
    }

    outStream2.close(); // Closes the file before exiting
    clearHTMLweapon();  // Clears Link List from Memory
    return;
}

/*--------------------------------------------------------------------------------*/
// Write out the HTML FILE from Link List
void writeHTMLweaponrank() {

    string name = HTMLPATH;
    name += "weapon.html";

    struct ListItem3 *p;

    ofstream outStream2;
    outStream2.open( name.c_str(), ofstream::out | ofstream::trunc );
    if (!outStream2.is_open()) {
        cout << "\n\nError creating Weapon.html for Writing " << name <<endl;
        clearHTMLweapon();
        return;
    }

    for ( p = MYLIST3 ; p != 0 ; p = p->next ) { outStream2 << p->html << endl; }

    outStream2.close(); // Closes the file before exiting
    clearHTMLweapon();  // Clears Link List from Memory
    return;
}


/*--------------------------------------------------------------------------------*/
// Reads Link List Then Writes Out HTML Files for Players Stats
void buildHTMLweapon(string html) {

    string temp = html;

    struct ListItem3 *item,*last;
    item = (struct ListItem3 *) malloc(sizeof(struct ListItem3));
    if ( item==0 ) {
        printf ("Malloc Failed Link List 3 PlayerName.html \n");
        return;
    }

    strcpy(item->html,temp.c_str());
    item->next = 0;

    if ( MYLIST3 == 0 ) {
        MYLIST3 = item;
        return;
    }

    for( last = MYLIST3 ; last->next != 0 ; last = last->next );
    last->next = item;
}

/*--------------------------------------------------------------------------------*/
// Processes HTML for Write out to the Link List - Indivdual Weapon.html
void checkHTMLWeapon(string htmlline, char *tweapon) {

    struct ListItem15 *wp;

    // Do Testing if player name is in list, Update it with New Data
    for ( wp = MYLIST15 ; wp != 0 ; wp = wp->next ) {
        if (strcmp(wp->weapon.name, tweapon) == 0) {

            string temp = htmlline;
            string temp2;
            int id1 = -1; // String Index

            id1 = temp.find('$', 0);
            if (id1 == -1) {
                buildHTMLweapon(temp);
                return;
            }
            // Here Stars Parsing of Every Variable in the WeaponTOP & ROW1 & ROW 2.HTML And Templates..
            while (id1 != string::npos) {
                id1 = temp.find("timedate", 0);
                if (id1 != -1) {
                    char DateTime[100];
                    sprintf(DateTime,"%s %s",szDateFormat,szTimeFormat);
                    temp.replace(id1-1,9,DateTime);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("server.ip", 0);
                if (id1 != -1) {
                    char ServerIP[20];
                    sprintf(ServerIP,"%s",SERVERIP);
                    temp.replace(id1-1,10,ServerIP);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("webpage", 0);
                if (id1 != -1) {
                    char Webpage[255];
                    sprintf(Webpage,"%s",WEBPAGE);
                    temp.replace(id1-1,8,Webpage);
                    id1 = temp.find("server.name", 0);
                    if (id1 != -1) {
                        char ServerName[100];
                        sprintf(ServerName,"%s",SERVERNAME);
                        temp.replace(id1-1,12,ServerName);
                        buildHTMLweapon(temp);
                        return;
                    }
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("server.name", 0);
                if (id1 != -1) {
                    char ServerName[100];
                    sprintf(ServerName,"%s",SERVERNAME);
                    temp.replace(id1-1,12,ServerName);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("admin.email", 0);
                if (id1 != -1) {
                    char AdminEmail[100];
                    sprintf(AdminEmail,"%s",ADMINEMAIL);
                    temp.replace(id1-1,12,AdminEmail);
                    id1 = temp.find("admin.name", 0);
                    if (id1 != -1) {
                        char AdminName[100];
                        sprintf(AdminName,"%s",ADMINNAME);
                        temp.replace(id1-1,11,AdminName);
                        buildHTMLweapon(temp);
                        return;
                    }
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("admin.name", 0);
                if (id1 != -1) {
                    char AdminName[100];
                    sprintf(AdminName,"%s",ADMINNAME);
                    temp.replace(id1-1,11,AdminName);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("weapon.rank", 0);
                if (id1 != -1) {
                    char idx[10];
                    int rank = wp->weapon.rank ;
                    sprintf(idx, "%d", rank);
                    temp.replace(id1-1,12,idx);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("weapon.name", 0);
                if (id1 != -1) {
                    temp.replace(id1-1,12,wp->weapon.name);
                    id1 = temp.find("weapon.kills", 0);
                    if (id1 != -1) {
                        char pk[10];
                        long number = wp->weapon.kills;
                        sprintf(pk, "%d", number);
                        temp.replace(id1-1,13,pk);
                        buildHTMLweapon(temp);
                        return;
                    }
                    id1 = temp.find("weapon.name", 0);
                    if (id1 != -1) temp.replace(id1-1,12,wp->weapon.name);
                    id1 = temp.find("weapon.name", 0);
                    if (id1 != -1) temp.replace(id1-1,12,wp->weapon.name);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("weapon.kills", 0);
                if (id1 != -1) {
                    char pk[10];
                    long number = wp->weapon.kills;
                    sprintf(pk, "%d", number);
                    temp.replace(id1-1,13,pk);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("weapon.damdelt", 0);
                if (id1 != -1) {
                    char pk[10];
                    long number = wp->weapon.damdelt;
                    sprintf(pk, "%d", number);
                    temp.replace(id1-1,15,pk);
                    buildHTMLweapon(temp);
                    return;
                }
                buildHTMLweapon(temp);
                return;
            }  //END of While
        }  //END OF WP IF
    }  //END OF WP FOR
    return;
}

/*--------------------------------------------------------------------------------*/
// Processes HTML for Write out to the Link List - Top Players
void checkHTMLWeaponp(string htmlline,  // HTML String to Parse
                      int    rank,      // Players Ranks
                      char * name,      // Players Name
                      long   kills,     // Players Kills with this Weapon
                      long   damdelt,   // Players Weapon Damage
                      int    count) {   // Player Counter

    // Skip Any Players with 0 kills on this weapon..
    if (kills == 0) return;

    string temp = htmlline;
    string temp2;
    int id1 = -1; // String Index

    // Find the Begining of Each Variable
    id1 = temp.find('$', 0);
    if (id1 == -1) {
        buildHTMLweapon(temp);
        return;
    }
    // Here Stars Parsing of Every Variable in the WeaponPROW-1 & -2.HTML And Templates..
    while (id1 != string::npos) { // While Not End of String
        id1 = temp.find("player.count", 0);
        if (id1 != -1) {
            char pk[10];
            long number = count;
            sprintf(pk, "%d", number);
            temp.replace(id1-1,13,pk);
            buildHTMLweapon(temp);
            return;
        }
        id1 = temp.find("player.rank", 0);
        if (id1 != -1) {
            char idx[10];
            int rank2 = rank;
            sprintf(idx, "%d", rank2);
            temp.replace(id1-1,12,idx);

            id1 = temp.find("player.name", 0);
            if (id1 != -1) temp.replace(id1-1,12,name);

            buildHTMLweapon(temp);
            return;
        }
        id1 = temp.find("player.kills", 0);
        if (id1 != -1) {
            char pk[10];
            long number = kills;
            sprintf(pk, "%d", number);
            temp.replace(id1-1,13,pk);
            buildHTMLweapon(temp);
            return;
        }
        id1 = temp.find("player.damdelt", 0);
        if (id1 != -1) {
            char pk[10];
            long number = damdelt;
            sprintf(pk, "%d", number);
            temp.replace(id1-1,15,pk);
            buildHTMLweapon(temp);
            return;
        }
        buildHTMLweapon(temp);
        return;
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerTop.HTML For Multiple Runs
void buildHTMLweapontop(string html) {

    string temp = html;
    struct ListItem5 *item,*last;
    item = (struct ListItem5 *) malloc(sizeof(struct ListItem5));
    if ( item==0 ) {
        printf ("Malloc Failed \n");
        return;
    }

    strcpy(item->html,temp.c_str());
    item->next = 0;

    if ( MYLIST5 == 0 ) {
        MYLIST5 = item;
        return;
    }

    for( last = MYLIST5 ; last->next != 0 ; last = last->next );
    last->next = item;
    return;
}

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerTop.HTML For Multiple Runs
void buildHTMLweaponptop(string html) {

    string temp = html;
    struct ListItem8 *item,*last;
    item = (struct ListItem8 *) malloc(sizeof(struct ListItem8));
    if ( item==0 ) {
        printf ("Malloc Failed \n");
        return;
    }

    strcpy(item->html,temp.c_str());
    item->next = 0;

    if ( MYLIST8 == 0 ) {
        MYLIST8 = item;
        return;
    }

    for( last = MYLIST8 ; last->next != 0 ; last = last->next );
    last->next = item;
    return;
}


/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerRow1.HTML For Multiple Runs
void buildHTMLweaponrow1(string html) {

    string temp = html;
    struct ListItem6 *item,*last;
    item = (struct ListItem6 *) malloc(sizeof(struct ListItem6));
    if ( item==0 ) {
        printf ("Malloc Failed \n");
        return;
    }

    strcpy(item->html,temp.c_str());
    item->next = 0;

    if ( MYLIST6 == 0 ) {
        MYLIST6 = item;
        return;
    }

    for( last = MYLIST6 ; last->next != 0 ; last = last->next );
    last->next = item;
    return;
}

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerRow1.HTML For Multiple Runs
void buildHTMLweaponprow1(string html) {

    string temp = html;
    struct ListItem9 *item,*last;
    item = (struct ListItem9 *) malloc(sizeof(struct ListItem9));
    if ( item==0 ) {
        printf ("Malloc Failed \n");
        return;
    }

    strcpy(item->html,temp.c_str());
    item->next = 0;

    if ( MYLIST9 == 0 ) {
        MYLIST9 = item;
        return;
    }

    for( last = MYLIST9 ; last->next != 0 ; last = last->next );
    last->next = item;
    return;
}

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerRow2.HTML For Multiple Runs
void buildHTMLweaponrow2(string html) {

    string temp = html;
    struct ListItem7 *item,*last;
    item = (struct ListItem7 *) malloc(sizeof(struct ListItem7));
    if ( item==0 ) {
        printf ("Malloc Failed \n");
        return;
    }

    strcpy(item->html,temp.c_str());
    item->next = 0;

    if ( MYLIST7 == 0 ) {
        MYLIST7 = item;
        return;
    }

    for( last = MYLIST7 ; last->next != 0 ; last = last->next );
    last->next = item;
    return;
}

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerRow2.HTML For Multiple Runs
void buildHTMLweaponprow2(string html) {

    string temp = html;
    struct ListItem10 *item,*last;
    item = (struct ListItem10 *) malloc(sizeof(struct ListItem10));
    if ( item==0 ) {
        printf ("Malloc Failed \n");
        return;
    }

    strcpy(item->html,temp.c_str());
    item->next = 0;

    if ( MYLIST10 == 0 ) {
        MYLIST10 = item;
        return;
    }

    for( last = MYLIST10 ; last->next != 0 ; last = last->next );
    last->next = item;
    return;
}

/*--------------------------------------------------------------------------------*/
// Read Rank.html and setup for parsing. Into Link List
void loadHTMLweapon(void) {

    string name  = "WeaponTOP.html";
    string name1 = "WeaponROW-1.html";
    string name2 = "WeaponROW-2.html";

    string name4 = "WeaponPTOP.html";
    string name5 = "WeaponPROW-1.html";
    string name6 = "WeaponPROW-2.html";

    string TPATH = PATH;

    #ifdef _WIN32
    name  = TPATH+"Templates\\"+name;
    name1 = TPATH+"Templates\\"+name1;
    name2 = TPATH+"Templates\\"+name2;

    name4 = TPATH+"Templates\\"+name4;
    name5 = TPATH+"Templates\\"+name5;
    name6 = TPATH+"Templates\\"+name6;
    #else
    name  = TPATH+"Templates/"+name;
    name1 = TPATH+"Templates/"+name1;
    name2 = TPATH+"Templates/"+name2;

    name4 = TPATH+"Templates/"+name4;
    name5 = TPATH+"Templates/"+name5;
    name6 = TPATH+"Templates/"+name6;
    #endif

    string HTMLDATA; // Holds Each Line Read in from the Template

    // Process Inital RankTop.HTML
    ifstream inStream1;
    inStream1.open( name.c_str() );
    if (!inStream1.is_open()) {
        cout << "\n\nError Opening WeaponStatTop.html for Parsing " << name <<endl;
        return;
    }

    for (;;) { // Process And Load WeaponStatTop.HTML
        getline(inStream1,HTMLDATA);
        buildHTMLweapontop(HTMLDATA);
        if(inStream1.eof()) {
            inStream1.close();
            break;
        }
    }

        // Process Inital WeaponStatRow1.HTML
    ifstream inStream2;
    inStream2.open( name1.c_str() );
    if (!inStream2.is_open()) {
        cout << "\n\nError Opening WeaponStatRow1.html for Parsing " << name <<endl;
        return;
    }

    for (;;) { // Process and Load PlayerRow1.HTML
        getline(inStream2,HTMLDATA);
        buildHTMLweaponrow1(HTMLDATA);
        if(inStream2.eof()) {
            inStream2.close();
            break;
        }
    }

    // Process WeaponStatRow2.HTML
    ifstream inStream3;
    inStream3.open( name2.c_str() );
    if (!inStream3.is_open()) {
        cout << "\n\nError Opening WeaponStatRow2.html for Parsing " << name <<endl;
        return;
    }

    for (;;) { // Process and Load WeaponStatRow2.HTML
        getline(inStream3,HTMLDATA);
        buildHTMLweaponrow2(HTMLDATA);
        if(inStream3.eof()) {
            inStream3.close();
            break;
        }
    }

    // Process Inital RankTop.HTML
    ifstream inStream4;
    inStream4.open( name4.c_str() );
    if (!inStream4.is_open()) {
        cout << "\n\nError Opening WeaponStatTop.html for Parsing " << name <<endl;
        return;
    }

    for (;;) { // Start Processing WeaponStatTop.HTML
        getline(inStream4,HTMLDATA);
        buildHTMLweaponptop(HTMLDATA);
        if(inStream4.eof()) {
            inStream4.close();
            break;
        }
    }

    // Process Inital WeaponStatRow1.HTML
    ifstream inStream5;
    inStream5.open( name5.c_str() );
    if (!inStream5.is_open()) {
        cout << "\n\nError Opening WeaponStatRow1.html for Parsing " << name <<endl;
        return;
    }

    for (;;) { // Process and Load PlayerRow1.HTML
        getline(inStream5,HTMLDATA);
        buildHTMLweaponprow1(HTMLDATA);
        if(inStream5.eof()) {
            inStream5.close();
            break;
        }
    }

    // Process WeaponStatRow2.HTML
    ifstream inStream6;
    inStream6.open( name6.c_str() );
    if (!inStream6.is_open()) {
        cout << "\n\nError Opening WeaponStatRow2.html for Parsing " << name <<endl;
        return;
    }

    for (;;) { // Process and Load WeaponStatRow2.HTML
        getline(inStream6,HTMLDATA);
        buildHTMLweaponprow2(HTMLDATA);
        if(inStream6.eof()) {
                inStream6.close();
                break;
        }
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Read and setup for parsing.
void readHTMLweapon(char * weaponname) {

    struct ListItem15 *wp;  // Holds All Weapons for Faster Parsing
    struct ListItem12 *pl;  // Holds All Players for Faster Parsing

    string HTMLDATA;        // Holds Each Line Read in from the Log File
    struct ListItem5  *p5;  // Holds HTML Templates WeaponStatTOP.HTML
    struct ListItem6  *p6;  // Holds HTML Templates WeaponROW-1.HTML
    struct ListItem7  *p7;  // Holds HTML Templates WeaponROW-2.HTML
    struct ListItem9  *p9;  // HTML
    struct ListItem10 *p10; // HTML
    struct ListItem11 *p11; // TOP PLAYERS FOR THIS WEAPON

    // Reading in Eeach players Kills with this current weapon and sort by kills
    // This will go for Players Top Kills with this weapon, Loops Though All Players

    int count = 0;  // Counter for Alterating Top 10 Places..
    int mod   = 2;  // Modulious

    // Do Testing if player name is in list, Update it with New Data
    for ( wp = MYLIST15 ; wp != 0 ; wp = wp->next ) {
        if (strcmp(wp->weapon.name, weaponname) == 0) {
            // Do Testing if player name is in list, Update it with New Data
            for ( pl = MYLIST12 ; pl != 0 ; pl = pl->next ) {
                // Creates Link List 11 For Top Players with this Weapon
                topweaponplayers(&pl->player,wp->weapon.name);
            }
            // Process WeaponTOP.HTML
            for (;;) {
                for ( p5 = MYLIST5 ; p5 != 0 ; p5 = p5->next ) {
                    // Prase's the string And splits for Processing
                    HTMLDATA = (p5->html);
                    checkHTMLWeapon(HTMLDATA,wp->weapon.name);
                }
                break;
            }
            //Process WeaponRow-1.HTML Here...
            p5 = MYLIST5;   // Resets
            // Setup For Rotating WeaponROW-1 and -2
            wp = MYLIST15;  // Resets

            // Start Processing Weaponrow-1.HTML
            bool DONE = false;
            while(DONE == false) {
                if (count % mod == 0) {
                    for (;;) {
                        if (count == 36) { // Total # of Weapons
                            DONE = true;
                            break;
                        }
                        for ( p6 = MYLIST6 ; p6 != 0 ; p6 = p6->next ) {
                            // Prase's the string And splits for Processing
                            HTMLDATA = (p6->html);
                            checkHTMLWeapon(HTMLDATA,wp->weapon.name);
                        }
                        ++count;       // Incriment Count for Mod...
                        wp = wp->next; // Next Weapon
                        break;
                    }
                }
                //Process WeaponRow-2.HTML
                if (count % mod == 1) {
                    for (;;) {
                        if (count == 36) { // Total # of Weapons
                            DONE = true;
                            break;
                        }

                        for ( p7 = MYLIST7 ; p7 != 0 ; p7 = p7->next ) {
                        // Prase's the string And splits for Processing
                            HTMLDATA = (p7->html);
                            checkHTMLWeapon(HTMLDATA,wp->weapon.name);
                        }
                        ++count;       // Incriment Count for Mod...
                        wp = wp->next; // Next Weapon
                        break;
                    }
                }
            } // End While Loop

            // Start Processing WeaponPTOP.HTML
            struct ListItem8 *p8;

            for ( p8 = MYLIST8 ; p8 != 0 ; p8 = p8->next ) {
                HTMLDATA = (p8->html);
                checkHTMLWeapon(HTMLDATA,weaponname);
            }

            count = 0;       // RESET COUNTER
            p11 = MYLIST11;  // Handle to Top Player's Sorted Link List

            bool DONE2 = false;
            while(DONE2 == false) {
                if (count % mod == 0) {
                    for (;;) {
                        if (p11 == 0) {
                            clearwprank1();
                            DONE2 = true;
                            return;
                        }
                        ++count; // Incriment Count for Player Row
                        if (count == MAXWEAPONRANK+1) {
                            clearwprank1();
                            DONE2 = true;
                            return;
                        }
                        for ( p9 = MYLIST9 ; p9 != 0 ; p9 = p9->next ) {
                            // Prase's the string And splits for Processing
                            HTMLDATA = (p9->html);
                            checkHTMLWeaponp(HTMLDATA,     // String to be Parsed
                                             p11->rank,    // Player Rank
                                             p11->name,    // Player Name
                                             p11->kills,   // Weapon Kills
                                             p11->damdelt, // Weapon Damage
                                             count);       // Player Rank with this weapon
                        }
                        p11 = p11->next; // Goto Next Weapon in List
                        break;
                    }
                }
                //Process PlayerRow-2.HTML
                if (count % mod == 1) {
                    for (;;) {
                        if (p11 == 0) {  // End of List
                            clearwprank1();
                            DONE2 = true;
                            return;
                        }
                        ++count; // Incriment Count for For Player Row
                        if (count == MAXWEAPONRANK+1) {
                            clearwprank1();
                            DONE2 = true;
                            return;
                        }
                        for ( p10 = MYLIST10 ; p10 != 0 ; p10 = p10->next ) {
                            // Prase's the string And splits for Processing
                            HTMLDATA = (p10->html);
                            checkHTMLWeaponp(HTMLDATA,
                                             p11->rank,
                                             p11->name,
                                             p11->kills,
                                             p11->damdelt,
                                             count);
                        }
                        p11 = p11->next; // Goto Next Weapon in List
                        break;
                    }
                }
            } // End While Loop
        } // End of 1st Run of Weapons WP Loop
    } // End first FOR LOOP for Weapon WP
    return;
}

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearHTMLweapon(void) {

    struct ListItem3 *p,*next;
    if ( MYLIST3 == 0) return;

    for(p = MYLIST3 ; p !=0 ; p = next ) {
        next = p->next;
        free ( p );
    }
    MYLIST3 = 0;
}

/*--------------------------------------------------------------------------------*/
// Read Rank.html and setup for parsing. Into Link List
void loadHTMLweaponrank(void) {

    string name  = "WeaponRankTop.html";
    string name1 = "WeaponRankRow-1.html";
    string name2 = "WeaponRankRow-2.html";

    string TPATH = PATH;

    #ifdef _WIN32
    name  = TPATH+"Templates\\"+name;
    name1 = TPATH+"Templates\\"+name1;
    name2 = TPATH+"Templates\\"+name2;
    #else
    name  = TPATH+"Templates/"+name;
    name1 = TPATH+"Templates/"+name1;
    name2 = TPATH+"Templates/"+name2;
    #endif

    string HTMLDATA; // Holds Each Line Read in from the Template

    // Process Inital RankTop.HTML
    ifstream inStream1;
    inStream1.open( name.c_str() );
    if (!inStream1.is_open()) {
        cout << "\n\nError Opening WeaponRankTop.html for Parsing " << name <<endl;
        return;
    }

    // Start Processing WeaponStatTop.HTML
    for (;;) {
        getline(inStream1,HTMLDATA);
        buildHTMLweapontop(HTMLDATA);
        if(inStream1.eof()) {
            inStream1.close();
            break;
        }
    }

    // Process Inital WeaponStatRow1.HTML
    ifstream inStream2;
    inStream2.open( name1.c_str() );
    if (!inStream2.is_open()) {
        cout << "\n\nError Opening WeaponRankRow1.html for Parsing " << name <<endl;
        return;
    }

    for (;;) { // Process and Load PlayerRow1.HTML
        getline(inStream2,HTMLDATA);
        buildHTMLweaponrow1(HTMLDATA);
        if(inStream2.eof()) {
            inStream2.close();
            break;
        }
    }

    // Process WeaponStatRow2.HTML
    ifstream inStream3;
    inStream3.open( name2.c_str() );
    if (!inStream3.is_open()) {
        cout << "\n\nError Opening WeaponRankRow2.html for Parsing " << name <<endl;
        return;
    }

    for (;;) { // Process and Load WeaponStatRow2.HTML
        getline(inStream3,HTMLDATA);
        buildHTMLweaponrow2(HTMLDATA);
        if(inStream3.eof()) {
            inStream3.close();
            break;
        }
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Processes HTML for Write out to the Link List - Weapon.HTML
void checkHTMLweaponrank(string htmlline, char *tweapon) {

    struct ListItem15 *wp;
    // Do Testing if player name is in list, Update it with New Data
    for ( wp = MYLIST15 ; wp != 0 ; wp = wp->next ) {
        if(strcmp(wp->weapon.name,tweapon) == 0) {

            string temp = htmlline;
            string temp2;
            int id1 = -1;  // String Index

            // Find the Begining of Each Log Line
            id1 = temp.find('$', 0);
            if (id1 == -1) {
                buildHTMLweapon(temp);
                return;
            }
            // Here Stars Parsing of Every Variable in the WeaponTOP
            // & ROW1 & ROW 2.HTML And Templates..
            while (id1 != string::npos) {
                id1 = temp.find("timedate", 0);
                if (id1 != -1) {
                    char DateTime[100];
                    sprintf(DateTime,"%s %s",szDateFormat,szTimeFormat);
                    temp.replace(id1-1,9,DateTime);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("server.ip", 0);
                if (id1 != -1) {
                    char ServerIP[20];
                    sprintf(ServerIP,"%s",SERVERIP);
                    temp.replace(id1-1,10,ServerIP);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("webpage", 0);
                if (id1 != -1) {
                    char Webpage[255];
                    sprintf(Webpage,"%s",WEBPAGE);
                    temp.replace(id1-1,8,Webpage);
                    id1 = temp.find("server.name", 0);
                    if (id1 != -1) {
                        char ServerName[100];
                        sprintf(ServerName,"%s",SERVERNAME);
                        temp.replace(id1-1,12,ServerName);
                        buildHTMLweapon(temp);
                        return;
                    }
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("server.name", 0);
                if (id1 != -1) {
                    char ServerName[100];
                    sprintf(ServerName,"%s",SERVERNAME);
                    temp.replace(id1-1,12,ServerName);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("admin.email", 0);
                if (id1 != -1) {
                    char AdminEmail[100];
                    sprintf(AdminEmail,"%s",ADMINEMAIL);
                    temp.replace(id1-1,12,AdminEmail);
                    id1 = temp.find("admin.name", 0);
                    if (id1 != -1) {
                        char AdminName[100];
                        sprintf(AdminName,"%s",ADMINNAME);
                        temp.replace(id1-1,11,AdminName);
                        buildHTMLweapon(temp);
                        return;
                    }
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("admin.name", 0);
                if (id1 != -1) {
                    char AdminName[100];
                    sprintf(AdminName,"%s",ADMINNAME);
                    temp.replace(id1-1,11,AdminName);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("weapon.rank", 0);
                if (id1 != -1) {
                    char idx[10];
                    int rank = wp->weapon.rank;
                    sprintf(idx, "%d", rank);
                    temp.replace(id1-1,12,idx);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("weapon.name", 0);
                if (id1 != -1) {
                    temp.replace(id1-1,12,wp->weapon.name);
                    id1 = temp.find("weapon.name", 0);
                    if (id1 != -1) temp.replace(id1-1,12,wp->weapon.name);
                    id1 = temp.find("weapon.name", 0);
                    if (id1 != -1) temp.replace(id1-1,12,wp->weapon.name);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("weapon.kills", 0);
                if (id1 != -1) {
                    char pk3[10];
                    long number = wp->weapon.kills;
                    sprintf(pk3, "%d", number);
                    temp.replace(id1-1,13,pk3);
                    id1 = temp.find("weapon.damdelt", 0);
                    if (id1 != -1) {
                        char pk[10];
                        int number = wp->weapon.damdelt;
                        sprintf(pk, "%d", number);
                        temp.replace(id1-1,15,pk);
                        buildHTMLweapon(temp);
                        return;
                    }
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("weapon.pkills", 0);
                if (id1 != -1) {
                    char pk1[10];
                    double number = wp->weapon.pkills;
                    sprintf(pk1, "%.1f", number);
                    temp.replace(id1-1,14,pk1);
                    buildHTMLweapon(temp);
                    return;
                }
                id1 = temp.find("weapon.damdelt", 0);
                if (id1 != -1) {
                    char pk2[10];
                    long number = wp->weapon.damdelt;
                    sprintf(pk2, "%d", number);
                    temp.replace(id1-1,15,pk2);
                    buildHTMLweapon(temp);
                    return;
                }
                buildHTMLweapon(temp);
                return;
            } //End of While
        } //END OF WP IF
    } //END OF WP FOR
    return;
}


/*--------------------------------------------------------------------------------*/
// Setup And Process Weapon Rankings
void readHTMLweaponrank() {

    string HTMLDATA;        // Holds Each Line Read in from the Log File
    struct ListItem5 *p5;   // Holds HTML Templates WeaponRankTOP.HTML

    // Setup For Rotating WeaponRankROW-1 and -2
    struct ListItem6 *p6;  // Holds HTML Templates WeaponRankROW-1.HTML
    struct ListItem7 *p7;  // Holds HTML Templates WeaponRankROW-2.HTML

    int count = 0;  // Counter for Alterating Top 10 Places..
    int mod   = 2;  // Modulious

    struct ListItem15 *wp;
    // Do Testing if player name is in list, Update it with New Data
    for ( wp = MYLIST15 ; wp != 0 ; wp = wp->next ) {
        // Process WeaponRankTOP.HTML
        for (;;) {
            for ( p5 = MYLIST5 ; p5 != 0 ; p5 = p5->next ) {
                // Prase's the string And splits for Processing
                HTMLDATA = (p5->html);
                checkHTMLweaponrank(HTMLDATA,wp->weapon.name);
            } break;
        }
        // Reset To Begining of List
        wp = MYLIST15;
        // Start Processing WeaponRankRow-1.HTML
        bool DONE = false;
        while(DONE == false) {
            if (count % mod == 0) {
                for (;;) {
                    if (wp == 0) {  // Total # of Weapons
                        DONE = true;
                        return;
                    }

                    for ( p6 = MYLIST6 ; p6 != 0 ; p6 = p6->next ) {
                        // Prase's the string And splits for Processing
                        HTMLDATA = (p6->html);
                        checkHTMLweaponrank(HTMLDATA,wp->weapon.name);
                    }
                    ++count;  // Incriment Count for Mod...
                    wp = wp->next;
                    break;
                }
            }
            //Process WeaponRankRow-2.HTML
            if (count % mod == 1) {
                for (;;) {
                    if (wp == 0) {  // Total # of Weapons
                        DONE = true;
                        return;
                    }

                    for ( p7 = MYLIST7 ; p7 != 0 ; p7 = p7->next ) {
                        // Prase's the string And splits for Processing
                        HTMLDATA = (p7->html);
                        checkHTMLweaponrank(HTMLDATA,wp->weapon.name);
                    }
                    ++count;
                    wp = wp->next;
                    break;
                }
            }
        } // End While Loop
    } // END FOR WP LOOP
    return;
}

/*--------------------------------------------------------------------------------*/
// Adds All Weapons to Link List for Stat Calculations
void setupplayerdc() {

    PLAYERREC2 player;

    int tidx  = 0;  // Temp Index - Counter
    int total = 0;  // Number or Total Weapons to Process
    total = countpridx();

    // This Loops Filles up the Link List with all Weapons
    while (tidx != total) {
        readprank(&player,tidx);  // Loads Weapon form Dat for Weapon Name
        playerdatacont(&player);  // Add Weapons To Container
        ++tidx;
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Calculate each weapons Percentage of Total Overall Kills
void doweaponpkills() {

    WEAPONREC weapon;            // Handle to WEAPON Structure

    long double totalkills = 0; // Container for Total Weapon Kills
    int tidx  = 0;               // Temp Index - Counter
    int total = 0;               // Number or Total Weapons to Process
    total = countweapons();

    // This loop Calculates Total Overall Weapon Kills
    while (tidx != total) {
        readw(&weapon,tidx);
        totalkills += weapon.kills;
        ++tidx;
    }

    long double pkills = 0.0;  // Holds Percentage of Total Kills
    tidx  = 0;                 // Reset Counter index for second run

    // This Loops Calculates Each Weapons Kills Percentage out of Total Kills
    while (tidx != total) {
        readw(&weapon,tidx);   // Loads Weapon form Dat for Weapon Name
        if (weapon.kills > 0){
            weapon.pkills = 100 * (weapon.kills / totalkills);
            writew(&weapon,tidx);
        }
        else {
            weapon.pkills = 0.0;
            writew(&weapon,tidx);
        }
        ++tidx;
    }
    return;
}


/*--------------------------------------------------------------------------------*/
// Gets Information for Weapon.dat And adds all Weapon Data to Link List
void addweapondc(char * weaponname) {

    int index = findweapon(weaponname);
    WEAPONREC weapon;

    readw(&weapon,index);
    weapondatacontainer(&weapon);
    return;
}


/*--------------------------------------------------------------------------------*/
// This Function will setup the a Link List, sort for And create The HTML STAT Files for All Players
void doweaponHTML() {

    clearall();
    char title[100] = "Creating HTML Weapon Statistics . . .";
    drawtop(title,11,0,22);

    double p1 = 0,  // Percentage Top
           p2 = 0;  // Percentage Left

    WEAPONREC weapon;
    loadHTMLweapon();    // Loads Weapon HTML Templates into Memory

    int tidx  = 0;
    int total = 0;
    total = countweapons();

    // This Loops Filles up the Link List with all Weapons
    while (readw(&weapon,tidx)) {
        addweapondc(weapon.name);      // Add Weapons To Container
        ++tidx;
    }

    setupplayerdc(); // Load Players Into Memory for Weapon Rankings

    struct ListItem15 *wp;
    tidx = 0;
    // Do Testing if player name is in list, Update it with New Data
    for ( wp = MYLIST15 ; wp != 0 ; wp = wp->next ) {
        clearallleft();
        p1 = compwkillpercent1(tidx,total);
        percenttop(p1);
        char text1[40] = "Creating Weapons!";
        drawleft(text1,3,0);

          readHTMLweapon(wp->weapon.name);
        writeHTMLweapon(wp->weapon.name);
        ++tidx;

        percentleft(100);
        char text3[40];
        sprintf(text3,"Completed OK! ");
        drawleft2(text3,9,0);
    }
    clearweaponcontainer();  // Removes Weapon Data Container from Memory
    clearplayercont();       // Removes Player Data Container from Memory
    RemoveWeaponHTML();     // Releases Weapon HTML from Memory
    percenttop(100);
    #ifdef _WIN32
    Sleep(1000);
    #else
    system("sleep 1s");
    #endif
    return;
}


/*--------------------------------------------------------------------------------*/
// This Function will setup the a Link List, sort for And create The HTML STAT Files
void doweaponrankHTML() {

    clearall();
    char title[100] = "Creating HTML Weapon Rankings . . .";
    drawtop(title,11,0,21);

    WEAPONREC weapon;
    doweaponpkills();  // Calculates Weapons Percentage of Total Kills
    loadHTMLweaponrank();

    int tidx  = 0,
        total = 0;

    total = countweapons();

    // This Loops Filles up the Link List with all Weapons
    while (tidx != total ) {
        readw(&weapon,tidx);
        addweapondc(weapon.name);
        ++tidx;
    }

    char text1[40] = "Creating Weapon Ranks";
    drawright(text1,3,0);

    // DO HTML PROCESSING
    readHTMLweaponrank();    // Process Templates
    writeHTMLweaponrank();   // Write out HTML Weapon.HTML File
    clearweaponcontainer();  // Removes Weapon Data Container from Memory
    RemoveWeaponHTML();     // Releases Weapon HTML from Memory

    percentright(100);
    char text3[40];
    sprintf(text3,"Completed OK! ");
    drawright2(text3,9,0);

    percenttop(100);
    #ifdef _WIN32
    Sleep(1000);
    #else
    system("sleep 1s");
    #endif
    return;
}


#endif
