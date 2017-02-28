/* If there were any type definitions local to the Process Manager, they would
 * be here.  This file is included only for symmetry with the kernel and File
 * System, which do have some local type definitions.
 */
typedef struct procInfo{
	int procid;
	long CreationTime;
	long TerminationTime;
} procInfo;

typedef struct cBuffer{
	int CurrentReadIndex;
	int CurrentWriteIndex;
	int BufferSize;
	procInfo procs[1024];
} cBuffer;


