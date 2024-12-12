#include "aoclib.h"
#include <stdint.h>
#include <string.h>

#define CNRBTREE_IMPLEMENTATION
#include "cnrbtree.h"


CNRBTREETEMPLATE( int64_t, int64_t, RBptrcmp, RBptrcpy, RBnullop );
typedef cnrbtree_int64_tint64_t intintmap;

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

int main()
{
	int step;
	int i;
	intintmap * last = cnrbtree_int64_tint64_t_create();

	int64_t sum = 0;

	while( !iseof() )
	{
		int64_t num;
		if( takeChar( '\n' ) ) continue;
		if( !takeNumber64( &num ) )
			terror( "expected number" );
		consumeWhitespace();
		RBA( last, num )++;
	}
	int c;
	int count = 75;
	for( c = 0; c < count; c++ )
	{
		intintmap * new = cnrbtree_int64_tint64_t_create();
		RBFOREACH( int64_tint64_t, last, r )
		{
			int64_t stone = r->key;
			int64_t lastcount = r->data;
			int count = 0;

			if( stone == 0 )
			{
				RBA( new, 1 ) += lastcount;
			}
			else
			{
				int d = digits( stone );
				if( ( d % 2 ) == 0 )
				{
					int64_t place = po10( d/2 );
					int64_t stone1 = stone / place;
					int64_t stone2 = stone % place;
					RBA( new, stone1 ) += lastcount;
					RBA( new, stone2 ) += lastcount;
				}
				else
				{
					RBA( new, stone*2024 ) += lastcount;
				}
			}
		}
		RBDESTROY( last );
		last = new;
	}

	RBFOREACH( int64_tint64_t, last, r )
	{
	//	printf( "%ld,%ld  ", r->key, r->data );
		sum += r->data;
	}
	printf( "%ld\n", sum );
	RBDESTROY( last );
}
