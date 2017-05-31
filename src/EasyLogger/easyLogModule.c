

#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <assert.h>
#include "module.h"
#include <pthread.h>
#include <string.h>
#include <elog.h>

#if 0

#endif


/************************inner typedef*****************************/

typedef struct{
	int initflag;
}EasyLogModule_c;


/***********************static Var****************************/
EasyLogModule_c  __easyLogModule_c = {0};
EasyLogModule_c  *easyLogModule_c = &__easyLogModule_c;



/**********************Private Function*******************/
static inline EasyLogModule_c *getDev(){
	return easyLogModule_c;
}
/**
 *    This Function will be called by module_init automatic
 */
static inline void setInitFlag(){
	assert(getDev()->initflag == 0);
	getDev()->initflag = 0xB;
}
/**
 *    [如果没有init则立刻中止程序，用来规范程序的加载顺序]
 *
 */
static inline __maybe_unused int  isInit(){
	assert(getDev()->initflag == 0xB);
}






/***********************Extern function********************/







void prieasyLogModule_c(void){
	printf("*************************easyLogModule_c*************************\n");

	printf("\n");

}


static int  easyLogModule_c_init(void)
{
	setbuf(stdout, NULL);
	/* initialize EasyLogger */
	elog_init();
	/* set EasyLogger log format */
	elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
	elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
	elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
	elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
	elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
	elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);

#ifdef ELOG_COLOR_ENABLE
	elog_set_text_color_enabled(true);
#endif
	/* start EasyLogger */
	elog_start();
	return 0;
}

static void  easyLogModule_c_exit(void)
{

}
early_init(easyLogModule_c_init)
early_exit(easyLogModule_c_exit)


