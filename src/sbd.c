#include "../include/sbd_common.h"


static int __init SBD_init(void)
{
	int ret;
	ENTRY;
	sbd = (struct SBD*)kmalloc(sizeof(struct SBD),GFP_KERNEL);
	if(sbd == NULL){
		printk(KERN_ERR "malloc failure at %s \n", __func__);
		goto OUT;
	}

	memset(sbd,'\0',sizeof(struct SBD));
	
	major_no = register_blkdev(0, DEVICE_NAME);
	if(major_no < 0){
		printk(KERN_ERR "Can't get major number\n");
		goto OUT;
	}
	printk(KERN_INFO "Major Number = %d\n",major_no);
	EXIT;
	return 0;

OUT:
	printk(KERN_ERR "EXIT with error %s\n",__func__);
}

static void __exit SBD_exit(void)
{
	ENTRY;
	unregister_blkdev(major_no, DEVICE_NAME);
	EXIT;
}

module_init(SBD_init);
module_exit(SBD_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jatinder");
