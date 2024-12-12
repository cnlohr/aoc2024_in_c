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

#if 0
int64_t GetStoneCountAt( int64_t stone, int64_t step )
{
	int64_t count;

	if( step == 0 )
	{
		count = 1;
	}
	else
	{

		cnrbtree_int64_tint64_t_node * n = cnrbtree_int64_tint64_t_access( stonemap[step], stone );
		if( n->data )
		{
			count = n->data;
		}
		else
		{
			if( stone == 0 )
				count = GetStoneCountAt( 1, step-1 );
			else
			{
				int d = digits( stone );
				if( ( d % 2 ) == 0 )
				{
					int64_t place = po10( d/2 );
					int64_t stone1 = stone / place;
					int64_t stone2 = stone % place;
					count = GetStoneCountAt( stone1, step-1 ) + GetStoneCountAt( stone2, step-1 );
				}
				else
				{
					count = GetStoneCountAt( stone * 2024, step-1 );
				}
			}
			n->data = count;
		}
	}

	//printf( "GetStoneCountAt( %ld, %ld ) = %d\n", stone, step, count );
	return count;
}
#endif

//221291560078593
//240482415673427

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
		//sum += GetStoneCountAt( num, 25 );
		if( !RBHAS( last, num ) )RBA( last, num ) = 0;
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
				if( !RBHAS( new, 1 ) ) RBA(new,1 ) = 0;
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
					if( !RBHAS( new, stone1 ) ) RBA( new, stone1 ) = 0;
					if( !RBHAS( new, stone2 ) ) RBA( new, stone2 ) = 0;
					RBA( new, stone1 ) += lastcount;
					RBA( new, stone2 ) += lastcount;
				}
				else
				{
					if( !RBHAS( new, stone*2024 ) ) RBA(new, stone*2024 ) = 0;
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


/*
	printf( "StoneCount: %ld\n", GetStoneCountAt( 17, 0 ) );
	printf( "StoneCount: %ld\n", GetStoneCountAt( 17, 1 ) );
	printf( "StoneCount: %ld\n", GetStoneCountAt( 17, 2 ) );
	printf( "StoneCount: %ld\n", GetStoneCountAt( 17, 3 ) );
	printf( "StoneCount: %ld\n", GetStoneCountAt( 17, 4 ) );
	printf( "StoneCount: %ld\n", GetStoneCountAt( 17, 5 ) );
*/
#if 0
	for( step = 1; step < MAXSTEP; step++ )
	{
		int * llist = stones[step-1];
		int * tlist = stones[step];
		for( i = 0; i < MAXSTONE; i++ )
		{
			int v = i;
			int tstone = 1;

			if( v == 0 )
				tstone = llist[1];
			else
			{
				int d = digits( v );
				if( ( d % 2 ) == 0 )
				{
					int64_t place = po10( d/2 );
					int64_t stone1 = v / place;
					int64_t stone2 = v % place;
					if( stone1 > MAXSTONE ) { printf( "Missing stone %ld\n", stone1 ); exit( -6 ); }
					if( stone2 > MAXSTONE ) { printf( "Missing stone %ld\n", stone2 ); exit( -6 ); }
					tstone = llist[stone1] + llist[stone2];
				}
				else
				{
					int64_t index = v * 2024;
					if( index > MAXSTONE ) { printf( "Missing stone %ld\n", index ); exit( -6 ); }
					tstone = llist[index];
				}
			}
			tlist[i] = tstone;
		}
		printf( "%d\n", tlist[0] );
	}
#endif

#if 0
	const int steps = 75;
	intintmap * mapsets[steps];

	intintmap * ms = mapsets[0] = cnrbtree_int64_tint64_t_create();
	for( int i = 0; i < listlen; i++ )
	{
		RBA( ms, list[i] ) = 1;
	}

	for( int i = 1; i < steps; i++ )
	{
		intintmap * prev = ms;
		ms = mapsets[i] = cnrbtree_int64_tint64_t_create();
		RBFOREACH( int64_tint64_t, prev, r )
		{
			printf( "%ld %ld\n", r->key, r->data );
			if( r->key 

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

		}
	}
#endif	
}
