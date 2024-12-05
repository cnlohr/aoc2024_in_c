#include "aoclib.h"

#define MAXPAGES 100

// 0 for not needed
// 1 for needed
// 2 for already printed.
char neededpages[MAXPAGES];

// 2D map.
char reqprev[MAXPAGES][MAXPAGES];

int printinline = 0;
int * printlinelist;

int * neededpageslist = 0;
int neededpageslistnum = 0;

int sum = 0;
int violated = 0;

void PrintPage( int p )
{
	int j;

	for( j = 0; j < MAXPAGES; j++ )
	{
		if( reqprev[j][p] )
		{
			if( neededpages[j] == 1 )
			{
				violated = 1;
				PrintPage(j);
			}
		}
	}

	if( neededpages[p] == 1 )
	{
		//if( printinline )
		//	printf( "," );
		//printf( "%d", p );
		appendToList( &printlinelist, &printinline, p );
	}
	neededpages[p] = 2;
}


int main()
{	
	zdata( reqprev, sizeof( reqprev ) );

	while( !iseof() )
	{
		int pagebefore;
		int pageafter;
		if( !takeNumber( &pagebefore ) ||
			!takeChar('|') ||
			!takeNumber( &pageafter ) ||
			!takeChar('\n') )
			{
				terror( "invalid input in pre list" );
			}
		if( takeChar('\n') )
			break;
		reqprev[pagebefore][pageafter] = 1;
	}
	
	zdata( neededpages, sizeof(neededpages) );

	while( !iseof() )
	{
		int pn;
		if( !takeNumber( &pn ) )
			terror( "invalid post list" );

		appendToList( &neededpageslist, &neededpageslistnum, pn );
		neededpages[pn] = 1;

		if( takeChar(',') ) continue;

		if( !takeChar('\n') && !takeChar(-1) ) terror( "invalid format in post list" );

		// Proess this list.

		int i;
		for( i = 0; i < neededpageslistnum; i++ )
		{
			int p = neededpageslist[i];
			PrintPage( p );
		}

	//printf( " // %d (%d)\n", printlinelist[printinline/2], violated );
	
#if PARTB
		if( violated )
#else
		if( !violated )
#endif
			sum += printlinelist[printinline/2];

		zdata( neededpages, sizeof(neededpages) );

		free( printlinelist );
		printlinelist = 0;
		printinline = 0;
		violated = 0;
		
		neededpageslistnum = 0;
		free( neededpageslist );
		neededpageslist = 0;

	}
	printf( "%d\n", sum );

	return 0;
}


