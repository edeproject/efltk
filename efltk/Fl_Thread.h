#ifndef FL_THREAD_H_
#define FL_THREAD_H_

#include "Enumerations.h"

// Thread and Mutex classes.
// These are made inline, so You need only
// link with thread libs when using these.

#ifdef _WIN32

# include <process.h>
# include <windows.h>
# include <limits.h>

#else

# include <pthread.h>
# include <signal.h>
# include <unistd.h>

#endif

typedef int (*thread_function)(void * arg);

/////////////////////////////////////////////
// MUTEX CLASS

class Fl_Mutex
{
public:
    Fl_Mutex() { init(); }
    ~Fl_Mutex() { destroy(); }
    inline void lock();
    inline void unlock();
private:
	inline void init();
	inline void destroy();
#ifndef _WIN32
    pthread_mutex_t cs;
    pthread_t owner_;
	int recursive_counter;
#else
    CRITICAL_SECTION cs;
#endif
};

/////////////////////////////////////////////
// THREAD CLASS

class Fl_Thread
{
public:
    // Values for set/get priority functions
    enum {
        IDLE_PR = 0,
        LOWEST_PR,
        BELOW_NORMAL_PR,
        NORMAL_PR,
        ABOVE_NORMAL_PR,
        HIGHEST_PR,
        REALTIME_PR
    };

    Fl_Thread() {
        _threadHandle = 0; _threadId = 0;_function = 0; _arg = 0;
        _kill_thread = 0; _th_running = 0; _ms_sleep = 0;
    }
    virtual ~Fl_Thread() { destroy(); }

    inline bool create(thread_function function = 0, void* arg = 0);
    inline void destroy(int exitcode);
    inline void join(int timeout = 100);
    inline void kill_thread() { _kill_thread = true; }

    inline int get_priority() const;
    inline int set_priority(unsigned int priority);

    virtual int single_step() { return 0; }

    // sleep time between single_steps
    void ms_sleep(int sleep) { _ms_sleep = sleep; }
    int ms_sleep()			 { return _ms_sleep;  }

private:
    int internal_th_function();

    bool _kill_thread, _th_running;
    unsigned int _ms_sleep;

    unsigned long	_threadId;
    thread_function _function;
    void *_arg;

    // static thread linker function
#ifndef _WIN32
    static void *st_th_func(void *arg);
    pthread_t _threadHandle;
#else
    static int st_th_func(void *arg);
    HANDLE _threadHandle;
#endif
	inline void destroy();
};

// Include system depend inline functions
#ifdef _WIN32
# include "Fl_Thread_w32.h"
#else
# include "Fl_Thread_Linux.h"
#endif

static inline int fl_create_thread(Fl_Thread& t, int (*f) (void *), void* p) {
    return t.create(f, p);
}

#endif /* FL_THREAD_H_ */




