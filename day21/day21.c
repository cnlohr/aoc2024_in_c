#include "aoclib.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define CNRBTREE_IMPLEMENTATION
#include "cnrbtree.h"

// Holy C-Style
typedef uint64_t u64;
typedef uint8_t u8;

//CNRBTREETEMPLATE( u64, u64, RBptrcmpnomatch, RBptrcpy, RBnullop );
//CNRBTREETEMPLATE( int, int, RBptrcmp, RBptrcpy, RBnullop );

//static const int dirx[] = { -1, 0, 1, 0 };
//static const int diry[] = { 0,  1, 0,-1 };
//static const char dirc0[] = "0123456789A";
//static const char dirc1[] = "<v>^A";

int iabs( int a ) { return a < 0 ? -a : a; }


static const int buttonlocs0[][2] = {
	{ 1, 3 }, // 0
	{ 0, 2 }, { 1, 2 }, { 2, 2 }, // 123
	{ 0, 1 }, { 1, 1 }, { 2, 1 }, // 123
	{ 0, 0 }, { 1, 0 }, { 2, 0 }, // 123
	{ 2, 3 }, // 'A'
};

static const int buttonlocs1[][2] = {
	{ 0, 1 }, // <
	{ 1, 1 }, // v
	{ 2, 1 }, // >
	{ 1, 0 }, // ^
	{ 2, 0 }, // A
};

int chartocode0( char c )
{
	if( c >= '0' && c <= '9' )
		return c - '0';
	if( c == 'A' )
		return 10;
	fprintf( stderr, "Bad Number %c\n", c );
	exit( -5 );
}

int chartocode1( char c )
{
	switch( c ) {
		case '<': return 0;
		case 'v': return 1;
		case '>': return 2;
		case '^': return 3;
		case 'A': return 4;
		default: fprintf( stderr, "Bad Dir %c\n", c ); exit( -5 );
	}
}

int (*chartocode[2])(char) = { chartocode0, chartocode1 };
static const void * buttonloclevels[2] = { buttonlocs0, buttonlocs1 };
static const int    buttonloclen[2] = { 11, 5 };

int isImpossible( int level, int x, int y )
{
	if( level == 0 )
	{
		return x == 0 && y == 3;
	}
	else
	{
		return x == 0 && y == 0;
	}
}

int SolveDirFinder( int ilevel, char * code, int codelen, char *** codepointers, int ** codepointerslen, uint64_t permutation, int * permutenumber )
{
	int * outcodelen = codepointerslen[ilevel];
	char ** outcode = codepointers[ilevel];

	int level = ilevel;
	if( level > 1 ) level = 1;
	const int (*blocs)[2] = buttonloclevels[level];
	const int bllen = buttonloclen[level];
	int (*ccode)(char) = chartocode[level];

	int icX = blocs[bllen-1][0];
	int icY = blocs[bllen-1][1];

	int c;
	while( (c = (*code++)) )
	{
		int n = ccode( c );
		int toX = blocs[n][0];
		int toY = blocs[n][1];
		int deltaX = toX - icX;
		int deltaY = toY - icY;
		// The samples prefer X first then Y.  We will do the same.

		int axisfirst = 0;

		if( deltaX == 0 )
			axisfirst = 1;
		else if( deltaY == 0 )
			axisfirst = 0;
		else if( isImpossible( level, icX + deltaX, icY ) )
			axisfirst = 1;
		else if( isImpossible( level, icX, icY + deltaY ) )
			axisfirst = 0;
		else
		{
			axisfirst = (permutation >> ((*permutenumber)++)) & 1;
		}

		int axisno;
		for( axisno = 0; axisno < 2; axisno++ )
		{
			int delta;
			int i;
			char deltacode;

			if( axisno == axisfirst )
			{
				delta = deltaX;
				deltacode = delta < 0 ? '<' : '>';
				delta = iabs( delta );
				for( i = 0; i < delta; i++ )
					appendToListC( (u8**)outcode, outcodelen, deltacode );
			}
			else
			{
				delta = deltaY;
				deltacode = delta < 0 ? '^' : 'v';
				delta = iabs( delta );
				for( i = 0; i < delta; i++ )
					appendToListC( (u8**)outcode, outcodelen, deltacode );
			}
		}

		appendToListC( (u8**)outcode, outcodelen, 'A' );
		icX = toX;
		icY = toY;
	}
	appendToListC( (u8**)outcode, outcodelen, 0 );

	if( ilevel < 2 )
	{
			SolveDirFinder( ilevel + 1, *outcode, *outcodelen, codepointers, codepointerslen, permutation, permutenumber );
	}

	return 0;
}

int main()
{
	char ** codes = 0;
	int * codelen = 0;
	int numcodes = 0;
	int numcodelen = 0;

	while( !iseof() )
	{
		char * tempcode;
		int tempcodelen;
		tempcode = 0;
		tempcodelen = 0;
		while( !iseof() )
		{
			int c = gchar();
			if( c == '\n' ) break;
			if( c != 'A' && ( c < '0' || c > '9' ) )
				terror( "invalid input" );
			appendToListC( (u8**)&tempcode, &tempcodelen, c );
		}
		if( tempcodelen > 0 )
		{
			appendToListC( (u8**)&tempcode, &tempcodelen, 0 );
			appendToListP( (void***)&codes, &numcodes, tempcode );
			appendToList( &codelen, &numcodelen, tempcodelen );
		}
	}

	u64 sum = 0;
	int c;
	for( c = 0; c < numcodes; c++ )
	{

		uint64_t permutation;
		int bestcodel3 = INT_MAX;
		//char * bestl1 = 0;
		//char * bestl2 = 0;
		char * bestl3 = 0;
		int permutenumber = 40;
		int maxpermutation = 0;

		for( permutation = 0; permutation == 0 || permutation < (1ULL<<maxpermutation); permutation++ )
		{
			int outcodeL1len = 0;
			int outcodeL2len = 0;
			int outcodeL3len = 0;
			char * outcodeL1 = 0;
			char * outcodeL2 = 0;
			char * outcodeL3 = 0;
			char ** codepointers[3] = { &outcodeL1, &outcodeL2, &outcodeL3 };
			int * codepointerslen[3] = { &outcodeL1len, &outcodeL2len, &outcodeL3len };

			permutenumber = 0;
			SolveDirFinder( 0, codes[c], codelen[c], codepointers, codepointerslen, permutation, &permutenumber );
			//printf( "%lx %d %d\n", permutation, permutenumber, outcodeL3len-1 );
			//printf( "%lx / %d\n", permutation, outcodeL3len-1 );
			if( outcodeL3len < bestcodel3 )
			{
				//printf( "%s (%lx)\n", outcodeL3-1, permutation );
				bestl3 = strdup( outcodeL3 );
				//bestl2 = strdup( outcodeL2 );
				//bestl1 = strdup( outcodeL1 );
				bestcodel3 = outcodeL3len;
			}
			permutenumber++;
			free( outcodeL1 );
			free( outcodeL2 );
			free( outcodeL3 );
			if( permutenumber > maxpermutation ) maxpermutation = permutenumber;
			//printf( "%lx %d\n", permutation, permutenumber );
		}

		sum += strlen( bestl3) * atoi( codes[c] );
		//printf( "%s (%ld)\n%s (%ld)\n%s (%ld)\n", bestl3, strlen( bestl3), bestl2, strlen( bestl2 ), bestl1, strlen ( bestl1 ) );

		//printf( "%s\n", outcodeL2 );
		//printf( "%s (%ld)\n%s\n%s\n%s\n", outcodeL3, strlen( outcodeL3), outcodeL2, outcodeL1, codes[c] );
	}
	printf( "%ld\n", sum );

	return 0;
}
