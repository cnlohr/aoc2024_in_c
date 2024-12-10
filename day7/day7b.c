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

int experiment( int64_t * listremain, int nremain, int64_t answer )
{
	// Compute with operations from left to right.
	int64_t cribbed[nremain];
	int cribop[nremain-1];
	int b = 0;
	int i;

	cribbed[0] = listremain[0];

	for( i = 0; i < nremain-1; i++ ) cribop[i] = 0;

	goto compute;

	carry:		// Start at the end and enumerate to a new operator.
		for( b = nremain - 2; ; b-- )
		{
			if( b < 0 )
				return 0;

			int next = (cribop[b] + 1) % 3;
			cribop[b] = next;

			// If we have to overflow the front, break out.
			if( next != 0 )
				break;
		}

	compute:	// Only compute the values that have changed.
		b++;
		int64_t last = cribbed[b-1];

		for( ; b < nremain; b++ )
		{
			int op = cribop[b-1];
			int val = listremain[b];
			if( op == 0 )
				last = last + val;
			else if( op == 1 )
				last = last * val;
			else if( op == 2 )
				last = last * rebase10(val) + val;
			cribbed[b] = last;
		}

		if( last == answer )
			return 1;

		goto carry;
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

