#include "aoclib.h"

int main()
{
	int safect = 0;
	while( !iseof() )
	{
		if( peekChar() == '\n' ) { gchar(); continue; }
		int direction = 0;
		int safe = 1;
		int last;
		if( !takeNumber( &last ) )
			terror( "failed to get first number" );
		while( peekChar() != '\n' )
		{
			int nnum;
			consumeWhitespace();
			if( !takeNumber( &nnum ) )
				terror( "failed to get subsequent number" );
			if( direction == 0 )
			{
				direction = ( nnum > last ) ? 1 : -1;
			}
			int diff = (nnum-last) * direction;
			if( diff < 1 || diff > 3 )
			{
				safe = 0;
			}
			last = nnum;
		}
		int c = gchar();
		if( safe ) safect++;
	}
	printf( "%d\n", safect );
	return 0;
}


