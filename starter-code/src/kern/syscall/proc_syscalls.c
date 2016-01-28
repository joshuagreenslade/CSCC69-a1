/*
 * Process-related syscalls.
 * New for ASST1.
 */

#include <types.h>
#include <kern/errno.h>
#include <lib.h>
#include <thread.h>
#include <current.h>
#include <pid.h>
#include <machine/trapframe.h>
#include <syscall.h>

/*
 * sys_fork
 * 
 * create a new process, which begins executing in md_forkentry().
 */


int
sys_fork(struct trapframe *tf, pid_t *retval)
{
	struct trapframe *ntf; /* new trapframe, copy of tf */
	int result;

	/*
	 * Copy the trapframe to the heap, because we might return to
	 * userlevel and make another syscall (changing the trapframe)
	 * before the child runs. The child will free the copy.
	 */

	ntf = kmalloc(sizeof(struct trapframe));
	if (ntf==NULL) {
		return ENOMEM;
	}
	*ntf = *tf; /* copy the trapframe */

	result = thread_fork(curthread->t_name, enter_forked_process, 
			     ntf, 0, retval);
	if (result) {
		kfree(ntf);
		return result;
	}

	return 0;
}

/*
 * sys_getpid
 * Placeholder to remind you to implement this.
 */
int
sys_getpid(void)
{
	return curthread->t_pid;
}


/*
 * sys_waitpid
 * Placeholder comment to remind you to implement this.
 */
int
waitpid(pid_t pid, int *returncode, int flags)
{
	if(flags != 0)
		return EINVAL;

	//pid was not being watched by the current process or wasnt the parent
//	if()
//		return ECHILD;

	return pid_join(pid, returncode, flags);
}


/*
 * sys_kill
 * Placeholder comment to remind you to implement this.
 */
int
kill(pid_t pid, int signal)
{
	int length = 23;
	int unimplemented[] = {3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 16, 18, 20,
				 21, 22, 23, 24, 25, 26, 27, 30, 31};

	//invalid signal
	if((signal < 0) || (signal > 31))
		return EINVAL;

	//unimplemented signal
	for(int i=0, i < length; i++) {
		if(unimplemented[i] == signal)
			return EUNIMP;
	}

	//pid does not exist
}


