// I AM NOT PROUD OF THIS.
// I really wish I had a precanned priority queue
// or an RB Multimap.
#include "aoclib.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

int * program;
int programlen;

int64_t Combo( int64_t * reg, int op )
{
	switch( op )
	{
	case 0 ... 3: return op;
	case 4 ... 6: return reg[op-4];
	}
	fprintf( stderr, "Bad Combo Operand %d\n", op );
	exit( -5 );
}

int main()
{
	int64_t reg[3] = { 0 };
	int64_t reginitial[3] = { 0 };
	int64_t sum = 0;
	int tx = 0;
	int ty = 0;
	while( !iseof() )
	{
		if( takeString( "Register " ) )
		{
			if( takeString( "A: " ) )
			{
				if( !takeNumber64( &reginitial[0] ) ) terror( "Invalid Number" );
			}
			else if( takeString( "B: " ) )
			{
				if( !takeNumber64( &reginitial[1] ) ) terror( "Invalid Number" );
			}
			else if( takeString( "C: " ) )
			{
				if( !takeNumber64( &reginitial[2] ) ) terror( "Invalid Number" );
			}
			else
			{
				terror( "Invalid Register" );
			}
		}
		else if( takeString( "Program: " ) )
		{
			break;
		}
		else if( takeChar( '\n' ) )
		{
			continue;
		}
		else terror( "Invalid String" );
	}

	while( !iseof() )
	{
		int num;
		if( takeChar( '\n' ) ) continue;
		if( !takeNumber( &num ) ) terror( "Bad Number" );
		appendToList( &program, &programlen, num );
		takeChar( ',' );
	}

#ifdef PARTB
	int64_t initial;
	#define MAXIT 2000000000000000ULL
	#define INCREMENT 1ULL // Set to big number when scrubbing around
	// First 16 digit number 35184372088830ULL + 2
	for( initial = 109019476330000ULL; initial < MAXIT; initial+=INCREMENT )
	{
		reg[0] = initial;
#else
	{
		reg[0] = reginitial[0];
#endif

		reg[1] = reginitial[1];
		reg[2] = reginitial[2];
		int * outlist = 0;
		int outlistlen = 0;
		int pc = 0;
		int didout = 0;
		while( pc < programlen - 1 )
		{
			int inst = program[pc++];
			int op = program[pc++];
			//printf( "%d (%d,%d) %ld/%ld/%ld\n", pc, inst, op, reg[0], reg[1], reg[2], reg[3] );
			switch( inst )
			{
			case 0: reg[0] = reg[0] >> Combo( reg, op ); break; // ADV
			case 1: reg[1] = reg[1] ^ op; break; // BXL
			case 2: reg[1] = Combo( reg, op ) & 7; break; // BST
			case 3: if( reg[0] != 0 ) pc = op; break; // JNZ
			case 4: reg[1] = reg[1] ^ reg[2]; break; // BXC
			case 5: appendToList( &outlist, &outlistlen, Combo( reg, op ) & 7 ); break; //OUT
			case 6: reg[1] = reg[0] >> Combo( reg, op ); break; // BDV
			case 7: reg[2] = reg[0] >> Combo( reg, op ); break; // CDV
			}
		}
#ifdef PARTB
		//if( ( initial % 10000000 ) == 0  )
		if( outlistlen == programlen && 
			outlist[15] == program[15] &&
			outlist[14] == program[14] && // Refine these manually while shrinking search space.
			outlist[13] == program[13] &&
			outlist[12] == program[12] &&
			outlist[11] == program[11] &&
			outlist[10] == program[10] &&
			outlist[9] == program[9] &&
			outlist[8] == program[8] &&
			outlist[7] == program[7] &&
			outlist[6] == program[6] &&
			outlist[5] == program[5] &&
			outlist[4] == program[4] &&
			outlist[3] == program[3] &&
			outlist[2] == program[2] &&
			outlist[1] == program[1] &&
			outlist[0] == program[0] &&
			1
		)
		{
			//printf( " " );
		//	printf( "%ld ", initial );
		//	for( int i = 0; i < outlistlen; i++ )
		//		printf( "%d%c", outlist[i], (i == outlistlen-1)?'\n':',' );
			//printf( "+" );
			//for( int i = 0; i < programlen; i++ )
			//	printf( "%d%c", program[i], (i == programlen-1)?'\n':',' );
		}
		if( outlistlen == programlen && 0 == memcmp( outlist, program, programlen*sizeof(program[0]) ) )
		{
			printf( "%ld\n", initial  );
			break;
		}
		free( outlist );
		/*if( ( initial % 100000 ) == 0 )
		{
			printf( "%.3f%% %d %d\n", initial / (double)MAXIT, outlistlen, programlen );
		}*/
#else
		for( int i = 0; i < outlistlen; i++ )
			printf( "%d%c", outlist[i], (i == outlistlen-1)?'\n':',' );
#endif
	}
	return 0;
}
//136902133483675 is too high for part B
//MAybe 109019476330651
