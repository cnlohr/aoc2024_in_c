#include "aoclib.h"

int * map = 0;
int nummap = 0;
int lx, ly;

int guardx, guardy;
int guarddir = 0;

const int gdx[] = { 0, 1, 0, -1 };
const int gdy[] = { -1, 0, 1, 0 };

int main()
{
	int locations = 0;
	int x, y;
	int xthisline = 0;
	while( !iseof() )
	{
		int c = gchar();
		if( c == '\n')
		{
			if( xthisline > 0 ) ly++;
			xthisline = 0;
		}
		else
		{
			if( c == '^' )
			{
				guardx = xthisline;
				guardy = ly;
			}
			appendToList( &map, &nummap, c );
			if( ly == 0 ) lx++;
			xthisline++;
		}
	}

	if( xthisline != 0 ) ly++;
	
	// "Including the guard's starting position" may be a lie?
	// If I mark the starting place with an X, I get the wrong answer.
	map[guardx + guardy*lx] = 'X';

	while( 1 )
	{
		int nextx = guardx + gdx[guarddir];
		int nexty = guardy + gdy[guarddir];
		if( map[nextx+nexty*lx] == '#' )
		{
			guarddir = (guarddir + 1) % 4;
		}
		else
		{
			guardx = nextx;
			guardy = nexty;
		}
		if( guardx < 0 || guardx >= lx || guardy < 0 || guardy >= ly ) break;
		map[guardx + guardy*lx] = 'X';
	}

	for( y = 0; y < ly; y++ )
	{
		for( x = 0; x < lx; x++ )
		{
			int c = map[x+y*lx];
			printf( "%c", c );
			if( c == 'X' ) locations++;
		}
		printf( "; %d\n", locations );
	}
	printf( "%d\n", locations );
	//printf( "%d %d\n", lx,ly );
}