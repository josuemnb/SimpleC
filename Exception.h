#ifndef SIMPLE_EXCEPTION_H
#define SIMPLE_EXCEPTION_H

#include <setjmp.h>
#include <string.h>

static int buf_status=0;
jmp_buf ex_buf__;

#define try  buf_status = setjmp(ex_buf__); if(buf_status==0)
#define catch(excp) else if(buf_status==((Exception)excp).id)
#define finally else
#define throw(excp) ({\
		printf("EXCEPTION RAISED: \'%s\' \n\tAT FILE \'%s\' \n\tIN LINE \'%d\' \n\tCALLED BY \'%s\'\n",((Exception)excp).msg, __FILE__, __LINE__,__FUNCTION__);\
		longjmp(ex_buf__, ((Exception)excp).id);\
	})


typedef struct Exception Exception;
typedef struct Exception{
    int id;
    const char * msg;
    Exception * supertype;
}Exception;

#define _Exception_new(message) ({Exception UID(Exception) = { __COUNTER__+1, message};UID(Exception);})


#endif // SIMPLE_EXCEPTION_H
