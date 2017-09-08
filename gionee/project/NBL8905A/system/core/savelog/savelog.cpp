/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
      
#define LOG_TAG "savelog"

#include <cutils/properties.h>
 
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#include <utils/Log.h>
#include <utils/threads.h>

#if defined(HAVE_PTHREADS)
# include <pthread.h>
# include <sys/resource.h>
#endif

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

//#define LOGE(x...) do { KLOG_ERROR("charger", x); } while (0)
//#define LOGI(x...) do { KLOG_INFO("charger", x); } while (0)
//#define LOGV(x...) do { KLOG_DEBUG("charger", x); } while (0)

using namespace android;

char savepath[256] = "/system/bin/cat /proc/kmsg > /";
void gen_fname(int is_sdcard)
{
	char buffer[30];
	struct timeval tv;
	time_t cur_time;

	if(is_sdcard)
	{
		strcat(savepath, "storage/sdcard0/logs-chg/");		
	}
	else
	{
		strcat(savepath, "data/local/tmp/");		
	}

	gettimeofday(&tv, NULL);
	cur_time=tv.tv_sec;
	strftime(buffer, 30, "%Y%m%d%H%M%S", localtime(&cur_time));

	strcat(savepath, "poweroff_chg_");
	strcat(savepath, buffer);
	strcat(savepath, ".log");
}

int main(int argc, char** argv)
{
        //char* argv[] = {"/system/bin/cat","/proc/kmsg"," > /data/local/1", (char*)0};
        //execv( "/system/bin/cat", argv);
        //execl( "/system/bin/cat", "cat", "/system/build.prop", " > /data/local/tmp/1", NULL);
	int pid = fork();
	int result = 0;
	
      //klog_init();
	  //klog_set_level(6);
      //LOGI("--------------- enter save poweroff chg log ---------------\n"); 

      if(pid <0) 
      {
          printf("fork error");  
          //LOGI("fork error");  
      }
      
      if (pid == 0)
      {
      	printf("I am child process, My process id is %d\n", getpid()); 
      	//LOGI("child process running ...\n"); 
		system("/system/bin/mount -t vfat -r -w /dev/block/mmcblk0p20 /storage/sdcard0/");
		system("/system/bin/mkdir /storage/sdcard0/test");
		if (access("/storage/sdcard0/test/", F_OK) != 0)
		{
			printf("sdcard mount error\n");  
			gen_fname(0);
		}
		else
		{
			printf("sdcard mount success\n"); 
			system("/system/bin/rm /storage/sdcard0/test");
			if (access("/storage/sdcard0/logs-chg/", F_OK) != 0)
			{
				system("/system/bin/mkdir /storage/sdcard0/logs-chg");
			}
			gen_fname(1);
		}
		
		printf("%s\n", savepath);  
		system(savepath);
        printf("child process running over\n");
      }
      else
      {
      	printf("I am parent process, My process id is %d\n", getpid());
		//LOGI("parent process running\n"); 
      	waitpid(pid,&result,0);
        printf("parent process running over\n");
      }

      //LOGI("--------------- exit save poweroff chg log ---------------\n"); 
    return 0;
}
