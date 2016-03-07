#include "../include/sbd_common.h"

int myfunction()
{
	printk("hello from %s file", __FILE__);

	return 0;
}
