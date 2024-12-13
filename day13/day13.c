// I am not proud of this one :(

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
		int64_t ax, ay;
		int64_t bx, by;
		int64_t prizex, prizey;
		if( !takeString( "Button A: X+" ) ||
			!takeNumber64( &ax ) || 
			!takeString( ", Y+" ) ||
			!takeNumber64( &ay ) || 
			!takeChar( '\n' ) ||
			!takeString( "Button B: X+" ) ||
			!takeNumber64( &bx ) ||
			!takeString( ", Y+" ) ||
			!takeNumber64( &by ) ||
			!takeChar( '\n' ) ||
			!takeString( "Prize: X=" ) ||
			!takeNumber64( &prizex ) ||
			!takeString( ", Y=" ) ||
			!takeNumber64( &prizey ) )
		{
			terror( "Formatting error\n" );
		}

#ifdef PARTB
		prizex += 10000000000000;
		prizey += 10000000000000;
#endif


		int64_t a, b;
		int64_t maxax = prizex / ax;
		int64_t maxay = prizey / ay;
		int64_t maxa = (maxax > maxay) ? maxax : maxay;
		int coarse = 3000;

		int upangle = ((ax * 10000 / bx) / (ay * 10000 / by)) ? 1 : 0;

		double ad = prizex / (bx+ax)  + prizey / (by+ay);

		for( a = 0; a < (coarse >= 10) || maxa; a++ )
		{
			if( a < 0 ) { a = -1; continue; }
			//prizex = ax * a + bx * b
			//prizey = ay * a + by * b
			// (prizex -  ax * a ) / bx = b
			int64_t dbx = ( prizex - ax * a );
			int64_t dby = ( prizey - ay * a );


			int64_t bkx = dbx / bx;
			int64_t bky = dby / by;

			coarse--;
			//printf( "COARSE: %d\n", coarse );
			if( coarse < 0 ) break;
			if( coarse < 10 )
			{
				if( bkx != bky ) continue;
				if( dbx % bx  || dby % by ) continue;
			}
			else
			{
				int64_t bkx = dbx / bx;
				int64_t bky = dby / by;

				ad *= 0.99;
				if( ( bkx < 0 && bky < 0) ) 
				{
					a -= ad;
					continue;
				}
				if( coarse == 10 )
				{
					a -= 5;
					//printf( "BARNK: %d %d (A=%d) (%d %d  %d %d  %d %d)X\n", bkx, bky, a, ax, ay, bx, by, prizex, prizey );
					coarse = 10;
					continue;
				}

				if( bkx != bky )
				{
					//printf( "COMP: %ld != %ld // %d %f\n", bkx, bky, a, ad );
					if( ( bkx > bky ^ upangle ) )
					{
						a -= ad;
					}
					else
					{
						a += ad;
					}
					continue;
				}
				//printf( "%d %d  %d %d\n", dbx, dby, dbx % bx, dby % by );
				if( dbx % bx  || dby % by ) { coarse = 10;  a -= 5; continue; }
			}


			//printf( "%d / %d,%d = %d,%d\n", b, akx, aky, 0, 0 );
			sum += bkx + a * 3;
			break;
		}

		// We have two lines, A and B, and they sum together to make prize.
		//prizex = ax * a + bx * b
		//prizey = ay * a + by * b
		//
		//
		//printf( "%d %d / %d %d / %d %d --> %d %% %d\n", ax, ay, bx, by, prizex, prizey, b, a );


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
