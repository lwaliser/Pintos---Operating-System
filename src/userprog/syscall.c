#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "filesys/filesys.h"

static void syscall_handler (struct intr_frame *);
static bool valid_pointer (const void *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
  lock_init (&thread_lock);
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  
  const struct syscall *sc;
  unsigned call_nr;
  int args[3];

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

  /* Get the system call. */
  copy_in (&call_nr, f->esp, sizeof call_nr);
  if (call_nr >= sizeof syscall_table / sizeof *syscall_table) 
    thread_exit ();
  sc = syscall_table + call_nr;

  /* Get the system call arguments. */
  ASSERT (sc->arg_cnt <= sizeof args / sizeof *args);
  memset (args, 0, sizeof args); 
  copy_in (args, (uint32_t *) f->esp + 1, sizeof *args * sc->arg_cnt);

  /* Execute the system call,      
     and set the return value. */ 
  f->eax = sc->func (args[0], args[1], args[2]);
  thread_exit ();
}

/*list of system calls */

static void halt (void);
static void exit (int);
static pid_t exec (const char *);
static int wait (pid_t);
static bool create (const char*, unsigned);
static bool remove (const char*);
static int open (const char *);
static int filesize (int);
static int read (int, void *, unsigned);
static int write (int, const void *, unsigned);
static void seek (int, unsigned);
static unsigned tell (int);
static void close (int);


//terminates Pintos
void
halt (void)
{
   shutdown_power_off();
}


//terminates current user program, returning status to the kernel
void
exit (int status)
{
   struct thread *cur = thread_current ();
}

//runs the executable whose name is given in the parameter and runs the new process's program id
pid_t
exec (const char *cmd_line)
{

}

//waits for a child process pid and retrieves the child's exit status
int
wait (pid_t pid)
{
   
   return process_wait(user_thread); //per the document.....we will implement code for process_wait in order to fulfill the wait() function
}


//creates a new file based on the parameters
bool
create (const char *file, unsigned initial_size)
{
   bool file_status;

   //check if pointer to the file is correct
   if(!valid_pointer (file))
      {
         exit (-1);
      }

   //make sure only one thread at a time is accessing the filesystem
   lock_acquire (&thread_lock);
   file_status = filesys_remove(file);
   lock_release (&thread_lock);
   return status;
}


//deletes the called file
bool
remove (const char *file)
{
   bool file_status;
  
   //check if pointer to the file is correct
   if(!valid_pointer (file))
      {
         exit (-1);
      }

   //make sure only one thread at a time is accessing the filesystem
   lock_acquire (&thread_lock);
   file_status = filesys_remove (file);
   lock_release (&thread_lock);
   return status;
}


//opens the given file
int
open (const char *file)
{

}

//returns the size of the file in bytes
int
filesize (int fd)
{

  

}



bool
valid_pointer (const void *ptr)
{
  
  bool status;

  if(ptr != NULL)
    {  
       status = (pagedir_get_page (thread_current()->pagedir, ptr)) != NULL;
       return status;
    }

  return false;

}
