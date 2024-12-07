#include "aoclib.h"
#include <stdint.h>

// Goal: Get the combination of things as close to nmaxanswer without going over.
int experiment( int64_t * listremain, int nremain, int64_t nmaxanswer )
{
	if( nremain > 31 ) terror( "too many numbers" );
	int o;
	int test;
	uint64_t ntestmask;
	for( ntestmask = 0; ntestmask < 1<<(nremain-1); ntestmask++ )
	{
		
		int64_t running = listremain[0];
		for( o = 1; o < nremain; o++ )
		{
			int op = (ntestmask >> (o-1))&1;
			//printf( "[%d,%d,%d]", ntestmask, op, o );
			int v = listremain[o];
			if( op )
				running = running * v;
			else
				running = running + v;
		}
		if( running == nmaxanswer ) return 1;
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

// Tried 619777075 - but no dice.  (Input overload)
// Tried 21617015027 - but no dice.
