
/*--------------------------------------------------------------------------------*/
/*  Ansi Parser - Michael Griffin
    Inspired from Saeger's Source Code.

    2/10/03 - Starting Initial Conversion of code from Dos to Windows Platform
            - Rewrote Console output drawing functions,  Need to change color
            - out from attribs becasue output color is not correct.
            - Broke out Ansi Parsing into Function. - Need to break up Parsing
              by file, and parsing by data passed to function.
             - ANSI Parsing Fully working, Riped out horriable Color Code and Replaced
              with Invisi color code,  Now works perfect!


                                                                                  */
/*--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "ansi.h"

using namespace std;

int main (int argc, char **argv) {

    ansiparse(argc,argv);

     system("pause");
    return 0;
}
