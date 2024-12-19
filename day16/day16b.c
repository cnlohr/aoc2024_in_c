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


CNRBTREETEMPLATE( int64_t, int64_t, RBptrcmp, RBptrcpy, RBnullop );
typedef cnrbtree_int64_tint64_t intintmap;

int64_t * map;
int maplen;
int mapx;
int mapy;

int64_t *backtrackbitmap;
int backtrackbitmaplen;

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

int64_t COSTANYFN( int64_t * cost, int x, int y) {
	int d;
	int64_t r = INT_MAX;
	for( d = 0; d < 4; d++ )
		if(COST( x, y, d ) > r ) r = COST(x, y, d );
	return r;
}

int64_t COSTALLFN( int64_t * cost, int x, int y) {
	int d;
	int64_t r = 0;
	for( d = 0; d < 4; d++ )
		if(COST( x, y, d ) < r ) r = COST(x, y, d );
	return r;
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

void PrintMapB( int64_t * map )
{
	int x, y;
	for( y = 0; y < mapy; y++ )
	{
		for( x = 0; x < mapx; x++ )
		{
			printf( "%x", (char)MAP(x,y) );
		}
		printf( "\n" );
	}
}

int BackTrack( int x, int y, int sx, int sy )
{
	if( x == sx && y == sy ) return 0;
	MAP(x,y) = 'O';
	int r = 1;
	int d = 0;
	int64_t bb = backtrackbitmap[x+y*mapx];
	backtrackbitmap[x+y*mapx] = 0;
	//printf( "* %d %ld (%d %d)\n", x+y*mapx, backtrackbitmap[x+y*mapx], x, y );
	for( d = 0; d < 4; d++ )
	{
		if( bb & (1<<d) )
		{
			//printf( "B %d %d\n", x-dirx[d], y-diry[d] );
			r += BackTrack( x-dirx[d], y-diry[d], sx, sy );
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
		appendToList64( &backtrackbitmap, &backtrackbitmaplen, 0 );
		tx++;
	}

	intintmap * traversallist = cnrbtree_int64_tint64_t_create();

	int64_t start = COORD(reindeerx, reindeery, reindeerd);
	RBA( traversallist, start ) = 0;

	uint64_t ocost = 0;
	int64_t endkey;
	while(1)
	{
		cnrbtree_int64_tint64_t_node * i = traversallist->begin;
		int count = 0;
		RBFOREACH( int64_tint64_t, traversallist, n )
		{
			if( n->data < i->data ) i = n;
			count++;
		}
		if( count == 0 ) { endkey = -1; break; }
		int d = i->key & 3;
		int x = (i->key >> 2) & 0x3fffffff;
		int y = (i->key) >> 32;
		int dx = dirx[d];
		int dy = diry[d];
		int tcost = i->data;
		int next = MAP( x + dx, y + dy );
		int ths = MAP( x, y ); // probably unused.
		int matching = 0;
		printf( "%d %d %c\n", x, y, next );
		// Can we go forward?
		if( next == 'E' )
		{
			if( COST( x + dx, y + dy, d ) > tcost + 1 )
			{
				backtrackbitmap[x+dx+(y+dy)*mapx] = 0;
			}
			backtrackbitmap[x+dx+(y+dy)*mapx] |= 1<<d;
			printf( "E AT %d %d %d\n", x, y, x+dx+(y+dy)*mapx);
			break;
		}
		if( next == '.' )
		{
			int64_t newkey = COORD( x + dx, y + dy, d );
			if( ( COST( x + dx, y + dy, d ) >= tcost + 1 ) )
			{
				if( COSTALL( x + dx, y + dy, d ) > tcost + 1 )
				{
					backtrackbitmap[x+dx+(y+dy)*mapx] = 0;
				}
				backtrackbitmap[x+dx+(y+dy)*mapx] |= 1<<d;
				RBA( traversallist, newkey ) = tcost + 1;
				if( COST( x + dx, y + dy, d ) > tcost+1 ) COST( x + dx, y+dy, d ) = tcost+1;
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
				RBA( traversallist, newkey ) = ncost;
				COST( x, y, nd ) = ncost;
			}
		}
		
		RBREMOVE( traversallist, i );
	}

//	RevTrav( completelistprevlist, endkey, start );

	PrintMapB( backtrackbitmap );

	BackTrack( reindeerendx, reindeerendy, reindeerx, reindeery );

	int x, y;

	for( y = 0; y < mapy; y++ )
	for( x = 0; x < mapx; x++ )
	{
		int c = MAP( x, y );
		ocost += 'O' == c || 'S' == c;
	}

	PrintMap( map );
	//SolveMap( reindeerx, reindeery, reindeerd, reindeerendx, reindeerendy );
	printf( "%lx\n", endkey );
	printf( "%ld\n", ocost );
}
// 580 is too high.
// 580 - 38 ???
// 542 too high.
// -10
// 532 too high
// 528 << Not 528
