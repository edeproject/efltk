#include <efltk/Fl_Thread.h>

#ifndef _WIN32
#define Sleep(x) usleep(x*1000)
#endif

#ifdef _WIN32
int Fl_Thread::st_th_func(void *arg)
#else
void *Fl_Thread::st_th_func(void *arg)
#endif
{
    int ret =0;
    Fl_Thread *thread = (Fl_Thread *)arg;
    ret = thread->internal_th_function();
#ifdef _WIN32
    return ret;
#else
    return 0;
#endif
}

int Fl_Thread::internal_th_function()
{
    _th_running = true;
    int ret = -1;
    if(!_function) {

        while(!_kill_thread) {

            ret = single_step();
            if(ret==0) break;
            if( _kill_thread )
                ms_sleep(0);
            if(_ms_sleep )
                Sleep(_ms_sleep);
        }

    } else {

        ret = _function(_arg);

    }
    _th_running = false;
    return ret;
}

