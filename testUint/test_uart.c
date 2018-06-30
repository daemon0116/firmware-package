#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	if  ( tcgetattr( fd,&oldtio)  !=  0)
	{
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD; //CLOCAL:忽略modem控制线  CREAD：打开接受者
	newtio.c_cflag &= ~CSIZE; //字符长度掩码。取值为：CS5，CS6，CS7或CS8

	switch( nBits )
	{
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 8:
		newtio.c_cflag |= CS8;
		break;
	}

	switch( nEvent )
	{
	case 'O':
		newtio.c_cflag |= PARENB; //允许输出产生奇偶信息以及输入到奇偶校验
		newtio.c_cflag |= PARODD;  //输入和输出是奇及校验
		newtio.c_iflag |= (INPCK | ISTRIP); // INPACK:启用输入奇偶检测；ISTRIP：去掉第八位
		break;
	case 'E':
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch( nSpeed )
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	case 460800:
		cfsetispeed(&newtio, B460800);
		cfsetospeed(&newtio, B460800);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	}

	if( nStop == 1 )
		newtio.c_cflag &=  ~CSTOPB; //CSTOPB:设置两个停止位，而不是一个
	else if ( nStop == 2 )
		newtio.c_cflag |=  CSTOPB;

	newtio.c_cc[VTIME]  = 0; //VTIME:非cannoical模式读时的延时，以十分之一秒位单位
	newtio.c_cc[VMIN] = 0; //VMIN:非canonical模式读到最小字符数
	tcflush(fd,TCIFLUSH); // 改变在所有写入 fd 引用的对象的输出都被传输后生效，所有已接受但未读入的输入都在改变发生前丢弃。
	if((tcsetattr(fd,TCSANOW,&newtio))!=0) //TCSANOW:改变立即发生
	{
		perror("com set error");
		return -1;
	}
	printf("set done!\n\r");
	return 0;
}

int main(int argc, unsigned char **argv)
{
    if(2 != argc)
    {
        printf("Usge error: ./test_uart [ttymxc1/ttymxc2/ttymxc3/ttymxc4/ttymxc5]\n");
        return -1;
    }
    
	int fd1,nset,nread,ret;
	char buf[100]= {"Com loop test!..........."};
	char buf1[100];
    
    char path[20] = {0};
    
    sprintf(path, "/dev/%s", argv[1]);
	fd1 = open(path, O_RDWR);
	if (fd1 == -1)
    {
        printf("Open device %s failed!\n", argv[1]);
		exit(1);
    }
	printf("Open %s success!!\n", argv[1]);

	nset = set_opt(fd1, 9600, 8, 'N', 1);
	if (nset == -1)
		exit(1);
	printf("Enter loop test!\n");

	while (1)

	{
		memset(buf1, 0, sizeof(buf1));
		ret = write(fd1, buf, 100);
		nread = read(fd1, buf1, 100);
		if(nread > 0)
		{
			printf("receive data:%s\n", buf1);
		}
		usleep(500000);
		//nread = read(fd1, buf1,1);
		//if(buf1[0] == 'q')
		//break;
	}
	close(fd1);

	return 0;
}

