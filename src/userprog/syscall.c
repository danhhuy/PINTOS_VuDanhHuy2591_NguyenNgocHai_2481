#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
  lock_init (&filesys_lock);
}

void
syscall_exit (int status, struct intr_frame *f)
{
  (thread_current ()->wait_status)->exit_code = status;
  printf ("%s: exit(%d)\n", &thread_current ()->name, status);
  f->eax = status;
  thread_exit ();
}

void
validate_addr (void *ptr, struct intr_frame *f, int num, int size)
{
  if (!is_user_vaddr (ptr) || !is_user_vaddr (ptr + size * num - 1)
    || pagedir_get_page (thread_current ()->pagedir, ptr) == NULL
    || pagedir_get_page (thread_current ()->pagedir, ptr + size * num - 1) == NULL)
    {
      syscall_exit (-1, f);
    }
}


static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  uint32_t* args = ((uint32_t*) f->esp);
  validate_addr (&args[0], f, 1, sizeof (uint32_t *));

  if (args[0] == SYS_EXIT)
    {
      validate_addr (&args[1], f, 1, sizeof (uint32_t * ));
      syscall_exit (args[1], f);
    }
  else if (args[0] == SYS_HALT)
    {
      shutdown_power_off ();
    }
  else if (args[0] == SYS_PRACTICE)
    {
      validate_addr (&args[1], f, 1, sizeof (uint32_t * ));
      f->eax = args[1] + 1;
    }
  else if (args[0] == SYS_EXEC)
    {
      validate_addr (&args[1], f, 1, sizeof (uint32_t * ));
      validate_addr ((void *) args[1], f, 1, 1);
      f->eax = process_execute ((void *) args[1]);
    }
  else if (args[0] == SYS_WAIT)
    {
      validate_addr (&args[1], f, 1, sizeof (uint32_t * ));
      f->eax = process_wait (args[1]);
    }
}
