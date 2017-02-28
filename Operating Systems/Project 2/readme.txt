This is the documentation file for Project 2. It elaborates all changes made to implement process state change logging, effectively describing the patch deployed by "make test".


 All changes from project 1 are also included in this patch.

=== Project 2 ===

A large number of changes had to be made for this project, spanning the kernel, process manager, and vfs. For sake of simplicity, this report will detail a trace of what happens when a process is set to have its transitions tracked, mentioning the bulk of what was changed, but potentially omitting small details such as additional message definitions to use being defined in the com.h header and glossing over relatively small implementation details.

plog_state_start/stop are called through a system library call similar to the first project. The 'start' call creates the log file if it is not already created. When they are received by the process manager, the PM makes a kernel call, which searches the proc.h table for a matching endpoint. When that endpoint is found, it modifies a few pieces of information - setting a "is tracked" variable to true and assigns it the corresponding PID (which was sent in with the kernel call). This PID is used later to hold in the buffer, since when the buffer gets flushed the process with that endpoint may no longer exist in the PM process table.

When a process is being tracked, it will be detected in the RTS_SET and RTS_UNSET functions by a couple of flags. BLOCKED and RECEIVING were used to identify blocking/unblocking. NO_QUANTUM and PREEMPTED was used to to identify when a process is done running, but is not blocked. PROC_STOP is used to identify when a process has received a signal to exit. The function pick_proc in proc.c of the kernel additionally logs whenever a process is chosen to be the running process. 

Whenever a transition occurs that is not ready -> running or running -> exit (as these were ones that seemed to cause hangs), the kernel sends a MINI_NOTIFY message to the process manager, which then calls back a series of kernel calls. The first is to determine how many entries need to be cleared from the log, the remainder are each to get a specific index (from 0 to the number obtained by the first call) from the kernel's buffer.

For each log entry retrival, the PM translates the message into a message the VFS was set up to accept. The VFS then converts the message into a single line to be written in to the file created by the syscall. Then it attempts to open the file and write that line to the log. Then it cleans up its work and continues.

In terms of "challenges encountered," basically every step of this was a pretty formidable challenge. The sum of challenges can be somewhat broken down into a few categories - communicating from the PM to the VFS, from the kernel to the PM (with enough information to actually carry out the project), discerning where processes can change and actually writing to the file. Of course, the implementation of these details is explained above, but none of them really followed from our changes for the first project.



=== Project 1 ===

The most obvious and required changes for any syscall addition that were made include the editing of Minix's callnr header, prototype header, and syscall table header. Additionally, the standard library had relevant functions (which were detailed in the project specification) added to redirect requests to the syscall. Associated makefiles also saw updates to include new libary definition files.

The most changes were made within the process manager server. Several new functions were added related to the syscall. The first was the syscall itself, which was reached through the library calls and handled all of the project specified functions. The others were each auxilary functions, used to add, remove, and search for processes in/to the process log.

Two extern variables were added in glo.h to accomodate the new system call. The first is an int pm_is_logging to maintain the status of the process log. When 0, the process log is not accepting updates, otherwise it is. The second is the process log itself, to allocate permanent space for the process log when the process manager starts.

The process log itself is implemented as a 1024 struct array, with each struct containing a pid, creation time, and termination time, when applicable. These changes were made in type.h. 

Forkexit.c was modified to call for process log addition in the do_fork call, and do_exit updates termination time for processes which are exited and have a pid still in the process log.

Testing was done by utilizing a combination of fork() and exit() to test retrieving plog entries by PID. Getting plog entries by index was completed by testing various indices while running high process count functions such as a makefile in a second desktop. The testing of the remaining functions is trivial, but can be done in combination with the other tests. For example, stop should prevent writes, which can be made apparent after resetting the log and testing low indices for what they contain, and so on. There are no known bugs.