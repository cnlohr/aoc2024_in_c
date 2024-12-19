// I AM NOT PROUD OF THIS. I AM REALY NOT PROUD OF THIS.
// I really wish I had a precanned priority queue
// or an RB Multimap
// 
// NOTE: OMG I HAD THE ANSWER THE WHOLE TIME: RBptrcmpnomatch
//
// Doesn't actually work without manual fixup.
#include "aoclib.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define CNRBTREE_IMPLEMENTATION
#include "cnrbtree.h"

typedef uint64_t u64;
CNRBTREETEMPLATE( u64, u64, RBptrcmpnomatch, RBptrcpy, RBnullop );

int64_t * map;
int maplen;
int mapx;
int mapy;

int64_t * cost;
int costlen;

int reindeerx;
int reindeery;
int reindeerd;

int reindeerendx;
int reindeerendy;

#define MAP(x,y) (*ml( map, x, y))
#define COST(x,y,d) (*ml3( cost, x, y, d ))

#define COSTANY(x,y,dummy) (COSTANYFN( cost, x, y ))
#define COSTALL(x,y,dummy) (COSTALLFN( cost, x, y ))

#define COORD(x,y,d) ( ((uint64_t)x<<2)  | (((uint64_t)y)<<32ULL) | (d) )

int valid( int x, int y )
{
	return ( x >= 0 && y >= 0 && x < mapx && y < mapy );
}

int64_t * ml( int64_t * map, int x, int y )
{
	if( valid( x, y ) )
		return & map[x+y*mapx];
	else
	{
		static int64_t dead = '.';
		return &dead;
	}
}


int64_t * ml3( int64_t * map, int x, int y, int d )
{
	if( valid( x, y ) )
		return & map[(x+y*mapx)*4+d];
	else
	{
		static int64_t dead = '.';
		return &dead;
	}
}

static const int dirx[] = { -1, 0, 1, 0 };
static const int diry[] = { 0,  1, 0,-1 };

void PrintMap( int64_t * map )
{
	int x, y;
	for( y = 0; y < mapy; y++ )
	{
		for( x = 0; x < mapx; x++ )
		{
			printf( "%c", (char)MAP(x,y) );
		}
		printf( "\n" );
	}
}

void PrintMapC( int64_t * cost )
{
	int x, y;
	for( y = 0; y < mapy; y++ )
	{
		for( x = 0; x < mapx; x++ )
		{
			if( COST(x,y,0) < 100000 ) printf( "%6ld", COST(x,y,0) ); else printf( "      " );
			if( COST(x,y,1) < 100000 ) printf( "%6ld", COST(x,y,1) ); else printf( "      " );
			if( COST(x,y,2) < 100000 ) printf( "%6ld", COST(x,y,2) ); else printf( "      " );
			if( COST(x,y,3) < 100000 ) printf( "%6ld", COST(x,y,3) ); else printf( "      " );
			printf("|");
		}
		printf( "\n" );
	}
}

int BackTrack( int x, int y, int d, int sx, int sy )
{
	if( x == sx && y == sy ) return 0;
	MAP(x,y) = 'O';

	int r = 0;
	int tc = COST( x, y, d );
	int td;
	for( td = 0; td < 4; td++ )
	{
		if( td == d )
		{
			int nx = x - dirx[td];
			int ny = y - diry[td];
			int nc = COST( nx, ny, td );
			if( nc == tc-1 )
				r += BackTrack( nx, ny, td, sx, sy );
		}
		else if( ( td + d ) & 1 )
		{
			int nc = COST( x, y, td );
			if( nc == tc-1000 )
				r += BackTrack( x, y, td, sx, sy );
		}
	}
	return r;
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
		if( c != '#' && c != 'S' && c != 'E' && c != '.' ) terror( "invalid char." );
		if( c == 'S' )
		{
			reindeerx = tx;
			reindeery = ty;
			reindeerd = 2;
		}
		if( c == 'E' )
		{
			reindeerendx = tx;
			reindeerendy = ty;
		}
		appendToList64( &map, &maplen, c );
		appendToList64( &cost, &costlen, INT_MAX );
		appendToList64( &cost, &costlen, INT_MAX );
		appendToList64( &cost, &costlen, INT_MAX );
		appendToList64( &cost, &costlen, INT_MAX );
		tx++;
	}

	cnrbtree_u64u64 * traversallist = cnrbtree_u64u64_create();

	int64_t start = COORD(reindeerx, reindeery, reindeerd);
	RBA( traversallist, 0 ) = start;

	uint64_t ocost = 0;
	int64_t endkey;
	while(1)
	{
		cnrbtree_u64u64_node * i = traversallist->begin;
		if( RBISNIL( i ) )
		{
			break;
		}
		int d = i->data & 3;
		int x = (i->data >> 2) & 0x3fffffff;
		int y = (i->data) >> 32;
		int dx = dirx[d];
		int dy = diry[d];
		int tcost = i->key;
		int next = MAP( x + dx, y + dy );
		int ths = MAP( x, y ); // probably unused.
		int matching = 0;
		// Can we go forward?
		if( next == 'E' )
		{
			COST( x + dx, y+ dy, d ) = tcost + 1;
		}
		if( next == '.' )
		{
			int64_t newkey = COORD( x + dx, y + dy, d );
			int ncost = tcost + 1;
			if( ( COST( x + dx, y + dy, d ) >= ncost ) )
			{
				RBA( traversallist, ncost ) = newkey;
				COST( x + dx, y+dy, d ) = ncost;
			}
		}
		int nd;
		for( nd = 0; nd < 4; nd++ )
		{
			int cd = ((nd - d) + 4 ) % 4;
			if( cd == 2 || cd == 0 ) continue; // can't turn around
			int ncost = tcost + 1000;
			int64_t newkey = COORD( x, y, nd );
			if( ( COST( x, y, nd ) >= ncost ) )
			{
				RBA( traversallist, ncost ) = newkey;
				COST( x, y, nd ) = ncost;
			}
		}
		
		RBREMOVE( traversallist, i );
	}

	//PrintMapC( cost );

	{
		int d;
		int minend = INT_MAX;
		for( d = 0; d < 4; d++ )
			if( COST( reindeerendx, reindeerendy, d ) < minend )
				minend = COST( reindeerendx, reindeerendy, d );
		for( d = 0; d < 4; d++ )
			if( COST( reindeerendx, reindeerendy, d ) == minend )
				BackTrack( reindeerendx, reindeerendy, d, reindeerx, reindeery );
	}

	int x, y;

	for( y = 0; y < mapy; y++ )
	for( x = 0; x < mapx; x++ )
	{
		int c = MAP( x, y );
		ocost += 'O' == c || 'S' == c;
	}

	//PrintMap( map );
	//SolveMap( reindeerx, reindeery, reindeerd, reindeerendx, reindeerendy );
	//printf( "%lx\n", endkey );
	printf( "%ld\n", ocost );
}
// 580 is too high.
// 580 - 38 ???
// 542 too high.
// -10
// 532 too high
// 528 << Not 528
