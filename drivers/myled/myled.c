#include <nuttx/config.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fixedmath.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>
#include <nuttx/kmalloc.h>
#include <nuttx/fs/fs.h>

#include <nuttx/myled/myled.h>


#if defined(CONFIG_MY_LED)
/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/
static int  myled_open(FAR struct file *filep);
static int  myled_close(FAR struct file *filep);
static int  myled_ioctl(FAR struct file *filep, int cmd, unsigned long arg);
static int  myled_read(FAR struct file *filep, FAR char *buffer, size_t buflen);
static int  myled_write(FAR struct file *filep, FAR const char *buffer,size_t buflen);

/****************************************************************************
 * Private Data
 ****************************************************************************/
static const struct file_operations myled_fops = {
    .open   = myled_open,
    .close  = myled_close,
    .read   = myled_read,
    .write  = myled_write,
    .ioctl  = myled_ioctl,
};
/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: myled_ioctl
 ****************************************************************************/
static int  myled_open(FAR struct file *filep){
    return OK;
}
static int  myled_close(FAR struct file *filep){
    return OK;
}
static int myled_read(FAR struct file *filep, FAR char *buffer, size_t buflen){
    return OK;
}
static int myled_write(FAR struct file *filep, FAR const char *buffer,size_t buflen){
    FAR struct inode *inode    = filep->f_inode;
    FAR struct myled_lower_s *lower = inode->i_private;
    // syslog(LOG_DEBUG,"in myled_write\n");

    return OK;
}
static int myled_ioctl(FAR struct file *filep, int cmd, unsigned long arg)
{
    FAR struct inode *inode    = filep->f_inode;
    FAR struct myled_lower_s *lower = inode->i_private;
    FAR struct myled_param_s param = {0};
    param.num = arg;
    int ret = 1;

    switch (cmd)
    {
        case SLEDIOC_SET:{
            if(lower->getio(param.num) == 1){
                lower->setio((int)param.num,(bool)0);
            }else{
                lower->setio((int)param.num,(bool)1);
            }
            break;
        }
        case SLEDIOC_GET:{
            FAR struct myled_status_s *ptr = (FAR struct myled_status_s*)((uintptr_t)arg);
            DEBUGASSERT(ptr != NULL);
            ret = lower->getio(param.num); //TODO:这里可以选中GPIO引脚
            break;
        }
        default:
            // ret = lower->ioctl(lower, cmd, arg);
        break;
    }
    return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: myled_register
 ****************************************************************************/

int myled_register(FAR const char *path, FAR void *lower)
{
    int ret;

    DEBUGASSERT(path != NULL);
    DEBUGASSERT(lower != NULL);

    syslog(LOG_DEBUG,"in myled_register\n");
    /* Register the myled character driver */
    ret = register_driver(path, &myled_fops, 0666, lower);
    if (ret < 0){
        _err("ERROR: Failed to register slim led driver: %d\n", ret);
    }

    return ret;
}

#endif
