#include "kernel/system.h"
#include "../kernel.h"
#include "../glo.h"
#include <string.h>

#include <minix/endpoint.h>
#include <minix/u64.h>

LogBuffer transitionLog = { .transitions = {{0,0,0,0}},
			    .currentWriteIndex = 0
			    };

void AddToLogBuffer(struct proc * rp, int pid, int time, int fromstate, int tostate){
	if (rp->p_laststate == tostate || rp->p_laststate == 4) return;
	TransitionInfo new;
	new.pid = pid;
	new.transitionTime = get_uptime();
	new.transitionedFrom = rp->p_laststate;
	new.transitionedTo = tostate;

	rp->p_laststate = tostate;

	transitionLog.transitions[transitionLog.currentWriteIndex] = new;
	transitionLog.currentWriteIndex = transitionLog.currentWriteIndex + 1;
	if (new.transitionedTo != 2 && new.transitionedTo != 4){
		FlushLogBuffer();
	}
	if (transitionLog.currentWriteIndex == 32){
		FlushLogBuffer(); //will reset write index
	}
}

void FlushLogBuffer(){
	mini_notify(proc_addr(IDLE), PM_PROC_NR);
//	transitionLog.currentWriteIndex = 0;
//dont forget to reset write index somehow
}

int do_flushlog(struct proc * caller_ptr, message *m_ptr){
	FlushLogBuffer();
	//printf("flush log");
	return(OK);
}

int do_updatetracking(struct proc * caller_ptr, message *m_ptr){
	if(m_ptr->m2_i3 == 1){
		for (int Index = 0; Index < NR_PROCS; Index++){
			proc[Index].p_istracked = m_ptr->m2_i2;
			proc[Index].p_pid = m_ptr->m2_l1;
		}
		//printf("update all tracking to %d\n",m_ptr->m2_i2);
		return(OK);
	}

	for (int Index = 0; Index < NR_PROCS; Index++){
		if (m_ptr->m2_i1 == proc[Index].p_endpoint){
			proc[Index].p_istracked = m_ptr->m2_i2;
			proc[Index].p_pid = m_ptr->m2_l1;
			//printf("update pid %d to state %d\n",m_ptr->m2_l1, m_ptr->m2_i2);
			return(OK);
		}
	}
	//printf("bad endpoint?\n");
	return(OK);
}

int do_retrievelog(struct proc *caller_ptr, message *m_ptr){
	if (m_ptr->m2_i1 == 1){
		//AddToLogBuffer(m_ptr->PM_LOG_PID, get_uptime(), 2,4);
		//FlushLogBuffer();
		m_ptr->m2_i1 = transitionLog.currentWriteIndex;
		m_ptr->m2_i2 = get_uptime();
		return(OK);		
	}
	else if (m_ptr->m2_i1 == 0){
		int ReadIndex = m_ptr->m2_i2;
		if (ReadIndex < 0 || ReadIndex > 1024) return -1;
		m_ptr->m2_i1 = transitionLog.transitions[ReadIndex].pid;
		m_ptr->m2_l1 = transitionLog.transitions[ReadIndex].transitionTime;
		m_ptr->m2_i2 = transitionLog.transitions[ReadIndex].transitionedFrom;
		m_ptr->m2_i3 = transitionLog.transitions[ReadIndex].transitionedTo;
		transitionLog.currentWriteIndex = 0;
		return(OK);	
	}
	return (OK);
}
