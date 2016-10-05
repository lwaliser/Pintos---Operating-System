#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);

struct lock thread_lock;
bool valid_pointer (const void *);

#endif /* userprog/syscall.h */
