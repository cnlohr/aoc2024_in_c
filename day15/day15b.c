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

int TryMove( int cx, int cy, int dx, int dy, int check )
{
	int nx = cx + dx;
	int ny = cy + dy;
	//int tm = MAP( cx, cy );
	int om = MAP( nx, ny );
	//printf( "%d\n", om); // XXX??? XXX ??? Creates bad output
	//printf( "%d, %d; %c\n", nx, ny, om );
	if( om == '#' )
	{
		return 0;
	}
	else if( om == '.' )
	{
		return 1;
	}
	else if( dy == 0 && ( om == '[' || om == ']' ) )
	{
		int next = TryMove( nx, ny, dx, dy, check );
		if( next == 0 ) return 0;
		if( !check ) MAP( nx+dx, ny+dy ) = om;
		return 1;
	}
	else if( om == '[' )
	{
		//printf( "TMAIN %d %d\n", nx, ny );
		int nextA = TryMove( nx, ny, dx, dy, check );
		int nextB = TryMove( nx+1, ny, dx, dy, check );
		//printf( "TMA %d %d\n", nextA, nextB );
		if( nextA == 0 || nextB == 0 ) return 0;
		if( !check )
		{
			MAP( nx+dx, ny+dy ) = '[';
			MAP( nx+dx+1, ny+dy ) = ']';
			MAP( nx, ny ) = '.';
			MAP( nx+1, ny ) = '.';
		}
		return 1;
	}
	else if( om == ']' )
	{
		//printf( "TMBIN %d %d\n", nx, ny );
		int nextA = TryMove( nx, ny, dx, dy, check );
		int nextB = TryMove( nx-1, ny, dx, dy, check );
		if( nextA == 0 || nextB == 0 ) return 0;
		//printf( "TMB %d %d\n", nextA, nextB );
		if( !check )
		{
			MAP( nx+dx, ny+dy ) = ']';
			MAP( nx+dx-1, ny+dy ) = '[';
			MAP( nx, ny ) = '.';
			MAP( nx-1, ny ) = '.';
		}
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
			appendToList( &map, &maplen, '@' );
			appendToList( &map, &maplen, '.' );
		}
		if( c == '#' )
		{
			appendToList( &map, &maplen, '#' );
			appendToList( &map, &maplen, '#' );
		}
		if( c == 'O' )
		{
			appendToList( &map, &maplen, '[' );
			appendToList( &map, &maplen, ']' );
		}
		if( c == '.' )
		{
			appendToList( &map, &maplen, '.' );
			appendToList( &map, &maplen, '.' );
		}
		tx+=2;
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
	//PrintWarehouse( map );
	for( i = 0; i < moveslen; i++ )
	{
		int m = moves[i];
		static const int dirx[] = { -1, 0, 1, 0 };
		static const int diry[] = { 0,  1, 0,-1 };
		int mx = dirx[m];
		int my = diry[m];
		//printf( "Move: %d (%d,%d) @ %d\n", m, mx, my, i );
		if( TryMove( robotx, roboty, mx, my, 1 ) )
		{
			TryMove( robotx, roboty, mx, my, 0 );
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
			if( MAP( x, y ) == '[' )
			{
				sum += x + y * 100;
			}
		}
	}
	printf( "%ld\n", sum );
}

