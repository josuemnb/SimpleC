#ifndef SIMPLE_H
#define SIMPLE_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define new(Class,...) _##Class##_new(__VA_ARGS__)

#define VECTOR_TYPE		1234
#define STRING_TYPE 	2345
#define MAP_TYPE 		3456

#define false 0
#define true !0
#define and &&
#define or ||
#define xor ^
#define not !=
#define null NULL

#define foreach(item,collection) \
	int i = 0;\
	for(__typeof__(collection->get(0)) item  = collection->get(0);\
		i<collection->size();\
			item = collection->get(++i))

#define STR(s) #s

#define MERGE_(a,b)  a##b
#define LABEL_(a,b) MERGE_(a,b)
#define UID(b) LABEL_(b,__LINE__)
#define NUMARGS(...)  (sizeof((int[]){0, ##__VA_ARGS__})/sizeof(int)-1)

	typedef char* string;
	typedef unsigned char bool;
	typedef unsigned char byte;
	typedef void* variant;


	typedef struct var {
		union {
			unsigned char Bool:1;
			unsigned char Byte;
			char Char;
			int Int;
			float Float;
			double Double;
			string String;
			void *Pointer;
		}value;
		char type;
	} var;

	typedef struct Iterator {
		void *private;
		void* (*next)();
		bool  (*hasNext)();
		void* (*previous)();
		void* (*last)();;
		void* (*first)();
		int position;
	}Iterator;

//	#ifdef SIMPLE_STRING
//		#include <string.h>
//		#include "String.h"
//	#endif
//
//	#ifdef SIMPLE_CONSOLE
//		#include "in.h"
//		#include "out.h"
//	#endif

#endif
