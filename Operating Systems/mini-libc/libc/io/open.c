// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	/* TODO: Implement open system call. */
	int flag;

	if (flags & O_CREAT) {
		va_list list;
		va_start(list, flags);
		flag = va_arg(list, int);
		va_end(list); 
	}
	
	int ret = syscall(__NR_open, filename, flags, flag);

	if(ret >= 0)
		return ret;

	errno = -ret;
	return -1;
}
