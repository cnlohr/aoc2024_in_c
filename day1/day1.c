#include "aoclib.h"

int main( int argc, char ** argv )
{
	int * left = 0;  int leftlen = 0;
	int * right = 0; int rightlen = 0;

	while( !iseof() )
	{
		if( peekChar() == '\n' ) { gchar(); continue; }

		int n1, n2;
		consumeWhitespace();
		if( !takeNumber( &n1 ) ) terror( "can't get num 1" );
		consumeWhitespace();
		if( !takeNumber( &n2 ) ) terror( "can't get num 2" );
		appendToList( &left, &leftlen, n1 );
		appendToList( &right, &rightlen, n2 );
		takeChar('\n' );
	}
	quickSort( left, 0, leftlen-1 );
	quickSort( right, 0, rightlen-1 );

	int r;
	int sumrun = 0;
	for( r = 0; r < leftlen; r++ )
	{
		int diff = left[r] - right[r];
		if( diff < 0 ) diff = -diff;
		sumrun += diff;
	}
	printf( "%d\n", sumrun );
	return 0;
}

