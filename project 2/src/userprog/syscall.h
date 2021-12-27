#include <stdbool.h>
#include "threads/synch.h"
#include "filesys/directory.h"
#include <list.h>
#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

#define pid_t int
#define mapid_t int

struct file_fd{
  int fd;                 /* number of file descriptor */
  struct file *file;      /* opened file */
  struct dir *dir;        /* opened directory */
  struct list_elem elem;
};

struct lock file_lock;

void syscall_init (void);

void sys_halt (void);
void sys_exit (int status);
pid_t sys_exec (const char *cmd_line);
int sys_wait (pid_t pid);
#endif /* userprog/syscall.h */
