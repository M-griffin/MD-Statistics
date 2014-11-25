#include <list>
#include <vector>
#include <algorithm>


using namespace std;

// store the stats relative to a given category in a struct
struct stats_t
{
   double frags; 
   double deaths;
   double suicides;
   double damdelt;
   double damrec;
   double dambleed;
};

// define an enum with all the stats categories
// using their values as an index.
enum stats_category
{
   st_self = 0, st_m203,
   st_famas, st_g36e,
   /* and so on */

   // st_max is an extra value, used to size the vector
   // i.e. being the last value in the enum, its value
   // is equal to the number of values in the enum.
   st_max
};

struct ListItem13
{
  // why bother with a char* when we have strings
  string name;
  // why write out all the values when you can have them 
  // in a vector of structs ? Even the overall statistics
  // can be kept there, as I didn't see much difference.
  vector<stats_t> stats;

  // This will do your initialisation : 
  // structs are initialised to zero by their default constructor
  ListItem13( string name ) : name( name ), stats( st_max ) {};
};

// Using a standard list instead of a custom-made one !
typedef list<ListItem13*> List13;
typedef List13::iterator ListItor13;
List13 MyList13;
 
void clearplayerdata(void)
{
  // While the list is not empty, delete the last element.
  while( !MyList13.empty() )
  {
     delete MyList13.back();
     MyList13.pop_back();
  }
}

// This object class is used to compare the name of a list 
// item (pointer) with a predefined one (as passed to the
// constructor).
// i.e. 
//   SameNamePredicate foo( "blah" );
//   foo( str );  ... will compare str to "blah"

class SameNamePredicate
{
   string name;
public:
   SameNamePredicate( const string& name ) : name ( name ) {};
   inline bool operator( ListItem13* item ) { return item->name == name; };
};

bool newplayerdata(string name)
{
   // create a player (initialised and everything)
   ListItem13 item = new ListItem13( name );
   // out of memory
   if( !item )
   {
      cout << "Malloc Failed for holding Player Data\n";
      cout << "You do not have enough memory for this program!\n";
      exit(1);
   }

   // Look if the player is in the list
   ListItor13 itor = find_if( MyList13.begin(), MyList13.end(), SameNamePredicate( name ) );
   if( itor != MyList13.end() ) return true;

   // if not, add it
   MyList13.push_back( item );

   return false;
}

