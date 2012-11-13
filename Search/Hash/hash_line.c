/*
 *	创建和查找散列表
 *	用线性探测解决冲突
 */

#include <stdio.h>

#define HASH_LEN 13
#define TABLE_LEN 8

int data[TABLE_LEN] = { 69, 65, 90, 37, 92, 6, 28, 54 };
int hash[HASH_LEN] = {0};

void insert_hash( int data )
{
	int i;

	i = data % HASH_LEN;
	/* 线性探测是否存在冲突 */
	while (hash[i]) {
		/* 若存在冲突，则后移以为继续探测 */
		i++;
		i %= (HASH_LEN);
	}
	hash[i] = data;
}

void create_hash()
{
	int i;

	for ( i = 0; i < TABLE_LEN; i++ ) {
		insert_hash( data[i] );
	}
}

int search_hash( int key )
{
	int i;

	i = key % HASH_LEN;
	/* 存在冲突的情况 */
	while ( hash[i] && hash[i] != key ) {
		i++;
		i %= (HASH_LEN);
	}

	if ( hash[i] == 0 ) {
		return -1;
	} else {
		return i;
	}
}

int main()
{
	int key, i, pos;

	create_hash();
	printf( "散列表的值： " );
	for ( i = 0; i < HASH_LEN; i++ ) {
		printf( "%d ", hash[i] );
	}
	printf( "\n" );

	printf( "输入查找关键字： " );
	scanf( "%d", &key );
	fflush(stdin);

	pos = search_hash( key );
	if ( pos == -1 ) {
		printf( "查找失败！\n" );
	} else {
		printf( "查找成功，该关键字位于数组的 %d 个位置！\n", pos );
	}

	return 0;
}
