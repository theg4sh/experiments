#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <vector>
#include <string>
#include <utility>
#include <algorithm>

#define FUNCNAMELEN "30"

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

    for (int a=1; a<=n; a++) {
        for (int b=0; b<a; b++) {
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
        for (int b=0; b<a; b++) {
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

void filling_lesssort_precalc2(const long long n) {
    long long sa5b5, n5=(long long)n*n*n*n*n;
    vector< long long > vec;
    int a, b;
    long long *pows, *p, *a5, *b5;
    pows = new long long[n];

    for (a=1, p = pows; a<=n; ++a, ++p) {
        *p = a*a*a*a*a;
    }

    for (a5 = pows+1; *a5<n5; ++a5) {
        for (b5 = pows; b5<a5; ++b5) {
            sa5b5 = (*a5) + (*b5);
            if (sa5b5 < n5) {
                vec.push_back( sa5b5 ); //make_pair( sa5b5, (a<<16)+b ) );
            }
        }
    }
    sort( vec.begin(), vec.end() );
#   ifdef MANUAL_CLEARING
    // Free memory to clear memory allocation test
    vec.clear();
    vec.shrink_to_fit();
    delete [] pows;
#   endif
}

void filling_lesssort_alloc(const long long n) {
    long long a5, b5, sa5b5, n5=(long long)n*n*n*n*n;
    vector< pair<long long, int> > vec;

    vec.reserve((long long)(n-1)*(n));
    for (int a=1; a<=n; a++) {
        for (int b=0; b<a; b++) {
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

void filling_lesssort_alloc_break(const long long n) {
    long long a5, b5, sa5b5, n5=(long long)n*n*n*n*n;
    vector< pair<long long, int> > vec;

    vec.reserve((long long)(n-1)*(n));
    for (int a=1; a<=n; ++a) {
        sa5b5 = a5 = (long long) a*a*a*a*a;
        for (int b=0; b<a; ++b) {
            b5 = (long long) b*b*b*b*b;
            sa5b5 += b5;
            if (sa5b5 < n5) {
                vec.push_back( make_pair( sa5b5, (a<<16)+b ) );
            } else {
                break;
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
    bool enabled;
    void (*func)(const long long);
    const char *name;
    const char *desc;
};

void help(char *progname, struct filling_kind *kinds)
{
    printf("Usage: %s <count> <number> [func1 func2 ...]\n", progname);
    printf("Functions:\n");
    for (int i=0; kinds[i].func != NULL; ++i) {
        printf("    %-" FUNCNAMELEN "s %s\n", kinds[i].name, kinds[i].desc);
    }
}

int main(int argc, char **argv)
{
    int repeats = 100;
    long long n = 10000;

    struct timespec ts_start, ts_end, ts_res;

    struct filling_kind kinds[] = {
        { true,  filling_origin,                   "filling_origin",                 "Original algorythm" },
        { true,  filling_minopt,                   "filling_minopt",                 "Original algorythm with minimum optimisations" },
        { true,  filling_alloc,                    "filling_alloc",                  "Filling array with reserving memory" },
        { true,  filling_lesssort,                 "filling_lesssort",               "Back-filling array" },
        { true,  filling_lesssort_precalc,         "filling_lesssort_precalc",       "Back-filling array with precalculated n^5" },
        { true,  filling_lesssort_precalc2,        "filling_lesssort_precalc2",      "Back-filling array with precalculated n^5 - no vector for precalculated" },
        { true,  filling_lesssort_alloc,           "filling_lesssort_alloc",         "Back-filling array with reserving memory" },
        { true,  filling_lesssort_alloc_break,     "filling_lesssort_alloc_break",   "Back-filling array with reserving memory and breaking inner loop on a^5+b^5>=n5" },
        { false, NULL, NULL, NULL }
    };
    if (argc < 2) {
        help(argv[0], kinds);
        exit(1);
    }

    if (argc >=3 ) {
        n       = stol(argv[1]);
        repeats = stol(argv[2]);
        if (argc > 3) {
            int func_count = 0;
            for(int i=0; kinds[i].func != NULL; ++i) {
                kinds[i].enabled = false;
            }
            for (int f=3; f<argc; ++f) {
                for (int i=0; kinds[i].func != NULL; ++i) {
                    if (strcmp(argv[f], kinds[i].name) == 0) {
                        kinds[i].enabled = true;
                        ++func_count;
                    }
                }
            }
            if (func_count == 0) {
                help(argv[0], kinds);
                exit(1);
            }
        }
    }

    printf("repeats: %d\n", repeats);
    printf("count: %d\n", n);

    for (int i=0; kinds[i].func != NULL; ++i) {
        if (kinds[i].enabled == false)
            continue;
        clock_gettime(CLOCK_MONOTONIC, &ts_start);
        for(int it=0; it<repeats; it++) {
            kinds[i].func(n);
        }
        clock_gettime(CLOCK_MONOTONIC, &ts_end);
        timespec_diff(ts_start, ts_end, &ts_res);
        double extime = (double)(ts_res.tv_sec + 1.0e-9*ts_res.tv_nsec);
        printf("%" FUNCNAMELEN "s x %d: %.9f  1 iter avg %.9f\n", kinds[i].name, repeats, extime, extime/repeats);
    }

    return 0;
}
