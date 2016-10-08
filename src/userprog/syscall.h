#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);

  typedef int syscall_function (int, int, int);
  /* A system call */
  struct syscall
    {
      size_t arg_cnt;          /* Number of arguments. */
      syscall_function *func;  /* Implementation. */
    };
  /* Table of system calls. */
  static const struct syscall syscall_table[] =
    {
      {0, (syscall_function *) halt},
      {1, (syscall_function *) exit},
      {1, (syscall_function *) exec},
      {1, (syscall_function *) wait},
      {2, (syscall_function *) create},
      {1, (syscall_function *) remove},
      {1, (syscall_function *) open},
      {1, (syscall_function *) filesize},
      {3, (syscall_function *) read},
      {3, (syscall_function *) write},
      {2, (syscall_function *) seek},
      {1, (syscall_function *) tell},
      {1, (syscall_function *) close}
    }

#endif /* userprog/syscall.h */
