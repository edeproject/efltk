#ifndef _FL_THREAD_LINUX_H_
#define _FL_THREAD_LINUX_H_

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

void Fl_Thread::destroy() { }

/////////////
// FL_MUTEX

// Linux supports recursive locks, use them directly, with some cheating:
#ifdef PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP

extern pthread_mutexattr_t Fl_Mutex_attrib;

void Fl_Mutex::init() {
	pthread_mutex_init(&cs, &Fl_Mutex_attrib);
}

void Fl_Mutex::lock() {
	pthread_mutex_lock(&cs);
}

void Fl_Mutex::unlock() {
	pthread_mutex_unlock(&cs);
}

#else 

// standard pthread mutexes need a bit of work to be recursive:
void Fl_Mutex::init() {
	recursive_counter = 0;
	pthread_mutex_init(&cs, NULL);
}

void Fl_Mutex::lock() {
    if(!recursive_counter || owner_ != pthread_self()) {
		pthread_mutex_lock(&cs);
		owner_ = pthread_self();
    }
    recursive_counter++;	
}

void Fl_Mutex::unlock() {
	if (!--recursive_counter) 
		pthread_mutex_unlock(&cs);
}

#endif

void Fl_Mutex::destroy() {
	pthread_mutex_destroy(&cs);
}


#endif
