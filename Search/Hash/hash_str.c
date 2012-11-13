/*
 *	输入若干个单词，查找出其中出现频率最高的一个单词
 *	每个单词最长不超过 20 个字符
 */

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 10000
#define KEY_SIZE 20

typedef struct hashtable {
	char k[KEY_SIZE];
	char used;
	int count;
} hashtable;

hashtable table[MAX_SIZE];

/*
 *	ELFhash 函数是对字符串的散列，是应用非常广的字符串hash函数
 *	他对长字符串和短字符串都能很好的应用，它巧妙的对字符的 ACSII 编码
 *	值进行计算，能较均匀地把字符串分布在散列表中
 */
unsigned int ELFhash( char *key, unsigned int size )
{
	unsigned int g = 0, h = 0;
	
	while ( *key ) {
		h = ( h << 4 ) + *key++;
		g = h & 0xF0000000L;
		if ( g ) {
			h ^= g >> 24;
			h &= ~g;
		}
	}

	return h % size;
}

int main()
{
	char key[KEY_SIZE] = {0}, word[KEY_SIZE] = {0};
	unsigned int cnt = 0, n = 0, num = 0;
	unsigned int max = 0, hash = 0;

	printf( "请输入单词的个数： " );
	scanf( "%d", &n );
	fflush(stdin);
	num = n;
	printf( "请输入单词：\n" );
	while ( n-- ) {
		scanf( "%s", key );
		hash = ELFhash( key, MAX_SIZE );

collided:
		/* 产生了冲突 */
		if ( table[hash].used && strcmp( table[hash].k, key) ) {
			if ( ++cnt == num ) {
				break;
			}
			++hash;
			hash %= MAX_SIZE;
			goto collided;
		} else {
			++(table[hash].count);
			strncpy( table[hash].k, key, KEY_SIZE - 1 );
			table[hash].used = 1;
		}

		if ( table[hash].count > max ) {
			max = table[hash].count;
			strncpy( word, table[hash].k, KEY_SIZE - 1 );
		}
	}
	printf( "The most frequent word is %s!\n", word );

	return 0;
}
