(*****************************************************************************)
(* Illusion BBS - Chat song data                                             *)
(*****************************************************************************)

{$A+,B-,D-,E-,F+,I+,L-,N-,O+,R-,S-,V-}

unit mmsound;

interface

const
  bach2MAX = 216;   { >>> Put this statment before the MELODY array!!! <<< }
  bach2 : array[0..bach2MAX,1..2] of integer = (
(  0,  0),(523,100),(311,100),(294,100),(311,100),(262,100),(311,100)
,(294,100),(311,100),(523,100),(311,100),(294,100),(311,100),(262,100)
,(311,100),(294,100),(311,100),(415,100),(349,100),(330,100),(349,100)
,(262,100),(349,100),(330,100),(349,100),(415,100),(349,100),(330,100)
,(349,100),(262,100),(349,100),(330,100),(349,100),(494,100),(349,100)
,(311,100),(349,100),(294,100),(349,100),(311,100),(349,100),(494,100)
,(349,100),(311,100),(349,100),(294,100),(349,100),(311,100),(349,100)
,(523,100),(392,100),(349,100),(392,100),(311,100),(392,100),(349,100)
,(392,100),(523,100),(392,100),(349,100),(392,100),(311,100),(392,100)
,(349,100),(392,100),(622,100),(415,100),(392,100),(415,100),(311,100)
,(415,100),(392,100),(415,100),(622,100),(415,100),(392,100),(415,100)
,(311,100),(415,100),(392,100),(415,100),(588,100),(370,100),(330,100)
,(370,100),(294,100),(370,100),(330,100),(370,100),(588,100),(370,100)
,(330,100),(370,100),(294,100),(370,100),(330,100),(370,100),(588,100)
,(392,100),(370,100),(392,100),(294,100),(392,100),(370,100),(392,100)
,(588,100),(392,100),(370,100),(392,100),(294,100),(392,100),(370,100)
,(392,100),(524,100),(330,100),(294,100),(330,100),(262,100),(330,100)
,(294,100),(330,100),(524,100),(330,100),(294,100),(330,100),(262,100)
,(330,100),(294,100),(330,100),(524,100),(349,100),(330,100),(349,100)
,(262,100),(349,100),(330,100),(349,100),(524,100),(349,100),(330,100)
,(349,100),(262,100),(349,100),(330,100),(349,100),(466,100),(349,100)
,(311,100),(349,100),(294,100),(349,100),(311,100),(349,100),(466,100)
,(349,100),(311,100),(349,100),(294,100),(349,100),(311,100),(349,100)
,(466,100),(392,100),(349,100),(392,100),(311,100),(392,100),(349,100)
,(392,100),(466,100),(392,100),(349,100),(392,100),(311,100),(392,100)
,(349,100),(392,100),(415,100),(392,100),(349,100),(392,100),(311,100)
,(392,100),(349,100),(392,100),(415,100),(392,100),(349,100),(392,100)
,(311,100),(392,100),(349,100),(392,100),(415,100),(294,100),(262,100)
,(294,100),(233,100),(294,100),(262,100),(294,100),(415,100),(294,100)
,(262,100),(294,100),(233,100),(294,100),(262,100),(277,100),(392,100)
,(233,100),(208,100),(233,100),(311,100),(233,100),(208,100),(233,100));

  toreodorMAX = 67;   { >>> Put this statment before the MELODY array!!! <<< }
  toreodor : array[0..toreodorMAX,1..2] of integer = (
(  0,  0),(523,400),(587,300),(523,100),(440,200),(440,100),(  0,100)
,(440,400),(440,300),(392,100),(440,300),(466,100),(440,400),(440,200)
,(  0,200),(466,400),(392,300),(523,100),(440,600),(  0,200),(349,400)
,(294,300),(392,100),(262,600),(  0,200),(392,800),(392,200),(587,200)
,(523,200),(466,200),(440,200),(392,200),(440,200),(466,200),(440,600)
,(  0,200),(330,400),(440,400),(440,400),(415,200),(494,200),(659,1600)
,(659,200),(587,100),(659,100),(587,100),(554,200),(587,200),(392,200)
,(440,200),(466,200),(  0,200),(440,100),(466,100),(440,100),(349,200)
,(587,200),(523,600),(  0,200),(  0,200),(349,100),(392,100),(349,100)
,(262,200),(466,200),(440,400),(392,400),(349,600));

  rondoMAX = 125;   { >>> Put this statment before the MELODY array!!! <<< }
  rondo : array[0..rondoMAX,1..2] of integer = (
(  0,  0),(494,100),(440,100),(415,100),(440,100),(523,200),(  0,200)
,(587,100),(523,100),(494,100),(523,100),(659,200),(  0,200),(699,100)
,(659,100),(622,100),(659,100),(988,100),(880,100),(830,100),(880,100)
,(988,100),(880,100),(830,100),(880,100),(1046,400),(880,200),(1046,200)
,(988,200),(880,200),(784,200),(880,200),(988,200),(880,200),(784,200)
,(880,200),(988,200),(880,200),(784,200),(740,200),(660,400),(494,100)
,(440,100),(415,100),(440,100),(523,200),(  0,200),(587,100),(523,100)
,(494,100),(523,100),(659,200),(  0,200),(699,100),(659,100),(622,100)
,(659,100),(988,100),(880,100),(830,100),(880,100),(988,100),(880,100)
,(830,100),(880,100),(1046,400),(880,200),(1046,200),(988,200),(880,200)
,(784,200),(880,200),(988,200),(880,200),(784,200),(880,200),(988,200)
,(880,200),(784,200),(740,200),(660,400),(659,200),(699,200),(784,200)
,(784,200),(880,100),(784,100),(699,100),(659,100),(587,400),(659,200)
,(699,200),(784,200),(784,200),(880,100),(784,100),(699,100),(659,100)
,(587,400),(523,200),(587,200),(659,200),(659,200),(699,100),(659,100)
,(587,100),(523,100),(494,400),(523,200),(587,200),(659,200),(659,200)
,(699,100),(659,100),(587,100),(523,100),(494,400),(494,100),(440,100)
,(415,100),(440,100),(523,200),(  0,200),(587,100),(523,100),(494,100));

  joplin1MAX = 209;   { >>> Put this statment before the MELODY array!!! <<< }
  joplin1 : array[0..joplin1MAX,1..2] of integer = (
(  0,  0),(1174,100),(1318,100),(1046,100),(880,100),(880,100),(988,100)
,(784,200),(587,100),(659,100),(523,100),(440,100),(440,100),(494,100)
,(392,200),(294,100),(330,100),(262,100),(220,100),(220,100),(247,100)
,(220,100),(208,100),(196,200),(  0,100),(392,100),(294,100),(311,100)
,(330,100),(523,200),(330,100),(523,200),(330,100),(523,100),(523,400)
,(523,100),(523,100),(587,100),(622,100),(659,100),(523,100),(587,100)
,(659,100),(659,100),(494,100),(587,200),(523,400),(523,200),(294,100)
,(311,100),(330,100),(523,200),(330,100),(523,200),(330,100),(523,100)
,(523,400),(523,200),(440,100),(392,100),(370,100),(440,100),(523,100)
,(659,200),(587,100),(523,100),(440,100),(587,400),(587,200),(294,100)
,(311,100),(330,100),(523,200),(330,100),(523,200),(330,100),(523,100)
,(523,400),(523,100),(523,100),(587,100),(622,100),(659,100),(523,100)
,(587,100),(659,100),(659,100),(494,100),(587,100),(523,400),(523,200)
,(523,100),(587,100),(659,100),(523,100),(587,100),(659,100),(659,100)
,(523,100),(587,100),(523,100),(659,100),(523,100),(587,100),(659,100)
,(659,100),(523,100),(587,100),(523,100),(659,100),(523,100),(587,100)
,(659,100),(659,100),(494,100),(587,200),(523,400),(523,200),(330,100)
,(349,100),(370,100),(392,200),(440,100),(392,100),(392,100),(330,100)
,(349,100),(370,100),(392,200),(440,100),(392,100),(392,100),(659,100)
,(523,100),(392,100),(440,100),(494,100),(523,100),(587,100),(659,100)
,(587,100),(523,100),(587,100),(392,100),(659,100),(699,100),(784,100)
,(880,100),(784,100),(659,100),(699,100),(392,200),(440,100),(392,100)
,(392,100),(330,100),(349,100),(370,100),(392,200),(440,100),(392,100)
,(392,100),(392,100),(440,100),(466,100),(494,100),(494,200),(494,100)
,(494,100),(440,100),(370,100),(294,100),(392,400),(330,100),(349,100)
,(370,100),(392,200),(440,100),(392,100),(392,100),(330,100),(349,100)
,(370,100),(392,200),(440,100),(392,100),(392,100),(659,100),(523,100)
,(392,100),(440,100),(494,100),(523,100),(587,100),(659,100),(587,100)
,(523,100),(587,100),(523,400),(523,100),(392,100),(370,100),(392,100)
,(523,200),(440,100),(523,100),(523,100),(440,100),(523,100),(440,100));

  inventioMAX = 209;   { >>> Put this statment before the MELODY array!!! <<< }
  inventio : array[0..inventioMAX,1..2] of integer = (
(  0,  0),(349,100),(  0,100),(440,100),(  0,100),(349,100),(  0,100)
,(524,100),(  0,100),(349,100),(  0,100),(698,100),(  0,100),(660,100)
,(588,100),(524,100),(588,100),(524,100),(466,100),(440,100),(466,100)
,(440,100),(392,100),(349,100),(  0,100),(440,100),(  0,100),(524,100)
,(  0,100),(440,100),(  0,100),(698,100),(  0,100),(524,100),(  0,100)
,(880,100),(1048,100),(932,100),(1048,100),(880,100),(1048,100),(932,100)
,(1048,100),(880,100),(1048,100),(932,100),(1048,100),(698,100),(880,100)
,(784,100),(880,100),(698,100),(880,100),(784,100),(880,100),(698,100)
,(880,100),(784,100),(880,100),(588,100),(698,100),(660,100),(698,100)
,(588,100),(698,100),(660,100),(698,100),(588,100),(698,100),(660,100)
,(698,100),(494,100),(  0,100),(392,100),(  0,100),(588,100),(  0,100)
,(494,100),(  0,100),(698,100),(  0,100),(588,100),(  0,100),(784,100)
,(880,100),(784,100),(698,100),(660,100),(698,100),(660,100),(588,100)
,(524,100),(588,100),(524,100),(466,100),(440,100),(  0,100),(588,100)
,(524,100),(494,100),(524,100),(494,100),(440,100),(392,100),(440,100)
,(392,100),(349,100),(330,100),(349,100),(330,100),(294,100),(262,100)
,(  0,100),(524,100),(494,100),(524,100),(  0,100),(330,100),(  0,100)
,(349,100),(  0,100),(524,100),(  0,100),(330,100),(  0,100),(524,100)
,(  0,100),(294,100),(  0,100),(494,100),(  0,100),(524,400),(  0,400)
,(  0,200),(524,100),(  0,100),(660,100),(  0,100),(524,100),(  0,100)
,(784,100),(  0,100),(524,100),(  0,100),(1048,100),(  0,100),(988,100)
,(880,100),(784,100),(880,100),(784,100),(698,100),(660,100),(698,100)
,(660,100),(588,100),(524,100),(466,100),(524,100),(880,100),(524,100)
,(880,100),(466,100),(880,100),(524,100),(880,100),(440,100),(  0,100)
,(466,100),(  0,100),(392,100),(  0,100),(466,100),(  0,100),(392,100)
,(  0,100),(588,100),(  0,100),(392,100),(  0,100),(784,100),(  0,100)
,(698,100),(622,100),(588,100),(622,100),(588,100),(524,100),(466,100)
,(524,100),(466,100),(440,100),(392,100),(  0,100),(466,100),(  0,100)
,(588,100),(  0,100),(466,100),(  0,100),(784,100),(  0,100),(588,100)
,(  0,100),(932,100),(  0,100),(554,100),(  0,100),(932,100),(  0,100));

  havaMAX = 138;   { >>> Put this statment before the MELODY array!!! <<< }
  hava : array[0..havaMAX,1..2] of integer = (
(  0,  0),(294,300),(294,300),(  0, 75),(370,150),(311,150),(294,150)
,(370,300),(370,300),(  0, 75),(440,150),(392,150),(370,150),(392,300)
,(392,300),(  0, 75),(466,150),(440,150),(392,150),(370,300),(311,300)
,(294,600),(294,300),(294,300),(  0, 75),(370,150),(311,150),(294,150)
,(370,300),(370,300),(  0, 75),(440,150),(392,150),(370,150),(392,300)
,(392,300),(  0, 75),(466,150),(440,150),(392,150),(370,300),(311,300)
,(294,600),(  0, 75),(370,150),(370,300),(311,150),(294,150),(294,150)
,(294,300),(  0, 75),(311,150),(311,300),(294,150),(262,150),(262,150)
,(262,300),(  0, 75),(262,300),(311,300),(262,300),(392,300),(370,300)
,(311,300),(311, 75),(294,600),(370,150),(370,300),(311,150),(294,150)
,(294,150),(294,300),(  0, 75),(311,150),(311,300),(294,150),(262,150)
,(262,150),(262,300),(  0, 75),(262,300),(311,300),(262,300),(392,300)
,(370,300),(311,300),(311, 75),(294,600),(  0, 75),(392,600),(  0, 75)
,(392,600),(  0, 75),(392,300),(466,300),(466,600),(392,150),(392,150)
,(466,150),(440,150),(392,150),(466,150),(440,150),(392,150),(392,150)
,(392,150),(466,150),(440,150),(392,150),(466,150),(440,150),(392,150)
,(440,150),(440,150),(523,150),(466,150),(440,150),(523,150),(466,150)
,(440,150),(440,150),(440,150),(523,150),(466,150),(440,150),(523,150)
,(466,150),(440,150),(  0,150),(440,150),(587,300),(440,150),(440,150)
,(587,300),(440,150),(523,150),(466,150),(440,150),(392,600));

  eliseMAX = 97;   { >>> Put this statment before the MELODY array!!! <<< }
  elise : array[0..eliseMAX,1..2] of integer = (
(  0,  0),(659,200),(622,200),(659,200),(622,200),(659,200),(494,200)
,(587,200),(523,200),(440,400),(  0,200),(330,200),(440,200),(523,200)
,(494,400),(  0,200),(330,200),(415,200),(494,200),(523,400),(  0,200)
,(330,200),(659,200),(622,200),(659,200),(622,200),(659,200),(494,200)
,(587,200),(523,200),(440,400),(  0,200),(330,200),(440,200),(523,200)
,(494,400),(  0,200),(330,200),(523,200),(494,200),(440,400),(  0,200)
,(494,200),(523,200),(587,200),(659,400),(  0,200),(440,200),(699,200)
,(659,200),(587,400),(  0,200),(392,200),(659,200),(587,200),(523,400)
,(  0,200),(392,200),(587,200),(523,200),(494,400),(165,200),(330,200)
,(330,200),(659,200),(660,200),(1318,200),(622,200),(659,200),(622,200)
,(659,200),(494,200),(587,200),(523,200),(440,400),(  0,200),(330,200)
,(440,200),(523,200),(494,400),(  0,200),(330,200),(415,200),(494,200)
,(523,400),(  0,200),(659,200),(622,200),(659,200),(622,200),(659,200)
,(494,200),(587,200),(523,200),(440,400),(  0,200),(330,200),(440,200));

  bethovenMAX = 97;   { >>> Put this statment before the MELODY array!!! <<< }
  bethoven : array[0..bethovenMAX,1..2] of integer = (
(  0,  0),(440,200),(699,200),(659,200),(587,400),(  0,200),(440,200)
,(699,200),(659,200),(587,400),(  0,200),(440,200),(699,200),(659,200)
,(587,400),(  0,200),(440,200),(699,200),(587,200),(659,400),(  0,200)
,(440,200),(784,200),(699,200),(659,400),(  0,200),(440,200),(784,200)
,(699,200),(659,400),(  0,200),(440,200),(784,200),(699,200),(659,400)
,(  0,200),(440,200),(784,200),(659,200),(699,400),(  0,200),(587,200)
,(880,200),(1174,200),(932,400),(  0,200),(466,200),(587,200),(932,200)
,(784,400),(  0,200),(392,200),(466,200),(784,200),(659,400),(  0,200)
,(330,200),(440,200),(659,200),(699,400),(  0,200),(349,200),(440,200)
,(699,200),(587,400),(  0,200),(294,200),(440,200),(587,200),(554,400)
,(  0,200),(277,200),(440,200),(554,200),(587,400),(  0,200),(587,200)
,(880,200),(1174,200),(932,400),(  0,200),(466,200),(587,200),(932,200)
,(784,400),(  0,200),(392,200),(466,200),(784,200),(659,400),(  0,200)
,(330,200),(440,200),(659,200),(699,400),(  0,200),(349,200),(440,200));

implementation

end.
