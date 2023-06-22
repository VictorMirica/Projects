#include <fcntl.h>
#include <internal/syscall.h>
#include <stdio.h>
#include <errno.h>

int puts(const char* str) {

    int ret;

    while(*str != '\0') {
        ret = syscall(__NR_write, 1, str, 1);
        if (ret == -1) {
            errno = -ret;
            return -1;
        }
        str++;
    }

    ret = syscall(__NR_write, 1, "\n", 1);

    if(ret == -1) {
        errno = -ret;
        return -1;
    }

    return 0;
}