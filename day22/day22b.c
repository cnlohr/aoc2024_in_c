#include "aoclib.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define CNRBTREE_IMPLEMENTATION
#include "cnrbtree.h"

// Holy C-Style
typedef uint64_t u64;
typedef int64_t i64;
typedef uint8_t u8;

CNRBTREETEMPLATE( u64, u64, RBptrcmp, RBptrcpy, RBnullop );


i64 * initial;
int initiallen;

static inline u64 Advance( u64 num )
{
	u64 tmp = num * 64;
	num = tmp ^ num;
	num = num & 16777215;
	tmp = num / 32;
	num = tmp ^ num;
	num = num & 16777215;
	tmp = num * 2048;
	num = tmp ^ num;
	num = num & 16777215;
	return num;
}

int main()
{
	while( !iseof() )
	{
		i64 num;
		if( !takeNumber64( &num ) )
			terror( "Not a Number" );
		takeChar( '\n' );
		takeChar( '\n' );
		appendToList64( &initial, &initiallen, num );
	}

	int i;
	u64 sum = 0;

	cnrbtree_u64u64 * seqvals = cnrbtree_u64u64_create();

	for( i = 0; i < initiallen; i++ )
	{
		u64 num = initial[i];

		int iter;
		int last = num % 10ULL;
		u64 lastseq = 0;

		cnrbtree_u64u64 * seqvalsthis = cnrbtree_u64u64_create();

		for( iter = 0; iter < 2000; iter++ )
		{
			num = Advance( num );
			int ones = num % 10ULL;
			int diff = ones - last;

			lastseq <<= 8;
			lastseq |= (((uint32_t)diff)&0xff);
			lastseq &= 0xffffffffULL;
			if( iter >= 4 )
			{
				if( !RBHAS( seqvalsthis, lastseq ) )
					RBA( seqvalsthis, lastseq ) = ones;
			}
			//printf( "%d %lx %d\n", num, lastseq, ones );
			last = ones;
		}

		RBFOREACH( u64u64, seqvalsthis, s )
		{
			RBA( seqvals, s->key ) += s->data;
		}

		RBDESTROY( seqvalsthis );

		sum += num;
	}

	//u64 bestkey = 0;
	u64 bestvalue = 0;
	RBFOREACH( u64u64, seqvals, s )
	{
		if( s->data > bestvalue )
		{
			bestvalue = s->data;
			//bestkey = s->key;
		}
	}
	//printf( "%lx %ld\n", bestkey, bestvalue );
	printf( "%ld\n", bestvalue );
	//printf( "%ld\n", sum );

	return 0;
}
