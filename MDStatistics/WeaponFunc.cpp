#ifndef __WEAPONFUNCT_CPP    /*  An extra safeguard to prevent this header from  */
#define __WEAPONFUNCT_CPP    /*  being included twice in the same source file    */


// This file is the basic i/o for WEAPON.DAT and holds all Weapon Statistics

/*--------------------------------------------------------------------------------*/
// Libraries  c/c++

#include "structs.h"
#include "WeaponFunc.h"

using namespace std;            // Standard C++ Namespace

/*--------------------------------------------------------------------------------*/
// WEAPON.DAT FUNCTIONS
/*--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
// WEAPON.DAT Write - I/O Adds logname to Log File
int writew(WEAPONREC * weapon, int idx) {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\weapon.dat";
       #else
    path += "Data/weapon.dat";
       #endif

    FILE *stream;
    int x = 0;

    stream=fopen(path.c_str(),"rb+");         // file test
    if(stream == NULL){
        stream=fopen(path.c_str(), "wb"); // open file Writing
        if(stream == NULL) {
            fprintf(stderr, "Error Creating Weapon.dat!\n");
            return x;
        }
    }
    if(fseek(stream,(long)idx*sizeof(WEAPONREC),SEEK_SET)==0)
        x = fwrite(weapon,sizeof(WEAPONREC),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// WEAPON.DAT Reads - I/O Read Any Log by Index Number
int readw(WEAPONREC * weapon, int idx) {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\weapon.dat";
       #else
    path += "Data/weapon.dat";
       #endif

    int x;
    FILE * stream = fopen(path.c_str(), "rb");
    if(fseek(stream,(long)idx*sizeof(WEAPONREC),SEEK_SET)==0)
        x = fread(weapon,sizeof(WEAPONREC),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// Reads weapon.dat and gets Total number of Weapons that have been loaded
int countweapons() {

    int i=0;
    WEAPONREC weapon;

    while(readw(&weapon,i++));
    if(i < 1)    i = -1;
    else        i--;
    return(i);
}


/*--------------------------------------------------------------------------------*/
// Find Weapon record By Matching name - Gets Weapons Index
int findweapon(char * tweapon) {

    int idx = 0;
    string temp1,temp2;
    WEAPONREC weapon;

    temp1 = (tweapon);

    while(readw(&weapon,idx)){
         temp2 = (weapon.name);
         if(temp1 == temp2)    return(idx);
         idx++;
    }
    return(-1);
}

/*--------------------------------------------------------------------------------*/
// Function Check if Name already exists in Weapon.dat
bool matchweapon(char * name) {

    int index=-1;
    while(index == -1) {
        index = findweapon(name);
        if (index == -1) return false;
    }
    return true;
}


/*--------------------------------------------------------------------------------*/
// Checks if Weapon.dat file exists,  if not Creates it
bool wdataexists() {

    string path = PATH;

    #ifdef _WIN32
    path += "Data\\weapon.dat";
       #else
    path += "Data/weapon.dat";
       #endif


    FILE * stream;
    stream=fopen(path.c_str(),"rb+");
    if(stream == NULL) {
        stream=fopen(path.c_str(), "wb");   // open file Writing
        if(stream == NULL) {
            fprintf(stderr, "Error Creating weapon.dat!\n");
            return false;
        }
    }
    fclose(stream);
    return true;
}

/*--------------------------------------------------------------------------------*/
// Add New Weaponname to STRUCTURE AND Weapon.dat
void addweapon(char * name) {

        WEAPONREC weapon;

        if(wdataexists() == false) {
            cout << "Can't Generate weapon.dat for Indexing Weapon Names & Stats...";
            exit(1);
        }
        int idx = countweapons();

        memset(&weapon,0,sizeof(WEAPONREC)); // Sets Weapons to 0
        strcpy(weapon.name, name);

        // Adds LogName to Database log.dat
        if (matchweapon(weapon.name) != true) {
            // Creates Weapon And Sets Defaults
            weapon.index = idx;
            writew(&weapon,idx);
        }
        return;
}

/*--------------------------------------------------------------------------------*/
// Create Starting Weapon Structures For Version 2.6 Firearms Adding Names
void createweapons() {

    char name1[30] = "M-203";
    addweapon(name1);
    char name2[30] = "FA-MAS";
    addweapon(name2);
    char name3[30] = "H&K G36E";
    addweapon(name3);
    char name4[30] = "BENELLI M3 SUPER 90 P";
    addweapon(name4);
    char name5[30] = "SAIGA 12K";
    addweapon(name5);
    char name6[30] = "M-16A2";
    addweapon(name6);
    char name7[30] = "AK-47";
    addweapon(name7);
    char name8[30] = "BARRET M82A1";
    addweapon(name8);
    char name9[30] = "BIZON-2";
    addweapon(name9);
    char name10[30] = "COMBAT KNIFE";
    addweapon(name10);
    char name11[30] = "COLT 1911";
    addweapon(name11);
    char name12[30] = "BERETTA 92F";
    addweapon(name12);
    char name13[30] = "BERETTA 93R";
    addweapon(name13);
    char name14[30] = "IMI DESERT EAGLE";
    addweapon(name14);
    char name15[30] = "COLT ANACONDA";
    addweapon(name15);
    char name16[30] = "STIELHANDGRANATE";
    addweapon(name16);
    char name17[30] = "M81 CLAYMORE";
    addweapon(name17);
    char name18[30] = "STERLING L2A3MK4";
    addweapon(name18);
    char name19[30] = "H&K MP5A2-MP5SD2";
    addweapon(name19);
    char name20[30] = "M-60";
    addweapon(name20);
    char name21[30] = "M-79";
    addweapon(name21);
    char name22[30] = "IMI UZI";
    addweapon(name22);
    char name23[30] = "PKM";
    addweapon(name23);
    char name24[30] = "H&K G3A3";
    addweapon(name24);
    char name25[30] = "AK-74";
    addweapon(name25);
    char name26[30] = "SVD DRAGUNOV";
    addweapon(name26);
    char name27[30] = "GP-25";
    addweapon(name27);
    char name28[30] = "SIG SSG-3000";
    addweapon(name28);
    char name29[30] = "M61-FRAG GRENADE";
    addweapon(name29);
    char name30[30] = "MORTAR";
    addweapon(name30);
    char name31[30] = "SPARK SHOWER";
    addweapon(name31);
    char name32[30] = "MONSTER MORTAR";
    addweapon(name32);
    char name33[30] = "TANK";
    addweapon(name33);
    char name34[30] = "EXPLOSION";
    addweapon(name34);
    char name35[30] = "CONCUSSION GRENADE";
    addweapon(name35);
    char name36[30] = "AMMO BOX";
    addweapon(name36);
    return;
}

#endif
