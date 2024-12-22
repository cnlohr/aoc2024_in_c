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
	for( i = 0; i < initiallen; i++ )
	{
		u64 num = initial[i];

		int iter;
		for( iter = 0; iter < 2000; iter++ )
		{
			num = Advance( num );
		}
		sum += num;
	}
	printf( "%ld\n", sum );

	return 0;
}
