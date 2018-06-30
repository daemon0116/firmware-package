#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/ioctl.h>

/*******************************************************************************
function	：void findEventByName(char* name,char* eventNum)
input		: name:device name;eventNum:vent number point(actual output)
ouput		: eventNum: return event number
return		: none
*******************************************************************************/
void findEventByName(char* name,char* eventNum)
{
    int fd = 0;
    char i = 0;
    char devNamePath[64] = {0};
    char devName[64] = {0};
    while(1){
        memset(devNamePath,0,sizeof(devNamePath));
        memset(devName,0,sizeof(devName));
        sprintf(devNamePath,"/sys/class/input/input%d/name",i++);
        if(!access(devNamePath,F_OK))
        {
            fd = open(devNamePath,O_RDONLY);
            if(fd < 0){
                printf("%s:open %s is failed",__func__,devNamePath);
                return;
            }
            if(read(fd, devName, sizeof(devName)) < 0){
                printf("%s:read %s is failed",__func__,devNamePath);
                close(fd);
                return;
            }
            if(strstr(devName,name)){
                *eventNum = i-1;
                close(fd);
                return;
            }
            close(fd);
        }
        else
            break;
    }
}
/*******************************************************************************
function	：int openKeyDev()
input		: none
ouput		: none
return		: fd: <0 failed, >=0 success
*******************************************************************************/
int openKeyDev(void)
{
	int fd = 0;
    char eventNum = 0;
	char devName[64] = {0};
    findEventByName("gpio_keys",&eventNum);
    sprintf(devName,"/dev/input/event%d",eventNum);
	fd = open(devName,O_RDONLY);
	if(fd < 0)
	{
		printf("%s:open %s is failed",__func__,devName);
		return -1;
	}
	return fd;
}
/*******************************************************************************
function	：void AeCloseKeyDev(int fd)
input		: fd:file description
ouput		: none
return		: none
*******************************************************************************/
void closeKeyDev(int fd)
{
	close(fd);
}
int main(void)
{
	int fd = 0;
	printf("**********************************************\n");
	printf("\tWelcome Test gpio_keys driver.\n");
	printf("\tGpio_keys test program already run.\n");
	printf("\tPlease triggle key event.\n");
	printf("**********************************************\n");
	fd = openKeyDev();
	while(1){
	struct input_event t;
	if(read(fd,&t,sizeof(t))==sizeof(t))
		if(t.type == EV_KEY && (t.value == 0 || t.value == 1))
			printf("key code:%d,key value:%d\n",t.code,t.value);
	}
	closeKeyDev(fd);
}
