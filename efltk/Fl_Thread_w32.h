#ifndef FL_THREAD_W32_H_
#define FL_THREAD_W32_H_

// DO NOT INCLUDE DIRECTLY

static int priority_values[] = {
  THREAD_PRIORITY_IDLE,
  THREAD_PRIORITY_LOWEST,
  THREAD_PRIORITY_BELOW_NORMAL,
  THREAD_PRIORITY_NORMAL,
  THREAD_PRIORITY_ABOVE_NORMAL,
  THREAD_PRIORITY_HIGHEST,
  THREAD_PRIORITY_TIME_CRITICAL
};
static int NumPriorities = 7;

bool Fl_Thread::create(thread_function function, void* arg)
{
	bool result = true;
	_function  = function;
	_arg       = arg;
	_kill_thread = _th_running = 0;

	_threadHandle = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Fl_Thread::st_th_func, this, 0, &_threadId);
	if(!_threadHandle)
		result = false;
	else
		set_priority(NORMAL_PR);

	return result;
}

void Fl_Thread::destroy(int exitcode)
{
	TerminateThread(_threadHandle, exitcode);
}

void Fl_Thread::join(int timeout)
{
	int ret = WaitForSingleObject(_threadHandle, timeout);
	if( ret == WAIT_TIMEOUT ) destroy(-1);
}


int Fl_Thread::get_priority() const
{
	int priority = GetThreadPriority(_threadHandle);
	for(int i=0; i < NumPriorities; i++) {
		if(priority_values[i] == priority) {
  			priority = i;
			break;
		}
	}
	return priority;
}

int Fl_Thread::set_priority(unsigned int priority)
{
	int old = GetThreadPriority(_threadHandle);
	if(SetThreadPriority(_threadHandle, priority_values[priority])==0) return -1;
	for(int i=0; i < NumPriorities; i++) {
		if(priority_values[i] == old) {
  			old = i;
			break;
		}
	}
	return old;
}

void Fl_Thread::destroy() {
	if(_threadHandle) CloseHandle(_threadHandle);
}

/////////////
// FL_MUTEX

void Fl_Mutex::init() {
	InitializeCriticalSection(&cs);
}

void Fl_Mutex::destroy() {
	DeleteCriticalSection(&cs);
}

void Fl_Mutex::lock() {
	EnterCriticalSection(&cs);
}

void Fl_Mutex::unlock() { 
	LeaveCriticalSection(&cs); 
}

#endif
