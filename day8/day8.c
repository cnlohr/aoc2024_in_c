#include "aoclib.h"
#include <stdint.h>

int * map;
int mapx;
int mapy;
int maplen;
int hastower[256];
int * towerlistx[256];
int * towerlisty[256];
int towerlistxct[256];
int towerlistyct[256];

int CountNodes( int * omap, int tid )
{
	int sums = 0;
	int * towerxs;
	int * towerys;
	int towerxct;
	int toweryct;

	int * ttlx = towerlistx[tid];
	int * ttly = towerlisty[tid];
	int tct = towerlistxct[tid];

	int ot = 0;
	int it = 0;
	for( ot = 0; ot < tct; ot++ )
	{
		int x1 = ttlx[ot];
		int y1 = ttly[ot];
		for( it = 0; it < tct; it++ )
		{
			if( it == ot ) continue;
			int x2 = ttlx[it];
			int y2 = ttly[it];
			int dx = (x2 - x1);
			int dy = (y2 - y1);
#if PARTB
			int ox = x2;
			int oy = y2;
			do
			{
				//printf( "%d, %d -> %d %d / %d %d / %d %d\n", ot, it, x1, y1, x2, y2, ox, oy );
				if( ox >= 0 && oy >= 0 && ox < mapx && oy < mapy )
				{
					if( omap[ox+oy*mapx] != '#' ) sums++;
					omap[ox+oy*mapx] = '#';
				}
				else
				{
					break;
				}
				ox += dx;
				oy += dy;
			} while( 1 );
#else
			int ox = x2 + dx;
			int oy = y2 + dy;
			//printf( "%d, %d -> %d %d / %d %d / %d %d\n", ot, it, x1, y1, x2, y2, ox, oy );
			if( ox >= 0 && oy >= 0 && ox < mapx && oy < mapy )
			{
				if( omap[ox+oy*mapx] != '#' ) sums++;
				omap[ox+oy*mapx] = '#';
			}
#endif
		}
	}

	return sums;
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
		if( c != '.' )
		{
			hastower[c] = 1;
			appendToList( &towerlistx[c], &towerlistxct[c], tx );
			appendToList( &towerlisty[c], &towerlistyct[c], ty );
		}
		appendToList( &map, &maplen, c );
		tx++;
	}

	//int * tmap = malloc( maplen * sizeof(int) );
	int i;

	for( i = 0; i < 256; i++ )
	{
		if( hastower[i] )
		{
			//memcpy( tmap, map, maplen * sizeof(int));
			int tsum = CountNodes( map, i );
			if( tsum )
			{
				//printf( "%c: %d\n", i, tsum );
			}
			sum += tsum;
		}
	}

	if( 0 )
	{
		int x, y;
		for( y = 0; y < mapy; y++ )
		{
			for( x = 0; x < mapx; x++ )
			{
				printf( "%c", map[x+y*mapx] );
			}
			printf( "\n" );
		}
	}

	printf( "%ld\n", sum );
}

// Tried 619777075 - but no dice.  (Input overload)
// Tried 21617015027 - but no dice.
