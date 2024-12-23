#include "aoclib.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define CNRBTREE_IMPLEMENTATION
#include "cnrbtree.h"

// Holy C-Style
typedef uint64_t u64;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint8_t u8;

// Be as triangular-ish as possible.
// Only connect lower-upper.
u8 connectionmap[676][676];

int * computerlist;
int computerlistlen;

#define CtoS( c ) ((c/26)+'a'), ((c%26)+'a')

int gcharA()
{
	int c = gchar();
	if( c < 'a' || c > 'z' ) terror( "invalid char" );
	return c - 'a';
}

void GetInterconnection( int * interconnectlist, int * bestlist, int * bestdepth, int icl )
{
	int j;
	for( j = 0; j < computerlistlen; j++ )
	{
		int cj = computerlist[j];

		int c;
		for( c = 0; c < icl; c++ )
		{
			int ctw = interconnectlist[c];
			if( ctw == cj )
				break;
			if( !connectionmap[ctw][cj] && !connectionmap[cj][ctw] )
				break;
		}
		if( c != icl ) continue;
		interconnectlist[icl++] = cj;

		if( icl > *bestdepth )
		{
			memcpy( bestlist, interconnectlist, sizeof(int)*icl );
			*bestdepth = icl;
		}

		GetInterconnection( interconnectlist, bestlist, bestdepth, icl );
	}
	return;
}


int main()
{
	{
		u8 addedcomputer[676] = { 0 };
		while( !iseof() )
		{
			u32 comp1 = gcharA() * 26;
			comp1 += gcharA();
			if( !takeChar( '-' ) )
				terror( "Not a Number" );
			u32 comp2 = gcharA() * 26;
			comp2 += gcharA();
			if( !takeChar( '\n' ) )
				terror( "No ending" );
			takeChar('\n');

			if( comp1 < comp2 )
				connectionmap[comp1][comp2] = 1;
			else
				connectionmap[comp2][comp1] = 1;

			if( !addedcomputer[comp1] )
			{
				appendToList( &computerlist, &computerlistlen, comp1 );
				addedcomputer[comp1] = 1;
			}
			if( !addedcomputer[comp2] )
			{
				appendToList( &computerlist, &computerlistlen, comp2 );
				addedcomputer[comp2] = 1;
			}
		}
	}

	quickSort( computerlist, 0, computerlistlen-1 );

	int i;
	//u64 sum = 0;
	int interconnectlist[676] = { 0 };
	int bestlist[676] = { 0 };
	int bestdepth = 0;
	int interconnectlistplace = 0;
	int bestoveralldepth = 0;
	int bestoveralllist[676] = { 0 };
	for( i = 0; i < computerlistlen; i++ )
	{
		int ci = computerlist[i];
		interconnectlist[0] = ci;
		interconnectlistplace = 1;
		bestdepth = 0;
		GetInterconnection( interconnectlist, bestlist, &bestdepth, interconnectlistplace );
		if( bestdepth > bestoveralldepth )
		{
			bestoveralldepth = bestdepth;
			memcpy( bestoveralllist, bestlist, bestdepth * sizeof( int ) );
#if 0
	printf( "***\n" );
	for( i = 0; i < bestoveralldepth; i++ )
	{
		printf( "%c%c,", CtoS( bestoveralllist[i] ) );
	}
	printf( "%d\n", bestoveralldepth );
#endif
		}
	}

	quickSort( bestoveralllist, 0, bestoveralldepth-1 );
#if 1
	for( i = 0; i < bestoveralldepth; i++ )
	{
		printf( "%c%c%c", CtoS( bestoveralllist[i] ), (i==bestoveralldepth-1)?'\n':',' );
	}
	//printf( "%d\n", bestoveralldepth );
#endif
//	printf( "%ld\n", sum );

	return 0;
}
