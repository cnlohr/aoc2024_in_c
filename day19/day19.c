#include "aoclib.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

char ** towels;
int towellen;

char ** targets;
int targetslen;

#define CNRBTREE_IMPLEMENTATION
#include "cnrbtree.h"

typedef char * str;
typedef uint64_t u64;
CNRBTREETEMPLATE( str, u64, RBstrcmp, RBstrstrcpy, RBstrdel );

cnrbtree_stru64 * memo;

u64 Solvable( char * target, int depth )
{
	int t;
	u64 sum = 0;

	cnrbtree_stru64_node * cache = RBHAS( memo, target );
	if( cache )
	{
		//printf( "C%*s%s -> %d\n", depth, "", target, RBA( memo, target ) );
		return cache->data;
	}

	//printf( "N%*s%s\n", depth, "", target );
	for( t = 0; t < towellen; t++ )
	{
		if( strsubmatch( towels[t], target ) == 0 )
		{
			int ttst = strlen( towels[t] );
			//printf( ">%*s%s\n", depth, "", towels[t] );
			u64 solvable = 0;
			if( strlen( towels[t] ) >= strlen( target ) ) solvable = 1;
			else solvable += Solvable( target + ttst, depth+1 );
			sum+=solvable;
			//printf( "<%*s%s %d (%d)\n", depth, "", towels[t], solvable, sum );
#ifndef PARTB
			if( solvable )
				return 1;
#endif
		}
	}
	//printf( "O%*s%s %d\n", depth, "", target, sum );

	RBA( memo, target ) = sum;

	return sum;
}

int main()
{
	uint8_t * bytepairs = 0;
	int bytepairlen = 0;

	memo = cnrbtree_stru64_create();

	{
		char * thistowel = 0;
		int thistowellen = 0;
		while( !iseof() )
		{
			int c;
			for(;;)
			{
				c = gchar();
				if( c == ',' ) break;
				else if( c == '\n' ) break;
				else if( c == 'w' || c == 'u' || c == 'b' || c == 'r' || c == 'g' )
				{
					appendToListC( (unsigned char**)&thistowel, &thistowellen, c );
				}
				else terror( "Bad color" );
			}
			if( thistowellen )
			{
				appendToListC( (unsigned char**)&thistowel, &thistowellen, 0 );
				appendToListP( (void***)&towels, &towellen, thistowel );
			}
			thistowel = 0;
			thistowellen = 0;
			if( takeChar('\n' ) ) break;
			if( !takeChar(' ') ) terror( "Expected space" );
		}

		takeChar( '\n' ); // get rid of extra newline

		while( !iseof() )
		{
			while( !iseof() )
			{
				int c = gchar();
				if( c == '\n' )
				{
					break;
				}
				else if( c == 'w' || c == 'u' || c == 'b' || c == 'r' || c == 'g' )
				{
					appendToListC( (unsigned char**)&thistowel, &thistowellen, c );
				}
				else terror( "Bad color" );
			}

			if( thistowellen )
			{
				appendToListC( (unsigned char**)&thistowel, &thistowellen, 0 );
				appendToListP( (void***)&targets, &targetslen, thistowel );
			}
			thistowel = 0;
			thistowellen = 0;
		}
	}

	//printf( "%d Towels [%s], %d Targets [%s]\n", towellen, towels[0], targetslen, targets[0] );
	int t;
	int64_t sum = 0;
	for( t = 0; t < targetslen; t++ )
	{
		int64_t solvable = Solvable( targets[t], 0 );
		//printf( "%ld: %s\n", solvable, targets[t] );
		sum += solvable;
	}
	printf( "%ld\n", sum );

	return 0;
}

// 319 for part A
// Not 692575723305545 for part b
