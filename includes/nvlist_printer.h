#ifndef NVLIST_PRINTER_H
#define NVLIST_PRINTER_H

#include <sys/nvpair.h>

void print_nvlist(nvlist_t *nvl, int indent);

#define PRINT_NVLIST(nvl) \
    print_nvlist(nvl, 0)

#endif // NVLIST_PRINTER_H
