#include "aoclib.h"

int * letters = 0;
int numletters = 0;
int lx, ly;

int main()
{
	const char * XMAS = "XMAS";
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

	for( int dir = 0; dir < 8; dir++ )
	{
		static const int dXL[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
		static const int dYL[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
		int dx = dXL[dir];
		int dy = dYL[dir];
		int sx, sy;
		for( sy = 0; sy < ly; sy++ )
		for( sx = 0; sx < lx; sx++ )
		{
			int xlm1 = xmaslen - 1;
			if( sx + xlm1 * dx >= lx ||
				sy + xlm1 * dy >= ly ||
				sx + xlm1 * dx < 0 ||
				sy + xlm1 * dy < 0 ) continue;
			int x = sx;
			int y = sy;
			int i;
			for( i = 0; i < xmaslen; i++ )
			{
				//printf( "COMP: %c %c\n", letters[x+ly*y], XMAS[i] );
				if( letters[x+ly*y] != XMAS[i] ) break;
				x += dx;
				y += dy;
			}
			if( i == xmaslen ) hits++;
		}
	}

	printf( "%d\n", hits );
	return 0;
}


