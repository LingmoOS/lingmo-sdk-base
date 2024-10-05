#include "libkylog.h"
#include "klog_mqueue.h"
#include "write.h"
#include "format.h"
#include "core.h"
#include <libkyconf.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

int kdk_logger_init(const char *ini)
{
	int retv	= 0;
	if (!ini)
	{
		ini = "/etc/kysdk/kysdk-base/kylog-default.conf";
	}
	int confid	= kdk_conf_init(ini);
	if (confid <= 0)
	{
		printf("%s配置文件加载失败\n", ini);
		retv = -1;
		goto clean_up;
	}
	loadFormatOptions(confid);

	retv	= initKLogger(confid);
	if (retv)
	{
		printf("kdk_logger初始化失败！%d\n" , retv);
		goto clean_up;
	}
	
	if (logger->otype == OUT_SPECFILE && logger->stype == ASYNC)
	{
		retv	= initMessageQueue(atoi(kdk_conf_get_value(confid, "MSGQUEUE" , "flushInterval")) , atoi(kdk_conf_get_value(confid, "MSGQUEUE" , "autoIncrementQueueSize")));
		if (retv)
		{
			printf("消息队列初始化失败！%d\n" , retv);
			goto clean_up;
		}
	}

clean_up:
	return retv;
}

int kdk_logger_setdir(const char* dpath)
{
	return setRootDir(dpath);
}

int kdk_logger_write(int lvl , const char *filename , const char *func , int linenum , const char *fmt , ...)
{
	if (!logger && kdk_logger_init(NULL))
	{
		printf("kdk_logger尚未初始化\n");
		return -1;
	}
	if (lvl > logger->level)
		return 0;
	char message[KLOG_MAXMSGSIZE + 1]	= {0};
	va_list vl;
	va_start(vl , fmt);
	vsnprintf(message , sizeof(char) * KLOG_MAXMSGSIZE , fmt , vl);
	va_end(vl);
	append_wrap(message);
	return writeLog(lvl , filename , func , linenum , message);
}

void kdk_logger_flush()
{
	if (!logger)
	{
		return;
	}
	if (logger->stype == ASYNC)
		flushMessageQueue(0);
}

void kdk_logger_set_autowrap(int autowrap)
{
	set_autowrap(autowrap);
}