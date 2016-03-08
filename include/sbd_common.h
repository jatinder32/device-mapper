#ifndef __SBD_COMMON_H__
#define __SBD_COMMON_H__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>

#ifdef SBD_DEBUG 
#    define ENTRY       printk("<1>SDB : ===>> Entering function %s", __FUNCTION__); \
                                 printk("\n");
#    define EXIT        printk("<1>SBD : <<=== Exitting function %s", __FUNCTION__); \
                                 printk("\n");
#else   
#  define ENTRY
#  define EXIT
#endif //SDB_DEBUG

#ifndef DEVICE_NAME
#define DEVICE_NAME "jitu_block"
#endif

#ifndef SECTOR_SIZE 
#define SECTOR_SIZE 512
#endif

#ifndef SECTORS
#define SECTORS 102400
#endif


unsigned int major_no;
int minors = 1;
int sector_size = SECTOR_SIZE;
int sectors = SECTORS;


struct SBD
{
        int device_size;
        struct gendisk *gd;
        spinlock_t lock;
        u8 *data;
        struct request_queue *req;
} *sbd;

int sbd_init(void);
void req_fun(struct request_queue *);
int sbd_open(struct block_device *, fmode_t);
int sbd_release(struct gendisk *, fmode_t);
void sbd_transfer(char *buffer,struct request *req,int num);

struct block_device_operations bops=
{
        .owner = THIS_MODULE,
        .open  = sbd_open,
        .release = sbd_release

};


extern  int		myfunction(void);
#endif 
