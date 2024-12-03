#include "aoclib.h"

int main()
{
	int sum = 0;
	while( !iseof() )
	{
		int n1, n2;
		if( !stringMatch( "mul(" ) ||
			!takeNumber( &n1 ) ||
			!stringMatch(",") ||
			!takeNumber( &n2 ) ||
			!stringMatch( ")" ) )
		{
			gchar();
			continue;
		}

		sum += n1 * n2;
	}
	printf( "%d\n", sum );
	return 0;
}


