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
	uint64_t ntestmask;
	for( ntestmask = 0; ntestmask < 1<<(2*(nremain-1)); ntestmask++ )
	{
		
		int64_t running = listremain[0];
		for( o = 1; o < nremain; o++ )
		{
			int op = (ntestmask >> ((o-1)*2))&3;
			//printf( "[%d,%d,%d]", ntestmask, op, o );
			int64_t v = listremain[o];
			if( op == 0 )
				running = running * v;
			else if( op == 1 )
				running = running + v;
			else if( op == 2 )
				running = running * rebase10(v) + v;
			else
				break;
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
