#ifndef UMCXRAY_H
#define UMCXRAY_H

#define UMC_MAGIC 0xAFA0
#define UMCXRAY_VERSION "v1.0.0"
#define UMCXRAY_DEV_PATH "/dev/umcxray"

struct umc_regs {
    unsigned short magic;
};

#endif // UMCXRAY_H
