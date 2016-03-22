# SimpleC
C with classes and generics

Code like java or c++ but in c pure code.

#include "simple.h"
#include "Vector.h"
#include "Map.h"

void main() {
//
	Vector(string) *vi = new(Vector,string);
	for(int i=0;i<10;i++)
		vi->add(StringUtils.valueInt(i));
	foreach(id,vi)
		printf("%s\n",id);
	vi->destroy();

	Map(int,string) *m = new(Map,int,string);
	for(int i=0;i<20;i++)
		m->put(i,StringUtils.build("teste de getKey ", StringUtils.valueInt(i), " done"));


	for(int i=0;i<10;i++)
		m->setValue("ola",i);
	puts(m->getValue(10));
