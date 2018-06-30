#include <stdio.h>  
#include <fcntl.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/types.h>  
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define IMX6_GPIO_MAGIC 'k'  
#define IMX6_OUT_GPIO        	    _IOWR(IMX6_GPIO_MAGIC,0x23,int)
#define IMX6_SET_GPIO               _IOWR(IMX6_GPIO_MAGIC,0x24,int)
#define IMX6_GET_GPIO        	    _IOWR(IMX6_GPIO_MAGIC,0x25,int)
#define IMX6_DISABEL_WATCHDOG       _IOWR(IMX6_GPIO_MAGIC,0x26,int)

#define IMX_GPIO_NR(port, index)		((((port)-1)*32)+((index)&31))

struct gpio_data_s{
    unsigned int gpio;
    unsigned int state;
};

int main(void)
{
    struct gpio_data_s ioctl_rdata = {
        IMX_GPIO_NR(1, 8), 
        0
    };
    int fd, ret;
    fd = open ( "/dev/imx6_gpio" , O_RDWR);
    if ( fd == -1 ) {
      perror("open");
      exit(0);
    }
    ret = ioctl( fd, IMX6_DISABEL_WATCHDOG, &ioctl_rdata);
    if ( ret == -1) {
        perror("ioctl disable watchdog");
        exit(0);
    }
    
    ret = ioctl( fd, IMX6_OUT_GPIO, &ioctl_rdata);
    if ( ret == -1) {
        perror("ioctl output");
        exit(0);
    }

    int i = 20;
    do {
        ret = ioctl( fd, IMX6_GET_GPIO, &ioctl_rdata);
        if ( ret == -1) {
            perror("ioctl get value");
            exit(0);
        }
        printf("state: %d\n", ioctl_rdata.state);
        
        ioctl_rdata.state = !ioctl_rdata.state;
        
        ret = ioctl( fd, IMX6_OUT_GPIO, &ioctl_rdata);
        if ( ret == -1) {
            perror("ioctl set value");
            exit(0);
        }
        sleep(1);        
    } while (i-- > 0);
    
    close(fd);
    return 0;
}