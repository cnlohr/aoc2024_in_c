#include "aoclib.h"
#include <stdint.h>
#include <string.h>


#ifdef SAMPLE
	#define sx  11
	#define sy  7
#else
	#define sx 101
	#define sy 103
#endif

#ifdef PARTB
	#define maxs 1024
	int counts[maxs][sy][sx];
	int tus[maxs];
#endif

int main()
{
#ifdef PARTB
	memset( counts, 0, sizeof( counts ) );
#endif
	int64_t sum = 0;
	int64_t quadrantcount[4] = { 0 };

	while( !iseof() )
	{
		int64_t px, py;
		int64_t dx, dy;
		if( !takeString( "p=" ) ||
			!takeNumber64( &px ) || 
			!takeString( "," ) ||
			!takeNumber64( &py ) || 
			!takeString( " v=" ) ||
			!takeNumber64( &dx ) ||
			!takeString( "," ) ||
			!takeNumber64( &dy ) )
		{
			terror( "Formatting error\n" );
		}


// Part B
//   22 H, 79 V
//   125 H, 180 V
//   228 H, 281 V
//   331 H, 382 V
//	 434 H, 483 V
//  22 + X * 103 == 79 + Y * 101
//

#ifdef PARTB
		int t = 0;
		for( t = 0; t < maxs; t++ )
		{
			double tu = 8159;
			int64_t ex = px + dx * tu;
			int64_t ey = py + dy * tu;
			ex = ((ex % sx) + sx) % sx;
			ey = ((ey % sy) + sy) % sy;
			counts[t][ey][ex]++;
			tus[t] = tu;
		}
#else
		const int time = 100;
		int64_t ex = px + dx * time;
		int64_t ey = py + dy * time;

		ex = ((ex % sx) + sx) % sx;
		ey = ((ey % sy) + sy) % sy;

		if( ex < sx/2 )
		{
			if( ey < sy/2 )
				quadrantcount[0]++;
			else if( ey > sy/2 )
				quadrantcount[1]++;
		}
		else if( ex > sx/2 )
		{
			if( ey < sy/2 )
				quadrantcount[2]++;
			else if( ey > sy/2 )
				quadrantcount[3]++;
		}
#endif
		while( takeChar( '\n' ) );
	}

#ifdef PARTB
		int t;
		for( t = 0; t < maxs; t++ )
		{
			printf( "T: %d\n", tus[t] );
			int x, y;
			for( y = 0; y < sy; y++ )
			{
				for( x = 0; x < sx; x++ )
				{
					int v = counts[t][y][x];
					printf( "%c", ( v > 0 ) ? ( v + '0' ) : '.' );
				}
				printf( "\n" );
			}
		}
#else
	//printf( "Qs: %ld %ld %ld %ld\n" ,quadrantcount[0], quadrantcount[1], quadrantcount[2], quadrantcount[3] );
	sum = quadrantcount[0] * quadrantcount[1] * quadrantcount[2] * quadrantcount[3];
	printf( "%ld\n", sum );
#endif
}


