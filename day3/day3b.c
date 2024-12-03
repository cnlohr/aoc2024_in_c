#include "aoclib.h"

int main()
{
	int sum = 0;
	int dont = 0;
	while( !iseof() )
	{
		int n1, n2;
		if( takeString( "do" ) )
		{
			if( peekChar() == 'n' )
			{
				if( takeString( "n't()" ) )
					dont = 1;
			}
			else
			{
				if( takeString( "()" ) )
					dont = 0;
			}
		}

		if( !takeString( "mul(" ) ||
			!takeNumber( &n1 ) ||
			!takeChar( ',' ) ||
			!takeNumber( &n2 ) ||
			!takeChar( ')' ) )
		{
			gchar();
			continue;
		}

		if( !dont ) sum += n1 * n2;
	}
	printf( "%d\n", sum );
	return 0;
}


