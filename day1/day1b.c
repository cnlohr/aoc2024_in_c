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
		if( !takeNumber( &n1 ) ) terror( "error getting number 1" ); 
		consumeWhitespace();
		if( !takeNumber( &n2 ) ) terror( "error getting number 2" );
		appendToList( &left, &leftlen, n1 );
		appendToList( &right, &rightlen, n2 );
		takeChar('\n' );
	}
	quickSort( left, 0, leftlen-1 );
	quickSort( right, 0, rightlen-1 );

	int l;
	int r;
	int sumrun = 0;
	for( l = 0; l < leftlen; l++ )
	{
		int lv = left[l];
		for( r = 0; r < rightlen; r++ )
		{
			if( right[r] == lv )
				sumrun += lv;
		}
	}
	printf( "%d\n", sumrun );
	return 0;
}


