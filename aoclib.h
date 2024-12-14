#ifndef AOCLIB_H
#define AOCLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lastchar = 0;
int haslastchar = 0;
int lineno = 1;
int charno = 1;

int gchar( void );
void unget( void );
int iseof( void );
int peekChar( void );
int takeNumber( int * n );
int takeNumber64( int64_t * rnum );
int takeChar( int c );
void consumeWhitespace( void );
void quickSort( int * list, int start, int end );
void appendToList( int ** list, int * len, int num );
void appendToList64( int64_t ** list, int * len, int64_t num );
int takeString( const char * str );

void terror( const char * err );
void zdata( void * data, int len );

static double OGGetAbsoluteTime();
static void StartProfile() __attribute__((constructor));
static void StopProfile() __attribute__((destructor));

void quickSort( int * list, int start, int end )
{
    if( start >= end )
		return;

	int pivot = list[end];
	int i = start;
	for( int j = start; j < end; j++ )
	{
		if( list[j] <= pivot )
		{
			int temp = list[i];
			list[i] = list[j];
			list[j] = temp;
			i++;
		}
	}

	int temp = list[i];
	list[i] = list[end];
	list[end] = temp;

	quickSort( list, start, i - 1 );
    quickSort( list, i + 1, end );
	return;
}

void appendToList( int ** list, int * len, int num )
{
	int lenv = *len;
	int lenp1 = lenv + 1;
	*list = realloc( *list, sizeof(int) * lenp1 );
	(*list)[lenv] = num;
	*len = lenp1;
}

void appendToList64( int64_t ** list, int * len, int64_t num )
{
	int lenv = *len;
	int lenp1 = lenv + 1;
	*list = realloc( *list, sizeof(int64_t) * lenp1 );
	(*list)[lenv] = num;
	*len = lenp1;
}

int gchar( void )
{
	if( haslastchar )
	{
		haslastchar = 0;
		return lastchar;
	}
	lastchar = getchar();
	if( lastchar == '\n' )
	{
		lineno++;
		charno = 0;
	}
	charno++;
	return lastchar;
}

void unget( void )
{
	if( haslastchar )
	{
		terror( "double unget" );
	}
	haslastchar = 1;
}

int iseof( void )
{
	return peekChar() == EOF;
}

int peekChar( void )
{
	if( haslastchar )
		return lastchar;
	else
	{
		int c = gchar();
		unget();
		return c;
	}
}

int takeString( const char * str )
{
	int c;
	while( c = *(str++) )
	{
		if( gchar() != c )
		{
			unget();
			return 0;
		}
	}
	return 1;
}

int takeNumber( int * rnum )
{
	int num = 0;
	int numpl = 0;
	int nneg = 1;

	do
	{
		int c = gchar();
		if( c >= '0' && c <= '9' )
		{
			num = num * 10 + c - '0';
			numpl++;
		}
		else if( !numpl )
		{
			if( c == '-' ) { nneg = -1; continue; }
			return 0;
		}
		else
		{
			break;
		}
	} while( 1 );
	unget();
	*rnum = num * nneg;
	return numpl;
}

int takeNumber64( int64_t * rnum )
{
	int64_t num = 0;
	int numpl = 0;
	int nneg = 1;
	do
	{
		int c = gchar();
		if( c >= '0' && c <= '9' )
		{
			num = num * 10 + c - '0';
			numpl++;
		}
		else if( !numpl )
		{
			if( c == '-' ) { nneg = -1; continue; }
			return 0;
		}
		else
		{
			break;
		}
	} while( 1 );
	unget();
	*rnum = num * nneg;
	return numpl;
}

int takeChar( int c )
{
	if( gchar() == c )
	{
		return 1;
	}
	unget();
	return 0;
}

void consumeWhitespace( void )
{
	int c;
	do
	{
		c = gchar();
	} while( c == ' ' || c == '\t' );
	unget();
	return;
}


void terror( const char * err )
{
	fprintf( stderr, "Error: %s (at %d, %d) (%c, %d)\n", err, lineno, charno, lastchar, lastchar );
	exit( 0 );
}

void zdata( void * data, int len )
{
	memset( data, 0, len );
}


#if defined( WIN32 ) || defined (WINDOWS) || defined( _WIN32)
static double OGGetAbsoluteTime()
{
	static LARGE_INTEGER lpf;
	LARGE_INTEGER li;

	if( !lpf.QuadPart )
	{
		QueryPerformanceFrequency( &lpf );
	}

	QueryPerformanceCounter( &li );
	return (double)li.QuadPart / (double)lpf.QuadPart;
}
#else
#include <unistd.h>
#include <sys/time.h>
static double OGGetAbsoluteTime()
{
	struct timeval tv;
	gettimeofday( &tv, 0 );
	return ((double)tv.tv_usec)/1000000. + (tv.tv_sec);
}
#endif

static double StartTime;
static void StartProfile()
{
	if( getenv("AOCPROF") )
		StartTime = OGGetAbsoluteTime();
}

static void StopProfile()
{
	double EndTime;
	if( StartTime )
	{
		EndTime = OGGetAbsoluteTime();
		int microseconds = (int)((EndTime-StartTime)*1000000);

		char exe[1024] = { 0 };
		int ret;
		ret = readlink("/proc/self/exe",exe,sizeof(exe)-1);
		char * rend = exe;
		char * t;
		for( t = exe; *t; t++ )
		{
			if( *t == '/' )
			{
				*t = 0;
				rend = t + 1;
			}
		}

		fprintf( stderr, "PROFILE,%s,%d\n", rend, microseconds );
	}
}

#endif
