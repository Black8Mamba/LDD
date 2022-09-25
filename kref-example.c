// SPDX-License-Identifier: GPL-2.0
/*
 * Sample kref implementation
 *
 */
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include<linux/slab.h>
struct my_data
{
    struct kref refcount;
    char *name;
};

static struct my_data *data = NULL;

void data_release(struct kref *ref)
{
    struct my_data *data = container_of(ref, struct my_data, refcount);
    if (data)
        kfree(data);

    printk("data_release!\n");
}

static int __init example_init(void)
{
    printk("example_init!\n");
    data = kmalloc(sizeof(struct my_data), GFP_KERNEL);
    if (!data)
        return -ENOMEM;
    kref_init(&data->refcount);

    return 0;
}

static void __exit example_exit(void)
{
    kref_put(&data->refcount, data_release);
    printk("example_exit!\n");
}

module_init(example_init);
module_exit(example_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Yongjie Ji <jiyongjie@cvte.com>");

