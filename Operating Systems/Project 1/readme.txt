This is the documentation file for Project 1. It elaborates all changes made to implement the syscall, effectively describing the patch deployed by "make test".



The most obvious and required changes for any syscall addition that were made include the editing of Minix's callnr header, prototype header, and syscall table header. Additionally, the standard library had relevant functions (which were detailed in the project specification) added to redirect requests to the syscall. Associated makefiles also saw updates to include new libary definition files.

The most changes were made within the process manager server. Several new functions were added related to the syscall. The first was the syscall itself, which was reached through the library calls and handled all of the project specified functions. The others were each auxilary functions, used to add, remove, and search for processes in/to the process log.

Two extern variables were added in glo.h to accomodate the new system call. The first is an int pm_is_logging to maintain the status of the process log. When 0, the process log is not accepting updates, otherwise it is. The second is the process log itself, to allocate permanent space for the process log when the process manager starts.

The process log itself is implemented as a 1024 struct array, with each struct containing a pid, creation time, and termination time, when applicable. These changes were made in type.h. 

Forkexit.c was modified to call for process log addition in the do_fork call, and do_exit updates termination time for processes which are exited and have a pid still in the process log.

Testing was done by utilizing a combination of fork() and exit() to test retrieving plog entries by PID. Getting plog entries by index was completed by testing various indices while running high process count functions such as a makefile in a second desktop. The testing of the remaining functions is trivial, but can be done in combination with the other tests. For example, stop should prevent writes, which can be made apparent after resetting the log and testing low indices for what they contain, and so on. 

At the time of project submission, there was an unrealized bug that caused get_plog_size() to both return the size and print the size to the console. This has been remedied in the current version. There are no known bugs.
