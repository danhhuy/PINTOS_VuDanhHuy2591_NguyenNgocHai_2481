//#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include <list.h>

/* Process identifier type. */
typedef int pid_t;
#define PID_ERROR ((pid_t) -1)      /* Error value for pid_t. */


/* Process status flags. */
#define PROCESS_LOADING 0           /* Process is loading. */
#define PROCESS_RUNNING 1           /* Process is running. */
#define PROCESS_FAIL 2              /* Process loading failed. */
#define PROCESS_EXIT 4              /* Process has exited. */


//User process
struct process
  {
    int pid;                      /* Process identifier. */
    struct process *parent;         /* Parent process. */
    //struct list child_list;         /* List of child processes. */

    struct process_info *info;      /* Process information for its parent. */
    int fd_next;                    /* File descriptor tracker. */
  };

struct process_info
  {
    int pid;                      /* Process identifier. */
    struct process *process;        /* Process. */
    int status;                     /* Process status. */
    int exit_code;                  /* Exit code. */
    bool is_waiting;                /* Whether parent is waiting or not. */
    struct list_elem elem;          /* List element. */
  };
pid_t process_execute (const char *file_name);
int process_wait (pid_t);
void process_exit (void);
void process_activate (void);
//struct process *process_current (void);
//struct process_info *process_find_child (pid_t);

