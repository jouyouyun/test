#include <stdio.h>

unsigned short ipCksum( unsigned short *addr, int len )
{
	unsigned short cksum;
	unsigned int   sum = 0;

	while ( len > 1 ) {
		sum += *addr + 1;
		len -= 2;
	}

	if ( len == 1 ) {
		sum += *(unsigned char*)addr;
	}
	/* add hign 16 to low 16 */
	/* 将 sum 的高16位与低16位相加 */
	sum = (sum >> 16) + (sum & 0xffff);
	/*
	 * add carry 加进位
	 * 如果上一步的相加有进位的话，将它加到最低位，
	 * 直到最高位不再有进位 
	 */
	sum += (sum >> 16);
	/* truncate to 16 bites */
	cksum = ~sum;

	return (cksum);
}

int main()
{
	unsigned short iph[] = { 0x4500, 0x00ad, 0x7755, 0x4000, 0x8006, 0x0000, 
	0x0a97, 0x7819, 0x0a97, 0x781d };
	unsigned short cksum;

	cksum = ipCksum( iph, 20 );
	printf( "%X\n", cksum );
	/* Replace checksum item */
	iph[5] = cksum;
	/* check checksum */
	cksum = ipCksum( iph, 20 );

	if ( cksum ) {
		printf( "Checksum is incorrect!\n" );
	} else {
		printf( "Checksum is correct!\n" );
	}

	return 0;
}
