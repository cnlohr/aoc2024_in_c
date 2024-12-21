#include "aoclib.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define CNRBTREE_IMPLEMENTATION
#include "cnrbtree.h"

// Holy C-Style
//typedef uint64_t u64;
typedef uint8_t u8;

//CNRBTREETEMPLATE( u64, u64, RBptrcmpnomatch, RBptrcpy, RBnullop );
//CNRBTREETEMPLATE( int, int, RBptrcmp, RBptrcpy, RBnullop );

//static const int dirx[] = { -1, 0, 1, 0 };
//static const int diry[] = { 0,  1, 0,-1 };
//static const char dirc0[] = "0123456789A";
//static const char dirc1[] = "<v>^A";

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

char * SolveDirFinder( int level, char * code, int codelen )
{
	int outcodelen = 0;
	char * outcode = 0;
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
		int axisno;
		for( axisno = 0; axisno < 2; axisno++ )
		{
			int delta;
			int i;
			char deltacode;

			if( axisno == axisfirst )
			{
				delta = deltaX;
				deltacode = '>';
				if( delta < 0 ) { delta *= -1; deltacode = '<'; }
				for( i = 0; i < delta; i++ )
					appendToListC( (u8**)&outcode, &outcodelen, deltacode );
			}
			else
			{
				delta = deltaY;
				deltacode = 'v';
				if( delta < 0 ) { delta *= -1; deltacode = '^'; }
				for( i = 0; i < delta; i++ )
					appendToListC( (u8**)&outcode, &outcodelen, deltacode );
			}
		}

		appendToListC( (u8**)&outcode, &outcodelen, 'A' );
		icX = toX;
		icY = toY;
	}
	appendToListC( (u8**)&outcode, &outcodelen, 0 );

	return outcode;
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

	int c;
	for( c = 0; c < numcodes; c++ )
	{
		char * outcodeL1 = SolveDirFinder( 0, codes[c], codelen[c] );
		char * outcodeL2 = SolveDirFinder( 1, outcodeL1, strlen( outcodeL1 ) );
		char * outcodeL3 = SolveDirFinder( 1, outcodeL2, strlen( outcodeL2 ) );
		printf( "%s (%ld)\n%s\n%s\n%s\n", outcodeL3, strlen( outcodeL3) , outcodeL2, outcodeL1, codes[c] );
	}

	return 0;
}
