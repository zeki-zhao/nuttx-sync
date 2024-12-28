#ifndef _DRIVERS_LEDBLING_H
#define _DRIVERS_LEDBLING_H
 
#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <nuttx/fs/ioctl.h>
 
 
#define LEDBLING_SET  0
#define LEDBLING_GET  1
 
struct LEDBling_status
{
    bool state;         //存储IO口状态
};
 
struct LEDBling_param
{
    short num;
    struct LEDBling_status on;
};
 
struct LEDBling_regis_s
{
    CODE int (*setio)(FAR struct file * fp ,int cmd , unsigned long arg);
    CODE int (*getio)(FAR struct file * fp ,int cmd , unsigned long arg);
    CODE int (*ioctl)(FAR struct file * fp ,int cmd , unsigned long arg);
};
 
int LEDBling_register(FAR const char *path , FAR void *lower);
 
#endif