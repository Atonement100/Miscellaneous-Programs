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
// Defined in types.h, presented here for quick reference
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

int pm_is_logging = 0;							 //Assigning externs
cBuffer ProcessLog = {  .CurrentWriteIndex = 0,  //Can't use MakeNewProcessLog() to init extern var
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
	else if (LogCommand == 4) { //get_plog_byPID(int procid, long* c_time, long* t_time)
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
	else if (LogCommand == 5) { //get_plog_byindex(int index, long* c_time, long* t_time)
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
	return 0;
}

void AddProcessToLog(int procid){
	if (pm_is_logging == 0) return;
	/*Calculate unix time 					   					*
	 *Calculated here instead of do_time() as it wasn't working	*/
	clock_t uptime, boottime;
	getuptime2(&uptime, &boottime);
	long cTime = (long)(boottime + uptime/system_hz);

	int CurrIndex = ProcessLog.CurrentWriteIndex;
	ProcessLog.procs[CurrIndex].procid = procid;
	ProcessLog.procs[CurrIndex].CreationTime = cTime;
	ProcessLog.procs[CurrIndex].TerminationTime = 0; //In case overwriting previous log, set termination time
	ProcessLog.CurrentWriteIndex = (ProcessLog.CurrentWriteIndex + 1) % LOGPROCS_BUFFER_SIZE; 
}

void AddProcessTerminationTime(int procid){
	if (pm_is_logging == 0) return; //No need to record time if we aren't logging  

	int newid = procid;
	SetReadIndex(newid);
	if (ProcessLog.CurrentReadIndex == -1) return; //Can't record if we can't find the process...

	clock_t uptime, boottime;		//See AddProcessToLog for why time is calculated here
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
