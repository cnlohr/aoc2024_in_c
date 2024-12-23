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

	int i;
	u64 sum = 0;
	for( i = 0; i < computerlistlen; i++ )
	{
		int j;
		int ci = computerlist[i];
		for( j = 0; j < computerlistlen; j++ )
		{
			int cj = computerlist[j];
			if( connectionmap[ci][cj] )
			{
				int k;
				for( k = 0; k < computerlistlen; k++ )
				{
					int ck = computerlist[k];
					if( connectionmap[ci][ck] && connectionmap[cj][ck] )
					{
						if( ci / 26 == 't'-'a' ||
							cj / 26 == 't'-'a' ||
							ck / 26 == 't'-'a' )
						{
							//printf( "%c%c,%c%c,%c%c\n", CtoS(ci), CtoS(cj), CtoS(ck) );
							sum++;
						}
					}
				}
			}
		}
		//sum += num;
	}
	printf( "%ld\n", sum );

	return 0;
}
