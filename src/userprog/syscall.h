#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);

struct lock *thread_lock; //a lock to make sure that only one thread is accessing the file system at a time
typedef int pid_t;

#endif /* userprog/syscall.h */
