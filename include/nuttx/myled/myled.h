#ifndef __DRIVERS_MY_LED_H__
#define __DRIVERS_MY_LED_H__

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <nuttx/fs/ioctl.h>


#define SLEDIOC_SET         0x0000
#define SLEDIOC_GET         0x0001

struct myled_status_s{
    unsigned char  state;
};

struct myled_param_s{
    short num;
    struct myled_status_s on;
};

struct myled_lower_s{
    CODE bool (*getio)(int lednum);
    CODE void (*setio)(int lednum, bool ledon);
    CODE void (*ioctl)(int lednum, bool ledon);
};

int myled_register(FAR const char *path, FAR void *lower);
// extern struct myled_lower_s myled_lower;

#endif