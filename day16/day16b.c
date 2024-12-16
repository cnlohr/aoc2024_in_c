// I AM NOT PROUD OF THIS. I AM REALY NOT PROUD OF THIS.
// I really wish I had a precanned priority queue
// or an RB Multimap.
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

int64_t * cost;
int costlen;

int reindeerx;
int reindeery;
int reindeerd;

int reindeerendx;
int reindeerendy;

#define MAP(x,y) (*ml( map, x, y))
#define COST(x,y) (*ml( cost, x, y ))

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

void BackTrack( int x, int y, int sx, int sy )
{
	if( x == sx && y == sy ) return;
	MAP(x,y) = 'O';

	printf( "%d %d %d\n", x, y, COST( x, y ) );
	int TC = COST( x, y );
	int ad = 0;
	int lowestcost = INT_MAX;
	for( ad = 0; ad < 4; ad++ )
	{
		int dx = dirx[ad];
		int dy = diry[ad];
		if( MAP( x+dx, y+dy ) == '.' && COST( x+dx, y+dy ) < lowestcost ) lowestcost = COST( x+dx, y+dy );
	}

	for( ad = 0; ad < 4; ad++ )
	{
		int dx = dirx[ad];
		int dy = diry[ad];
		if( MAP( x+dx, y+dy ) == '.' && COST( x+dx, y+dy ) == lowestcost ) BackTrack( x + dx, y + dy, sx, sy );
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
		tx++;
	}

	intintmap * traversallist = cnrbtree_int64_tint64_t_create();
	intintmap * completelist = cnrbtree_int64_tint64_t_create();
	intintmap * completelistprev = cnrbtree_int64_tint64_t_create();

	int64_t start = COORD(reindeerx, reindeery, reindeerd);
	RBA( traversallist, start ) = 0;

	uint64_t ocost = 0;
	int64_t endkey;
	while(1)
	{
		cnrbtree_int64_tint64_t_node * i = traversallist->begin;
		RBFOREACH( int64_tint64_t, traversallist, n )
		{
			if( n->data < i->data ) i = n;
		}

		if( RBISNIL( i ) ) { endkey = -1; break; }
		int d = i->key & 3;
		int x = (i->key >> 2) & 0x3fffffff;
		int y = (i->key) >> 32;
		int dx = dirx[d];
		int dy = diry[d];
		int tcost = i->data;
		int next = MAP( x + dx, y + dy );
		int ths = MAP( x, y ); // probably unused.
		int matching = 0;
	//	printf( "%d %d %c\n", x, y, next );
		// Can we go forward?
	//	if( next == 'E' )
	//	{
	//		endkey = i->key;
	//		ocost = tcost + 1;
	//		break;
	//	}
		if( next == '.' )
		{
			int64_t newkey = COORD( x + dx, y + dy, d );
			cnrbtree_int64_tint64_t_node * has = RBHAS( completelist, newkey );
			if( ( has && RBA( completelist, newkey ) >= tcost + 1 ) || !has )
			{
				RBA( completelist, newkey ) = tcost + 1;
				RBA( completelistprev, newkey ) = i->key;
				RBA( traversallist, newkey ) = tcost + 1;
				if( COST( x + dx, y + dy ) > tcost+1 ) COST( x + dx, y+dy ) = tcost+1;
			}
		}
		int nd;
		for( nd = 0; nd < 4; nd++ )
		{
			int cd = ((nd - d) + 4 ) % 4;
			if( cd == 2 || cd == 0 ) continue; // can't turn around
			int ncost = tcost + 1000;
			int64_t newkey = COORD( x, y, nd );
			cnrbtree_int64_tint64_t_node * has = RBHAS( completelist, newkey );
			if( ( has && RBA( completelist, newkey ) >= ncost ) || !has )
			{
				RBA( completelist, newkey ) = ncost;
				RBA( completelistprev, newkey ) = i->key;
				RBA( traversallist, newkey ) = ncost;
				if( COST( x, y ) > ncost ) COST( x, y ) = ncost;
			}
		}
		
		RBREMOVE( traversallist, i );
	}

//	RevTrav( completelistprevlist, endkey, start );

	BackTrack( reindeerendx, reindeerendy, reindeerx, reindeery );


	PrintMap( map );
	//SolveMap( reindeerx, reindeery, reindeerd, reindeerendx, reindeerendy );
	printf( "%lx\n", endkey );
	printf( "%ld\n", ocost );
}

