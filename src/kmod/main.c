#include <linux/init.h>
#include <linux/module.h>
#include <linux/err.h>

#include <linux/printk.h>
#include <linux/debugfs.h>

#include "atlxray.h"
#include "addr_resolver.h"
#include "umc.h"


static struct atl_regs regs = { 0 };
static struct debugfs_blob_wrapper regs_wrapper = (struct debugfs_blob_wrapper) {
    .data = NULL,
    .size = sizeof(struct atl_regs)
};

static struct dentry *root = NULL;
static struct dentry *regfile = NULL;

static int __init init(void)
{
    pr_info("%s: loading...\n", KBUILD_MODNAME);

    get_umc_info_mi300_t get_umc = (get_umc_info_mi300_t) kprobe_symbol_lookup("get_umc_info_mi300");
    if (get_umc == NULL)
    {
        pr_err("%s: kprobe_symbol_lookup(): get_umc_info_mi300() not found!", KBUILD_MODNAME);
        return 1;
    }

    if (get_umc() != 0)
    {
        pr_err("%s: get_umc_info_mi300(): Failed", KBUILD_MODNAME);
        return 1;
    }

    struct atl_addr_hash *addr_hash = (struct atl_addr_hash *) kprobe_symbol_lookup("addr_hash");
    struct atl_bit_shifts *bit_shifts = (struct atl_bit_shifts *) kprobe_symbol_lookup("bit_shifts");

    if (addr_hash == NULL)
    {
        pr_err("%s: addr_hash: NULL", KBUILD_MODNAME);
        return 1;
    }

    if (bit_shifts == NULL)
    {
        pr_err("%s: bit_shifts: NULL", KBUILD_MODNAME);
        return 1;
    }

    root = debugfs_create_dir("atlxray", NULL);
    if (IS_ERR(root))
    {
        long ec = PTR_ERR(root);
        pr_err("%s: debugfs_create_dir(): Fail with error %li!\n", KBUILD_MODNAME, ec);
        return ec;
    }

    regs.magic = ATL_MAGIC;
    /* TODO: Fill ATL register */

    regs_wrapper.data = &regs;

    regfile = debugfs_create_blob("regs", 0, root, &regs_wrapper);
    if (IS_ERR(regfile))
    {
        long ec = PTR_ERR(regfile);
        pr_err("%s: debugfs_create_blob(): Fail with error %li!\n", KBUILD_MODNAME, ec);
        debugfs_remove(root);
        return ec;
    }

    pr_info("%s: loaded!\n", KBUILD_MODNAME);
    return 0;
}

static void __exit cleanup(void)
{
    pr_info("%s: unloading...\n", KBUILD_MODNAME);

    if (regfile != NULL)
    {
        debugfs_remove(regfile);
    }

    if (root != NULL)
    {
        debugfs_remove(root);
    }

    pr_info("%s: unloaded!\n", KBUILD_MODNAME);
}

module_init(init);
module_exit(cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("arch.fail");
MODULE_DESCRIPTION("Expose the registers of the ATL AMD64 interface");
MODULE_VERSION("0.0.1");
