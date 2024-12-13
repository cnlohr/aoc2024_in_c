#include "aoclib.h"
#include <stdint.h>
#include <string.h>


int main()
{
	int64_t sum = 0;
	int tx = 0;
	int ty = 0;
	while( !iseof() )
	{
		int ax, ay;
		int bx, by;
		int prizex, prizey;
		if( !takeString( "Button A: X+" ) ||
			!takeNumber( &ax ) || 
			!takeString( ", Y+" ) ||
			!takeNumber( &ay ) || 
			!takeChar( '\n' ) ||
			!takeString( "Button B: X+" ) ||
			!takeNumber( &bx ) ||
			!takeString( ", Y+" ) ||
			!takeNumber( &by ) ||
			!takeChar( '\n' ) ||
			!takeString( "Prize: X=" ) ||
			!takeNumber( &prizex ) ||
			!takeString( ", Y=" ) ||
			!takeNumber( &prizey ) )
		{
			terror( "Formatting error\n" );
		}

		// We have two lines, A and B, and they sum together to make prize.
		//prizex = ax * a + bx * b
		//prizey = ay * a + by * b
		//
		//
		printf( "%d %d / %d %d / %d %d --> %d %% %d\n", ax, ay, bx, by, prizex, prizey, b, a );


#if 0
		int tx = 0;
		int ty = 0;

		int a = 0, b = 0;
		int cost = 0;
		int ocost = 0;
		for( cost = 0; cost < prizex + prizey; cost++ )
		{
			for( a = 0; a <= cost/3; a++ )
			{
				for( b = 0; b <= cost; b++ )
				{
					if( a*3+b>cost ) continue;
					if( tx + ax * a + bx * b == prizex &&
						ty + ay * a + by * b == prizey )
					{
						sum += a * 3 + b;
						goto done;
					}
				}
			}
			ocost = cost;
		}

		done:
#endif
		while( takeChar( '\n' ) );
	}

	printf( "%ld\n", sum );
}

// Not 27116
