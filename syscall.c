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
  //need to implement this 
}

/*list of system calls */

static void halt (void);
static void exit (int);
static bool create (const char*, unsigned);
static bool remove (const char*);
static int wait (pid_t);
static int filesize (int);





void
halt (void)
{
   shutdown_power_off();
}


void
exit (int status)
{
   struct thread *cur = thread_current ();
}

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


int
wait (pid_t user_thread)
{
   
   return process_wait(user_thread); //per the document.....we will implement code for process_wait in order to fulfill the wait() function
}


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





