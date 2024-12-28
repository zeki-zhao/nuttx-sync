#include <nuttx/config.h>
#include <stdlib.h>
#include <fixedmath.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>
#include <nuttx/kmalloc.h>
#include <nuttx/fs/fs.h>
#include <nuttx/drivers/LEDBling.h>
 
#if defined (CONFIG_LEDBLING)
static int LEDBLING_open(FAR struct file * fp);
static int LEDBLING_close(FAR struct file * fp);
static int LEDBLING_ioctl(FAR struct file * fp ,int cmd , unsigned long arg);
static int LEDBLING_read(FAR struct file * fp , FAR char * buffer ,size_t buflen);
static int LEDBLING_write(FAR struct file * fp , FAR const char* buffer , size_t buflen);
 
static const struct file_operations LEDBLing_op = {
    .open = LEDBLING_open;
    .close = LEDBLING_close;
    .read = LEDBLING_read;
    .write = LEDBLING_write;
    .ioctl = LEDBLING_ioctl;
}
 
static int LEDBLING_open(FAR struct file * fp)
{
    return OK;
}
 
static int LEDBLING_close(FAR struct file * fp)
{
    return OK;
}
 
static int LEDBLING_read(FAR struct file * fp , FAR char * buffer ,size_t buflen)
{
    return OK;
}
 
static int LEDBLING_write(FAR struct file * fp , FAR const char* buffer , size_t buflen)
{
    return OK;
}
 
static int LEDBLING_ioctl(FAR struct file * fp ,int cmd , unsigned long arg)
{
    FAR struct inode * inode  = fp -> f_inode;
    FAR struct LEDBling_regis_s *lower = inode->i_private;
    int ret = OK;
 
    switch(cmd)
    {
        // 这个函数是设置GPIO的状态函数
        case LEDBLING_SET:
            FAR struct LEDBling_param param = {0};
            param.num = arg & 0xFF;
            param.on.state = (arg >> 8) & 0x03;
            ret = lower -> setio(lower,param);
        break;
 
        case LEDBLING_GET:
            FAR struct LEDBling_status *ptr = (FAR struct LEDBling_status*)((uintptr_t)arg);
            DEBUGASSERT(ptr!=NULL);
            ret = lower-> getio(lower,ptr);
        break;
 
        default:
            ret  = lower -> ioctl(lower,cmd,arg);
        break;
             
    }
    return ret;
}
 
int LEDBling_register(FAR const char *path,FAR struct LEDBling_regis_s *dev,FAR void* lower)
{
    int ret;
 
    DEBUGASSERT(path != NULL);
    DEBUGASSERT(lower != NULL);
 
    ret = register_driver(path, &LEDBLing_op, 0666, lower);
 
    if (ret < 0){
        _err("ERROR: Failed to register slim led driver: %d\n", ret);
    }
 
    return ret;
 
}