/*
 * SysGuard - minimal Linux character device driver.
 *
 * This module demonstrates the kernel-space side of the project.
 * It exposes a read-only misc character device at /dev/sysguard.
 *
 * The driver returns a short diagnostic message when read.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_MESSAGE "SysGuard kernel driver: device communication OK\n"

static ssize_t sysguard_read(struct file *file,
                             char __user *buffer,
                             size_t length,
                             loff_t *offset)
{
    size_t msg_len = sizeof(DEVICE_MESSAGE) - 1;

    if (*offset >= msg_len)
        return 0;

    if (length > msg_len - *offset)
        length = msg_len - *offset;

    if (copy_to_user(buffer, DEVICE_MESSAGE + *offset, length))
        return -EFAULT;

    *offset += length;
    return length;
}

static const struct file_operations sysguard_fops = {
    .owner = THIS_MODULE,
    .read = sysguard_read,
};

static struct miscdevice sysguard_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "sysguard",
    .fops = &sysguard_fops,
    .mode = 0444,
};

static int __init sysguard_init(void)
{
    int ret = misc_register(&sysguard_device);
    if (ret)
        pr_err("SysGuard: failed to register device\n");
    else
        pr_info("SysGuard: /dev/sysguard registered\n");
    return ret;
}

static void __exit sysguard_exit(void)
{
    misc_deregister(&sysguard_device);
    pr_info("SysGuard: device removed\n");
}

module_init(sysguard_init);
module_exit(sysguard_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SysGuard Project");
MODULE_DESCRIPTION("Minimal character device driver for SysGuard");
MODULE_VERSION("1.0");
