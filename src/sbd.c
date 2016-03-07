#include "../include/sbd_common.h"


static int __init sbd_init(void)
{
	printk(KERN_INFO "Hello world\n");
	myfunction();
	return 0;

}

static void __exit sbd_exit(void)
{
	printk(KERN_INFO "my exit\n");

}

module_init(sbd_init);
module_exit(sbd_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jatinder");
