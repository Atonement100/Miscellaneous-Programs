#include "pm.h" 
#include "mproc.h"
#include <stdio.h>
#include <lib.h>
#include <unistd.h>
#include <time.h>
#define LOGPROCS_BUFFER_SIZE 1024

void SetReadIndex(int procid); //Prototype function only used here
/*=================*
 * circular buffer *
 *=================*/
/*  
typedef struct procInfo{
	int 	procid;
	long	CreationTime;
	long	TerminationTime;
} procInfo;

typedef struct cBuffer{
	int	 CurrentWriteIndex;
	int	 CurrentReadIndex;
	int	 BufferSize;
	procInfo procs[LOGPROCS_BUFFER_SIZE];
} cBuffer;
*/
cBuffer MakeNewProcessLog(){
	cBuffer NewBuffer = { 	.CurrentWriteIndex = 0,
				.CurrentReadIndex = 0,
				.BufferSize = LOGPROCS_BUFFER_SIZE,
			    	.procs = { {0,0,0} } 
		 	    };
	return NewBuffer;
}
/*=================*
 *   do_logprocs   *
 *=================*/

int tracking_all_processes = 0;
int ActivePIDTraces[NR_PROCS] = {-1}; 
int pm_is_logging = 0;
cBuffer ProcessLog = {  .CurrentWriteIndex = 0, 
			.CurrentReadIndex = 0,
			.BufferSize = LOGPROCS_BUFFER_SIZE,
			.procs = {{0,0,0}}
	     	     };

int do_logprocs(void){
 	int LogCommand = m_in.m2_i1;

	//This should quite honestly be a switch statement
	//Performance difference will be neglible however
	if (LogCommand == 0){ //stop_plog()
		pm_is_logging = 0;
	}
	else if (LogCommand == 1) { //start_plog()
		pm_is_logging = 1;
	}
	else if (LogCommand == 2) { //reset_plog()
		ProcessLog = MakeNewProcessLog();
	}
	else if (LogCommand == 3) { //get_plog_size()
		mp->mp_reply.m2_i1 = (sizeof(ProcessLog.procs) / sizeof(ProcessLog.procs[0]));
	}
	else if (LogCommand == 4) {
		//get_plog_byPID(int procid, long* c_time, long* t_time)
		int Index = m_in.m2_i2;
		SetReadIndex(Index);
		if (ProcessLog.CurrentReadIndex == -1){
			mp->mp_reply.m2_i1 = -1;
		}
		else{
		mp->mp_reply.m2_i1 = 0;
		mp->mp_reply.m2_l1 = ProcessLog.procs[ProcessLog.CurrentReadIndex].CreationTime;
		mp->mp_reply.m2_l2 = ProcessLog.procs[ProcessLog.CurrentReadIndex].TerminationTime;
		}
	}
	else if (LogCommand == 5) {
		//get_plog_byindex(int index, long* c_time, long* t_time)
		int index = m_in.m2_i2;	
		if (index < 0 || index > sizeof(ProcessLog.procs)/sizeof(ProcessLog.procs[0])-1){
			mp->mp_reply.m2_i1 = -1;
			mp->mp_reply.m2_l1 = -1;
			mp->mp_reply.m2_l2 = -1;
		}
		else{
		mp->mp_reply.m2_i1 = 0;
		mp->mp_reply.m2_l1 = ProcessLog.procs[index].CreationTime;
		mp->mp_reply.m2_l2 = ProcessLog.procs[index].TerminationTime;
		}
	}
	else if (LogCommand == 10) {
		//plog_state_start(int PID);
		int In_PID = m_in.m2_i2;
		
		if (In_PID == 0){
			for(int Index = 0; Index < NR_PROCS; Index++){
				if((!(mproc[Index].mp_flags & PRIV_PROC)) && mproc[Index].mp_flags & IN_USE){
					mproc[Index].mp_is_traced = 1;
					sys_updatetracking(0,PM_PROC_NR,mproc[Index].mp_endpoint, mproc[Index].mp_pid,1);
				}
			}
			mp->mp_reply.m2_i1 = 0;
			return 0;
		}

		int StartResponse = 1; // 0 = good, 1 = pid not found, 2 = priv proc
		for(int Index = 0; Index < NR_PROCS; Index++){
			if (mproc[Index].mp_pid == In_PID){
				StartResponse = 2;	
				if ((!(mproc[Index].mp_flags & PRIV_PROC)) && mproc[Index].mp_flags & IN_USE){
					StartResponse = 0;
					mproc[Index].mp_is_traced = 1;
					sys_updatetracking(0, PM_PROC_NR, mproc[Index].mp_endpoint, mproc[Index].mp_pid, 1);
				}
				break;
			}
		}
		
		mp->mp_reply.m2_i1 = StartResponse;	
	}
	else if (LogCommand == 11) {
		//plog_state_stop(int PID);
		int In_PID = m_in.m2_i2;

		if (In_PID == 0){
			for(int Index = 0; Index < NR_PROCS; Index++){
				if((!(mproc[Index].mp_flags & PRIV_PROC)) && mproc[Index].mp_flags & IN_USE){
					mproc[Index].mp_is_traced = 0;
					sys_updatetracking(0,PM_PROC_NR,mproc[Index].mp_endpoint, mproc[Index].mp_pid,0);
				}
			}
			mp->mp_reply.m2_i1 = 0;
			return 0;
		}

		int StopResponse = 1; // 0 = good, 1 = pid not found
		//check list of traced processes for In_PID, return 0/1 accordingly
		
		for(int Index = 0; Index < NR_PROCS; Index++){
			if (mproc[Index].mp_pid == In_PID){
				StopResponse = 2;	
				if ((!(mproc[Index].mp_flags & PRIV_PROC)) && mproc[Index].mp_flags & IN_USE){
					StopResponse = 0;
					mproc[Index].mp_is_traced = 0;
					sys_updatetracking(0, PM_PROC_NR, mproc[Index].mp_endpoint, mproc[Index].mp_pid, 0);
				}
				break;
			}
		}
		
		mp->mp_reply.m2_i1 = StopResponse;
	}
	return 0;
}

void AddProcessToLog(int procid){
	if (pm_is_logging == 0) return;
	/*Calculate unix time 					   */
	clock_t uptime, boottime;
	getuptime2(&uptime, &boottime);
	long cTime = (long)(boottime + uptime/system_hz);
	int CurrIndex = ProcessLog.CurrentWriteIndex;
	ProcessLog.procs[CurrIndex].procid = procid;
	ProcessLog.procs[CurrIndex].CreationTime = cTime;
	//In case overwriting previous log, set termination time
	ProcessLog.procs[CurrIndex].TerminationTime = 0;
	ProcessLog.CurrentWriteIndex = (ProcessLog.CurrentWriteIndex + 1) % LOGPROCS_BUFFER_SIZE; 

}

void AddProcessTerminationTime(int procid){
	if (pm_is_logging == 0) return;  
	int newid = procid;
	SetReadIndex(newid);
	if (ProcessLog.CurrentReadIndex == -1) return;

	clock_t uptime, boottime;
	getuptime2(&uptime, &boottime);
	long cTime = (long)(boottime + uptime/system_hz);
	ProcessLog.procs[ProcessLog.CurrentReadIndex].TerminationTime = cTime;

}

void SetReadIndex(int procid){
	for (int Index = 0; Index < LOGPROCS_BUFFER_SIZE; Index++){
		if (ProcessLog.procs[Index].procid == procid){
			ProcessLog.CurrentReadIndex = Index;
			return;
		}
	}
	ProcessLog.CurrentReadIndex = -1;
	//If procid is not found, assume does not exist!
}

void vfs_log(message* m_ptr){
	int r;
	r = asynsend3(VFS_PROC_NR, m_ptr, AMF_NOREPLY);
}

message translate_sys_message_for_vfs(message *m_ptr){
	message vm;
	vm.m_type = PM_LOG;
	vm.PM_LOG_PID = m_ptr->m2_i1;
	vm.PM_LOG_FROM_STATE = m_ptr->m2_i2;
	vm.PM_LOG_TO_STATE = m_ptr->m2_i3;
	vm.PM_LOG_TIME = 0;
	vm.PM_LOG_UTIME = m_ptr->m2_l1;
	return vm;
}

void handle_full_log(){
	//kernel call to get no. of entries to do
	message m;
	m.m2_i1 = 1;
	sys_retrievelog(&m);
	int entriesToRetrieve = m.m2_i1;

	for (int Index = 0; Index < entriesToRetrieve; Index++){
		m.m2_i1 = 0;
		m.m2_i2 = Index;
		sys_retrievelog(&m);
		message vm = translate_sys_message_for_vfs(&m);
		vfs_log(&vm);
	}	
	return;		
}

void handle_exit_log(int exitingPID){
	//kernel call to get no. of entries to do
	message m;
	m.m2_i1 = 2;
	m.m_type = PM_LOG;
	m.PM_LOG_PID = exitingPID;
	sys_retrievelog(&m);
	int entriesToRetrieve = m.m2_i1;
	printf("log has %d entries\n",entriesToRetrieve);
	//loop of kernel calls that retrieve and create messages for vfs_log
	for (int Index = 0; Index < entriesToRetrieve; Index++){
		m.m2_i1 = 0;
		m.m2_i2 = Index;
		sys_retrievelog(&m);
		message vm = translate_sys_message_for_vfs(&m);
		vfs_log(&vm);
	}	
}
