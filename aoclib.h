#ifndef AOCLIB_H
#define AOCLIB_H

#include <stdio.h>
#include <stdlib.h>

int lastchar = 0;
int haslastchar = 0;
int lineno = 1;
int charno = 1;

int gchar( void );
void unget( void );
int iseof( void );
int peekChar( void );
int takeNumber( int * n );
int takeChar( int c );
void consumeWhitespace( void );
void quickSort( int * list, int start, int end );
void appendToList( int ** list, int * len, int num );
int takeString( const char * str );

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

void terror( const char * err )
{
	fprintf( stderr, "Error: %s (at %d, %d) (%c, %d)\n", err, lineno, charno, lastchar, lastchar );
	exit( 0 );
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
		terror( "got extra char" );
		exit( -1 );
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
			return 0;
		}
		else
		{
			break;
		}
	} while( 1 );
	unget();
	*rnum = num;
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

#endif
