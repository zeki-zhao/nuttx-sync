#include <nuttx/config.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <fixedmath.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>
#include <nuttx/kmalloc.h>
#include <nuttx/fs/fs.h>
#include <nuttx/myled/myled.h>

#if defined(CONFIG_MY_LED)

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct myled_dev_s
{
    FAR struct myled_lower_s *lower;
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static ssize_t myled_read(FAR struct file *filep, FAR char *buffer,
                          size_t buflen);
static ssize_t myled_write(FAR struct file *filep, FAR const char *buffer,
                           size_t buflen);
static int  myled_ioctl(FAR struct file *filep, int cmd, unsigned long arg);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct file_operations myled_fops = {
    .read   = myled_read,
    .write  = myled_write,
    .ioctl  = myled_ioctl,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static ssize_t myled_read(FAR struct file *filep, FAR char *buffer,
                          size_t buflen)
{
    FAR struct inode *inode = filep->f_inode;
    FAR struct myled_dev_s *dev = inode->i_private;
    bool state;

    DEBUGASSERT(dev != NULL && dev->lower->read != NULL);
    state = dev->lower->read();

    if (buflen < 2)
    {
        return -ENOSPC;
    }

    buffer[0] = state ? '1' : '0';
    buffer[1] = '\n';
    return 2;
}

static ssize_t myled_write(FAR struct file *filep, FAR const char *buffer,
                           size_t buflen)
{
    FAR struct inode *inode = filep->f_inode;
    FAR struct myled_dev_s *dev = inode->i_private;

    DEBUGASSERT(dev != NULL && dev->lower->write != NULL);

    if (buflen < 1)
    {
        return 0;
    }

    if (buffer[0] == '0')
    {
        dev->lower->write(false);
    }
    else if (buffer[0] == '1')
    {
        dev->lower->write(true);
    }
    else
    {
        return -EINVAL;
    }

    return buflen;
}

static int myled_ioctl(FAR struct file *filep, int cmd, unsigned long arg)
{
    FAR struct inode *inode = filep->f_inode;
    FAR struct myled_dev_s *dev = inode->i_private;
    int ret;

    DEBUGASSERT(dev != NULL);

    switch (cmd)
    {
        case SLEDIOC_SET:
        {
            bool cur = dev->lower->read();
            dev->lower->write(!cur);
            ret = OK;
            break;
        }

        case SLEDIOC_GET:
        {
            ret = (int)dev->lower->read();
            break;
        }

        default:
            ret = -ENOTTY;
            break;
    }

    return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int myled_register(FAR const char *path, FAR void *lower)
{
    FAR struct myled_dev_s *dev;
    int ret;

    DEBUGASSERT(path != NULL);
    DEBUGASSERT(lower != NULL);

    dev = kmm_zalloc(sizeof(struct myled_dev_s));
    if (dev == NULL)
    {
        return -ENOMEM;
    }

    dev->lower = lower;

    ret = register_driver(path, &myled_fops, 0666, dev);
    if (ret < 0)
    {
        kmm_free(dev);
        _err("ERROR: Failed to register myled driver: %d\n", ret);
    }

    return ret;
}

#endif
