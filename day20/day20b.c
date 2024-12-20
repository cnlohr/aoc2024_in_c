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
CNRBTREETEMPLATE( u64, u8, RBptrcmp, RBptrcpy, RBnullop );
CNRBTREETEMPLATE( int, int, RBptrcmp, RBptrcpy, RBnullop );

u8 * map;
int maplen;
int mapx;
int mapy;

int * cost;
int costlen;

int * visitlist;
int visitlistlen;

int startx;
int starty;
int endx;
int endy;

int sav100 = 0;
int sav10 = 0;
cnrbtree_intint * savingses;


static const int dirx[] = { -1, 0, 1, 0 };
static const int diry[] = { 0,  1, 0,-1 };

#define MAP(x,y) (*ml( map, x, y))
#define COST(x,y) (*mli( cost, x, y ))
#define VISIT(x,y) (*mli( visitlist, x, y ))
#define QP(sx,sy,ex,ey) ( ((sx)<<0) | ((sy)<<16) | (((u64)ex)<<32) | (((u64)ey)<<48) )
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


cnrbtree_u64u8 * solutionlist;

void ComputeSavingsFrom( int sx, int sy, int x, int y, int cheatamount, int maxcheat, int savingsatstart )
{
	int extent = maxcheat - cheatamount+1;
	int dx, dy;
	for( dy = -extent; dy <= extent; dy++ )
	{
		int def = (dy < 0 ) ? -dy : dy;
		int extentx = extent - def;
		int ny = sy + dy;
		if( ny <=0 || ny >= mapy-1 ) continue;
		for( dx = -extentx; dx <= extentx; dx++ )
		{
			int defx = (dx < 0) ?  -dx: dx;
			int distance = defx + def;
			int nx = sx + dx;
			if( nx <= 0 || nx >= mapx - 1 ) continue;

			//if( distance > maxcheat ) continue;
			{
				int ec = COST( nx, ny );
				int savings = ec - savingsatstart - distance+1;
				if( ec < INT_MAX && savings > 0)
				{
					if( savings > 0 )
					{
						//RBA( savingses, savings )++;
					}
					if( savings >= 100 ) sav100++;
					if( savings >= 10 ) sav10++;
				}
			}
		}
	}
#if 0
	// Old way - do DFS directly.
	cnrbtree_u64u64 * tocalc = cnrbtree_u64u64_create();
	cnrbtree_u64u64_node * n = tocalc->access( tocalc, cheatamount );
	n->data = COORD( x, y );
	do
	{
		int x = (n->data) & 0xffffffff;
		int y = (n->data) >> 32;
		int lcheatamt = n->key;
		RBREMOVE( tocalc, n );
		int d;
		for( d = 0; d < 4; d++ )
		{
			int dx = dirx[d];
			int dy = diry[d];
			int nx = x + dx;
			int ny = y + dy;
			if( nx <= 0 || nx >= mapx-1 || ny <=0 || ny >= mapy-1 ) continue;

			if( VISIT( nx, ny ) >= INT_MAX )
			{
				VISIT( nx, ny ) = 0;

				int next = MAP( nx, ny );

				if( lcheatamt+1 <= maxcheat )
				{
					RBA( tocalc, lcheatamt+1 ) = COORD( nx, ny );
				}

				if( !RBHAS( solutionlist, QP( sx, sy, nx, ny ) ) && next != '#' )
				{
					RBA( solutionlist, QP( sx, sy, nx, ny ) ) = 1;
					int ec = COST( nx, ny );
					int savings = ec - savingsatstart - lcheatamt;
					if( ec < INT_MAX && savings > 0)
					{
						if( savings > 0 )
						{
							RBA( savingses, savings )++;
						}
						if( savings >= 100 ) sav100++;
						if( savings >= 10 ) sav10++;
					}
				}
			}
		}
		n = tocalc->begin;
	} while( !RBISNIL( n ) );
	RBDESTROY( tocalc );
#endif
}


int main()
{
	savingses = cnrbtree_intint_create();
	solutionlist = cnrbtree_u64u8_create();

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

	visitlistlen = maplen;
	visitlist = malloc( visitlistlen * sizeof(int));

	Solve( startx, starty, 0 );
	//int * dupcost = malloc( costlen * sizeof(cost[0]) );
	//u8 * dupmap = malloc( maplen );
	//memcpy( dupcost, cost, costlen* sizeof(cost[0]) );
	//memcpy( dupmap, map, maplen );

	//printf( "COST: %d\n", COST( endx, endy ));
	//int origcost = COST( endx, endy );

	int sy, sx;

	for( sy = 1; sy < mapy-1; sy++ )
	{
		for( sx = 1; sx < mapx-1; sx++ )
		{
			//if( MAP( sx, sy ) == '#' ) continue;
			int tc = COST( sx, sy );
			if( tc >= INT_MAX ) continue;

			int n = 0;
			for( n = 0; n < visitlistlen; n++ )
				visitlist[n] = INT_MAX;
			ComputeSavingsFrom( sx, sy, sx, sy, 1, 20, tc );

#if 0
			int d;
			for( d = 0; d < 4; d++ )
			{
				int nx = sx + dirx[d];
				int ny = sy + diry[d];
				if( nx <= 0 || nx >= mapx-1 || ny <=0 || ny >= mapy-1 ) continue;
				if( MAP( nx, ny ) == '#' )
				{
					printf( "TC: %d\n", tc );
					ComputeSavingsFrom( sx, sy, nx, ny, 1, 19, tc );
				}
			}
#endif
		}
	}

	//RBFOREACH( intint, savingses, i )
	//	fprintf( stderr, "%d cheats that save %d\n", i->data, i->key );
	printf( "%d,%d\n", sav10, sav100 );
	RBDESTROY( savingses );
	//free( dupmap );
	//free( dupcost );
	free( cost );
	free( map );
}
//1863 is too high.
//1461 is too low.

