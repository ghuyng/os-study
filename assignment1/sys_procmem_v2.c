#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
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
    struct proc_segs result;

    printk("here1\n");
    read_lock(&tasklist_lock);
    proc = find_task_by_vpid(pid);
    if (proc)
        get_task_struct(proc);

    read_unlock(&tasklist_lock);
    if(!proc)
        return -1;

    mmaps = proc->active_mm;

    result.mssv          = 1810173;
    result.start_code    = mmaps->start_code;
    result.end_code      = mmaps->end_code;
    result.start_data    = mmaps->start_data;
    result.end_data      = mmaps->end_data;
    result.start_heap    = mmaps->start_brk;
    result.end_heap      = mmaps->brk;
    result.start_stack   = mmaps->start_stack;

    copy_to_user(info, &result, sizeof(result));
    put_task_struct(proc);
    return 0;
}
