/*
 * randapi.c
 * 
 * Random Functions API File
 * 
 */
 
 #include "randapi.h"
 #include<stdlib.h>
 
 /*
  * getsrand() returns a number between 0.0 and 1.0
  * 
  */
  
  float getsrand()
  {
	  float randvalue;
	  
	  randvalue = ((float) rand() / (float) RAND_MAX);
	  
	  return randvalue;
  }
  
  /*
   * getrand() return a number between 1 and max - 1.
   * 
   */
   
   int getrand(int max)
   {
	   int randvalue;
	   
	   randvalue = (int) ((float) max * rand() / (RAND_MAX + 1.0));
	   
	   return randvalue;
   }
