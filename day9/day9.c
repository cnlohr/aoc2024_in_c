#include "aoclib.h"
#include <stdint.h>
#include <string.h>

int64_t * diskmap;
int disklen;

int64_t * filemap;
int files;
int64_t * filesizes;
int filesizeslen;

int64_t * freemap;
int frees;
int64_t * freesizes;
int freesizeslen;

void PrintDisk()
{
	int i;
	int fn = 0;
	for( i = 0; i < disklen; i++ )
	{
		int n = diskmap[i];
		if( n >= 0 ) fn++;
		//if( n < 0 ) printf( "." ); else printf( "[%d]", n );
	}
	printf( "%d / %d\n", fn, i );
	printf( "\n" );
}

int main()
{
	{
		int isfreespace = 0;
		int fileno = 0;
		int fileplace = 0;
		while( !iseof() )
		{
			int c = gchar();
			if( c == '\n' ) continue;
			int num = c - '0';
			if( num < 0 || num > 9 ) terror( "invalid char" );
			int i;

			if( isfreespace )
			{
				appendToList64( &freemap, &frees, fileplace );
				appendToList64( &freesizes, &freesizeslen, num );
			}
			else
			{
				appendToList64( &filemap, &files, fileplace );
				appendToList64( &filesizes, &filesizeslen, num );
			}

			for( i = 0; i < num; i++ )
				appendToList64( &diskmap, &disklen, isfreespace?-1:fileno );
			fileplace += num;

			if( !isfreespace )
				fileno++;
			isfreespace = !isfreespace;
		}
	}


#if PARTB == 1
	int fn;

	for( fn = files-1; fn >= 0; fn-- )
	{
		int64_t tsize = filesizes[fn];
		int k;
		for( k = 0; k < frees; k++ )
		{
			int freesize = freesizes[k];
			if( freesize >= tsize )
			{
				break;
			}
		}
		if( k != frees && freemap[k] < filemap[fn] )
		{
			int freeplace = freemap[k];
			int tfnplace = filemap[fn];

			memcpy( diskmap + freeplace, diskmap + tfnplace, tsize * sizeof( int64_t ) );
			memset( diskmap + tfnplace, 0xff, tsize * sizeof( int64_t ) );

			filemap[fn] = freemap[k];
			freemap[k] += tsize;
			freesizes[k] -= tsize;
		}
		else
		{
			// Could not copy.
		}
	}

#else
	int endptr = disklen-1;
	int startptr = 0;

	do
	{
		for( ; endptr >= 0 && diskmap[endptr] == -1; endptr-- );
		for( ; startptr < disklen && diskmap[startptr] != -1; startptr++ );
		if( endptr < startptr ) break;
		int64_t a = diskmap[endptr];
		diskmap[endptr] = diskmap[startptr];
		diskmap[startptr] = a;
	} while(1);

#endif


	int i;
	int64_t sum = 0;
	for( i = 0; i < disklen; i++ )
	{
		int64_t n = diskmap[i];
		if( n > 0 )
			sum += n * i;
	}
	printf( "%ld\n", sum );


	free( diskmap );
	free( filemap );
	free( filesizes );
	free( freemap );
	free( freesizes );
}

// 8546756871770 is wrong (for part B)
