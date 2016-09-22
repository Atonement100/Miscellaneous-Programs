#include <lib.h>
#include <unistd.h>
#include <stdio.h>
void stop_plog(){
	message m;

	m.m2_i1 = 0; //0 is defined as log closer 
	return _syscall(PM_PROC_NR, LOGPROCS, &m);
}

void start_plog(){
	message m;

	m.m2_i1 = 1; //1 is defined as log process starter
	return _syscall(PM_PROC_NR, LOGPROCS, &m);
}

void reset_plog(){
	message m;

	m.m2_i1 = 2; //2 is defined as log reset
	return _syscall(PM_PROC_NR, LOGPROCS, &m);
}

int get_plog_size(){
	message m;

	m.m2_i1 = 3; //3 is defined as logprocs' size retriever
	_syscall(PM_PROC_NR, LOGPROCS, &m);
	return m.m2_i1;
}

int get_plog_byPID(int pid, long* c_time, long* t_time){
	message m;

	m.m2_i1 = 4; //4 is defined as logprocs' retrieve by pid
	m.m2_i2 = pid;
	_syscall(PM_PROC_NR, LOGPROCS, &m);
	if (m.m2_i1 == -1){
		*c_time = -1;
		*t_time = -1;
		return 2;
	}
	*c_time = m.m2_l1;
	*t_time = m.m2_l2;
	return 0;	
}

int get_plog_byindex(int index, long* c_time, long* t_time){
	message m;

	m.m2_i1 = 5; //5 is defined as logprocs' retrieve by index 
	m.m2_i2 = index;
	_syscall(PM_PROC_NR, LOGPROCS, &m);
	if (m.m2_i1 == -1){
		*c_time = -1;
		*t_time = -1;
		return 3;
	}
	*c_time = m.m2_l1;
	*t_time = m.m2_l2;
	return 0;
}
