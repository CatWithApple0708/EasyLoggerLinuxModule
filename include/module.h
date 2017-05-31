
#define __maybe_unused		__attribute__((unused))
#define __always_unused		__attribute__((unused))

typedef int (*initcall_t)(void);
typedef void (*exitcall_t)(void);


#define EARLY_INIT 101
#define SUB_INIT 150
#define MODULE_INIT 199
#define LATE_INIT 999

#define EARLY_EXIT 101
#define SUB_EXIT 300
#define MODULE_EXIT 500
#define LATE_EXIT 999

#define __module_init(func, level) 	\
	static inline initcall_t __maybe_unused __inittest(void)		\
	{ return func; }					\
	static inline void  __attribute__ ((constructor(level)))  init_module(void) \
	{	\
		printf(#level"::loading.........%s\n",__FILE__); 	\
		func();	\
		setInitFlag();\
	}

#define __module_init_final(func, level) 	\
	static inline initcall_t __maybe_unused __inittest(void)		\
	{ return func; }					\
	static inline void  __attribute__ ((constructor))  init_module(void) \
	{	\
		printf(#level"::loading.........%s\n",__FILE__); 	\
		func();	\
		setInitFlag();\
	}

#define __module_exit(exitfn, level)					\
	static inline exitcall_t __maybe_unused __exittest(void)		\
	{ return exitfn; }					\
	static inline void  __attribute__ ((destructor(level)))  exit_module(void) \
	{exitfn();}


/**
 *    下面的函数会
 *    1.在main函数前执行
 *    2. 库函数加载时执行
 *    WARNING:
 *    	1. 每个c文件中只能有一个下面的声明
 *    	2. 使用时候不能加分号，加了分号 编译器不会有提示，但加载时候可能会卡死
 */
#define early_init(func) __module_init(func,EARLY_INIT)
#define sub_init(func) __module_init(func,SUB_INIT)
#define module_init(func) __module_init(func,MODULE_INIT)
#define late_init(func) __module_init(func,LATE_INIT)
#define final_init(func) __module_init_final(func,FINAL)


#define module_init_X(func,X) __module_init(func,X)




/**
 *    下面的函数会
 *    1.在exit函数前执行
 *    2. 库卸载时执行
 *    WARNING:
 *    	1. 每个c文件中只能有一个下面的声明
 */
#define early_exit(func) __module_exit(func,EARLY_EXIT)
#define sub_exit(func) __module_exit(func,SUB_EXIT)
#define module_exit(func) __module_exit(func,MODULE_INIT)
#define late_exit(func) __module_exit(func,LATE_EXIT)




