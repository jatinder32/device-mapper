#include "../include/sbd_common.h"

int myfunction(void)
{
	printk("TESTINg\n");
	return 0;

}
EXPORT_SYMBOL(myfunction);

static int __init sbd_api_init(void)
{
	printk("hello from %s file\n", __FILE__);

	return 0;
}

static void __exit sbd_api_exit(void)
{
	printk("exit from %\n", __func__);


}

module_init(sbd_api_init);
module_exit(sbd_api_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jatinder");
