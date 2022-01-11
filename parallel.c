#include <stdio.h>
#include "utils.h"
#include <omp.h>

int main(int argc, char *argv[])
{
    int nthreads, i, tid;
    init_curl();
    if (argc < 2)
    {
        printf("Alteast one url should be passed as arguments.\nUsage:\n\t%s URL1 URL2 ... \n", *argv);
        exit(1);
    }

    nthreads = argc - 1;
    if (nthreads <= 0)
    {
        printf("Invalid value for NUM_THREADS.\nUsage:\n\t%s URL1 URL2 ... \n", *argv);
        exit(1);
    }

    omp_set_num_threads(nthreads);

    #pragma omp parallel shared(argv, argc) private(i, tid)
    {
        tid = omp_get_thread_num();

        printf("Thread %d starting...\n", tid);

        pull_one_url(*(argv + tid + 1));

    } /* end of parallel section */
    curl_global_cleanup();
    return 0;
}