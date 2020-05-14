#include "procmem.h"
#include <linux/kernel.h>
#include <sys/syscall.h>
#define SYS_NUM 546

long procmem(pid_t pid, struct proc_segs *info) {
    return syscall(SYS_NUM, pid, info);
}
