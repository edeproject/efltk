#ifndef FL_THREAD_LINUX_H_
#define FL_THREAD_LINUX_H_

// DO NOT INCLUDE DIRECTLY

bool Fl_Thread::create(thread_function function, void* arg)
{
	bool result = true;
	_function  = function;
	_arg       = arg;
	_kill_thread = _th_running = 0;
	if(pthread_create(&_threadHandle, NULL, Fl_Thread::st_th_func, this))
		result = false;
	return result;
}

void Fl_Thread::destroy(int exitcode)
{
	pthread_cancel(_threadHandle);
}

void Fl_Thread::join(int timeout)
{
	void *result;
    pthread_join(_threadHandle, &result);
}

int Fl_Thread::get_priority() const
{
	return 0;
}

int Fl_Thread::set_priority(unsigned int priority)
{
	return 0;
}


#endif
