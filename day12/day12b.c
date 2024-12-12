#include "aoclib.h"
#include <stdint.h>
#include <string.h>


#define CNRBTREE_IMPLEMENTATION
#include "cnrbtree.h"


CNRBTREETEMPLATE( int64_t, int64_t, RBptrcmp, RBptrcpy, RBnullop );
typedef cnrbtree_int64_tint64_t intintmap;

intintmap * cleartree;
intintmap * parametermap;

int * map;
int maplen;
int mapx;
int mapy;

#define MAP(x,y) (*ml( x, y))
#define COORD(x,y) ( ((uint64_t)x)  | (((uint64_t)y)<<32ULL) )
int valid( int x, int y )
{
	return ( x >= 0 && y >= 0 && x < mapx && y < mapy );
}

int * ml( int x, int y )
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

void ComputeAP( int x, int y, int * a, int * p )
{
	int tc = MAP( x, y );

	RBA( cleartree, COORD( x, y ) ) = 1;

	(*a)++;

	int dir;
	for( dir = 0; dir < 4; dir++ )
	{
		int tx = x + dirx[dir];
		int ty = y + diry[dir];
		int cc = MAP( tx, ty );
		if( cc == tc && !RBHAS( cleartree, COORD( tx, ty ) ) )
		{
			ComputeAP( tx, ty, a, p );
		}
		else if( cc != tc )
		{
			RBA( parametermap, COORD( tx, ty ) ) = 1;
			(*p)++;
		}
	}
}

int ComputeSides()
{
	int x, y;
	int sides = 0;
	while( parametermap->size )
	{
		// Take top, left-most parameter element.
		cnrbtree_int64_tint64_t_node * n = tree->begin;
		x = n->key & 0xffffffff;
		y = n->key >> 32;
		int dir;
		for( dir = 0; dir < 4; dir++ )
		{
			int tx = x + dirx[dir];
			int ty = y + diry[dir];
			if( RBHAS( parametermap, COORD( tx, ty ) )
				break;
		}

		if( dir == 4 )
		{
			terror( "Parameter broken\n" );
		}

		

		RBFOREACH( int64int64_t, parametermap, n )
		{
			
			break;
		}
	}
	int64_t firstp = 
	RBFOREACH( int64_tint64_t, cleartree, n )

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
			tx = 0;

			gchar();
			continue;
		}
		
		int c = gchar();
		if( c < 'A' || c > 'Z' ) terror( "invalid char." );
		appendToList( &map, &maplen, c );
		tx++;
	}

	cleartree = cnrbtree_int64_tint64_t_create();

	int x, y;
	for( y = 0; y < mapy; y++ )
	{
		for( x = 0; x < mapx; x++ )
		{
			int a, p;
			if( MAP(x,y) != '.' )
			{
				int z = MAP(x, y);
				a = 0; p = 0;
				ComputeAP( x, y, &a, &p );
				//printf( "Zone: %c at %d,%d = %d,%d\n", z, x, y, a, p );
				// Part 1
				//sum += ((int64_t)a)*(int64_t)p;

				int sides = ComputeSides();
				RBFOREACH( int64_tint64_t, cleartree, n )
				{
					int64_t c = n->key;
					MAP( c & 0xffffffff, c >> 32 ) = '.';
				}
			}
		}
	}

	printf( "%ld\n", sum );
}

