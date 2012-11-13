/*
 * Random Init Function API File
 * 
 */
 
 #include "randapi.h"
 #include<stdlib.h>
 #include<time.h>
 
 /*
  * initrand() initializes the random number generator.
  * 
  */
  
  void initrand()
  {
	  time_t seed;
	  
	  seed = time(NULL);
	  srand(seed);
	  
	  return ;
  }
