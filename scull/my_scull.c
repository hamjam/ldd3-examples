#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>


#define SCULL_MAJOR = 0;
#define SCULL_INIT_MINOR = 0;
#define SCULL_NR_DEVS = 4;

MODULE_AUTHOR('Hamed Jamshidian');

static unsigned int major_num = SCULL_MAJOR;
static unsigned int minor_init_num = SCULL_INIT_MINOR;
static unsigned int scull_nr_devs = SCULL_NR_DEVS;
module_param(major_num, int, S_IRUGO);
module_param(minor_init_num, int, S_IRUGO);

struct scull_dev
{
    struct scull_qset *data;
    int qset;
    int quantum;
    unsigned long size;
    struct mutex mutex;
    struct cdev cdev;
}

struct scull_qset
{
  void **data;
  struct scull_qset *next;
}

static struct scull_dev *devices;

int __init init_scull()
{
  dev_t scull_num = MKDEV(major_num, minor_init_num);
  int response = 0;
  if(major_num)
    response = register_chrdev_region(scull_num, scull_nr_devs, 'scull');
  else
  {
    response = alloc_chrdev_region(*scull_num, minor_init_num
      , scull_nr_devs, 'scull');
    major_num = MAJOR(scull_num);
    minor_num = MINOR(scull_num)
  }
  if(response < 0)
  {
    printk(KERN_WARNING"Can't get major with error %i", response);
    return response;
  }
  devices = kmalloc(scull_nr_devs * sizeof(struct scull_dev), GFP_KERNEL);
  for(int i = 0; i < scull_nr_devs; i++)
  {

  }

}

void __exit cleanup_scull()
{
  dev_t scull_num = MKDEV(major_num, minor_num);
  unregister_chrdev_region(scull_num, scull_nr_devs);
}



module_init(init_scull);
module_exit(cleanup_scull);
