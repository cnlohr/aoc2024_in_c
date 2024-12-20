#include "aoclib.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define CNRBTREE_IMPLEMENTATION
#include "cnrbtree.h"

// Holy C-Style
typedef uint64_t u64;
typedef uint8_t u8;

CNRBTREETEMPLATE( u64, u64, RBptrcmpnomatch, RBptrcpy, RBnullop );
CNRBTREETEMPLATE( int, int, RBptrcmp, RBptrcpy, RBnullop );

u8 * map;
int maplen;
int mapx;
int mapy;

int * cost;
int costlen;

int startx;
int starty;
int endx;
int endy;

static const int dirx[] = { -1, 0, 1, 0 };
static const int diry[] = { 0,  1, 0,-1 };

#define MAP(x,y) (*ml( map, x, y))
#define COST(x,y) (*mli( cost, x, y ))

#define COORD(x,y) ( ((uint64_t)x)  | (((uint64_t)y)<<32ULL) )


int valid( int x, int y )
{
	return ( x >= 0 && y >= 0 && x < mapx && y < mapy );
}


u8 * ml(u8 * map, int x, int y )
{
	if( valid( x, y ) )
		return &map[x+y*mapx];
	else
	{
		static u8 dead = '.';
		return &dead;
	}
}

int * mli(int * map, int x, int y )
{
	if( valid( x, y ) )
		return &map[x+y*mapx];
	else
	{
		static int dead = '.';
		return &dead;
	}
}

void Solve( int sx, int sy, int initialcost )
{
	cnrbtree_u64u64 * tocalc = cnrbtree_u64u64_create();
	cnrbtree_u64u64_node * n = tocalc->access( tocalc, initialcost );
	n->data = COORD( sx, sy );
	do
	{
		int x = (n->data) & 0xffffffff;
		int y = (n->data) >> 32;
		int tcost = n->key;
		RBREMOVE( tocalc, n );
		if( COST( x, y ) > tcost )
		{
			COST( x, y ) = tcost;
			int ncost = tcost + 1;
			int d;
			for( d = 0; d < 4; d++ )
			{
				int dx = dirx[d];
				int dy = diry[d];
				int nx = x + dx;
				int ny = y + dy;

				if( COST( nx, ny ) > ncost )
				{
					int next = MAP( nx, ny );
					if( next == '.' || next == 'E' )
					{
						RBA( tocalc, ncost ) = COORD( nx, ny );
					}
				}
			}
		}
		n = tocalc->begin;
	} while( !RBISNIL( n ) );
	RBDESTROY( tocalc );
}


int main()
{
	int tx = 0;
	int ty = 0;
	while( !iseof() )
	{
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
		if( c != '#' && c != 'S' && c != 'E' && c != '.' ) terror( "invalid char." );
		if( c == 'S' )
		{
			startx = tx;
			starty = ty;
		}
		if( c == 'E' )
		{
			endx = tx;
			endy = ty;
		}
		appendToListC( &map, &maplen, c );
		appendToList( &cost, &costlen, INT_MAX );
		tx++;
	}

	Solve( startx, starty, 0 );
	//int * dupcost = malloc( costlen * sizeof(cost[0]) );
	//u8 * dupmap = malloc( maplen );
	//memcpy( dupcost, cost, costlen* sizeof(cost[0]) );
	//memcpy( dupmap, map, maplen );

	//printf( "COST: %d\n", COST( endx, endy ));
	//int origcost = COST( endx, endy );

	int sy, sx;
	int sav100 = 0;
	int sav10 = 0;

	cnrbtree_intint * savingses = cnrbtree_intint_create();

	for( sy = 1; sy < mapy-1; sy++ )
	{
		for( sx = 1; sx < mapx-1; sx++ )
		{
			if( MAP( sx, sy ) == '#' ) continue;
			int d;
			int tc = COST( sx, sy );
			if( tc >= INT_MAX ) continue;
			for( d = 0; d < 4; d++ )
			{
				int dx = dirx[d];
				int dy = diry[d];
				int x = sx + dx;
				int y = sy + dy;
				int nx = x + dx;
				int ny = y + dy;

				if(  x <= 0 ||  x >= mapx-1 ||  y <=0 || y  >= mapy-1 ) continue;
				if( nx <= 0 || nx >= mapx-1 || ny <=0 || ny >= mapy-1 ) continue;
				if( MAP( x, y ) != '#' ) continue;
				if( MAP( nx, ny ) == '#' && MAP( nx + dx, ny + dy ) == '#' ) continue;
				//if( tc > COST( nx, ny ) ) continue;

				//MAP( x, y ) = '.';
				//MAP( nx, ny ) = '.';
				//Solve( x, y, tc + 1 );
				//int shortcutcost = COST( endx, endy );
				//int savings = origcost - shortcutcost;
				int term = COST( nx, ny );
				int savings = term - tc - 1;
				if( savings > 0 )
				{
					RBA( savingses, savings )++;
				}
				if( savings >= 100 ) sav100++;
				if( savings >= 10 ) sav10++;
			}
		}
	}

	//RBFOREACH( intint, savingses, i )
	//{
	//	fprintf( stderr, "%d cheats that save %d\n", i->data, i->key );
	//}
	printf( "%d,%d\n", sav10, sav100 );
	RBDESTROY( savingses );
	//free( dupmap );
	//free( dupcost );
	free( cost );
	free( map );
}
//1863 is too high.
//1461 is too low.

