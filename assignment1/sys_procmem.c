#include <linux/linkage.h>
#include <linux/sched.h>
struct proc_segs {
	unsigned long mssv;
	unsigned long start_code;
	unsigned long end_code;
	unsigned long start_data;
	unsigned long end_data;
	unsigned long start_heap;
	unsigned long end_heap;
	unsigned long start_stack;
};

asmlinkage long sys_procmem(int pid, struct proc_segs *info) {
    struct task_struct *proc;
    struct mm_struct *mmaps;

    read_lock(&tasklist_lock);
    proc = find_task_by_vpid(pid);
    if (proc)
        get_task_struct(proc);
    read_unlock(&tasklist_lock);
    if(!proc)
        return -1;

    mmaps = proc->active_mm;

    info->mssv          = 1810173;
    info->start_code    = mmaps->start_code;
    info->end_code      = mmaps->end_code;
    info->start_data    = mmaps->start_data;
    info->end_data      = mmaps->end_data;
    info->start_heap    = mmaps->start_brk;
    info->end_heap      = mmaps->brk;
    info->start_stack   = mmaps->start_stack;

    put_task_struct(proc);
    return 0;
}
