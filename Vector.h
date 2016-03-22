#ifndef SIMPLE_VECTOR_H
#define SIMPLE_VECTOR_H

#include <assert.h>

#include "simple.h"

#define Vector(type) \
	struct {\
		void *private;\
		int (*size)();\
		void (*add)(type*);\
		type* (*get)(int);\
		void (*set)(type*,int);\
		void (*destroy)();\
}

static struct private_Vector {
	int kind;
	int length;
	int capacity;
	void **value;
};

#define _Vector_new(type) ({\
	struct UID(vector_##type){\
		void *private;\
		int (*size)();\
		void (*add)(type*);\
		type* (*get)(int);\
		void (*set)(type*,int);\
		void (*destroy)();\
	}*v;\
	v =(struct UID(vector_##type)*) malloc(sizeof(struct UID(vector_##type)));\
	if(!v) {\
		puts("Erro na alocação da classe Vector");\
		return;\
	}\
	v->private =(struct private_Vector*) malloc(sizeof(struct private_Vector));\
	if(!v->private) {\
		puts("Erro na alocação das propriedades privadas");\
		return;\
	}\
	((struct private_Vector*)v->private)->length = 0;\
	((struct private_Vector*)v->private)->kind = VECTOR_TYPE;\
	((struct private_Vector*)v->private)->capacity = 10;\
	((struct private_Vector*)v->private)->value = malloc(10 * sizeof(type));\
	if(!((struct private_Vector*)v->private)->value) {\
		puts("Erro na alocação de dados do vector");\
		return;\
	}\
	void vector_add(type* data) {\
		if(((struct private_Vector*)v->private)->length + 1>=((struct private_Vector*)v->private)->capacity) {\
			((struct private_Vector*)v->private)->capacity *= 1.5;\
			((struct private_Vector*)v->private)->value = realloc(((struct private_Vector*)v->private)->value,sizeof(type) * (((struct private_Vector*)v->private)->capacity));\
			if(!((struct private_Vector*)v->private)->value) {\
				puts("ERRO de realocar vector na memoria");\
				return;\
			}\
		}\
		memcpy(((struct private_Vector*)v->private)->value + ((struct private_Vector*)v->private)->length, &data, sizeof(type));\
		((struct private_Vector*)v->private)->length++;\
	}\
	v->add = vector_add;\
	type* vector_get(int index) {\
		if(index>=((struct private_Vector*)v->private)->length+1){\
			puts("Erro na obtenção do index");\
			return (type*)null;\
		}\
        return (type*)((struct private_Vector*)v->private)->value[index];\
    }\
    v->get = vector_get;\
    void vector_set(type* data, int index) {\
		if(index>=((struct private_Vector*)v->private)->length+1){\
			puts("Erro na obtenção do index");\
			return (type*)null;\
		}\
		memcpy(((struct private_Vector*)v->private)->value + index, &data, sizeof(type));\
    }\
    int vector_size() {\
    	return ((struct private_Vector*)v->private)->length;\
    }\
    v->size = vector_size;\
	void vector_destroy() {\
		assert(v);\
		free(v);\
	}\
	v->destroy = vector_destroy;\
	v;\
})

#endif
