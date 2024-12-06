#include "aoclib.h"

int * map = 0;
int nummap = 0;
int lx, ly;

int * mapin = 0;

const int gdx[] = { 0, 1, 0, -1 };
const int gdy[] = { -1, 0, 1, 0 };

void PrintMap( int * map, int gx, int gy )
{
	int x, y;
	int locations = 0;
	for( y = 0; y < ly; y++ )
	{
		for( x = 0; x < lx; x++ )
		{
			int c = map[x+y*lx];
			printf( "%c", ((x != gx) || (y != gy )) ? c : '^' );
			if( c == 'X' ) locations++;
		}
		printf( "\n" );
	}
	printf( "\n" );
}

int guardrun( int * map, int * loopcheck, int guardx, int guardy )
{
	int guarddir = 0;
	int looped = 0;
	memset( loopcheck, 0, lx*ly*sizeof(int));
	loopcheck[guardx + guardy*lx] |= 1;

	//printf( "%d %d\n", lx,ly );
	int step = 0;
	while( 1 )
	{
		int nextx = guardx + gdx[guarddir];
		int nexty = guardy + gdy[guarddir];
		int nextc = map[nextx+nexty*lx];
		if( nextc == '#' || nextc == 'O' )
		{
			guarddir = (guarddir + 1) % 4;
		}
		else
		{
			guardx = nextx;
			guardy = nexty;
			
			if( !( guardx >= 0 && guardx < lx && guardy >= 0 && guardy < ly  ) ) break;
		}

		int gmask = 1<<guarddir;

		if( loopcheck[guardx + guardy*lx] & gmask )
			return 1;
		//step++;
		//if( step > 200000 ) return 1;
		
		char now = loopcheck[guardx + guardy*lx] |= gmask;
		map[guardx + guardy*lx] = " |-+||++-+-+++++"[now];
	}
	//printf( "\n" );
	return 0;
}

int main()
{
	int guardx = 0;
	int guardy = 0;
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
			appendToList( &mapin, &nummap, c );
			if( ly == 0 ) lx++;
			xthisline++;
		}
	}
	if( xthisline != 0 ) ly++;

	map = malloc( lx * ly * sizeof(int) );
	int * loopcheck = malloc( lx * ly  * sizeof(int) );
	int * firstmap = malloc( lx * ly * sizeof( int ) );
	memcpy( firstmap, mapin, sizeof(int) * lx * ly );
	guardrun( firstmap, loopcheck, guardx, guardy );
	PrintMap( firstmap, guardx, guardy );

	int x, y;
	
	int loops = 0;
	
	for( y = 0; y < ly; y++ )
	{
		for( x = 0; x < lx; x++ )
		{
			memcpy( map, mapin, sizeof(int)*lx*ly );
			int fmhere = firstmap[x+y*lx];
			if( fmhere != '|' && fmhere != '+' && fmhere != '-' ) continue;
			if( x == guardx && y == guardy ) continue;
			map[x+y*lx] = 'O';
			
			int looped = guardrun( map, loopcheck, guardx, guardy );

			if( looped )
			{
				loops++;
			}
		}
	}

	printf( "%d\n", loops );
}


// tried 1709, 1708 (just randomly 1708) -- 1708 is too high. ... not 1707 either.