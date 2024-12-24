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
	int height;

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

int ComputeHeight( object * o )
{
	if( o->height ) return o->height;
	if( o->type == 0 ) { o->height = 1; return 1; }
	int h1 = ComputeHeight( &RBA(nodes, o->in1 ) );
	int h2 = ComputeHeight( &RBA(nodes, o->in2 ) );
	o->height = (h1>h2)?h1:h2;
	return o->height + 1;
}


void PrintStack( char * key )
{
	object * o = &RBA( nodes, key );
	printf( "(%s", key );
	if( o->type == 0 )
	{
	}
	else
	{
		char * in1 = o->in1;
		char * in2 = o->in2;
		if( RBA( nodes, in1 ).height > RBA( nodes, in2 ).height )
		{
			char * tmp = in1;
			in1 = in2;
			in2 = tmp;
		}
		printf( "%02d", o->height );
		PrintStack( in1 );
		switch( o->type )
		{
		case 1: printf( "AND" ); break;
		case 2: printf( " OR" ); break;
		case 3: printf( "XOR" ); break;
		}
		PrintStack( in2 );
	}
	printf( ")" );
}


void Swap( char * a, char * b )
{
	object * o0 = &RBA( nodes, a );
	object * o1 = &RBA( nodes, b );

	object tmp;
	memcpy( &tmp, o0, sizeof( tmp ) );
	memcpy( o0, o1, sizeof( tmp ) );
	memcpy( o1, &tmp, sizeof( tmp ) );
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

	// z09 is hard required.

	Swap( "nnf", "z09" );
//	Swap( "vbr", "nnf" );
	Swap( "kqh", "ddn" );
	Swap( "z34", "wrc" );
	Swap( "z20", "nhs" );
//	Swap( "z09", "nnf" );

	uint64_t sum = 0;

	RBFOREACH( strobject, nodes, i )
	{
		if( i->key[0] != 'z' ) continue;
		object * o = &i->data;
		//sum |= (uint64_t)Evaluate( o ) << (uint64_t)pl;
		ComputeHeight( o );
		printf( "%s ", i->key );
		PrintStack( i->key );
		printf( "\n" );
	}
	printf( "%ld\n", sum );
	return 0;
}

// vbr, z09
// what about nnf / z09  <<COMMTI
// z20/nhs YES DONE
// kqh / ddn? << WRONG
// z34 / wrc

// z09  was undone
// ddn kgh nhs nnf vbr wrc z20 z34 z09?
// ddn,kgh,nhs,nnf,vbr,wrc,z20,z34,z09
// WRONG: ddn,kgh,nhs,nnf,vbr,wrc,z20,z34
// WRONG: ddn,kgh,nhs,nnf,vbr,wrc,z09,z20,z34
// ddn,kqh,nhs,nnf,wrc,z09,z20,z34

