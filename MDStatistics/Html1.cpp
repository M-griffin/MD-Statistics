#ifndef __HTML1_CPP    /*  An extra safeguard to prevent this header from  */
#define __HTML1_CPP    /*  being included twice in the same source file    */

// This file Processes both the Rank and Players HTML Files, Also Computing Statistics

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN_AND_MEAN
#include <windows.h>
#include "wincon.h"
#endif

#include <string>
#include <fstream>

#include "structs.h"              // Player / Weapon / Linklist Structures
#include "LogFunc.h"
#include "PlayerFunc.h"           // Displaying Link list with Players
#include "WeaponFunc.h"
#include "FA26.h"
#include "Stats.h"
#include "Html1.h"

using namespace std;              // Standard C++ Namespace

/*--------------------------------------------------------------------------------*/
// GLOBALS - Link List's For Data Contianers
/*--------------------------------------------------------------------------------*/

struct ListItem   *MyList   = 0 ; // Player Ranks Sorting for Index.HTML
struct ListItem3  *MyList3  = 0 ; // PlayerStats Write Out
struct ListItem4  *MyList4  = 0 ; // Weapon Sorting Players.HTML
struct ListItem5  *MyList5  = 0 ; // PlayerTop.HTML
struct ListItem6  *MyList6  = 0 ; // PlayerRow1.HTML
struct ListItem7  *MyList7  = 0 ; // PlayerRow2.HTML

struct ListItem12 *myList12 = 0 ; // Holds Player Ranks .dat Data			PLAYERREC2
struct ListItem14 *myList14 = 0 ; // Holding All Player Data while Creating HTML Files	PLAYERREC
struct ListItem15 *myList15 = 0 ; // Holding all Weapon Data While Calculating Stats	WEAPONREC

/*--------------------------------------------------------------------------------*/
// OUTPUT STREAMING HANDLES FOR HTML CREATION
/*--------------------------------------------------------------------------------*/

ofstream index1;
ofstream index2;
ofstream index3;
ofstream index4;
ofstream index5;
ofstream index6;
ofstream index7;

int index_html_number = 0; // keeps track of current html output



/*--------------------------------------------------------------------------------*/
// Initalize and Handle Output file streams
void init_index() {

	string index_path1 = HTMLPATH;
	index_path1 += "index.html";
	index1.open( index_path1.c_str(), ofstream::out | ofstream::trunc );
	if (!index1.is_open()) {
		cout << "\n\nError Creating Index.html for Writing " << endl;
		return;
	}

	string index_path2 = HTMLPATH;
	index_path2 += "index2.html";
	index2.open( index_path2.c_str(), ofstream::out | ofstream::trunc );
	if (!index2.is_open()) {
		cout << "\n\nError Creating Index2.html for Writing " << endl;
		return;
	}

	string index_path3 = HTMLPATH;
	index_path3 += "index3.html";
	index3.open( index_path3.c_str(), ofstream::out | ofstream::trunc );
	if (!index3.is_open()) {
		cout << "\n\nError Creating Index3.html for Writing " << endl;
		return;
	}

	string index_path4 = HTMLPATH;
	index_path4 += "index4.html";
	index4.open( index_path4.c_str(), ofstream::out | ofstream::trunc );
	if (!index4.is_open()) {
		cout << "\n\nError Creating Index4.html for Writing " << endl;
		return;
	}

	string index_path5 = HTMLPATH;
	index_path5 += "index5.html";
	index5.open( index_path5.c_str(), ofstream::out | ofstream::trunc );
	if (!index5.is_open()) {
		cout << "\n\nError Creating Index5.html for Writing " << endl;
		return;
	}

	string index_path6 = HTMLPATH;
	index_path6 += "index6.html";
	index6.open( index_path6.c_str(), ofstream::out | ofstream::trunc );
	if (!index6.is_open()) {
		cout << "\n\nError Creating Index6.html for Writing " << endl;
		return;
	}

	string index_path7 = HTMLPATH;
	index_path7 += "index7.html";
	index7.open( index_path7.c_str(), ofstream::out | ofstream::trunc );
	if (!index7.is_open()) {
		cout << "\n\nError Creating Index7.html for Writing " << endl;
		return;
	}
	return;

}

/*--------------------------------------------------------------------------------*/
// Close Output file streams
void init_index_clean() {

	index1.close();
	index2.close();
	index3.close();
	index4.close();
	index5.close();
	index6.close();
	index7.close();
	return;
}

/*--------------------------------------------------------------------------------*/
// LINK LISTS Data Sorting Functions & Memory Freeing Functions
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void RemoveList(void) {

	struct ListItem *p,*next;
	if ( MyList== 0) return;

    for(p = MyList ; p !=0 ; p = next ) {
		next = p->next;
		delete (p);
	}
	MyList=0;
}

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void RemoveListWeapon(void) {

	struct ListItem4 *p,*next;
	if ( MyList4 == 0) {
		return;
	}

	for(p = MyList4 ; p !=0 ; p = next ) {
		next = p->next;
		delete (p);
	}
	MyList4=0;
}

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearprank() {

	struct ListItem12 *p,*next;
	if ( myList12 == 0) return;

    for(p = myList12 ; p !=0 ; p = next ) {
		next = p->next;
    	delete (p);
	}
	myList12 = 0;
}

/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void RemovePlayerHTML(void) {

	struct ListItem5 *p5,*next5;       // List 5
	struct ListItem6 *p6,*next6;       // List 6
	struct ListItem7 *p7,*next7;       // List 7

	if ( MyList5 != 0) {
		for(p5 = MyList5 ; p5 !=0 ; p5 = next5 ) {
			next5 = p5->next;
			delete (p5);
		}
		MyList5 = 0;
	}
	if ( MyList6 != 0) {
		for(p6 = MyList6 ; p6 !=0 ; p6 = next6 ) {
			next6 = p6->next;
			delete (p6);
		}
		MyList6 = 0;
	}
	if ( MyList7 != 0) {
		for(p7 = MyList7 ; p7 !=0 ; p7 = next7 ) {
			next7 = p7->next;
			delete (p7);
		}
		MyList7 = 0;
	}
	return;
}

/*--------------------------------------------------------------------------------*/
// DATA SORTING FUNCTIONS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// This Function Holds All Player Data While Creating HTML Files
// Contains Depending on Int Received, Determines which statistic players are sorted by.
void playerrankeddata(PLAYERREC2 * player, int num) {

	struct ListItem12 *next;
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

	if ( myList12 == 0 ) {  // If List is Empty, make this the first item
        myList12 = item;
        return;
    }

	// Do just normal Non Sorting for Top Rank by Kills
	if (num == 1) for( next = myList12 ; next->next != 0 ; next = next->next );
	// Do Sorting by Damage Delt for Top Ranks by Damage
	else if (num == 2) {
		if((player->damdelt - myList12->player.damdelt) > 0 ) {
			item->next = myList12;
			myList12 = item;
			return;
		}
		// Check to see if an item is inserted before the next item
		for ( next = myList12 ; next->next != 0 ; next = next->next ) {
			if ((player->damdelt - next->next->player.damdelt) > 0 ) {
				// Insert Item before the next Item.
				item->next = next->next;
				next->next = item ;
				return;
			}
		}
	}
	// Do Sorting by Players Deaths for Top Ranks
    else if (num == 3) {
    	if((player->deaths - myList12->player.deaths) > 0 ) {
    	   	item->next = myList12;
			myList12 = item;
			return;
		}
		// Check to see if an item is inserted before the next item
		for ( next = myList12 ; next->next != 0 ; next = next->next ) {
			if ((player->deaths - next->next->player.deaths) > 0 ) {
				// Insert Item before the next Item.
				item->next = next->next;
				next->next = item ;
				return;
			}
		}
	}
	// Do Sorting by Players Damage Take for Top Ranks
	else if (num == 4) {
		if((player->damrec - myList12->player.damrec) > 0 ) {
			item->next = myList12;
			myList12 = item;
			return;
		}
		// Check to see if an item is inserted before the next item
		for ( next = myList12 ; next->next != 0 ; next = next->next ) {
			if ((player->damrec - next->next->player.damrec) > 0 ) {
				// Insert Item before the next Item.
				item->next = next->next;
				next->next = item ;
				return;
			}
		}
	}
	// Do Sorting by Players Suicides Take for Top Ranks
    else if (num == 5) {
		if((player->sui - myList12->player.sui) > 0 ) {
			item->next = myList12;
			myList12 = item;
			return;
		}
		// Check to see if an item is inserted before the next item
		for ( next = myList12 ; next->next != 0 ; next = next->next ) {
			if ((player->sui - next->next->player.sui) > 0 ) {
				// Insert Item before the next Item.
				item->next = next->next;
				next->next = item ;
				return;
			}
		}
	}
	// Do Sorting by Players Damage Bled for Top Ranks
    else if (num == 6) {
		if((player->dambleed - myList12->player.dambleed) > 0 ) {
			item->next = myList12;
			myList12 = item;
			return;
		}
		// Check to see if an item is inserted before the next item
		for ( next = myList12 ; next->next != 0 ; next = next->next ) {
			if ((player->dambleed - next->next->player.dambleed) > 0 ) {
				// Insert Item before the next Item.
				item->next = next->next;
				next->next = item ;
				return;
            }
	    }
	}
	// Do Sorting by Players K:D:S % for Top Ranks
    else if (num == 7) {
		if((player->kdp - myList12->player.kdp) > 0 ) {
			item->next = myList12;
			myList12 = item;
			return;
		}
		// Check to see if an item is inserted before the next item
		for ( next = myList12 ; next->next != 0 ; next = next->next ) {
			if ((player->kdp - next->next->player.kdp) > 0 ) {
				// Insert Item before the next Item.
				item->next = next->next;
				next->next = item ;
				return;
			}
	    }
	}
	next->next = item;      // Append New Item to Last Item
    return;
}

/*--------------------------------------------------------------------------------*/
// Link List for Sorting By a single Player's Weapon by Kills
// Sorts Players in Player.html
void weaponkillsort(int    rank,
                    char * name,
                    long   kills,
                    long   deaths,   // Deaths by this Weapon
                    long   sui,      // Suicides with this weapon
                    double kdp,      // Weapon Kill Death Sui Percentage
                    char * kdr,      // Kill Death Ratio
                    double pkills,   // Weapons Total Kills
                    long   damdelt,  // Damage Delt
                    long   damrec,   // Damage Received
                    char * dratio) {

	struct ListItem4 *next;
	ListItem4 *Item = new ListItem4;

	if ( !Item ) {
		printf ("Malloc Failed \n");
		return;
    }

	// Store Weapon Information into List
	Item->rank = rank;
	strcpy(Item->name,name);
	Item->kills = kills;
	Item->deaths = deaths;
	Item->sui = sui;
	Item->kdp = kdp;
	strcpy(Item->kdr,kdr);
	Item->pkills = pkills;
	Item->damdelt = damdelt;
	Item->damrec = damrec;
	strcpy(Item->dratio,dratio);
	Item->next = 0;

	if ( MyList4 == 0 ) {
		MyList4 = Item;
		return;
    }

	if((kills - MyList4->kills) > 0 ) {
		Item->next = MyList4;
		MyList4 = Item;
		return;
	}

	// Check to see if an item is inserted before the next item
	for ( next = MyList4 ; next->next != 0 ; next = next->next ) {
		if ((kills - next->next->kills) > 0 ) {
			// Insert Item before the next Item.
			Item->next = next->next;
			next->next = Item ;
			return;
		}
	}
	// There are no more Items ! Add to end
	next->next = Item;
}


/*--------------------------------------------------------------------------------*/
// Reveices Player Weapons and Sorts by kills for Players.HTML
void calcweapons(PLAYERREC2 * player) {

	// Add Weapons to Linklist and Sort Weapons for Each Player by Kills
	weaponkillsort(player->weapon.knife.rank,       // Weapon Rank
				   player->weapon.knife.name,       // Weapon Name
				   player->weapon.knife.kills,      // Weapon Kills
				   player->weapon.knife.deaths,     // Weapon Deaths
				   player->weapon.knife.sui,        // Weapon sui
				   player->weapon.knife.kdp,        // Weapon Kill Death Suicide Percentage
				   player->weapon.knife.kdr,        // Weapon Kill : Death Ratio
				   player->weapon.knife.pkills,
				   player->weapon.knife.damdelt,
				   player->weapon.knife.damrec,
				   player->weapon.knife.dratio);

	weaponkillsort(player->weapon.coltgov.rank,
				   player->weapon.coltgov.name,
				   player->weapon.coltgov.kills,
				   player->weapon.coltgov.deaths,
				   player->weapon.coltgov.sui,
				   player->weapon.coltgov.kdp,
				   player->weapon.coltgov.kdr,
				   player->weapon.coltgov.pkills,
				   player->weapon.coltgov.damdelt,
				   player->weapon.coltgov.damrec,
				   player->weapon.coltgov.dratio);

	weaponkillsort(player->weapon.ber92f.rank,
				   player->weapon.ber92f.name,
				   player->weapon.ber92f.kills,
				   player->weapon.ber92f.deaths,
				   player->weapon.ber92f.sui,
				   player->weapon.ber92f.kdp,
				   player->weapon.ber92f.kdr,
				   player->weapon.ber92f.pkills,
				   player->weapon.ber92f.damdelt,
				   player->weapon.ber92f.damrec,
				   player->weapon.ber92f.dratio);

	weaponkillsort(player->weapon.ber93r.rank,
				   player->weapon.ber93r.name,
				   player->weapon.ber93r.kills,
				   player->weapon.ber93r.deaths,
				   player->weapon.ber93r.sui,
				   player->weapon.ber93r.kdp,
				   player->weapon.ber93r.kdr,
				   player->weapon.ber93r.pkills,
				   player->weapon.ber93r.damdelt,
				   player->weapon.ber93r.damrec,
				   player->weapon.ber93r.dratio);

	weaponkillsort(player->weapon.anaconda.rank,
				   player->weapon.anaconda.name,
				   player->weapon.anaconda.kills,
				   player->weapon.anaconda.deaths,
				   player->weapon.anaconda.sui,
				   player->weapon.anaconda.kdp,
				   player->weapon.anaconda.kdr,
				   player->weapon.anaconda.pkills,
				   player->weapon.anaconda.damdelt,
				   player->weapon.anaconda.damrec,
				   player->weapon.anaconda.dratio);

	weaponkillsort(player->weapon.desert.rank,
				   player->weapon.desert.name,
				   player->weapon.desert.kills,
				   player->weapon.desert.deaths,
				   player->weapon.desert.sui,
				   player->weapon.desert.kdp,
				   player->weapon.desert.kdr,
				   player->weapon.desert.pkills,
				   player->weapon.desert.damdelt,
				   player->weapon.desert.damrec,
				   player->weapon.desert.dratio);

	weaponkillsort(player->weapon.benelli.rank,
				   player->weapon.benelli.name,
				   player->weapon.benelli.kills,
				   player->weapon.benelli.deaths,
				   player->weapon.benelli.sui,
				   player->weapon.benelli.kdp,
				   player->weapon.benelli.kdr,
				   player->weapon.benelli.pkills,
				   player->weapon.benelli.damdelt,
				   player->weapon.benelli.damrec,
				   player->weapon.benelli.dratio);

	weaponkillsort(player->weapon.saiga.rank,
				   player->weapon.saiga.name,
				   player->weapon.saiga.kills,
				   player->weapon.saiga.deaths,
				   player->weapon.saiga.sui,
				   player->weapon.saiga.kdp,
				   player->weapon.saiga.kdr,
				   player->weapon.saiga.pkills,
				   player->weapon.saiga.damdelt,
				   player->weapon.saiga.damrec,
				   player->weapon.saiga.dratio);

	weaponkillsort(player->weapon.mp5a5.rank,
				   player->weapon.mp5a5.name,
				   player->weapon.mp5a5.kills,
				   player->weapon.mp5a5.deaths,
				   player->weapon.mp5a5.sui,
				   player->weapon.mp5a5.kdp,
				   player->weapon.mp5a5.kdr,
				   player->weapon.mp5a5.pkills,
				   player->weapon.mp5a5.damdelt,
				   player->weapon.mp5a5.damrec,
				   player->weapon.mp5a5.dratio);

	weaponkillsort(player->weapon.sterling.rank,
				   player->weapon.sterling.name,
				   player->weapon.sterling.kills,
				   player->weapon.sterling.deaths,
				   player->weapon.sterling.sui,
				   player->weapon.sterling.kdp,
				   player->weapon.sterling.kdr,
				   player->weapon.sterling.pkills,
				   player->weapon.sterling.damdelt,
				   player->weapon.sterling.damrec,
				   player->weapon.sterling.dratio);

	weaponkillsort(player->weapon.bizon.rank,
				   player->weapon.bizon.name,
				   player->weapon.bizon.kills,
				   player->weapon.bizon.deaths,
				   player->weapon.bizon.sui,
				   player->weapon.bizon.kdp,
				   player->weapon.bizon.kdr,
				   player->weapon.bizon.pkills,
				   player->weapon.bizon.damdelt,
				   player->weapon.bizon.damrec,
				   player->weapon.bizon.dratio);

	weaponkillsort(player->weapon.ak47.rank,
				   player->weapon.ak47.name,
				   player->weapon.ak47.kills,
				   player->weapon.ak47.deaths,
				   player->weapon.ak47.sui,
				   player->weapon.ak47.kdp,
				   player->weapon.ak47.kdr,
				   player->weapon.ak47.pkills,
				   player->weapon.ak47.damdelt,
				   player->weapon.ak47.damrec,
				   player->weapon.ak47.dratio);

	weaponkillsort(player->weapon.famas.rank,
				   player->weapon.famas.name,
				   player->weapon.famas.kills,
				   player->weapon.famas.deaths,
				   player->weapon.famas.sui,
				   player->weapon.famas.kdp,
				   player->weapon.famas.kdr,
				   player->weapon.famas.pkills,
				   player->weapon.famas.damdelt,
				   player->weapon.famas.damrec,
				   player->weapon.famas.dratio);

	weaponkillsort(player->weapon.g3a3.rank,
				   player->weapon.g3a3.name,
				   player->weapon.g3a3.kills,
				   player->weapon.g3a3.deaths,
				   player->weapon.g3a3.sui,
				   player->weapon.g3a3.kdp,
				   player->weapon.g3a3.kdr,
				   player->weapon.g3a3.pkills,
				   player->weapon.g3a3.damdelt,
				   player->weapon.g3a3.damrec,
				   player->weapon.g3a3.dratio);

	weaponkillsort(player->weapon.g36e.rank,
				   player->weapon.g36e.name,
				   player->weapon.g36e.kills,
				   player->weapon.g36e.deaths,
				   player->weapon.g36e.sui,
				   player->weapon.g36e.kdp,
				   player->weapon.g36e.kdr,
				   player->weapon.g36e.pkills,
				   player->weapon.g36e.damdelt,
				   player->weapon.g36e.damrec,
				   player->weapon.g36e.dratio);

	weaponkillsort(player->weapon.m16.rank,
				   player->weapon.m16.name,
				   player->weapon.m16.kills,
				   player->weapon.m16.deaths,
				   player->weapon.m16.sui,
				   player->weapon.m16.kdp,
				   player->weapon.m16.kdr,
				   player->weapon.m16.pkills,
				   player->weapon.m16.damdelt,
				   player->weapon.m16.damrec,
				   player->weapon.m16.dratio);

	weaponkillsort(player->weapon.m82.rank,
				   player->weapon.m82.name,
				   player->weapon.m82.kills,
				   player->weapon.m82.deaths,
				   player->weapon.m82.sui,
				   player->weapon.m82.kdp,
				   player->weapon.m82.kdr,
				   player->weapon.m82.pkills,
				   player->weapon.m82.damdelt,
				   player->weapon.m82.damrec,
				   player->weapon.m82.dratio);

	weaponkillsort(player->weapon.m60.rank,
				   player->weapon.m60.name,
				   player->weapon.m60.kills,
				   player->weapon.m60.deaths,
				   player->weapon.m60.sui,
				   player->weapon.m60.kdp,
				   player->weapon.m60.kdr,
				   player->weapon.m60.pkills,
				   player->weapon.m60.damdelt,
				   player->weapon.m60.damrec,
				   player->weapon.m60.dratio);

	weaponkillsort(player->weapon.m79.rank,
				   player->weapon.m79.name,
				   player->weapon.m79.kills,
				   player->weapon.m79.deaths,
				   player->weapon.m79.sui,
				   player->weapon.m79.kdp,
				   player->weapon.m79.kdr,
				   player->weapon.m79.pkills,
				   player->weapon.m79.damdelt,
				   player->weapon.m79.damrec,
				   player->weapon.m79.dratio);

	weaponkillsort(player->weapon.claymore.rank,
				   player->weapon.claymore.name,
				   player->weapon.claymore.kills,
				   player->weapon.claymore.deaths,
				   player->weapon.claymore.sui,
				   player->weapon.claymore.kdp,
				   player->weapon.claymore.kdr,
				   player->weapon.claymore.pkills,
				   player->weapon.claymore.damdelt,
				   player->weapon.claymore.damrec,
				   player->weapon.claymore.dratio);

	weaponkillsort(player->weapon.frag.rank,
				   player->weapon.frag.name,
				   player->weapon.frag.kills,
				   player->weapon.frag.deaths,
				   player->weapon.frag.sui,
				   player->weapon.frag.kdp,
				   player->weapon.frag.kdr,
				   player->weapon.frag.pkills,
				   player->weapon.frag.damdelt,
				   player->weapon.frag.damrec,
				   player->weapon.frag.dratio);

	weaponkillsort(player->weapon.stg24.rank,
				   player->weapon.stg24.name,
				   player->weapon.stg24.kills,
				   player->weapon.stg24.deaths,
				   player->weapon.stg24.sui,
				   player->weapon.stg24.kdp,
				   player->weapon.stg24.kdr,
				   player->weapon.stg24.pkills,
				   player->weapon.stg24.damdelt,
				   player->weapon.stg24.damrec,
				   player->weapon.stg24.dratio);

	weaponkillsort(player->weapon.m203.rank,
				   player->weapon.m203.name,
				   player->weapon.m203.kills,
				   player->weapon.m203.deaths,
				   player->weapon.m203.sui,
				   player->weapon.m203.kdp,
				   player->weapon.m203.kdr,
				   player->weapon.m203.pkills,
				   player->weapon.m203.damdelt,
				   player->weapon.m203.damrec,
				   player->weapon.m203.dratio);

	weaponkillsort(player->weapon.uzi.rank,
				   player->weapon.uzi.name,
				   player->weapon.uzi.kills,
				   player->weapon.uzi.deaths,
				   player->weapon.uzi.sui,
				   player->weapon.uzi.kdp,
				   player->weapon.uzi.kdr,
				   player->weapon.uzi.pkills,
				   player->weapon.uzi.damdelt,
				   player->weapon.uzi.damrec,
				   player->weapon.uzi.dratio);

	weaponkillsort(player->weapon.pkm.rank,
				   player->weapon.pkm.name,
				   player->weapon.pkm.kills,
				   player->weapon.pkm.deaths,
				   player->weapon.pkm.sui,
				   player->weapon.pkm.kdp,
				   player->weapon.pkm.kdr,
				   player->weapon.pkm.pkills,
				   player->weapon.pkm.damdelt,
				   player->weapon.pkm.damrec,
				   player->weapon.pkm.dratio);

	weaponkillsort(player->weapon.ak74.rank,
				   player->weapon.ak74.name,
				   player->weapon.ak74.kills,
				   player->weapon.ak74.deaths,
				   player->weapon.ak74.sui,
				   player->weapon.ak74.kdp,
				   player->weapon.ak74.kdr,
				   player->weapon.ak74.pkills,
				   player->weapon.ak74.damdelt,
				   player->weapon.ak74.damrec,
				   player->weapon.ak74.dratio);

	weaponkillsort(player->weapon.svd.rank,
				   player->weapon.svd.name,
				   player->weapon.svd.kills,
				   player->weapon.svd.deaths,
				   player->weapon.svd.sui,
				   player->weapon.svd.kdp,
				   player->weapon.svd.kdr,
				   player->weapon.svd.pkills,
				   player->weapon.svd.damdelt,
				   player->weapon.svd.damrec,
				   player->weapon.svd.dratio);

	weaponkillsort(player->weapon.gp25.rank,
				   player->weapon.gp25.name,
				   player->weapon.gp25.kills,
				   player->weapon.gp25.deaths,
				   player->weapon.gp25.sui,
				   player->weapon.gp25.kdp,
				   player->weapon.gp25.kdr,
				   player->weapon.gp25.pkills,
				   player->weapon.gp25.damdelt,
				   player->weapon.gp25.damrec,
				   player->weapon.gp25.dratio);

	weaponkillsort(player->weapon.ssg3000.rank,
				   player->weapon.ssg3000.name,
				   player->weapon.ssg3000.kills,
				   player->weapon.ssg3000.deaths,
				   player->weapon.ssg3000.sui,
				   player->weapon.ssg3000.kdp,
				   player->weapon.ssg3000.kdr,
				   player->weapon.ssg3000.pkills,
				   player->weapon.ssg3000.damdelt,
				   player->weapon.ssg3000.damrec,
				   player->weapon.ssg3000.dratio);

	weaponkillsort(player->weapon.weapmortar.rank,
				   player->weapon.weapmortar.name,
				   player->weapon.weapmortar.kills,
				   player->weapon.weapmortar.deaths,
				   player->weapon.weapmortar.sui,
				   player->weapon.weapmortar.kdp,
				   player->weapon.weapmortar.kdr,
				   player->weapon.weapmortar.pkills,
				   player->weapon.weapmortar.damdelt,
				   player->weapon.weapmortar.damrec,
				   player->weapon.weapmortar.dratio);

	weaponkillsort(player->weapon.spark_shower.rank,
				   player->weapon.spark_shower.name,
				   player->weapon.spark_shower.kills,
				   player->weapon.spark_shower.deaths,
				   player->weapon.spark_shower.sui,
				   player->weapon.spark_shower.kdp,
				   player->weapon.spark_shower.kdr,
				   player->weapon.spark_shower.pkills,
				   player->weapon.spark_shower.damdelt,
				   player->weapon.spark_shower.damrec,
				   player->weapon.spark_shower.dratio);

	weaponkillsort(player->weapon.monster_mortar.rank,
				   player->weapon.monster_mortar.name,
				   player->weapon.monster_mortar.kills,
				   player->weapon.monster_mortar.deaths,
				   player->weapon.monster_mortar.sui,
				   player->weapon.monster_mortar.kdp,
				   player->weapon.monster_mortar.kdr,
				   player->weapon.monster_mortar.pkills,
				   player->weapon.monster_mortar.damdelt,
				   player->weapon.monster_mortar.damrec,
				   player->weapon.monster_mortar.dratio);

	weaponkillsort(player->weapon.func_tank.rank,
				   player->weapon.func_tank.name,
				   player->weapon.func_tank.kills,
				   player->weapon.func_tank.deaths,
				   player->weapon.func_tank.sui,
				   player->weapon.func_tank.kdp,
				   player->weapon.func_tank.kdr,
				   player->weapon.func_tank.pkills,
				   player->weapon.func_tank.damdelt,
				   player->weapon.func_tank.damrec,
				   player->weapon.func_tank.dratio);

	weaponkillsort(player->weapon.env_explosion.rank,
				   player->weapon.env_explosion.name,
				   player->weapon.env_explosion.kills,
				   player->weapon.env_explosion.deaths,
				   player->weapon.env_explosion.sui,
				   player->weapon.env_explosion.kdp,
				   player->weapon.env_explosion.kdr,
				   player->weapon.env_explosion.pkills,
				   player->weapon.env_explosion.damdelt,
				   player->weapon.env_explosion.damrec,
				   player->weapon.env_explosion.dratio);

	weaponkillsort(player->weapon.concussion.rank,
				   player->weapon.concussion.name,
				   player->weapon.concussion.kills,
				   player->weapon.concussion.deaths,
				   player->weapon.concussion.sui,
				   player->weapon.concussion.kdp,
				   player->weapon.concussion.kdr,
				   player->weapon.concussion.pkills,
				   player->weapon.concussion.damdelt,
				   player->weapon.concussion.damrec,
				   player->weapon.concussion.dratio);

	weaponkillsort(player->weapon.ammobox.rank,
				   player->weapon.ammobox.name,
				   player->weapon.ammobox.kills,
				   player->weapon.ammobox.deaths,
				   player->weapon.ammobox.sui,
				   player->weapon.ammobox.kdp,
				   player->weapon.ammobox.kdr,
				   player->weapon.ammobox.pkills,
				   player->weapon.ammobox.damdelt,
				   player->weapon.ammobox.damrec,
				   player->weapon.ammobox.dratio);
	return;
}


/*--------------------------------------------------------------------------------*/
// PARSE HTML FILE TEMPLATES AND OUTPUT STATISTICS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// Reads Link List Then Writes Out HTML Files for Players Ranks
void buildHTML(string html) {

		 if (index_html_number == 1) index1 << html << endl;
	else if (index_html_number == 2) index2 << html << endl;
	else if (index_html_number == 3) index3 << html << endl;
	else if (index_html_number == 4) index4 << html << endl;
	else if (index_html_number == 5) index5 << html << endl;
	else if (index_html_number == 6) index6 << html << endl;
	else if (index_html_number == 7) index7 << html << endl;
	return;
}


/*--------------------------------------------------------------------------------*/
// Reads Link List Then Writes Out HTML Files for Players Stats
void buildHTML2(string html) {

    string temp = html;

    struct ListItem3 *last;
	ListItem3 *item = new ListItem3;
	if ( !item ) {
    	printf ("Malloc Failed Linke List 3 PlayerName.html \n");
        return;
    }

	strcpy(item->html,temp.c_str());
	item->next = 0;

	if ( MyList3 == 0 ) {
    	MyList3 = item;
        return;
    }

	for( last = MyList3 ; last->next != 0 ; last = last->next );
	last->next = item;
}


/*--------------------------------------------------------------------------------*/
// Clears Link List and Free's Current Memory
void clearHTML2(void) {

    struct ListItem3 *p,*next;
	if ( MyList3 == 0) {
    	return;
    }

    for(p = MyList3 ; p !=0 ; p = next ) {
		next = p->next;
		delete (p);
	}
	MyList3 = 0;
}

/*--------------------------------------------------------------------------------*/
// Write out the HTML FILE from Link List
void writeHTMLplayer(int rank) {

	char temp[350];
    sprintf(temp, "%s%i.html", HTMLPATH,rank);
    string name = (temp);

	struct ListItem3 *p;

	ofstream outStream2;
	outStream2.open( name.c_str(), ofstream::out | ofstream::trunc );
	if (!outStream2.is_open()) {
		cout << "\n\nError creating PlayersName.html for Writing " << name <<endl;
		clearHTML2();
		return;
	}

	for ( p= MyList3 ; p != 0 ; p = p->next ) { outStream2 << p->html << endl; }

	outStream2.close();
	clearHTML2();
	return;
}

/*--------------------------------------------------------------------------------*/
// Processes HTML for Write out to the Link List
void checkHTMLrank(string htmlline, char *tplayer, int rank) {

	struct ListItem12 *pl;

	string temp = htmlline;
	string temp2;

	// Start String Processing Below
	int id1 = -1;

	// Do Testing if player name is in list, Update it with New Data
	for ( pl = myList12 ; pl != 0 ; pl = pl->next ) {
		if (strcmp(pl->player.name,tplayer) == 0) {
			id1 = temp.find('$', 0);  // Find the Begining of Each Variable $
			if (id1 == -1) {
				buildHTML(temp);
				return;
			}
			// Here Stars Parsing of Every Variable in the RankTop.HTML And Templates..
			while (id1 != string::npos) {           // Not End of String
				id1 = temp.find("timedate", 0);
				if (id1 != -1) {
					char DateTime[100];
					sprintf(DateTime,"%s %s",szDateFormat,szTimeFormat);
					temp.replace(id1-1,9,DateTime);
					buildHTML(temp);
					return;
				}
				id1 = temp.find("server.ip", 0);
				if (id1 != -1) {
					temp.replace(id1-1,10,SERVERIP);
					buildHTML(temp);
					return;
				}
				id1 = temp.find("webpage", 0);
				if (id1 != -1) {
					temp.replace(id1-1,8,WEBPAGE);
					id1 = temp.find("server.name", 0);
						if (id1 != -1) {
							temp.replace(id1-1,12,SERVERNAME);
							buildHTML(temp);
						return;
					}
					buildHTML(temp);
					return;
				}
				id1 = temp.find("server.name", 0);
				if (id1 != -1) {
					temp.replace(id1-1,12,SERVERNAME);
					buildHTML(temp);
					return;
				}
				id1 = temp.find("admin.email", 0);
				if (id1 != -1) {
					temp.replace(id1-1,12,ADMINEMAIL);
					id1 = temp.find("admin.name", 0);
					if (id1 != -1) {
						temp.replace(id1-1,11,ADMINNAME);
						buildHTML(temp);
						return;
					}
					buildHTML(temp);
					return;
				}
				id1 = temp.find("admin.name", 0);
				if (id1 != -1) {
					temp.replace(id1-1,11,ADMINNAME);
					buildHTML(temp);
					return;
				}
				id1 = temp.find("player.rank", 0);
				if (id1 != -1) {
					char idx[10];
					//player.rank = rank;
					//writep(&player,index);
					sprintf(idx, "%d", pl->player.rank);
					temp.replace(id1-1,12,idx);
					id1 = temp.find("player.name", 0);
					if (id1 != -1) {
						temp.replace(id1-1,12,pl->player.name);
						buildHTML(temp);
						return;
					}
					buildHTML(temp);
					return;
				}
				id1 = temp.find("player.name", 0);
				if (id1 != -1) {
					temp.replace(id1-1,12,pl->player.name);
					buildHTML(temp);
					return;
				}
				id1 = temp.find("player.kills", 0);
				if (id1 != -1) {
					char pk[10];
					long number = pl->player.kills;
					sprintf(pk, "%d", number);
					temp.replace(id1-1,13,pk);

					id1 = temp.find("player.damdelt", 0);
					if (id1 != -1) {
						char ps[10];
						long number = pl->player.damdelt;
						sprintf(ps, "%d", number);
						temp.replace(id1-1,15,ps);
						buildHTML(temp);
						return;
					}
					buildHTML(temp);
					return;
				}
				id1 = temp.find("player.deaths", 0);
				if (id1 != -1) {
					char pd[10];
					long number = pl->player.deaths;
					sprintf(pd, "%d", number);
					temp.replace(id1-1,14,pd);

					id1 = temp.find("player.damrec", 0);
					if (id1 != -1) {
						char ps[10];
						long number = pl->player.damrec;
						sprintf(ps, "%d", number);
						temp.replace(id1-1,14,ps);
						buildHTML(temp);
						return;
					}
					buildHTML(temp);
					return;
				}
				id1 = temp.find("player.sui", 0);
				if (id1 != -1) {
					char ps[10];
					long number = pl->player.sui;
					sprintf(ps, "%d", number);
					temp.replace(id1-1,16,ps);

					id1 = temp.find("player.dambleed", 0);
					if (id1 != -1) {
						char ps[10];
						int number = pl->player.dambleed;
						sprintf(ps, "%d", number);
						temp.replace(id1-1,16,ps);
						buildHTML(temp);
						return;
					}
					buildHTML(temp);
					return;
				}
				id1 = temp.find("player.kdp", 0);
				if (id1 != -1) {
					char pkdp[10];
					double number = pl->player.kdp;
					sprintf(pkdp, "%.1f", number);
					temp.replace(id1-1,11,pkdp);
					buildHTML(temp);
					return;
				}
				id1 = temp.find("player.kdr", 0);
				if (id1 != -1) {
					temp.replace(id1-1,11,pl->player.kdr);
					buildHTML(temp);
					return;
				}
				id1 = temp.find("player.damdelt", 0);
				if (id1 != -1) {
					char ps[10];
					long number = pl->player.damdelt;
					sprintf(ps, "%d", number);
					temp.replace(id1-1,15,ps);
					buildHTML(temp);
					return;
				}
				id1 = temp.find("player.damrec", 0);
				if (id1 != -1) {
					char ps[10];
					long number = pl->player.damrec;
					sprintf(ps, "%d", number);
					temp.replace(id1-1,14,ps);
					buildHTML(temp);
					return;
				}
				id1 = temp.find("player.dratio", 0);
				if (id1 != -1) {
					temp.replace(id1-1,14,pl->player.dratio);
					buildHTML(temp);
					return;
				}
				id1 = temp.find("player.dambleed", 0);
				if (id1 != -1) {
					char ps[10];
					long number = pl->player.dambleed;
					sprintf(ps, "%d", number);
					temp.replace(id1-1,16,ps);
					buildHTML(temp);
					return;
				}
				id1 = temp.find("maxrank", 0);
				if (id1 != -1) {
					char mr[10];
					int number = MAXRANK;
					sprintf(mr, "%d", number);
					temp.replace(id1-1,8,mr);
					id1 = temp.find("server.name", 0);
					if (id1 != -1) {
						temp.replace(id1-1,12,SERVERNAME);
					}
					buildHTML(temp);
					return;
				}
				buildHTML(temp);
				return;
			}// End of While
		}// End of IF
	}// End of FOR Loop
	return;
}


/*--------------------------------------------------------------------------------*/
// Parses HTML and Replaces $Variables with Values for Write out to the Link List
void checkHTMLplayer2(string htmlline,        // HTML Data String
                      char *tplayer,          // Current Player Name
                      int rank,               // Weapons Rank
                      WEAPONREC * tweapon,    // Handle to Top Weapon
                      WEAPONREC * weapon) {   // Handle to Weapon Ranking

    struct ListItem12 *pl;

    string temp = htmlline;
	string temp2;
	int id1 = -1;


	// Do Testing if player name is in list, Update it with New Data
	for ( pl = myList12 ; pl != 0 ; pl = pl->next ) {
		if (strcmp(pl->player.name,tplayer) == 0) {
			id1 = temp.find('$', 0);
			if (id1 == -1) {
				buildHTML2(temp);
				return;
			}
			// Here Stars Parsing of Every Variable in the PlayerStats.HTML
			while (id1 != string::npos) {
				id1 = temp.find("timedate", 0);
				if (id1 != -1) {
					char DateTime[30];
					sprintf(DateTime,"%s %s",szDateFormat,szTimeFormat);
					temp.replace(id1-1,9,DateTime);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("server.ip", 0);
				if (id1 != -1) {
					char ServerIP[20];
					sprintf(ServerIP,"%s",SERVERIP);
					temp.replace(id1-1,10,ServerIP);
					buildHTML2(temp);
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
						buildHTML2(temp);
						return;
					}
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("server.name", 0);
				if (id1 != -1) {
					char ServerName[100];
					sprintf(ServerName,"%s",SERVERNAME);
					temp.replace(id1-1,12,ServerName);
					buildHTML2(temp);
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
						buildHTML2(temp);
						return;
					}
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("admin.name", 0);
				if (id1 != -1) {
					char AdminName[100];
					sprintf(AdminName,"%s",ADMINNAME);
					temp.replace(id1-1,11,AdminName);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("player.rank", 0);
				if (id1 != -1) {
					char idx[10];
					int rank = pl->player.rank;
					sprintf(idx, "%d", rank);
					temp.replace(id1-1,12,idx);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("player.name", 0);
				if (id1 != -1) {
					temp.replace(id1-1,12,pl->player.name);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("player.kills", 0);
				if (id1 != -1) {
					char pk[10];
					long number = pl->player.kills;
					sprintf(pk, "%d", number);
					temp.replace(id1-1,13,pk);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("player.deaths", 0);
				if (id1 != -1) {
					char pd[10];
					long number = pl->player.deaths;
					sprintf(pd, "%d", number);
					temp.replace(id1-1,14,pd);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("player.sui", 0);
				if (id1 != -1) {
					char ps[10];
					long number = pl->player.sui;
					sprintf(ps, "%d", number);
					temp.replace(id1-1,16,ps);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("player.kdp", 0);
				if (id1 != -1) {
					char pkdp[10];
					double number = pl->player.kdp;
					sprintf(pkdp, "%.1f", number);
					temp.replace(id1-1,11,pkdp);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("player.kdr", 0);
				if (id1 != -1) {
					temp.replace(id1-1,11,pl->player.kdr);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("player.damdelt", 0);
				if (id1 != -1) {
					char ps[10];
					long number = pl->player.damdelt;
					sprintf(ps, "%d", number);
					temp.replace(id1-1,15,ps);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("player.damrec", 0);
				if (id1 != -1) {
					char ps[10];
					long number = pl->player.damrec;
					sprintf(ps, "%d", number);
					temp.replace(id1-1,14,ps);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("player.dratio", 0);
				if (id1 != -1) {
					temp.replace(id1-1,14,pl->player.dratio);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("player.dambleed", 0);
				if (id1 != -1) {
					char ps[10];
					long number = pl->player.dambleed;
					sprintf(ps, "%d", number);
					temp.replace(id1-1,16,ps);
					buildHTML2(temp);
					return;
				}
				//---------------------------------------------------------------------------
				// Scan Instances - Weapons - Sorted By Most Kills Here
				id1 = temp.find("weapon.rank", 0);
				if (id1 != -1) {
					char rank[10];
					int number = weapon->rank;
					sprintf(rank, "%d", number);
					temp.replace(id1-1,12,rank);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("weapon.name", 0);
				if (id1 != -1) {
					temp.replace(id1-1,12,weapon->name);

					id1 = temp.find("weapon.name", 0);
					if (id1 != -1) {
						temp.replace(id1-1,12,weapon->name);
					}
					id1 = temp.find("weapon.name", 0);
					if (id1 != -1) {
						temp.replace(id1-1,12,weapon->name);
					}
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("weapon.kills", 0);
				if (id1 != -1) {
					char pkdp[10];
					long number = weapon->kills;
					sprintf(pkdp, "%d", number);
					temp.replace(id1-1,13,pkdp);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("weapon.deaths", 0);
				if (id1 != -1) {
					char pkdp[10];
					long number = weapon->deaths;
					sprintf(pkdp, "%d", number);
					temp.replace(id1-1,14,pkdp);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("weapon.sui", 0);
				if (id1 != -1) {
					char pkdp[10];
					long number = weapon->sui;
					sprintf(pkdp, "%d", number);
					temp.replace(id1-1,11,pkdp);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("weapon.pkills", 0);
				if (id1 != -1) {
					char pkdp[10];
					double number = weapon->pkills;
					sprintf(pkdp, "%.1f", number);
					temp.replace(id1-1,14,pkdp);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("weapon.kdr", 0);
				if (id1 != -1) {
					temp.replace(id1-1,11,weapon->kdr);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("weapon.damdelt", 0);
				if (id1 != -1) {
					char ps[10];
					long number = weapon->damdelt;
					sprintf(ps, "%d", number);
					temp.replace(id1-1,15,ps);
					buildHTML2(temp);
					return;
				}
				id1 = temp.find("weapon.damrec", 0);
				if (id1 != -1) {
					char ps[10];
					long number = weapon->damrec;
					sprintf(ps, "%d", number);
					temp.replace(id1-1,14,ps);
					buildHTML2(temp);
					return;
				}
				buildHTML2(temp);
				return;
			} // End of While
		} // End of Name Match
	} // End of For Loop For Processing Player Data
	return;
}

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerTop.HTML For Multiple Runs
void buildHTMLplayertop(string html) {

    string temp = html;

	struct ListItem5 *last;
	ListItem5 *item = new ListItem5;
	if ( !item ) {
		printf ("Malloc Failed \n");
		return;
	}

	strcpy(item->html,temp.c_str());
	item->next = 0;

	if ( MyList5 == 0 ) {
		MyList5 = item;
		return;
	}

	for( last = MyList5 ; last->next != 0 ; last = last->next );
	last->next = item;
	return;
}

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerRow1.HTML For Multiple Runs
void buildHTMLplayerrow1(string html) {

	string temp = html;

	struct ListItem6 *last;
	ListItem6 *item = new ListItem6;
	if ( !item ) {
		printf ("Malloc Failed \n");
		return;
	}

	strcpy(item->html,temp.c_str());
	item->next = 0;

	if ( MyList6 == 0 ) {
		MyList6 = item;
		return;
	}

	for( last = MyList6 ; last->next != 0 ; last = last->next );
	last->next = item;
	return;
}

/*--------------------------------------------------------------------------------*/
// Link List Reading in a Storing the PlayerRow2.HTML For Multiple Runs
void buildHTMLplayerrow2(string html) {

    string temp = html;

    struct ListItem7 *last;
	ListItem7 *item = new ListItem7;
	if ( !item ) {
    	printf ("Malloc Failed \n");
        return;
    }

	strcpy(item->html,temp.c_str()); // insert 1st HTML Line / Convert to C String
	item->next = 0;

	if ( MyList7 == 0 ) {
    	MyList7 = item;
        return;
    }

	for( last = MyList7 ; last->next != 0 ; last = last->next );
	last->next = item;
}

/*--------------------------------------------------------------------------------*/
// Read Rank.html Templates into memory for fast parsing of all html creation
void loadHTMLplayer(void) {

	string name  = "PlayerTop.html";
	string name1 = "PlayerRow-1.html";
	string name2 = "PlayerRow-2.html";

	string TPATH = PATH;

	#ifdef _WIN32
	name  = TPATH+"Templates\\"+name;   // Adds Path to Log Filename
	name1 = TPATH+"Templates\\"+name1;  // Adds Path to Log Filename
	name2 = TPATH+"Templates\\"+name2;  // Adds Path to Log Filename
	#else
	name  = TPATH+"Templates/"+name;   // Adds Path to Log Filename
	name1 = TPATH+"Templates/"+name1;  // Adds Path to Log Filename
	name2 = TPATH+"Templates/"+name2;  // Adds Path to Log Filename
	#endif

	string HTMLDATA;  // Holds Each Line Read in from the Template

	// Process Inital RankTop.HTML
	ifstream inStream1;
	inStream1.open( name.c_str() );
	if (!inStream1.is_open()) {
		cout << "\n\nError Opening PlayerTop.html for Parsing" << name <<endl;
		return;
	}

	// Start Processing RankTop.HTML
	for (;;) {
		getline(inStream1,HTMLDATA);
		buildHTMLplayertop(HTMLDATA);
		if(inStream1.eof()) {
			inStream1.close();
			break;
		}
	}

	// Process Inital PlayerRow1.HTML
	ifstream inStream2;
	inStream2.open( name1.c_str() );
	if (!inStream2.is_open()) {
		cout << "\n\nError Opening PlayerRow1.html for Parsing" << name <<endl;
		return;
	}

	for (;;) { // Process and Load PlayerRow1.HTML
		getline(inStream2,HTMLDATA);
		buildHTMLplayerrow1(HTMLDATA);
		if(inStream2.eof()) {
			inStream2.close();
			break;
		}
	}

	// Process PlayerRow2.HTML
	ifstream inStream3;
	inStream3.open( name2.c_str() );
	if (!inStream3.is_open()) {
		cout << "\n\nError Opening PlayerRow2.html for Parsing" << name <<endl;
		return;
	}

	for (;;) { // Process and Load PlayerRow2.HTML
		getline(inStream3,HTMLDATA);
		buildHTMLplayerrow2(HTMLDATA);
		if(inStream3.eof()) {
			inStream3.close();
			break;
		}
	}
	return;
}

/*--------------------------------------------------------------------------------*/
// Read Rank.html and setup for parsing.
void readHTMLplayer(char * playername) {

	struct ListItem12 *pl;

	WEAPONREC tweapon;      // Holds #1 Ranked Weapon / Players Top / Best Weapon
	WEAPONREC weapon;       // All Weapon For Ranking By # of Kills


	// Do Testing if player name is in list, Update it with New Data
	for ( pl = myList12 ; pl != 0 ; pl = pl->next ) {
		if (strcmp(pl->player.name,playername) == 0) {
			calcweapons(&pl->player);

			// Set Rank For Each Weapon
			struct ListItem4 *p;

			int rank = 0;
			for ( p= MyList4 ; p != 0 ; p = p->next ) { p->rank = ++rank; }

			p = MyList4; // Reassign / Reset Listing Instance of Link List

			// For Rotating Playerrow-1 and -2
			int count = 0;   // Counter for Alterating Top 10 Places..
			int mod   = 2;   // Modulious

			string HTMLDATA; // Holds Each Line Read in from the Log File

			// Gets Very First Weapon in Link List and Assigns it to The Top Used Weapon Spot
			// { Not in use anymore, but still working,, just need to readd to HTML Templates }
			tweapon.rank = p->rank;
			strcpy(tweapon.name, p->name);
			tweapon.kills = p->kills;
			tweapon.deaths = p->deaths;
			tweapon.sui = p->sui;
			tweapon.kdp = p->kdp;
			strcpy(tweapon.kdr,p->kdr);
			tweapon.pkills = p->pkills;
			tweapon.damdelt = p->damdelt;
			tweapon.damrec = p->damrec;

			// Pointers to Link Lists..
			struct ListItem5 *p5; // Holds HTML Templates PlayerTOP.HTML
			struct ListItem6 *p6; // Holds HTML Templates PlayerRow-1.HTML
			struct ListItem7 *p7; // Holds HTML Templates PlayerRow-2.HTML

			// Process PlayerTop.HTML
			for (;;) {
				for ( p5 = MyList5 ; p5 != 0 ; p5 = p5->next ) {
					// Prase's the string And splits for Processing
					HTMLDATA = (p5->html);
					checkHTMLplayer2(HTMLDATA,      // HTML String
							 pl->player.name,		// Players Name
							 pl->player.rank,		// Players Rank
							 &tweapon,       		// Players Top Weapon
							 &weapon);       		// Players Remaining Weapons...
				}
				++count; // Incriment Count for Mod...
				break;   // Exit Loop on End of File
			}
				// Start Processing Playerrow-1.HTML
			bool DONE = false;
			while(DONE == false) {
				if (count % mod == 1) {
					for (;;) {  // tests if a valid file was found to read from
						if (p == 0) {
							RemoveListWeapon();
							return;
						}
						weapon.rank = p->rank;
						strcpy(weapon.name, p->name);
						weapon.kills = p->kills;
						weapon.deaths = p->deaths;
						weapon.sui = p->sui;
						weapon.kdp = p->kdp;
						strcpy(weapon.kdr,p->kdr);
						weapon.pkills = p->pkills;
						weapon.damdelt = p->damdelt;
						weapon.damrec = p->damrec;

						for ( p6 = MyList6 ; p6 != 0 ; p6 = p6->next ) {
							// Prase's the string And splits for Processing
							HTMLDATA = (p6->html);
							checkHTMLplayer2(HTMLDATA,      // HTML String
									 pl->player.name,		// Players Name
									 pl->player.rank,		// Players Rank
									 &tweapon,       		// Players Top Weapon
									 &weapon);       		// Players Remaining Weapons...
						}
						p = p->next; // Goto Next Weapon in List
						++count;     // Incriment Count for Mod...
						break;       // Exit Loop on End of File
						}
					}
				//Process PlayerRow-2.HTML
				if (count % mod == 0) {
					for (;;) { // tests if a valid file was found to read from
						if (p == 0) {
							RemoveListWeapon();
							return;
						}
						weapon.rank = p->rank;
						strcpy(weapon.name, p->name);
						weapon.kills = p->kills;
						weapon.deaths = p->deaths;
						weapon.sui = p->sui;
						weapon.kdp = p->kdp;
						strcpy(weapon.kdr,p->kdr);
						weapon.pkills = p->pkills;
						weapon.damdelt = p->damdelt;
						weapon.damrec = p->damrec;

						// Prase's the string And splits for Processing
						for ( p7 = MyList7 ; p7 != 0 ; p7 = p7->next ) {
							// Prase's the string And splits for Processing
							HTMLDATA = (p7->html);
							checkHTMLplayer2(HTMLDATA,       // HTML String
									 pl->player.name,// Players Name
									 pl->player.rank,// Players Rank
									 &tweapon,       // Players Top Weapon
									 &weapon);       // Players Remaining Weapons...
						}
						p = p->next;             // Goto Next Weapon in List
						++count;                 // Incriment Count for Mod...
						break;                   // Exit Loop on End of File
					}
				}
			} // End While Loop
			return;
		} // And If Name Match's
	} // End For Loop for Player Link List
	return;
}


/*--------------------------------------------------------------------------------*/
// Does the Inital Top Rankings
void ranktop(int num) {

	string name;
	if 		(num == 1) name = "RankTop.html";
	else if (num == 2) name = "RankTop2.html";
	else if (num == 3) name = "RankTop3.html";
	else if (num == 4) name = "RankTop4.html";
	else if (num == 5) name = "RankTop5.html";
	else if (num == 6) name = "RankTop6.html";
	else if (num == 7) name = "RankTop7.html";

	string TPATH = PATH;

	#ifdef _WIN32
	name  = TPATH+"Templates\\"+name;            // Adds Path to Log Filename
	#else
	name  = TPATH+"Templates/"+name;            // Adds Path to Log Filename
	#endif


	// Process Inital RankTop.HTML right away.. Next Process Rows With Player Info
	ifstream inStream1;
	inStream1.open( name.c_str() );
	if (!inStream1.is_open()) {
		cout << "\n\nError Opening Rank.html for Parsing" << name <<endl;
		return;
	}
	string HTMLDATA;
	for (;;) {
		getline(inStream1,HTMLDATA);
		// Prase's the string And splits for Processing
		buildHTML(HTMLDATA);
		if(inStream1.eof()) {
			inStream1.close();
			break;
		}
	}
}


/*--------------------------------------------------------------------------------*/
// Read Rank.html and setup for parsing.
void readHTMLrank() {

	//Sets up Template HTML Files for Reading
	string name1 = "RankTop10-1.html";
	string name2 = "RankTop10-2.html";
	string name0 = "RankTop10.html";
	string name3 = "RankRest-1.html";
	string name4 = "RankRest-2.html";
	string name5 = "Footer.html";

	string HTMLDATA2;
	string TPATH = PATH;

	#ifdef _WIN32
	name1 = TPATH+"Templates\\"+name1;          // Adds Path to Log Filename
	name2 = TPATH+"Templates\\"+name2;          // Adds Path to Log Filename
	name0 = TPATH+"Templates\\"+name0;          // Adds Path to Log Filename
	name3 = TPATH+"Templates\\"+name3;          // Adds Path to Log Filename
	name4 = TPATH+"Templates\\"+name4;          // Adds Path to Log Filename
	name5 = TPATH+"Templates\\"+name5;          // Adds Path to Log Filename
	#else
	name1 = TPATH+"Templates/"+name1;           // Adds Path to Log Filename
	name2 = TPATH+"Templates/"+name2;           // Adds Path to Log Filename
	name0 = TPATH+"Templates/"+name0;           // Adds Path to Log Filename
	name3 = TPATH+"Templates/"+name3;           // Adds Path to Log Filename
	name4 = TPATH+"Templates/"+name4;           // Adds Path to Log Filename
	name5 = TPATH+"Templates/"+name5;           // Adds Path to Log Filename
	#endif

	int count = 1; // Counter for Alterating Top 10 Places..
	int mod   = 2; // Modulious to Alternate Color Rows

	struct ListItem12 *pl;


	// Do Testing if player name is in list, Update it with New Data
	for ( pl = myList12 ; pl != 0 ; pl = pl->next ) {
		while(count <= 10) {  // Process RankTop10-1.html & RankTop10-2.html
			if (count % mod == 1) {
				ifstream inStream2;
				inStream2.open( name1.c_str() );
				if (!inStream2.is_open()) {
					cout << "\n\nError Opening RankTOP10-1.html for Parsing" << name1 <<endl;
					return;
				}
				string HTMLDATA;
				for (;;) { // tests if a valid file was found to read from
					getline(inStream2,HTMLDATA);
					if ( pl == 0) { // Max Number of Users in Rankings
						inStream2.close();
						return;
					}
					// Prase's the string And splits for Processing
					checkHTMLrank(HTMLDATA,pl->player.name,pl->player.rank);
					if(inStream2.eof()) {
						pl = pl->next;           // Sets to Next Link list Player
						++count;                 // Increment Count for Top 10
						--mod;                   // Modifyer for Switching Colums
						if (count == MAXRANK+1) {
							inStream2.close();
							return;
						}
						inStream2.close();       // Closes the file before exiting
						break;
					}
				}
			}
			if (count % mod == 0) {
				ifstream inStream3;
				inStream3.open( name2.c_str() );
				if (!inStream3.is_open()) {
					cout << "\n\nError Opening RankTOP10-1.html for Parsing" << name2 <<endl;
					return;
				}
				string HTMLDATA;
				for (;;) { // tests if a valid file was found to read from
					getline(inStream3,HTMLDATA);
					if (pl == 0) {
						inStream3.close();
						return;
					}
					// Prase's the string And splits for Processing
					checkHTMLrank(HTMLDATA,pl->player.name,pl->player.rank);
					if(inStream3.eof()) {
						pl = pl->next;
						++count;                 // Increment Count for Top 10
						++mod;                   // Modifyer for Switching Colums
						if (count == MAXRANK+1) {
							inStream3.close();
							return;
						}
						inStream3.close();       // Closes the file before exiting
						break;
					}
				}
			} // Endif
		} // End While Loop
		break;
        } // End For Loop

        bool DONE = false;
        // Process RankTop.HTML Inbetween Top and Rest Rankings
        ifstream inStreamT;
        inStreamT.open( name0.c_str() );
        if (!inStreamT.is_open()) {
                cout << "\n\nError Opening RankTop10.html for Parsing" << name0 <<endl;
                return;
        }

        for (;;) { // tests if a valid file was found to read from
			getline(inStreamT,HTMLDATA2);
			// Prase's the string And splits for Processing
			buildHTML(HTMLDATA2);
			if(inStreamT.eof()) {
				inStreamT.close();
				break;
			}
        }

        // Continue list where last one left off - Process RankRest Rows
        for ( ; pl != 0 ; pl = pl->next ) {
		if (count > 10) {
			while(DONE == false) {
				if (count % mod == 1) {
					ifstream inStream4;
					inStream4.open( name3.c_str() );
					if (!inStream4.is_open()) {
						cout << "\n\nError Opening RankRest-1.html for Parsing" << name3 <<endl;
						return;
					}
					string HTMLDATA;
					for (;;) { // tests if a valid file was found to read from
						getline(inStream4,HTMLDATA);
						if (pl == 0) {
							inStream4.close();
							return;
						}
						// Prase's the string And splits for Processing
						checkHTMLrank(HTMLDATA,pl->player.name,pl->player.rank);
						if(inStream4.eof()) {
							pl = pl->next;
							++count;                 // Increment Count for Top 10
							--mod;                   // Modifyer for Switching Colums
							if (count == MAXRANK+1) {
								inStream4.close();
								return;
							}
							inStream4.close();       // Closes the file before exiting
							break;
						}
					}
				}
				if (count % mod == 0) {
					ifstream inStream5;
					inStream5.open( name4.c_str() );
					if (!inStream5.is_open()) {
						cout << "\n\nError Opening RankRest-2.html for Parsing" << name4 <<endl;
						return;
					}
					string HTMLDATA;
					for (;;) { // tests if a valid file was found to read from
						getline(inStream5,HTMLDATA);
						if (pl == 0) {
							inStream5.close();
							return;
						}
						checkHTMLrank(HTMLDATA,pl->player.name,pl->player.rank);         // Prase's the string And splits for Processing
						if(inStream5.eof()) {
							pl = pl->next;
							++count;                 // Increment Count for Top 10
							++mod;                   // Modifyer for Switching Colums
							if (count == MAXRANK+1) {
								inStream5.close();
								return;
							}
							inStream5.close();       // Closes the file before exiting
							break;
						}
					}
				}
			} // End While Loop
        } // End If
        return;
	} // End PL FOR Loop
    return;
}


/*--------------------------------------------------------------------------------*/
// Adds Footer to Index.html
void footerHTMLrank() {

	string name  = "Footer.html";
	string name0 = "RankTop10.html";
	string TPATH = PATH;

	#ifdef _WIN32
	name  = TPATH+"Templates\\"+name;
	name0 = TPATH+"Templates\\"+name0;
	#else
	name  = TPATH+"Templates/"+name;
	name0 = TPATH+"Templates/"+name0;
	#endif

	// Add Border Between Ranks and Footer
	ifstream inStreamT;
	inStreamT.open( name0.c_str() );
	if (!inStreamT.is_open()) {
		cout << "\n\nError Opening RankTop10.html for Parsing" << name0 <<endl;
		return;
	}
	string HTMLDATA2;
	for (;;) { // tests if a valid file was found to read from
		getline(inStreamT,HTMLDATA2);
		// Prase's the string And splits for Processing
		buildHTML(HTMLDATA2);
		if(inStreamT.eof()) {
			inStreamT.close();
			break;
		}
	}

 	// Add Footer for Player Ranks
	ifstream inStream1;
	inStream1.open( name.c_str() );
	if (!inStream1.is_open()) {
		cout << "\n\nError Opening Footer.html for Parsing " << endl;
		return;
	}
	string HTMLDATA;
	for (;;) {
		getline(inStream1,HTMLDATA);
		buildHTML(HTMLDATA);
		if(inStream1.eof()) {
			inStream1.close();
			break;
		}
	}
	return;
}

/*--------------------------------------------------------------------------------*/
// Gets Player from Playerrank.dat and Setups Link List
void getplayerrank(int num) {

	PLAYERREC2  player;
	int idx = 0;

	while(readprank(&player,idx)) {
		playerrankeddata(&player, num);
		++idx;
	}
	return;
}

/*--------------------------------------------------------------------------------*/
// This Function will setups the players Rankings
void doplayersrankHTML() {

	clearall();
	char title[100] = "Creating HTML Top Player Rankings . . .";
	drawtop(title,11,0,20);

	double p1 = 0,  // Percentage Top
	       p2 = 0;  // Percentage Left

	init_index();	// Sets up Output Streams

	// Creates Sets of Index.html for Sorting by Statistic
	for (int i = 1; i < 8; i++) {

		index_html_number = i;  // Set for Index# Output

		clearallleft();
		p1 = compwkillpercent1(i,7);
			percenttop(p1);

		char text1[40];
		sprintf(text1,"Creating Index%i.html!",i);
		drawleft(text1,3,0);

		getplayerrank(i);	 // Sets up Link List
		ranktop(i);		 // Sets up Header with Kills Highlighted
		percentleft(30);
		readHTMLrank();          // Reads in Player Rank Templates Process Players Rankings
		percentleft(60);
		footerHTMLrank();        // Process HTML Footer
		RemoveList();            // Clear ListItem
		percentleft(100);
		char text3[40];
		sprintf(text3,"Completed OK! ");
		drawleft2(text3,9,0);

		#ifdef _WIN32
		Sleep(1000);
		#else
		system("sleep 1s");
		#endif
	}
	percenttop(100);
	init_index_clean(); // Close Output Streams
	#ifdef _WIN32
	Sleep(1000);
	#else
	system("sleep 1s");
	#endif
	return;
}

/*--------------------------------------------------------------------------------*/
// This Function will setup the a Link List, sort for And create The HTML STAT Files for All Players
void doplayersHTML() {

	clearall();
	char title[100] = "Creating HTML Player Statistics . . .";
	drawtop(title,11,0,21);
	getplayerrank(1);   // Get Players Sorted by Kills - Default
	loadHTMLplayer();   // Loads HTML Templates into Memory for Faster Processing

	int count = 0;

	double p1 = 0,  // Percentage Top
      	       p2 = 0;  // Percentage Left

	//Goes though each user, And Creates a Players Stats HTML for that person
	struct ListItem12 *p;
	for ( p = myList12 ; p != 0 ; p = p->next ) {
		clearallright();
		p1 = compwkillpercent1(count,MAXRANK);
		percenttop(p1);

		char text1[40];
		sprintf(text1,"Creating %i of %i",count,MAXRANK);
		drawright(text1,3,0);

		if(count == MAXRANK+1) break;

		readHTMLplayer(p->player.name);         // Process Player Templates From Memory
		writeHTMLplayer(p->player.rank);        // Writes out HTML DATA to Files
		++count;

		percentright(100);
		char text3[40];
		sprintf(text3,"Completed OK! ");
		drawright2(text3,9,0);
    }

	char text2[40];
	sprintf(text2,"Creating %i of %i",MAXRANK,MAXRANK);
	drawright(text2,3,0);

 	clearprank();		// Clears Player Data From Memory after Writing HTML Files #12
	RemoveListWeapon();	// Removes #4
	RemovePlayerHTML();     // *MAIN* Clears all 3 Link Lists from Memory of Templated HTML Files

	percenttop(100);
	#ifdef _WIN32
	Sleep(1000);
	#else
	system("sleep 1s");
	#endif
	return;
}


#endif
