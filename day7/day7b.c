#include "aoclib.h"
#include <stdint.h>

int rebase10( int64_t n )
{
	int r = 1;
	do
	{
		r*=10;
		n/=10;
	} while( n );
	return r;
}

// Goal: Get the combination of things as close to nmaxanswer without going over.
int experiment( int64_t * listremain, int nremain, int64_t nmaxanswer )
{
	if( nremain > 31 ) terror( "too many numbers" );
	int o;
	int test;

	int64_t permutations = 1;
	int k;
	for( k = 0; k < nremain-1; k++ )
		permutations *= 3;

	// Before early exit:
	// 482407

	for( int64_t permutation = 0; permutation < permutations; permutation++ )
	{
		int64_t tperm = permutation;		
		int64_t running = listremain[0];
		for( o = 1; o < nremain; o++ )
		{
			int op = tperm % 3;
			//printf( "[%d,%d,%d]", ntestmask, op, o );
			int64_t v = listremain[o];
			switch( op )
			{
			case 0:	running = running * v; break;
			case 1: running = running + v; break;
			case 2: running * rebase10(v) + v; break;
			}
			tperm /= 3;
		}
		if( o == nremain && running == nmaxanswer ) return 1;
		//printf( " T %08x  %d\n", ntestmask, running );
	}
	return 0;
}

int main()
{
	int64_t sum = 0;
	while( !iseof() )
	{
		int64_t answer;
		if( peekChar() == '\n' )
		{
			gchar();
			continue;
		}

		if( !takeNumber64( &answer ) ) terror( "no answer" );

		if( !takeChar( ':' ) ) terror( "no colon" );
		int64_t * nlist = 0;
		int numitems = 0;
		do
		{
			consumeWhitespace();
			int64_t tnum;
			if( !takeNumber64( &tnum ) ) terror( "bad number" );
			appendToList64( &nlist, &numitems, tnum );
		} while( peekChar() != '\n' );
		int ok = experiment( nlist, numitems, answer );
		if( ok ) sum += answer;
		gchar();
		free( nlist );
	}
	printf( "%ld\n", sum );
}

// Part 2 - tried 1437294992354 no dice.
// Answer was 271691107779347
