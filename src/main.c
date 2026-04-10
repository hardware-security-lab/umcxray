#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mc_min.h"
#include "nvlist_printer.h"

static int
fetch_snapshot_blob(int fd, void **bufp, size_t *lenp)
{
    mc_snapshot_info_t info;
    void *buf;

    memset(&info, 0, sizeof(info));

    if (ioctl(fd, MC_IOC_DECODE_SNAPSHOT_INFO, &info) != 0)
    {
        perror("MC_IOC_DECODE_SNAPSHOT_INFO");
        return -1;
    }

    buf = malloc(info.mcs_size);
    if (buf == NULL)
    {
        perror("malloc");
        return -1;
    }

    if (ioctl(fd, MC_IOC_DECODE_SNAPSHOT, buf) != 0)
    {
        perror("MC_IOC_DECODE_SNAPSHOT");
        free(buf);
        return -1;
    }

    *bufp = buf;
    *lenp = info.mcs_size;
    return 0;
}

int
main(void)
{
    int fd = open("/dev/mc/mc0", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    void *blob = NULL;
    size_t blob_len = 0;
    if (fetch_snapshot_blob(fd, &blob, &blob_len) != 0)
    {
        close(fd);
        return 1;
    }

    nvlist_t *nvl = NULL;
    if (nvlist_unpack(blob, blob_len, &nvl, 0) != 0)
    {
        fprintf(stderr, "nvlist_unpack failed\n");
        free(blob);
        close(fd);
        return 1;
    }

    free(blob);
    close(fd);

    PRINT_NVLIST(nvl);
    nvlist_free(nvl);
    return 0;
}
