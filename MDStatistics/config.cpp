#ifndef __CONFIG_CPP    /*  An extra safeguard to prevent this header from  */
#define __CONFIG_CPP    /*  being included twice in the same source file    */

#include <string.h>      // C++ String Library
#include "structs.h"
#include "config.h"

using namespace std;

// CONFIG.DAT FUNCTIONS

char   SERVERNAME[255] ;	 // HTML Server Name
char   SERVERIP[255]; 		 // Server IP Address
char   WEBPAGE[255]; 		 // Server Web Page
char   ADMINNAME[255]; 		 // Admin Name
char   ADMINEMAIL[255]; 	 // Admin Email

/*--------------------------------------------------------------------------------*/
// LOG.DAT Write - I/O Adds logname to Log File
int writecfg(CONFIG * cfg, int idx) {

	string path = PATH;

    #ifdef _WIN32
    path += "Data\\config.dat";
    #else 
    path += "Data/config.dat";
    #endif

    FILE *stream;
    int x=0;

    stream=fopen(path.c_str(),"rb+");
    if(stream == NULL) {
    	stream=fopen(path.c_str(), "wb");
		if(stream == NULL) {
    		fprintf(stderr, "Error Creating config.dat!\n");
        	return x;
    	}
    }    
    if(fseek(stream,(long)idx*sizeof(CONFIG),SEEK_SET)==0)
    	x = fwrite(cfg,sizeof(CONFIG),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// LOG.DAT Reads - I/O Read Any Log by Index Number
int readcfg(CONFIG * cfg, int idx) {

    int x;

    string path = PATH;
        
    #ifdef _WIN32
    path += "Data\\config.dat";
    #else
    path += "Data/config.dat";
    #endif                

    FILE * stream = fopen(path.c_str(), "rb");
    if(fseek(stream,(long)idx*sizeof(CONFIG),SEEK_SET)==0)
    	x = fread(cfg,sizeof(CONFIG),1,stream);
    fclose(stream);
    return x;
}

/*--------------------------------------------------------------------------------*/
// Reads log.dat and gets Total number of Logs that have been loaded
int countcfg() {

    int i = 0;
    CONFIG cfg;

    while(readcfg(&cfg,i++));
    if(i < 1)	i =- 1;
    else		i--;
    return(i);
}

/*--------------------------------------------------------------------------------*/
// Lists ALL Users By Name from user.dat
void listcfg() {

	char config[30];
    CONFIG cfg;
	
	string temp;
    int idx = 0;
    printf("\nListing all Logs Processed!\n");
    while(readcfg(&cfg,idx)){
    	printf("#%i\t Log: %s\n",idx+1,cfg.currmap);
        idx++;
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Find log record By Matching name
int findcfg(char *tcfg) {

	string temp, temp1;
	CONFIG cfg;
 	temp = (tcfg);
	int idx=0;
	while(readcfg(&cfg,idx)) {
    	temp1 = (cfg.currmap);
        if(temp == temp1) return(idx);
        idx++;
    }
	return(-1);
}

/*--------------------------------------------------------------------------------*/
// Function for Seeing if A Log has already been loaded before
bool matchcfg(char* name) {

	int index=-1;
	index = findcfg(name);
   	if (index == -1) return false;
	else return true;
}

/*--------------------------------------------------------------------------------*/
// Checks if log.dat file exists,  if not Creates it
bool cfgdataexists() {

	string path = PATH;

    #ifdef _WIN32
    path += "Data\\config.dat";
    #else        
    path += "Data/config.dat";
    #endif

    FILE * stream;

    stream=fopen(path.c_str(),"rb+");
    if(stream == NULL) {
    	stream=fopen(path.c_str(), "wb");   //open file Writing
        if(stream == NULL) {
        	fprintf(stderr, "Error Creating config.dat!\n");
            return false;
		}
    }
    fclose(stream);
    return true;
}

// Config.cfg Functions


/*--------------------------------------------------------------------------------*/
// Checks if CONFIG.CFG file exists, if not return false
bool configdataexists() {

    FILE * stream;
	
	string path = PATH;
 	path += "config.cfg";
 	
    stream=fopen(path.c_str(),"rb+");
    if(stream == NULL) {
 	   return false;
    }
    fclose(stream);
    return true;
}

/*--------------------------------------------------------------------------------*/
// Creat Defauly Config File if None Exists
void createconfig() {        

	string name = PATH;
    name += "config.cfg";

    ofstream outStream2;
    outStream2.open( name.c_str(), ofstream::out | ofstream::trunc );
        
    if (!outStream2.is_open()) {
        printf( "\n\nError Creating: %s \n",name.c_str() );
        exit(1);
    }      
        
    #ifdef _WIN32
    outStream2 << "" << endl;
    outStream2 << "# .----------------------------------------------------------------." << endl;
    outStream2 << "# | .mD. Statistics Configuration file for Build [0.1.1.1] (WIN32) |-------------" << endl;
	outStream2 << "# `----------------------------------------------------------------'" << endl;
    #else        
    outStream2 << "# .----------------------------------------------------------------." << endl;
    outStream2 << "# | .mD. Statistics Configuration file for Build [0.1.1.1] (LINUX) |-------------" << endl;
	outStream2 << "# `----------------------------------------------------------------'" << endl;
    #endif            
    outStream2 << "#" << endl;
    outStream2 << "#" << endl;
    outStream2 << "# .----------------------------------------------------------------." << endl;
    outStream2 << "# | Note : This file is regenerated with defaults if missing.      |-------------" << endl;
    outStream2 << "# | Note : Any Lines with the # in them will be ignored            |-------------" << endl;	
    outStream2 << "# `----------------------------------------------------------------'" << endl;               
    outStream2 << "#" << endl;
    outStream2 << "#" << endl;
    outStream2 << "#" << endl;
    outStream2 << "# .-------------------------------------------------------------------------------------------." << endl;
    outStream2 << "# | Enter your Firearms Server Name Here : This is for the HTML Templates                     |" << endl;
	outStream2 << "# `-------------------------------------------------------------------------------------------'" << endl;
 	outStream2 << "#" << endl;
    outStream2 << "Set ServerName \".mD.Statistics Firearms Mod v2.6+\"" << endl;
    outStream2 << "" << endl;
    outStream2 << "#" << endl;
    outStream2 << "# .-------------------------------------------------------------------------------------------." << endl;
    outStream2 << "# | Enter your Firearms Server IP Address: This is for the HTML Templates                     |" << endl;
	outStream2 << "# `-------------------------------------------------------------------------------------------'" << endl;       
	outStream2 << "#" << endl;
    outStream2 << "Set ServerIP \"192.168.0.1\"" << endl;
	outStream2 << "" << endl;
    outStream2 << "# " << endl;
    outStream2 << "# .-------------------------------------------------------------------------------------------." << endl;
    outStream2 << "# | Enter your Firearms Server Web Page: This is for the HTML Templates                       |" << endl;
	outStream2 << "# `-------------------------------------------------------------------------------------------'" << endl;       
	outStream2 << "#" << endl;
    outStream2 << "Set WebPage \"http:\\\\www.firearmsmod.com\"" << endl;
    outStream2 << "" << endl;
    outStream2 << "# " << endl;
    outStream2 << "# .-------------------------------------------------------------------------------------------." << endl;
    outStream2 << "# | Enter your Firearms Server Admin's Name: This is for the HTML Templates                   |" << endl;
	outStream2 << "# `-------------------------------------------------------------------------------------------'" << endl;
	outStream2 << "#" << endl;
    outStream2 << "Set AdminName \"Mandr4ke\"" << endl;
    outStream2 << "" << endl;
    outStream2 << "# " << endl;
    outStream2 << "# .-------------------------------------------------------------------------------------------." << endl;
    outStream2 << "# | Enter your Firearms Server Admin's Email: This is for the HTML Templates                  |" << endl;
	outStream2 << "# `-------------------------------------------------------------------------------------------'" << endl;
	outStream2 << "# " << endl;        
    outStream2 << "Set AdminEmail \"MrMisticismo@Hotmail.com\"" << endl;
    outStream2 << "" << endl;
    outStream2 << "# " << endl;
    outStream2 << "# .-------------------------------------------------------------------------------------------." << endl;
    outStream2 << "# | Set the TOP # of Players you would like in your Player Rankings - Default \"100\" Players   |" << endl;
	outStream2 << "# `-------------------------------------------------------------------------------------------'" << endl;       
	outStream2 << "# " << endl;
    outStream2 << "Set Rankings \"100\"" << endl;
    outStream2 << "" << endl;
    outStream2 << "# " << endl;
    outStream2 << "# .-------------------------------------------------------------------------------------------." << endl;
    outStream2 << "# | Set the TOP # of Players you would like in your Weapon Rankings - Default \"25\" Players    |" << endl;
	outStream2 << "# `-------------------------------------------------------------------------------------------'" << endl;       
	outStream2 << "#" << endl;
    outStream2 << "Set WeaponRankings \"25\"" << endl;
    outStream2 << "" << endl;
    outStream2 << "# " << endl;
    outStream2 << "# .-------------------------------------------------------------------------------------------." << endl;
    outStream2 << "# | Set Drive and Directory Where your Firearms v2.6 Log files can be found.                  |" << endl;
    outStream2 << "# | Deafult = \"NONE\" And will use the Current Program Directory!                              |" << endl;
    outStream2 << "# |                                                                                           |" << endl;      
    #ifdef _WIN32
    outStream2 << "# | Set LogPath \"C:\\HALF-LIFE\\FIREARMS\\LOGS\\\"  Must have a \\ at the end of the PATH!          |" << endl;
    #else       
    outStream2 << "# | Set LogPath \"/HALF-LIFE/FIREARMS/LOGS/\"  Must have a / at the end of the PATH!            |" << endl;
    #endif
    outStream2 << "# `-------------------------------------------------------------------------------------------'" << endl;       
	outStream2 << "#" << endl;
    outStream2 << "Set LogPath \"NONE\"" << endl;
    outStream2 << "" << endl;
    outStream2 << "#" << endl;
    outStream2 << "# .-------------------------------------------------------------------------------------------." << endl;
    outStream2 << "# | Set Drive and Directory Where You want to Write out the HTML Files to.                    |" << endl;
    outStream2 << "# | Deafult = \"NONE\" And will use the Current Program Directory!                              |" << endl;
    outStream2 << "# |                                                                                           |" << endl;
    #ifdef _WIN32
    outStream2 << "# | Set LogPath \"C:\\WebpageStats\\\"  Must have a \\ at the end of the PATH!                     |" << endl;
    #else        
    outStream2 << "# | Set LogPath \"/WebpageStats/\"  Must have a / at the end of the PATH!                       |" << endl;
    #endif
	outStream2 << "# `-------------------------------------------------------------------------------------------'" << endl;       
    outStream2 << "#" << endl;
    outStream2 << "# .-------------------------------------------------------------------------------------------." << endl;
    outStream2 << "# | *NOTE* If you use the HTML Path, then you *must* put a copy of the Images Folder          |" << endl;
    outStream2 << "# | and the mD_stats.css file into the same directory, or your webpage will be missing        |" << endl;
    outStream2 << "# | All of the Pictures, and Colors!                                                          |" << endl;
	outStream2 << "# `-------------------------------------------------------------------------------------------'" << endl;
    outStream2 << "#" << endl;
    outStream2 << "Set HTMLPath \"NONE\"" << endl;
    outStream2 << " " << endl;
    outStream2.close();
    return;
}

/*--------------------------------------------------------------------------------*/
// Parses Config File Data
void checkcfg(string cfgdata) {

	string temp = cfgdata;
    int id1 = -1;
    // Disgards any Config lines with the # Character
    id1 = temp.find('#', 0);
    if (id1 != -1) return;

    // Sets the Server Name
    id1 = temp.find("Set ServerName", 0);
    if (id1 != -1) {
    	string temp1;

        int st1 = -1;
        int st2 = -1;
        signed int  ct = -1;

        st1 = temp.find('"', 0);
        st2 = temp.find('"', st1+1);
        ++st1;
        temp1 = temp.substr(st1,st2);
        ct = st2 - st1;
        if (temp1.length() > ct)
        	temp1.erase(ct,temp1.length());
        strcpy(SERVERNAME,temp1.c_str());
        return;
    }

    id1 = temp.find("Set ServerIP", 0);
    if (id1 != -1) {
    	string temp1;

        int st1 = -1;
        int st2 = -1;
        signed int  ct = -1;

        st1 = temp.find('"', 0);
        st2 = temp.find('"', st1+1);
        ++st1;
        temp1 = temp.substr(st1,st2);
        ct = st2 - st1;
        if (temp1.length() > ct)
        	temp1.erase(ct,temp1.length());
        strcpy(SERVERIP,temp1.c_str());
        return;
    }

	id1 = temp.find("Set WebPage", 0);
    if (id1 != -1) {
    	string temp1;

        int st1 = -1;
        int st2 = -1;
        signed int  ct = -1;

        st1 = temp.find('"', 0);
        st2 = temp.find('"', st1+1);
        ++st1;
        temp1 = temp.substr(st1,st2);
        ct = st2 - st1;
        if (temp1.length() > ct)
            temp1.erase(ct,temp1.length());
        strcpy(WEBPAGE,temp1.c_str());
        return;
    }

	id1 = temp.find("Set AdminName", 0);
    if (id1 != -1) {
    	string temp1;

        int st1 = -1;
        int st2 = -1;
        signed int  ct = -1;

        st1 = temp.find('"', 0);
        st2 = temp.find('"', st1+1);
        ++st1;
        temp1 = temp.substr(st1,st2);
        ct = st2 - st1;
        if (temp1.length() > ct)
            temp1.erase(ct,temp1.length());
        strcpy(ADMINNAME,temp1.c_str());
        return;
    }

	id1 = temp.find("Set AdminEmail", 0);
    if (id1 != -1) {
    	string temp1;

        int st1 = -1;
        int st2 = -1;
        signed int  ct = -1;

        st1 = temp.find('"', 0);
        st2 = temp.find('"', st1+1);
        ++st1;
        temp1 = temp.substr(st1,st2);
        ct = st2 - st1;
        if (temp1.length() > ct)
            temp1.erase(ct,temp1.length());
        strcpy(ADMINEMAIL,temp1.c_str());
    	return;
    }


    // Sets the Max Number Of Player to Process for Rankings
    id1 = temp.find("Set Rankings", 0);
    if (id1 != -1) {
    	string temp1;

        int st1 = -1;
        int st2 = -1;
        signed int  ct = -1;

        st1 = temp.find('"', 0);
        st2 = temp.find('"', st1+1);
        ++st1;
        temp1 = temp.substr(st1,st2);
        ct = st2 - st1;
        if (temp1.length() > ct)
        	temp1.erase(ct,temp1.length());               
		long rank;
		rank = atol(temp1.c_str());
        MAXRANK = rank;
        return;
    }
	// Sets the Max Number Of Player to Process for Weapon Rankings
    id1 = temp.find("Set WeaponRankings", 0);
    if (id1 != -1) {
    	string temp1;

        int st1 = -1;
        int st2 = -1;
        signed int  ct = -1;

        st1 = temp.find('"', 0);
        st2 = temp.find('"', st1+1);
        ++st1;
        temp1 = temp.substr(st1,st2);
        ct = st2 - st1;
        if (temp1.length() > ct)
                        temp1.erase(ct,temp1.length());                
		long rank;
		rank = atol(temp1.c_str());
                MAXWEAPONRANK = rank;
                return;
    }

    // Sets the Max Number Of Player to Process for Weapon Rankings
    id1 = temp.find("Set LogPath", 0);
    if (id1 != -1) {
        string temp1;

        int st1 = -1;
        int st2 = -1;
        signed int  ct = -1;

        st1 = temp.find('"', 0);
        st2 = temp.find('"', st1+1);
        ++st1;
        temp1 = temp.substr(st1,st2);
        ct = st2 - st1;
        if (temp1.length() > ct)
            temp1.erase(ct,temp1.length());
        strcpy(LOGPATH,temp1.c_str());
        return;
    }

    // Sets the Max Number Of Player to Process for Weapon Rankings
    id1 = temp.find("Set HTMLPath", 0);
    if (id1 != -1) {
        string temp1;

        int st1 = -1;
        int st2 = -1;
        signed int  ct = -1;

        st1 = temp.find('"', 0);
        st2 = temp.find('"', st1+1);
        ++st1;
        temp1 = temp.substr(st1,st2);
        ct = st2 - st1;
        if (temp1.length() > ct)
            temp1.erase(ct,temp1.length());
        strcpy(HTMLPATH,temp1.c_str());
        return;
    }
    return;
}

/*--------------------------------------------------------------------------------*/
// Read Config File
void parseconfig() {

    string name = PATH;
    name += "config.cfg";

    ifstream inStream;
    inStream.open( name.c_str() );

    if (!inStream.is_open()) {
        cout << "Coun't Open Config File For Reading " << name <<endl;
        system("pause");
        exit(1);
    }

    string cfgdata;
    for (;;) {
    	if (inStream.eof()) break;
        getline(inStream,cfgdata); // Gets line from log till '\n' & Stores in string
        checkcfg(cfgdata);         // Prase's the string And splits for Processing                
    }
    inStream.close();                  // Closes the file before exiting
    return;
}


#endif
