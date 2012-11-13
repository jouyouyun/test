/*
 * 静态库示例
 * 
 */

/*
 * randapi.h
 * 
 * Random Functions API File
 * 
 */
 
 #ifndef __RAND_API_H
 #define __RAND_API_H
 
 extern void initrand();
 
 extern float getsrand();
 
 extern int getrand( int max );
 
 #endif 
 /* __RAND_API_H */
