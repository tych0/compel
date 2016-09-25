#ifndef __COMPEL_PARASITE_H__
#define __COMPEL_PARASITE_H__

#include <stdbool.h>

#include "asm-generic/int.h"
#include "asm/parasite.h"
#include "asm/ptrace.h"

#define BUILTIN_SYSCALL_SIZE	8

typedef struct parasite_ctl_s {
	pid_t		pid;
	int		task_state;

	unsigned long	syscall_ip;			/* where sys_mmap/munmap can run */
	unsigned long	entry_ip;			/* plugin entry point IP */

	int		ctl_sock;
	int		ctl_accepted;
	thread_ctx_t	thread_ctx_orig;
	u8		code_orig[BUILTIN_SYSCALL_SIZE];

	void		*remote_map;
	void		*local_map;
	unsigned long	map_length;

	bool		was_seized;
} parasite_ctl_t;

extern parasite_ctl_t *parasite_start(pid_t pid, char *path, void *arg_p, unsigned int arg_s, bool seized);
extern int parasite_end(parasite_ctl_t *ptr);
extern int parasite_execute_syscall_trap(parasite_ctl_t *ctl, user_regs_struct_t *regs);
extern int parasite_set_return_value(parasite_ctl_t *ctl, unsigned long val);
extern int parasite_set_regs(parasite_ctl_t *ctl, user_regs_struct_t *regs);

static inline int ctl_sock(parasite_ctl_t *ctl)
{
	return ctl->ctl_accepted;
}

#endif /* __COMPEL_PARASITE_H__ */
