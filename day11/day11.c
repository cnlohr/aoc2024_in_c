#include "aoclib.h"
#include <stdint.h>
#include <string.h>

struct linkedlist
{
	int64_t value;
	struct linkedlist * next;
};

struct linkedlist * head;
struct linkedlist * tail;

struct linkedlist * linkedlist_insert( struct linkedlist ** ll, int64_t val )
{
	struct linkedlist * ths = malloc( sizeof( struct linkedlist ) );
	ths->next = *ll ? (*ll)->next : 0;
	ths->value = val;
	if( *ll )
		(*ll)->next = ths;
	else
		*ll = ths;
	return ths;
}

void linkedlist_print( struct linkedlist * ll )
{
	while( ll )
	{
		printf( "%ld%c", ll->value, ll->next ? ',' : '\n' );
		ll = ll->next;
	}
}


int linkedlist_count( struct linkedlist * ll )
{
	int stones = 0;
	while( ll )
	{
		ll = ll->next;
		stones++;
	}
	return stones;
}

int digits( int64_t n )
{
	int digs = 0;
	do
	{
		digs++;
		n/=10;
	} while( n );
	return digs;
}

int64_t po10( int d )
{
	int64_t ret = 1;
	while( d-- )
	{
		ret *= 10;
	}
	return ret;
}

void blink( struct linkedlist * ll )
{
	while( ll )
	{
		int64_t v = ll->value;

		if( v == 0 )
			ll->value = 1;
		else
		{
			int d = digits( v );
			if( ( d % 2 ) == 0 )
			{
				int64_t place = po10( d/2 );
				int64_t stone1 = v / place;
				int64_t stone2 = v % place;
				ll->value = stone1;
				ll = linkedlist_insert( &ll, stone2 );
			}
			else
			{
				ll->value = v * 2024;
			}
		}

		ll = ll->next;
	}
}

int main()
{
	head = 0;
	while( !iseof() )
	{
		int64_t num;
		if( takeChar( '\n' ) ) continue;
		if( !takeNumber64( &num ) )
			terror( "expected number" );
		consumeWhitespace();
		tail = linkedlist_insert( tail ? &tail : &head, num );
	}

	int step;
	for( step = 0; step < 25; step++ )
	{
		blink( head );
		//printf( "%d/%d\n", step, linkedlist_count( head ) );
	}
	//linkedlist_print( head );
	printf( "%d\n", linkedlist_count( head ) );
}
