#include <sys/errno.h>
#include <sys/sunddi.h>

#include "uxioctl.h"
#include "kmod/uxlog.h"

int
umcxray_ioctl(dev_t dev, int cmd, intptr_t arg, int mode, cred_t *credp, int *rvalp)
{
    if (ddi_model_convert_from(mode) == DDI_MODEL_ILP32)
    {
        WARN("UMCXray currently does not work on 32-bit systems!");
        return (EFAULT);
    }

    struct uxioctl_req res;
    switch (cmd)
    {
        case UMCXRAY_GET_STATUS:
            res.status = UMCXRAY_VALID_STATUS;
            if (ddi_copyout(&res, (void *) arg, sizeof(struct uxioctl_req), mode))
            {
                WARN("ddi_copyout fault!");
                return (EFAULT);
            }
            break;
        default:
            WARN("Unknown IOCTL command!");
            return (ENOTTY);
            break;
    }

    return 0;
}
