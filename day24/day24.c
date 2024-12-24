#include "aoclib.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define CNRBTREE_IMPLEMENTATION
#include "cnrbtree.h"

// Holy C-Style
typedef uint64_t u64;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint8_t u8;

typedef struct object_t
{
	int type;
	int value;
	int evaled;

	char * in1;
	char * in2;
} object;
typedef char * str;
CNRBTREETEMPLATE( str, object, RBstrcmp, RBstrcpy, RBstrdel );
cnrbtree_strobject * nodes;


CNRBTREETEMPLATE( str, int, RBstrcmp, RBstrcpy, RBstrdel );
cnrbtree_strint * opmap;


int Evaluate( object * o )
{
	if( o->evaled ) return o->value;
	if( o->type == 0 ) return o->value;

	int v = 0;
	int v1 = Evaluate( &RBA( nodes, o->in1 ) );
	int v2 = Evaluate( &RBA( nodes, o->in2 ) );
	switch( o->type )
	{
		case 1: v = v1 & v2; break;
		case 2: v = v1 | v2; break;
		case 3: v = v1 ^ v2; break;
	}
	o->value = v;
	o->evaled = 1;
	return v;
}

int main()
{
	//Constructs the tree
	nodes = cnrbtree_strobject_create();
	opmap = cnrbtree_strint_create();
	RBA( opmap, "AND" ) = 1;
	RBA( opmap, "OR" ) = 2;
	RBA( opmap, "XOR" ) = 3;

	while( !iseof() )
	{
		char * stro = takeString( ":" );
		if( !takeChar( ' ' ) )
			terror( "expected space\n" );
		int n;
		if( !takeNumber( &n ) )
			terror( "expected number\n" );
		if( !takeChar( '\n' ) )
			terror( "Exepcted newline\n" );
		object * o = &RBA( nodes, stro );
		o->type = 0;
		o->value = n;
		o->evaled = 1;

		if( takeChar( '\n' ) )
			break;
	}

	while( !iseof() )
	{
		char * stri1 = takeString( " " );
		char * op = takeString( " " );
		char * stri2 = takeString( " " );
		if( !matchString( "-> " ) ) terror( "Expected ->" );
		char * stro = takeString( "\n" );
		takeChar( '\n' ); // just in case.

		int opid = RBA( opmap, op );

		object * o = &RBA( nodes, stro );
		o->type = opid;
		o->value = 0;
		o->in1 = stri1;
		o->in2 = stri2;
	}

	uint64_t sum = 0;

	RBFOREACH( strobject, nodes, i )
	{
		if( i->key[0] != 'z' ) continue;
		object * o = &i->data;
		int pl = atoi( i->key+1 );
		sum |= (uint64_t)Evaluate( o ) << (uint64_t)pl;
	}
	printf( "%ld\n", sum );
	return 0;
}
