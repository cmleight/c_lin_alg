/* inc/bench_time.h.  Generated from bench_time.h.in by configure.  */

#if __STDC_VERSION__  < 201112L
    #include <sys/time.h>
#else
    #include <time.h>
#endif

struct bench_time {
#if __STDC_VERSION__  < 201112L
    struct timeval time;
#else
    struct timespec time;
#endif
};

long double
time_diff ( struct bench_time* start, struct bench_time* end );

void
set_time ( struct bench_time* bench );

