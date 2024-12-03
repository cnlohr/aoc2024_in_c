#include "aoclib.h"

int isSafe( int * list, int listlen, int skipid )
{
	int i;
	if( listlen < 1 )
		return 0;

	int last = 0;
	int direction = 0;
	int firsthit = 0;

	for( i = 0; i < listlen; i++ )
	{
		int ths = list[i];
		if( i == skipid ) continue;

		if( !firsthit )
		{
			firsthit = 1;
			last = ths;
			continue;
		}

		if( direction == 0 )
		{
			direction = ( ths > last ) ? 1 : -1;
		}
		int diff = ( ths - last ) * direction;
		if( diff < 1 || diff > 3 )
		{
			return 0;
		}
		last = ths;
	}
	return 1;
}

int main()
{
	int safect = 0;
	while( !iseof() )
	{
		if( peekChar() == '\n' ) { gchar(); continue; }
		int direction = 0;
		int unsafect = 0;

		int * list = 0;
		int listlen = 0;

		while( peekChar() != '\n' )
		{
			int num;
			consumeWhitespace();
			if( !takeNumber( &num ) )
				terror( "error getting number" );
			appendToList( &list, &listlen, num );
		}
		gchar();

		if( isSafe( list, listlen, -1 ) )
		{
			safect++;
		}
		else
		{
			int remove = 0;
			for( int i = 0; i < listlen; i++ )
			{
				if( isSafe( list, listlen, i ) )
				{
					safect++;
					break;
				}
			}
		}
		free( list );
	}
	printf( "%d\n", safect );
	return 0;
}

// 470 to 593

