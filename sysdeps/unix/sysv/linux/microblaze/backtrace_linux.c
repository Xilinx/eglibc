#include <stddef.h>
#include <asm/sigcontext.h>
#include <linux/signal.h>
#include <asm-generic/ucontext.h>
#include <asm/unistd.h>

int __backtrace_lookup_prev_stack_frame_sighandler(
				unsigned long fp, unsigned long pc,
				unsigned long *pprev_fp, unsigned long *pprev_pc,
				unsigned long *retaddr)
{
	unsigned long *tramp = 0;
	struct ucontext *uc;

	if (*retaddr == 0) {
		/*fprintf(stderr, "working out sig-handler (pc = %08x)\n", pc);*/
		/* In this case, the pc pointer should be accessible */
		/* Kernel insert the a tramp between the signal handler frame and the
		   caller frame in signal handling This is how the kernel add the tramp
		   between frames:
		   err |= __put_user(0x31800000 | __NR_rt_sigreturn ,
		   frame->tramp + 0); // addi r12, r0, __NR_sigreturn
		   err |= __put_user(0xb9cc0008, frame->tramp + 1); // brki r14, 0x8
		   regs->r15 = ((unsigned long)frame->tramp)-8;
		*/
		tramp = (unsigned long *)pc;
		tramp += 2;
		if ((*tramp == (0x31800000 | __NR_rt_sigreturn)) && (*(tramp+1) == 0xb9cc0008)) {
			//*pprev_fp = (unsigned long)(tramp + 2);
			/* Signal handler function argument is:
			   (int sig_num, siginfo_t * info, void * ucontext)
			   the uncontext is the 3rd argument
			*/
			unsigned long ucptr = ((unsigned long)tramp) - sizeof(struct ucontext);
			/*fprintf(stderr, "tramp = %08x\n", tramp);*/
			/*fprintf(stderr, "ucptr = %08x\n", ucptr);*/
			uc = (struct ucontext *)ucptr;
			*pprev_pc = uc->uc_mcontext.regs.pc;
			/* Need to record the return address since the return address of the
			   function which causes this signal may not be recorded in the stack
			*/
			*pprev_fp = uc->uc_mcontext.regs.r1;
			*retaddr = uc->uc_mcontext.regs.r15;
			/* it is a signal handler */
			return 1;
		}
	}
	return 0;
}
