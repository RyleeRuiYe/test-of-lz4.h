#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/lz4.h>
#include <linux/slab.h>
#include <linux/blkdev.h>



struct lz4_ctx{
	void *lz_comp_mem;
};


static int __init compress_init(void)
{
	size_t tmp_len, dst_len;
	int ret;
	size_t slen;
	char *src, *dst, *dst_compress;
	void *ctx;
	
	/*src视为连续空间*/
	src = (char*)kmalloc(PAGE_SIZE, GFP_KERNEL);
	slen = PAGE_SIZE;
	
	dst = (char*)kzalloc(lz4_compressbound(PAGE_SIZE), GFP_KERNEL);
	dst_compress = (char*)kzalloc(PAGE_SIZE, GFP_KERNEL);
	/*申请空间*/
	ctx = kzalloc(LZ4_MEM_COMPRESS, GFP_KERNEL);
	if(!ctx){
		printk("Error in allocing ctx\n");
		kfree(src);
		kfree(dst);
		kfree(dst_compress);
		return 0;
	}
	printk("Success in alloc\n");
	
	
	ret = lz4_compress(src, slen, dst, &tmp_len, ctx);
	
	/*释放空间*/
	kfree(ctx);
	
	if(ret < 0){
		printk("Compress error\n");
		kfree(src);
		kfree(dst);
		kfree(dst_compress);
		
		return 0;
	}
	printk("Success in compress\n");
	printk("compressed len: %d\n", tmp_len);
	
	/*ret = lz4_decompress_unknownoutputsize(dst, tmp_len, dst_compress, &dst_len);*/
	ret = lz4_decompress(dst, &dst_len, dst_compress, PAGE_SIZE);
	printk("compressed len: %d\n", dst_len);
	if(ret < 0)
	{
		printk("Decompress error\n");
		kfree(src);
		kfree(dst);
		kfree(dst_compress);
	
		return 0;
	}
	
	printk("Success in decompress\n");
	kfree(src);
	kfree(dst);
	kfree(dst_compress);
	
	return 0;
		
}

static void __exit compress_exit(void)
{
	printk("See you\n");
}

module_init(compress_init);
module_exit(compress_exit);
MODULE_LICENSE("GPL");
