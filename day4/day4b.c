#include "aoclib.h"

int * letters = 0;
int numletters = 0;
int lx, ly;

int main()
{
	const char * XMAS = "MAS";
	int xmaslen = strlen( XMAS );

	int xthisline = 0;
	while( !iseof() )
	{
		int c = gchar();
		if( c == '\n')
		{
			if( xthisline > 0 ) ly++;
			xthisline = 0;
		}
		else
		{
			appendToList( &letters, &numletters, c );
			if( ly == 0 ) lx++;
			xthisline++;
		}
	}

	int hits = 0;

	for( int dir = 0; dir < 4; dir++ )
	{
		static const int dXL1[] = { -1,  1, 1, -1 };
		static const int dYL1[] = { -1, -1,-1,  1 };
		static const int dXL2[] = { -1, -1, 1,  1 };
		static const int dYL2[] = {  1, -1, 1,  1 };

		int dx1 = dXL1[dir];
		int dy1 = dYL1[dir];
		int dx2 = dXL2[dir];
		int dy2 = dYL2[dir];
		int sx, sy;
		int xmhl = xmaslen/2;

		for( sy = xmhl; sy < ly - xmhl; sy++ )
		for( sx = xmhl; sx < lx - xmhl; sx++ )
		{
			int x1 = sx - dx1 * xmhl;
			int y1 = sy - dy1 * xmhl;
			int x2 = sx - dx2 * xmhl;
			int y2 = sy - dy2 * xmhl;

			int i;
			for( i = 0; i < xmaslen; i++ )
			{
				if( letters[x1+ly*y1] != XMAS[i] ) break;
				if( letters[x2+ly*y2] != XMAS[i] ) break;

				x1 += dx1;
				y1 += dy1;
				x2 += dx2;
				y2 += dy2;
			}
			if( i == xmaslen ) hits++;
		}
	}

	printf( "%d\n", hits );
	return 0;
}


