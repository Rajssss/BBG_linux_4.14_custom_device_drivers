/*
 * main.c
 *
 *  Created on: Feb 17, 2021
 *      Author: rajssss@github.com
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>

#define DEV_MEM_SIZE 512

/* Pseudo char device memory */
char device_buffer[DEV_MEM_SIZE];

dev_t device_number;

struct cdev pcd_dev;

struct class *class_pcd;

ssize_t pcd_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
	pr_info("Writing %zu bytes.\n", count);
	pr_info("Current file position: %lld\n", *f_pos);

	/* Check and adjust count */
	if ((*f_pos + count) > DEV_MEM_SIZE)
		count = DEV_MEM_SIZE - *f_pos;

	if (!count) {
		pr_info("No space left on device.\n");
		return -ENOMEM;
	}

	/* Copy from user */
	if (copy_from_user(&device_buffer[*f_pos], buff, count))
		return -EFAULT;

	/* Update current file position */
	*f_pos += count;

	pr_info("No of bytes successfully written: %zu bytes.\n", count);
	pr_info("Current file position: %lld\n", *f_pos);

	/* Return no of bytes written */
	return count;
}

ssize_t pcd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	pr_info("Reading for %zu bytes.\n", count);
	pr_info("Current file position: %lld\n", *f_pos);

	/* Check and adjust count */
	if ((*f_pos + count) > DEV_MEM_SIZE)
		count = DEV_MEM_SIZE - *f_pos;

	/* copy_to user */
	if (copy_to_user(buff, &device_buffer[*f_pos], count))
		return -EFAULT;

	/* Update current file position */
	*f_pos += count;

	pr_info("No of bytes successfully read: %zu bytes.\n", count);
	pr_info("Current file position: %lld\n", *f_pos);

	/* Return the no of bytes successfully read */
	return count;
}

loff_t pcd_lseek(struct file *filp, loff_t offset, int whence)
{
	return 0;
}

int pcd_open(struct inode *inode, struct file *filp)
{
	return 0;
}

int pcd_release(struct inode *inode, struct file *filp)
{
	return 0;
}

const struct file_operations pcd_fops = {
		.owner = THIS_MODULE,
		.write = pcd_write,
		.read = pcd_read,
		.llseek = pcd_lseek,
		.release = pcd_release,
		.open = pcd_open
};

static int __init pcd_driver_init(void)
{
	/* Allocate device number */
	alloc_chrdev_region(&device_number, 0, 1, "pcd_device_numbers");

	pr_info("Device number <major>:<minor> = %d:%d\n", MAJOR(device_number), MINOR(device_number));

	/* Initialize character device */
	cdev_init(&pcd_dev, &pcd_fops);

	/* Set pcd device owner */
	pcd_dev.owner = THIS_MODULE;

	/* Register pcd device with VFS */
	cdev_add(&pcd_dev, device_number, 1);

	/* Create device class under /sys/class */
	class_pcd = class_create(THIS_MODULE, "pcd_class");

	/* Create a device under sysfs */
	device_create(class_pcd, NULL, device_number, NULL, "pcd");

	pr_info("PCD Init Successful.\n");

	return 0;
}

static void __exit pcd_driver_cleanup(void)
{
	device_destroy(class_pcd, device_number);

	class_destroy(class_pcd);

	cdev_del(&pcd_dev);

	unregister_chrdev_region(device_number, 1);

	pr_info("PCD Device Removed.\n");

}


module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rajesh Kumbhakar");
MODULE_DESCRIPTION("Pseudo Character Driver");
