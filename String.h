#ifndef SIMPLE_STRING_H
#define SIMPLE_STRING_H

#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#include "Vector.h"

static struct private_String {
	unsigned int length;
	string value;
	int capacity;
	int id;
};

typedef struct String String;
typedef struct String {
	void *private;
	int (*size)();
	string (*toString)();
	string (*from)(int);
	string (*fromTo)(int,int);
	char (*charAt)(int);
	bool (*equals)(string);
	bool (*contains)(string);
	int (*resize)(int);
	string (*append)(string);
	int (*lastIndexOf)(char);
	int (*lastIndexOfFrom)(char,int);
	int (*indexOf)(char);
	int (*indexOfFrom)(char,int);
	void (*set)(string);
	string (*trim)();
	bool (*empty)();
	void (*clear)();
	char (*first)();
	char (*last)();
	string (*replace)(string,string);
	string (*insert)(string,int);
	Vector(string)* (*split)(char);
	string (*toLowerCase)();
	string (*toUpperCase)();
	bool (*starts)(string);
	bool (*ends)(string);
	int (*occurences)(string);
	string (*after)(string);
	string (*before)(string);
	void (*destroy)();
}String;

#define _String_new(val) ({\
		String *_String = (String*) malloc(sizeof(String));\
		if(!_String) return;\
		_String->private = malloc(sizeof(struct private_String));\
		if(!_String->private) return;\
		if(val!=null){\
			((struct private_String*)_String->private)->length = sizeof(val);\
			((struct private_String*)_String->private)->capacity = ((struct private_String*)_String->private)->length + 16;\
			((struct private_String*)_String->private)->value = calloc(1,((struct private_String*)_String->private)->capacity);\
			if(!((struct private_String*)_String->private)->value) return;\
			strcpy(((struct private_String*)_String->private)->value, val);\
		} else {\
			((struct private_String*)_String->private)->length = 0;\
			((struct private_String*)_String->private)->capacity = 32;\
			((struct private_String*)_String->private)->value = calloc(1,32);\
			if(!((struct private_String*)_String->private)->value) return;\
		}\
		string string_toString() {\
			return ((struct private_String*)_String->private)->value;\
		}\
		_String->toString = string_toString;\
		string string_from(int start) {\
			if(start>=((struct private_String*)_String->private)->length)\
				return "";\
			string ret = (string) malloc(((struct private_String*)_String->private)->length - start + 1);\
			if(!ret) {\
				puts("Erro ao criar string temporaria");\
				return "";\
			}\
			int j=0;\
			for(int i=start; i<((struct private_String*)_String->private)->length; i++, j++)\
				ret[j] = ((struct private_String*)_String->private)->value[i];\
			ret[j]='\0';\
			return ret;\
		}\
		_String->from = string_from;\
		string string_fromTo(int start, int end) {\
			if(start>=((struct private_String*)_String->private)->length)\
				return "";\
			if(end>=((struct private_String*)_String->private)->length)\
				end=((struct private_String*)_String->private)->length;\
			string ret = malloc(end - start + 1);\
			if(!ret) {\
				puts("Erro ao criar string temporaria");\
				return "";\
			}\
			int j=0;\
			for(int i=start; i<end; i++, j++)\
				ret[j] = ((struct private_String*)_String->private)->value[i];\
			ret[j]='\0';\
			return ret;\
		}\
		_String->fromTo = string_fromTo;\
		char string_charAt(int index) {\
			if(index>=((struct private_String*)_String->private)->length)\
				return -1;\
			return ((struct private_String*)_String->private)->value[index];\
		}\
		_String->charAt = string_charAt;\
		bool string_equals(string str) {\
			return strcmp(((struct private_String*)_String->private)->value,str)?false:true;\
		}\
		_String->equals = string_equals;\
		int string_resize(int size) {\
			if(((struct private_String*)_String->private)->length>=size) return -1;\
			((struct private_String*)_String->private)->capacity = size;\
			((struct private_String*)_String->private)->value = realloc(((struct private_String*)_String->private)->value,size);\
			if(!((struct private_String*)_String->private)->value) {\
				puts("Erro no string resize");\
				return -1;\
			}\
			return size;\
		}\
		_String->resize = string_resize;\
		bool string_contains(string str) {\
			return strstr(((struct private_String*)_String->private)->value,str)?true:false;\
		}\
		_String->contains = string_contains;\
		string string_append(string str) {\
			if(!str) return null;\
			int len = strlen(str);\
			char *ret = malloc(((struct private_String*)_String->private)->length + len);\
			if(!ret) {\
				puts("Erro no append");\
				return null;\
			}\
			strcpy(ret,((struct private_String*)_String->private)->value);\
			strcat(ret,str);\
			ret[((struct private_String*)_String->private)->length + len]='\0';\
			return ret;\
		}\
		_String->append = string_append;\
		__attribute__ ((destructor)) void string_destroy() {\
		}\
		((struct private_String*)_String->private)->destroy = string_destroy;\
		int string_size() {\
			return ((struct private_String*)_String->private)->length;\
		}\
		_String->size = string_size;\
		int string_indexOf(char ch) {\
			for(int i=0;i<((struct private_String*)_String->private)->length;i++) {\
				if(((struct private_String*)_String->private)->value[i]==ch)\
					return i;\
			}\
			return -1;\
		}\
		_String->indexOf = string_indexOf;\
		int string_lastIndexOf(char ch) {\
			for(int i=((struct private_String*)_String->private)->length;i>=0;i--) {\
				if(((struct private_String*)_String->private)->value[i]==ch)\
					return i;\
			}\
			return -1;\
		}\
		_String->lastIndexOf = string_lastIndexOf;\
		int string_indexOfFrom(char ch,int pos) {\
			for(int i=pos;i<((struct private_String*)_String->private)->length;i++) {\
				if(((struct private_String*)_String->private)->value[i]==ch)\
					return i;\
			}\
			return -1;\
		}\
		_String->indexOfFrom = string_indexOfFrom;\
		int string_lastIndexOfFrom(char ch, int pos) {\
			for(int i=((struct private_String*)_String->private)->length-pos;i>=0;i--) {\
				if(((struct private_String*)_String->private)->value[i]==ch)\
					return i;\
			}\
			return -1;\
		}\
		_String->lastIndexOfFrom = string_lastIndexOfFrom;\
		void string_set(string str) {\
			int len = strlen(str)+1;\
			char *temp;\
			if(((struct private_String*)_String->private)->capacity<len) {\
				temp = malloc(len);\
				if(!temp) {\
					puts("Erro no set da String");\
					return;\
				}\
				strcpy(temp,str);\
				free(((struct private_String*)_String->private)->value);\
				((struct private_String*)_String->private)->value = temp;\
			} else \
				strcpy(((struct private_String*)_String->private)->value, str);\
			((struct private_String*)_String->private)->length = len;\
			((struct private_String*)_String->private)->capacity = len;\
		}\
		_String->set = string_set;\
		string string_trim() {\
			int start, end;\
			end = ((struct private_String*)_String->private)->length;\
			for(start=0;start<end && isspace(((struct private_String*)_String->private)->value[start]);start++);\
			end-=2;\
			for(;end>=0 && isspace(((struct private_String*)_String->private)->value[end]);end--);\
			string ret = calloc(1,end-start);\
			if(!ret) {\
				puts("Erro ao criar string temporaria");\
				return ((struct private_String*)_String->private)->value;\
			}\
			strncpy(ret,((struct private_String*)_String->private)->value + start,end-start);\
			return ret;\
		}\
		_String->trim = string_trim;\
		bool string_empty() {\
			return ((struct private_String*)_String->private)->length>0;\
		}\
		_String->empty = string_empty;\
		void string_clear() {\
			free(((struct private_String*)_String->private)->value);\
			((struct private_String*)_String->private)->length = 0;\
			((struct private_String*)_String->private)->value = calloc(1,32);\
			((struct private_String*)_String->private)->capacity = 32;\
		}\
		_String->clear = string_clear;\
		char string_first() {\
			if(((struct private_String*)_String->private)->value==null)\
				return 0;\
			return ((struct private_String*)_String->private)->value[0];\
		}\
		_String->first = string_first;\
		char string_last() {\
			if(((struct private_String*)_String->private)->value==null)\
				return 0;\
			return ((struct private_String*)_String->private)->value[((struct private_String*)_String->private)->length-1];\
		}\
		_String->last = string_last;\
		string string_replace(string oldStr,string newStr) {\
			if(!oldStr)\
				return ((struct private_String*)_String->private)->value;\
			int oldLen=strlen(oldStr);\
			int newLen=0;\
			if(newStr)\
				newLen = strlen(newStr);\
			if(oldLen==0)\
				return ((struct private_String*)_String->private)->value;\
			if(((struct private_String*)_String->private)->length<=oldLen)\
				return null;\
			char *ret=null;\
			char *tmp = ((struct private_String*)_String->private)->value;\
			int count=0, total;\
			while(*tmp!='\0' && (tmp = strstr(tmp, oldStr))) {\
			   count++;\
			   tmp+=oldLen;\
			}\
			if(count>0) {\
				if(newLen>oldLen) \
					total = ((struct private_String*)_String->private)->length + count * (newLen - oldLen);\
				else if(oldLen>newLen) \
					total = ((struct private_String*)_String->private)->length - count * (oldLen - newLen) + 1;\
				else\
					total = ((struct private_String*)_String->private)->length + 1;\
				ret = malloc(total);\
				if(!ret) {\
					puts("Erro no append");\
					return ((struct private_String*)_String->private)->value;\
				}\
				tmp = ((struct private_String*)_String->private)->value;\
				count = 0;\
				while (*tmp) {\
					if (strstr(tmp, oldStr) == tmp) {\
						strcpy(&ret[count], newStr);\
						count += newLen;\
						tmp += oldLen;\
					} else\
						ret[count++] = *tmp++;\
				}\
				ret[count] = '\0';\
			}\
			return ret;\
		}\
		_String->replace = string_replace;\
		string string_insert(string str,int pos) {\
			if(!str) return null;\
			int len = strlen(str);\
			char *ret = malloc(((struct private_String*)_String->private)->length + len);\
			if(!ret) {\
				puts("Erro no append");\
				return null;\
			}\
			strncpy(ret,((struct private_String*)_String->private)->value,pos);\
			strncpy(ret+pos,str,len);\
			strncpy(ret+pos+len,((struct private_String*)_String->private)->value + pos,((struct private_String*)_String->private)->length -pos);\
			return ret;\
		}\
		_String->insert = string_insert;\
		string string_toLowerCase() {\
			int i;\
			char *temp = malloc(((struct private_String*)_String->private)->length + 1);\
			for(i=0;i<=((struct private_String*)_String->private)->length;i++)\
				temp[i]=tolower(((struct private_String*)_String->private)->value[i]);\
			temp[i]='\0';\
			return temp;\
		}\
		_String->toLowerCase = string_toLowerCase;\
		string string_toUpperCase() {\
			int i;\
			char *temp = malloc(((struct private_String*)_String->private)->length + 1);\
			for(i=0;i<=((struct private_String*)_String->private)->length;i++)\
				temp[i]=toupper(((struct private_String*)_String->private)->value[i]);\
			temp[i]='\0';\
			return temp;\
		}\
		_String->toUpperCase = string_toUpperCase;\
		void string_destroy() {\
			free(_String);\
		}\
		_String->destroy = string_destroy;\
		_String;\
	})


static string __value_int__(int value) {
	char *str = malloc(24);
	sprintf(str,"%d",value);
	return str;
}

static string __value_float__(float value) {
	string str = malloc(30);
	sprintf(str,"%0.4f",value);
	return str;
}

static string __value_double__(double value) {
	string str = malloc(36);
	sprintf(str,"%0.8f",value);
	return str;
}

static string __value_char__(char value) {
	char *str = malloc(2);
	str[0] = value;
	str[1] = '\0';
	return str;
}

static string __build__(string str, ...) {
	int len = strlen(str);
	int size=len;
	int capacity = len + 32;
	string s = malloc(capacity);
	strcpy(s,str);
	va_list list;
	va_start(list,str);
	while(1) {
		string st = va_arg(list,string);
		if(!st)
			break;
		len = strlen(st);
		if(!len)
			break;
        else if(len+1>=capacity) {
			capacity *= 1.5;
            s = realloc(s,capacity);
        }
        size +=len;
        strcat(s,st);
	}
	s[--size]='\0';
	return s;
}

static bool __compare__(string s1, string s2) {
	return strcmp(s1,s2)!=0;
}

struct {
	string (*valueInt)(int);
	string (*valueFloat)(float);
	string (*valueDouble)(double);
	string (*valueChar)(char);
	string (*toHex)(void*);
	bool (*compare)(string,string);
	string (*build)(string,...);
}StringUtils = {
	.valueInt = __value_int__,
	.valueFloat = __value_float__,
	.valueDouble = __value_double__,
	.valueChar = __value_char__,
	.build = __build__,
	.compare = __compare__
};

#endif
