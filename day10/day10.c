#include "aoclib.h"
#include <stdint.h>
#include <string.h>

int * map;
int maplen;
int mapx;
int mapy;

#define MAP(x,y) (map[x+y*mapx])
#define IB(x,y) (x>=0 && y>=0 && y < mapy && x < mapx )

int ComputeTrailhead( int * peaks, int x, int y )
{
	int value = 0;
	int v = MAP(x,y);
	if( v == '9' 
#ifndef PARTB
		&& peaks[x+y*mapx] == 0
#endif
	)
	{
		peaks[x+y*mapx] = 1;
		return 1;
	}

	static const int udlrx[] = { -1, 0, 1, 0 };
	static const int udlry[] = { 0, -1, 0, 1 };
	int dir;
	for( dir = 0; dir < 4; dir++ )
	{
		int tx = x + udlrx[dir];
		int ty = y + udlry[dir];
		if( IB( tx, ty ) && MAP( tx, ty ) == v+1 )
		{
			int rv = ComputeTrailhead( peaks, tx, ty );
			value += rv;
		}
	}

	//MAP(x,y) = value + 'A';
	return value;
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
		appendToList( &map, &maplen, c );
		tx++;
	}


	int peaks[mapx*mapy];

	int x, y;
	for( y = 0; y < mapy; y++ )
	for( x = 0; x < mapx; x++ )
	{
		if( MAP(x,y) == '0' )
		{
			memset( peaks, 0, mapx*mapy*sizeof(map[0]));
			int th = ComputeTrailhead( peaks, x, y );
			sum += th;
		}
	} 

	printf( "%ld\n", sum );

}



