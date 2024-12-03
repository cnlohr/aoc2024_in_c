#include "aoclib.h"

int main()
{
	int sum = 0;
	int dont = 0;
	while( !iseof() )
	{
		int n1, n2;
		if( stringMatch( "do" ) )
		{
			if( peekChar() == 'n' )
			{
				if( stringMatch( "n't()" ) )
					dont = 1;
			}
			else
			{
				if( stringMatch( "()" ) )
					dont = 0;
			}
		}

		if( !stringMatch( "mul(" ) ||
			!takeNumber( &n1 ) ||
			!stringMatch(",") ||
			!takeNumber( &n2 ) ||
			!stringMatch( ")" ) )
		{
			gchar();
			continue;
		}

		if( !dont ) sum += n1 * n2;
	}
	printf( "%d\n", sum );
	return 0;
}


