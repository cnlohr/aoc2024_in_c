#include "aoclib.h"
#include <stdint.h>
#include <string.h>


int * map;
int maplen;
int mapx;
int mapy;

int robotx, roboty;

int * moves;
int moveslen;

#define MAP(x,y) (*ml( map, x, y))
#define COORD(x,y) ( ((uint64_t)x)  | (((uint64_t)y)<<32ULL) )
int valid( int x, int y )
{
	return ( x >= 0 && y >= 0 && x < mapx && y < mapy );
}

int * ml( int * map, int x, int y )
{
	if( valid( x, y ) )
		return & map[x+y*mapx];
	else
	{
		static int dead = '.';
		return &dead;
	}
}

static const int dirx[] = { -1, 0, 1, 0 };
static const int diry[] = { 0,  1, 0,-1 };

void PrintWarehouse( int * map )
{
	int x, y;
	for( y = 0; y < mapy; y++ )
	{
		for( x = 0; x < mapx; x++ )
		{
			printf( "%c", MAP(x,y) );
		}
		printf( "\n" );
	}
}

int TryMove( int cx, int cy, int dx, int dy )
{
	int nx = cx + dx;
	int ny = cy + dy;
	int om = MAP( nx, ny );
	if( om == '#' )
	{
		return 0;
	}
	if( om == '.' )
	{
		return 1;
	}
	if( om == 'O' )
	{
		int next = TryMove( nx, ny, dx, dy );
		if( next == 0 ) return 0;
		MAP( nx+dx, ny+dy ) = om;
		return 1;
	}
	else
	{
		fprintf( stderr, "Fault confusing char %c\n", om );
		exit( -5 );
	}
}

int main()
{
	int64_t sum = 0;
	int tx = 0;
	int ty = 0;
	while( !iseof() )
	{
		int64_t answer;
		if( peekChar() == '\n' )
		{
			if( tx )
			{
				mapx = tx;
				mapy++;
				ty++;
			}
			else
			{
				break;
			}
			tx = 0;

			gchar();
			continue;
		}
		
		int c = gchar();
		if( c != '#' && c != '@' && c != 'O' && c != '.' ) terror( "invalid char." );
		if( c == '@' )
		{
			robotx = tx;
			roboty = ty;
		}
		appendToList( &map, &maplen, c );
		tx++;
	}
	while( !iseof() )
	{
		if( peekChar() == '\n' )
		{
			gchar();
		}
		else
		{
			int c = gchar();
			switch( c )
			{
			case '<': c = 0; break;
			case 'v': c = 1; break;
			case '>': c = 2; break;
			case '^': c = 3; break;
			default: terror( "invalid char" );
			}
			appendToList( &moves, &moveslen, c );
		}
	}
	int i;
	for( i = 0; i < moveslen; i++ )
	{
		int m = moves[i];
		static const int dirx[] = { -1, 0, 1, 0 };
		static const int diry[] = { 0,  1, 0,-1 };
		int mx = dirx[m];
		int my = diry[m];
		//printf( "Move: %d\n", m );
		if( TryMove( robotx, roboty, mx, my ) )
		{
			MAP( robotx+mx, roboty+my ) = '@';
			MAP( robotx, roboty ) = '.';
			robotx += mx;
			roboty += my;
		}
		//PrintWarehouse( map );
	}

	int x, y;
	for( y = 0; y < mapy; y++ )
	{
		for( x = 0; x < mapx; x++ )
		{
			if( MAP( x, y ) == 'O' )
			{
				sum += x + y * 100;
			}
		}
	}
	printf( "%ld\n", sum );
}

