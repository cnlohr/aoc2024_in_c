#include "aoclib.h"

int main()
{
	int sum = 0;
	while( !iseof() )
	{
		int n1, n2;
		if( !takeString( "mul(" ) ||
			!takeNumber( &n1 ) ||
			!takeChar(',') ||
			!takeNumber( &n2 ) ||
			!takeChar( ')' ) )
		{
			gchar();
			continue;
		}

		sum += n1 * n2;
	}
	printf( "%d\n", sum );
	return 0;
}


