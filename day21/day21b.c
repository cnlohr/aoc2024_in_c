#include "aoclib.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define CNRBTREE_IMPLEMENTATION
#include "cnrbtree.h"

// Holy C-Style
typedef uint64_t u64;
typedef uint8_t u8;

#define MAX_DEPTH 25

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

uint64_t permutation;
int permutenumber;

static int currentplace[MAX_DEPTH+1][2]; // Skip first.

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


int64_t EmitPosCode( int level, int tx, int ty )
{
	int fx = currentplace[level][0];
	int fy = currentplace[level][1];
	int deltaX = tx - fx;
	int deltaY = ty - fy;
	if( level == MAX_DEPTH )
	{
		currentplace[level][0] = tx;
		currentplace[level][1] = ty;
		return iabs( deltaX ) + iabs( deltaY ) + 1;
	}
	int axisfirst = 0;

	currentplace[level][0] = tx;
	currentplace[level][1] = ty;

	if( deltaX == 0 && deltaY == 0 )
	{
		// Don't go anywhere, just press A.
		return EmitPosCode( level + 1, 2, 0 );
	}
	else if( deltaX == 0 )
		axisfirst = 1;
	else if( deltaY == 0 )
		axisfirst = 0;
	else if( isImpossible( level, fx + deltaX, fy ) )
		axisfirst = 1;
	else if( isImpossible( level, fx, fy + deltaY ) )
		axisfirst = 0;
	else
	{
#if 1
		axisfirst = 0;
		if( deltaX > 0 && deltaY > 0 ) axisfirst = 1;
#else
// XXX NEITHER ONE OF THESE!!!
#if 0
		int subX = currentplace[level+1][0];
		int subY = currentplace[level+1][1];

		// both deltaX and deltaY are nonzero.

		int scoreifxfirst =
			iabs( subX - ((deltaX>0)?2:0) ) +
			iabs( subY - 1 ) +  // First go to <2or0>,<1>
			iabs( ((deltaX>0)?2:0) - 1 ) + 
			iabs( 1 - ((deltaY>0)?1:0));

		int scoreifyfirst =
			iabs( subX - 1 ) +
			iabs( subY - ((deltaY>0)?1:0 ) ) +  // First go to <1>,<1or0>
			iabs( 1 - ((deltaX>0)?2:0) ) + 
			iabs( ((deltaY>0)?1:0 ) - 1 );
		printf( "%d/%d\n", scoreifxfirst, scoreifyfirst );
		if( scoreifxfirst < scoreifyfirst )
			axisfirst = 0;
		else
			axisfirst = 1;
		//axisfirst = 2;//(permutation >> ((*permutenumber)++)) & 1;
		// Must figure out which one is first.
#else
		// Sub or this.

		//axisfirst = (permutation >> ((*permutenumber)++)) & 1;
		int tX = currentplace[level][0];
		int tY = currentplace[level][1];

		// both deltaX and deltaY are nonzero.

		int scoreifxfirst =
			iabs( tX - ((deltaX>0)?2:0) ) +
			iabs( tY - 1 ) +  // First go to <2or0>,<1>
			iabs( ((deltaX>0)?2:0) - 1 ) + 
			iabs( 1 - ((deltaY>0)?1:0));

		int scoreifyfirst =
			iabs( tX - 1 ) +
			iabs( tY - ((deltaY>0)?1:0 ) ) +  // First go to <1>,<1or0>
			iabs( 1 - ((deltaX>0)?2:0) ) + 
			iabs( ((deltaY>0)?1:0 ) - 1 );
		printf( "@%d %d/%d\n", level, scoreifxfirst, scoreifyfirst );
		if( scoreifxfirst < scoreifyfirst )
			axisfirst = 0;
		else
			axisfirst = 1;
#endif
#endif
//			axisfirst = 1;

			//axisfirst = (permutation >> ((permutenumber)++)) & 1;

	}

	int64_t cost = 0;
	if( axisfirst == 0 )
	{
		int n;
		for( n = 0; n < iabs(deltaX); n++ )
			cost += EmitPosCode( level + 1, (deltaX>0)?2:0,1 );
		for( n = 0; n < iabs(deltaY); n++ )
			cost += EmitPosCode( level + 1, 1, (deltaY>0)?1:0 );
	}
	else if( axisfirst == 1 )
	{
		int n;
		for( n = 0; n < iabs(deltaY); n++ )
			cost += EmitPosCode( level + 1, 1, (deltaY>0)?1:0 );
		for( n = 0; n < iabs(deltaX); n++ )
			cost += EmitPosCode( level + 1, (deltaX>0)?2:0,1 );
	}
	cost += EmitPosCode( level + 1, 2, 0 ); //A
	return cost;
}


/*
int EmitDeltaCode( int level, char dir )
{
	switch( dir )
	{
	}
}
*/

int64_t SolveDirFinder( int ilevel, char * code, int codelen, int ** codepointerslen )
{
	u64 cost = 0;
	int * outcodelen = codepointerslen[ilevel];
	//char ** outcode = codepointers[ilevel];


	int l;
	for( l = 0; l < MAX_DEPTH+1; l++ )
	{
		currentplace[l][0] = 2;
		currentplace[l][1] = 0;
	}

	currentplace[0][0] = 2;
	currentplace[0][1] = 3;

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
#if 1
		axisfirst = 0;
		if( deltaX > 0 && deltaY > 0 ) axisfirst = 1;
#else
#if 1
		// THIS NOT NEXT
			//axisfirst = (permutation >> ((*permutenumber)++)) & 1;
			int tX = currentplace[ilevel][0];
			int tY = currentplace[ilevel][1];

			// both deltaX and deltaY are nonzero.

			int scoreifxfirst =
				iabs( tX - ((deltaX>0)?2:0) ) +
				iabs( tY - 1 ) +  // First go to <2or0>,<1>
				iabs( ((deltaX>0)?2:0) - 1 ) + 
				iabs( 1 - ((deltaY>0)?1:0));

			int scoreifyfirst =
				iabs( tX - 1 ) +
				iabs( tY - ((deltaY>0)?1:0 ) ) +  // First go to <1>,<1or0>
				iabs( 1 - ((deltaX>0)?2:0) ) + 
				iabs( ((deltaY>0)?1:0 ) - 1 );
			printf( "SCOREIF %d/%d\n", scoreifxfirst, scoreifyfirst );
			if( scoreifxfirst < scoreifyfirst )
				axisfirst = 0;
			else
				axisfirst = 1;
#else
		int subX = currentplace[level+1][0];
		int subY = currentplace[level+1][1];

		// both deltaX and deltaY are nonzero.

		int scoreifxfirst =
			iabs( subX - ((deltaX>0)?2:0) ) +
			iabs( subY - 1 ) +  // First go to <2or0>,<1>
			iabs( ((deltaX>0)?2:0) - 1 ) + 
			iabs( 1 - ((deltaY>0)?1:0));

		int scoreifyfirst =
			iabs( subX - 1 ) +
			iabs( subY - ((deltaY>0)?1:0 ) ) +  // First go to <1>,<1or0>
			iabs( 1 - ((deltaX>0)?2:0) ) + 
			iabs( ((deltaY>0)?1:0 ) - 1 );
		printf( "%d/%d\n", scoreifxfirst, scoreifyfirst );
		if( scoreifxfirst < scoreifyfirst )
			axisfirst = 0;
		else
			axisfirst = 1;
		// Must figure out which one is first.
#endif
#endif

		}
		int axisno;
		for( axisno = 0; axisno < 2; axisno++ )
		{
			int delta;
			int i;
			//char deltacode;

			if( axisno == axisfirst )
			{
				delta = deltaX;
				//deltacode = delta < 0 ? '<' : '>';
				delta = iabs( delta );
				for( i = 0; i < delta; i++ )
					cost += EmitPosCode( ilevel+1, (deltaX>0)?2:0,1  ); 
					//outcodelen++;
					//appendToListC( (u8**)outcode, outcodelen, deltacode );
			}
			else
			{
				delta = deltaY;
				//deltacode = delta < 0 ? '^' : 'v';
				delta = iabs( delta );
				for( i = 0; i < delta; i++ )
					cost += EmitPosCode( ilevel+1, 1, (deltaY>0)?1:0 );

					//outcodelen += EmitPosCode( ilevel+1, deltacode ); 
					//outcodelen++;
					//appendToListC( (u8**)outcode, outcodelen, deltacode );
			}
		}
		cost += EmitPosCode( ilevel+1, 2, 0  ); 
		//appendToListC( (u8**)outcode, outcodelen, 'A' );
		//outcodelen++;
		icX = toX;
		icY = toY;
	}
	//appendToListC( (u8**)outcode, outcodelen, 0 );

//	if( ilevel < 2 )
//	{
//			SolveDirFinder( ilevel + 1, *outcode, codepointerslen, permutation, permutenumber );
//	}

	return cost;
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

		//uint64_t permutation;
		int64_t bestcodel3 = 1ULL<<63;
		char * bestl1 = 0;
		char * bestl2 = 0;
		char * bestl3 = 0;
		permutenumber = 40;
		int maxpermutation = 0;

		//for( permutation = 0; permutation == 0 || permutation < (1ULL<<maxpermutation); permutation++ )
		{
			int64_t outcodeL3len = 0;

			permutenumber = 0;
			bestcodel3 = SolveDirFinder( 0, codes[c], codelen[c], 0 );
			//printf( "%lx %d %d\n", permutation, permutenumber, outcodeL3len-1 );
			//printf( "%lx / %d\n", permutation, outcodeL3len-1 );
		}

		sum += bestcodel3 * atoi( codes[c] );
		printf( "****** %s %ld (%ld)\n", codes[c], bestcodel3, permutenumber );

		//printf( "%s\n", outcodeL2 );
		//printf( "%s (%ld)\n%s\n%s\n%s\n", outcodeL3, strlen( outcodeL3), outcodeL2, outcodeL1, codes[c] );
	}
	printf( "%ld\n", sum );

	return 0;
}
// 90245482350618 is too low????
// 225901581929724 too high
