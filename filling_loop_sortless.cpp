#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void filling_origin(const long long n) {
    long long a5, b5, sa5b5, n5=(long long)n*n*n*n*n;
    vector< pair<long long, int> > vec;

    for (int a=1; a<=n-1; a++) {
        for (int b=a+1; b<=n; b++) {
            a5 = (long long) a*a*a*a*a;
            b5 = (long long) b*b*b*b*b;
            if (a5+b5 < (long long)n*n*n*n*n) {
                vec.push_back( make_pair( a5+b5, (a<<16)+b ) );
            }
        }
    }

    sort( vec.begin(), vec.end() );
#   ifdef MANUAL_CLEARING
    // Free memory to clear memory allocation test
    vec.clear();
    vec.shrink_to_fit();
#   endif
}

void filling_minopt(const long long n) {
    long long a5, b5, sa5b5, n5=(long long)n*n*n*n*n;
    vector< pair<long long, int> > vec;

    for (int a=1; a<=n-1; a++) {
        for (int b=a+1; b<=n; b++) {
            a5 = (long long) a*a*a*a*a;
            b5 = (long long) b*b*b*b*b;
            sa5b5 = a5+b5;
            if (sa5b5 < n5) {
                vec.push_back( make_pair( sa5b5, (a<<16)+b ) );
            }
        }
    }
    sort( vec.begin(), vec.end() );
#   ifdef MANUAL_CLEARING
    // Free memory to clear memory allocation test
    vec.clear();
    vec.shrink_to_fit();
#   endif
}

void filling_alloc(const long long n) {
    long long a5, b5, sa5b5, n5=(long long)n*n*n*n*n;
    vector< pair<long long, int> > vec;

    vec.reserve((long long)(n-1)*(n));
    for (int a=1; a<=n-1; a++) {
        for (int b=a+1; b<=n; b++) {
            a5 = (long long) a*a*a*a*a;
            b5 = (long long) b*b*b*b*b;
            if (a5+b5 < (long long)n*n*n*n*n) {
                vec.push_back( make_pair( a5+b5, (a<<16)+b ) );
            }
        }
    }

    sort( vec.begin(), vec.end() );
#   ifdef MANUAL_CLEARING
    // Free memory to clear memory allocation test
    vec.clear();
    vec.shrink_to_fit();
#   endif
}

void filling_lesssort(const long long n) {
    long long a5, b5, sa5b5, n5=(long long)n*n*n*n*n;
    vector< pair<long long, int> > vec;

    for (int a=2; a<=n; a++) {
        for (int b=a-1; b<a; b++) {
            a5 = (long long) a*a*a*a*a;
            b5 = (long long) b*b*b*b*b;
            sa5b5 = a5+b5;
            if (sa5b5 < n5) {
                vec.push_back( make_pair( sa5b5, (a<<16)+b ) );
            }
        }
    }
    sort( vec.begin(), vec.end() );
#   ifdef MANUAL_CLEARING
    // Free memory to clear memory allocation test
    vec.clear();
    vec.shrink_to_fit();
#   endif
}

void filling_lesssort_precalc(const long long n) {
    long long a5, b5, sa5b5, n5=(long long)n*n*n*n*n;
    vector< pair<long long, int> > vec;
    vector< pair<long long, int> > pows;

    for (int a=1; a<=n; a++) {
        pows.push_back( make_pair( (long long) a*a*a*a*a, a ) );
    }

    for (int a=1; a<n; a++) {
        for (int b=a-1; b<a; b++) {
            a5 = pows[a].first;
            b5 = pows[b].first;
            sa5b5 = a5+b5;
            if (sa5b5 < n5) {
                vec.push_back( make_pair( sa5b5, (pows[a].second<<16)+pows[b].second ) );
            }
        }
    }
    sort( vec.begin(), vec.end() );
#   ifdef MANUAL_CLEARING
    // Free memory to clear memory allocation test
    vec.clear();
    vec.shrink_to_fit();
    pows.clear();
    pows.shrink_to_fit();
#   endif
}

void filling_lesssort_alloc(const long long n) {
    long long a5, b5, sa5b5, n5=(long long)n*n*n*n*n;
    vector< pair<long long, int> > vec;

    vec.reserve((long long)(n-1)*(n));
    for (int a=2; a<=n; a++) {
        for (int b=a-1; b<a; b++) {
            a5 = (long long) a*a*a*a*a;
            b5 = (long long) b*b*b*b*b;
            sa5b5 = a5+b5;
            if (sa5b5 < n5) {
                vec.push_back( make_pair( sa5b5, (a<<16)+b ) );
            }
        }
    }
    sort( vec.begin(), vec.end() );
#   ifdef MANUAL_CLEARING
    // Free memory to clear memory allocation test
    vec.clear();
    vec.shrink_to_fit();
#   endif
}

void timespec_diff(const struct timespec start, const struct timespec end, struct timespec *diff)
{
    if ((end.tv_nsec-start.tv_nsec)<0) {
        diff->tv_sec = end.tv_sec-start.tv_sec-1;
        diff->tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        diff->tv_sec = end.tv_sec-start.tv_sec;
        diff->tv_nsec = end.tv_nsec-start.tv_nsec;
    }
}


struct filling_kind {
    void (*func)(const long long);
    const char *name;
};

int main(int argc, char **argv)
{
    const int repeats = 1000;
    const long long n = 500;
    struct timespec ts_start, ts_end, ts_res;
    const struct filling_kind kinds[] = {
        { filling_origin,           "filling_origin" },
        { filling_minopt,           "filling_minopt" },
        { filling_alloc,            "filling_alloc" },
        { filling_lesssort,         "filling_lesssort" },
        { filling_lesssort_precalc, "filling_lesssort_precalc" },
        { filling_lesssort_alloc,   "filling_lesssort_alloc" },
        { NULL, NULL }
    };

    printf("repeats: %d\n", repeats);
    printf("count: %d\n", n);

    int i;
    for(i=0; kinds[i].func != NULL; i++) {
        clock_gettime(CLOCK_MONOTONIC, &ts_start);
        for(int it=0; it<repeats; it++) {
            kinds[i].func(n);
        }
        clock_gettime(CLOCK_MONOTONIC, &ts_end);
        timespec_diff(ts_start, ts_end, &ts_res);
        printf("%25s x %d: %llu.%.10llu\n", kinds[i].name, repeats, ts_res.tv_sec, ts_res.tv_nsec);
    }

    /*
    long long a5, b5, sa5b5, n5=(long long)n*n*n*n*n;
    vector< pair<long long, int> > vec;

    for (int a=2; a<=n; a++) {
        for (int b=1; b<a; b++) {
            a5 = (long long) a*a*a*a*a;
            b5 = (long long) b*b*b*b*b;
            sa5b5 = a5+b5;
            if (sa5b5 < n5) {
                vec.push_back( make_pair( sa5b5, (a<<16)+b ) );
            }
        }
    }

    for (int k=0; k<=vec.size(); k++) {
        //printf("%llu\n", 0);
    }
    */

    return 0;
}
