#ifndef UMCXRAY_IOCTL_H
#define UMCXRAY_IOCTL_H

#ifdef _KERNEL
#include <sys/types.h>
#include <sys/cred.h>
#endif // _KERNEL

#define UMCXRAY_IOC ('U' << 8)
#define UMCXRAY_GET_STATUS (UMCXRAY_IOC | 1)
#define UMCXRAY_GET_MAP (UMCXRAY_IOC | 2)

#define UMCXRAY_VALID_STATUS 0xCCCCCCCC

struct uxioctl_req {
    union {
        unsigned int status;
        struct {
            unsigned int indata[64];
            unsigned int outdata[64];
        };
    };
};

#ifdef _KERNEL
extern int umcxray_ioctl(dev_t dev, int cmd, intptr_t arg, int mode, cred_t *credp, int *rvalp);
#endif // _KERNEL

#endif // UMCXRAY_IOCTL_H
