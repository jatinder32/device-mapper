#include "../include/sbd_common.h"

int sbd_open(struct block_device * blk, fmode_t mode)
{

        printk(KERN_INFO"BEGIN := %s\n",__func__);

        printk(KERN_INFO"END := %s\n",__func__);

        return 0;
}
int sbd_release(struct gendisk * rgd, fmode_t mode)
{
        printk(KERN_INFO"BEGIN := %s\n",__func__);

        printk(KERN_INFO"END := %s\n",__func__);

        return 0;
}


void req_fun(struct request_queue *queue)
{

	struct request *req;
	struct SBD *lsdb;
	
	ENTRY;
	req = blk_fetch_request(queue);

	while(req != NULL){
		lsdb = req->rq_disk->private_data;
		if(req->cmd_type != REQ_TYPE_FS){
			printk(KERN_INFO"non fs-request :skip\n");
                        blk_end_request_all(req,-2);
		}
		sbd_transfer(req->buffer,req,rq_data_dir(req));

		if(!__blk_end_request_cur(req,0)){
			req = blk_fetch_request(queue);
		}
	}

	EXIT;
}


void sbd_transfer(char *buffer,struct request *req,int num)
{

	int offset,bytes;
        struct SBD *lsbd;

	ENTRY;
	offset = blk_rq_pos(req)*sector_size;
        bytes = blk_rq_cur_sectors(req)*sector_size;

        lsbd= req->rq_disk->private_data;

        if(num)
                memcpy(lsbd->data+offset,buffer,bytes);
        else
                memcpy(buffer,lsbd->data+offset,bytes);
	EXIT;

}

int sbd_init(void)
{
	ENTRY;
	sbd->device_size = sector_size * sectors;
	spin_lock_init(&sbd->lock);
	sbd->req = blk_init_queue(req_fun,&sbd->lock);	

	sbd->gd = alloc_disk(minors);
        if(sbd->gd ==NULL)
        {
                #ifdef DEBUG
                printk(KERN_ERR"alloc_disk failure\n");
                #endif

        }

        sbd->data = vmalloc(sizeof(char)*sbd->device_size);
        if(!sbd->data)
        {
                #ifdef DEBUG
                printk(KERN_ERR"alloc_disk failure\n");
                #endif
        }
        sbd->gd->major = major_no;
        sbd->gd->first_minor = 0;
        sbd->gd->minors = minors;
        blk_queue_logical_block_size(sbd->req,512);
        blk_queue_physical_block_size(sbd->req,512);
        sbd->gd->queue=sbd->req;
        sbd->gd->flags = GENHD_FL_UP;
        strcpy(sbd->gd->disk_name,"sbull");
        sbd->gd->fops = &bops;
        set_capacity(sbd->gd,sectors);
        sbd->gd->private_data = sbd;
        printk(KERN_INFO" add disk Begin\n");
        add_disk(sbd->gd);
        printk(KERN_INFO" add disk END\n");


        #ifdef DEBUG
        printk(KERN_INFO"END := %s\n",__func__);
        #endif

	
	EXIT;
	return 0;
}

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
	
	ret = sbd_init();
	EXIT;
	return 0;

OUT:
	printk(KERN_ERR "EXIT with error %s\n",__func__);
	return -1;
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
