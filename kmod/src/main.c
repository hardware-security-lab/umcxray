#include <sys/types.h>
#include <sys/conf.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/modctl.h>

#include "umcxray.h"
#include "uxlog.h"

static struct modlmisc modlmisc = {
    &mod_miscops,
    "IllumOS UMC Xray"
};

static struct modlinkage modlinkage = {
    MODREV_1,
    &modlmisc,
    NULL
};

int
_init(void)
{
    int error;
    error = mod_install(&modlinkage);
    if (error == 0)
    {
        INFO("UMCXray loaded!");
    }
    return (error);
}

int
_fini(void)
{
    int error;
    error = mod_remove(&modlinkage);
    if (error == 0)
    {
        INFO("UMCXray unloaded!");
    }
    return (error);
}

int
_info(struct modinfo *modinfop)
{
    return (mod_info(&modlinkage, modinfop));
}
