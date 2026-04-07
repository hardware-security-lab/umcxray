#ifndef UMCXRAY_LOG_H
#define UMCXRAY_LOG_H

#include <sys/cmn_err.h>

#define MODNAME "UMCXray"
#define MODTAG MODNAME ": "

#define INFO(format) \
    cmn_err(CE_NOTE, MODTAG format)

#define WARN(format) \
    cmn_err(CE_WARN, MODTAG format)

#endif // UMCXRAY_LOG_H
