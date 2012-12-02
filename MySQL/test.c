/*
 * Database db_test
 * table user(ID, name)
 * read from user && print
 */

#include <stdio.h>
#include <mysql/mysql.h>

int main( int argc, char *argv[] )
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query = "select * from user";
	int t, r;

	if( !mysql_init(&mysql) ) {
		printf( "Init Err: %s\n", mysql_error(&mysql) );
		return -1;
	}

	if ( !mysql_real_connect( &mysql, "localhost", "root", "root", "db_test", 
				0, NULL, 0) ) {
		printf( "Connect Err: %s\n", mysql_error(&mysql) );
		return -1;
	}
	printf( "Connected....\n" );

	t = mysql_query( &mysql, query );
	if ( t ) {
		printf( "Query Err: %s\n", mysql_error(&mysql) );
		mysql_close(&mysql);
		return -1;
	}
	printf( "Query made......\n" );

	res = mysql_use_result( &mysql );
	if ( !res ) {
		printf( "Result Err: %s\n", mysql_error(&mysql) );
		mysql_close(&mysql);
		return -1;
	}

	/*
	 * mysql_field_count 返回查询的列的数量
	 */
	for ( r = 0; r < mysql_field_count(&mysql); r++ ) {
		/*
		 * mysql_fetch_row 检索一个结果集合的下一行
		 */
		row = mysql_fetch_row( res );
		if ( row < 0 ) {
			break;
		}

		/*
		 * mysql_num_fields 返回集合中列的数量
		 */
		for ( t = 0; t < mysql_num_fields(res); t++ ) {
			printf( "%s ", row[t] );
		}
		printf( "\n" );
	}

	mysql_close(&mysql);

	return 0;
}
