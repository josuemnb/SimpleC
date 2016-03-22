#ifndef SIMPLE_MAP_H
#define SIMPLE_MAP_H

#include <assert.h>

#include "simple.h"

static struct private_Map {
	int kind;
	int length;
	int capacity;
	void **values;
	void **keys;
};

#define Map(Key,Value) \
	struct {\
		void *private;\
		void (*put)(Key*,Value*);\
		Key* (*getKey)(int);\
		Value* (*getValue)(int);\
		Value* (*get)(Key*);\
		void (*setValue)(Value*,int);\
		void (*setKey)(int);\
		int (*size)();\
		void (*destroy)();\
	}

#define _Map_new(Key,Value) ({\
		struct UID(map_##Key##_##Value){\
			void *private;\
			void (*put)(Key*,Value*);\
			Key* (*getKey)(int);\
			Value* (*getValue)(int);\
			Value* (*get)(Key*);\
			void (*setValue)(Value*,int);\
			void (*setKey)(int);\
			int (*size)();\
			void (*destroy)();\
		}*m;\
		m =(struct UID(map_##Key##_##Value)*) malloc(sizeof(struct UID(map_##Key##_##Value)));\
		if(!m) {\
			puts("Erro na alocação da classe Map");\
			return;\
		}\
		m->private = (struct private_Map*) malloc(sizeof(struct private_Map));\
		if(!m->private) {\
			puts("Erro na alocação dos dados privados");\
			return;\
		}\
		((struct private_Map*)m->private)->length=0;\
		((struct private_Map*)m->private)->capacity=10;\
		((struct private_Map*)m->private)->values = malloc(10 * sizeof(Value));\
		if(!((struct private_Map*)m->private)->values) {\
			puts("Erro na alocação dos dados da tabela");\
			return;\
		}\
		((struct private_Map*)m->private)->keys = malloc(10 * sizeof(Key));\
		if(!((struct private_Map*)m->private)->keys) {\
			puts("Erro na alocação dos dados da tabela");\
			return;\
		}\
		void map_put(Key* key, Value* value) {\
			if(((struct private_Map*)m->private)->length + 1>=((struct private_Map*)m->private)->capacity) {\
				((struct private_Map*)m->private)->capacity *= 1.5;\
				((struct private_Map*)m->private)->values = realloc(((struct private_Map*)m->private)->values, sizeof(Value) * (((struct private_Map*)m->private)->capacity));\
				if(!((struct private_Map*)m->private)->values) {\
					puts("ERRO de realocar values do map na memoria");\
					return;\
				}\
				((struct private_Map*)m->private)->keys = realloc(((struct private_Map*)m->private)->keys, sizeof(Key) * (((struct private_Map*)m->private)->capacity));\
				if(!((struct private_Map*)m->private)->keys) {\
					puts("ERRO de realocar keys do map na memoria");\
					return;\
				}\
			}\
			memcpy(((struct private_Map*)m->private)->values + ((struct private_Map*)m->private)->length, &value, sizeof(Value));\
			memcpy(((struct private_Map*)m->private)->keys + ((struct private_Map*)m->private)->length, &key, sizeof(Key));\
			((struct private_Map*)m->private)->length++;\
		}\
		m->put = map_put;\
		Value* map_getValue(int index) {\
			if(((struct private_Map*)m->private)->length + 1<=index){\
				puts("Erro na obtenção do index");\
				return (Value*)null;\
			}\
			return (Value*)((struct private_Map*)m->private)->values[index];\
		}\
		m->getValue = map_getValue;\
		Key* map_getKey(int index) {\
			if(((struct private_Map*)m->private)->length + 1<=index){\
				puts("Erro na obtenção do index");\
				return (Key*)null;\
			}\
			return (Key*)((struct private_Map*)m->private)->keys[index];\
		}\
		m->getKey = map_getKey;\
		int map_size() {\
			return ((struct private_Map*)m->private)->length;\
		}\
		m->size = map_size;\
		Value* map_get(Key* key) {\
			if(((struct private_Map*)m->private)->length==0)\
				return (Value*)NULL;\
			if(__builtin_types_compatible_p(__typeof__(*key), string)) {\
				for(int i = 0; i < ((struct private_Map*)m->private)->length; i++ ) {\
					if(!strcmp(((struct private_Map*)m->private)->keys[i],(string)key))\
						return (Value*)((struct private_Map*)m->private)->values[i];\
				}\
				return (Value*)NULL;\
			}else {\
				for(int i = 0; i < ((struct private_Map*)m->private)->length; i++ ) {\
					if(((struct private_Map*)m->private)->keys[i]==key)\
						return (Value*)((struct private_Map*)m->private)->values[i];\
				}\
				return (Value*)NULL;\
			}\
		}\
		m->get = map_get;\
		void map_setValue(Value* value, int index) {\
			if(((struct private_Map*)m->private)->length + 1<=index){\
				return;\
			}\
			memcpy(((struct private_Map*)m->private)->values + index, &value, sizeof(Value));\
		}\
		m->setValue = map_setValue;\
		void map_destroy() {\
			assert(m);\
		}\
		m->destroy = map_destroy;\
		m;\
	})

#endif /* MAP_H_ */
