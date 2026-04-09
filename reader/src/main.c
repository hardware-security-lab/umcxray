#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "umcxray.h"
#include "uxioctl.h"

int main(void) {
    struct uxioctl_req req = { 0 };

    int fd = open(UMCXRAY_DEV_PATH, O_RDONLY);
    if (fd == -1)
    {
        perror("open()");
    }

    if (ioctl(fd, UMCXRAY_GET_STATUS, &req) == -1) {
        perror("ioctl(status)");
    }

    if (req.status != UMCXRAY_VALID_STATUS)
    {
        fprintf(stderr, "Error: IOCTL status was invalid!");
    }

    return 0;
}
