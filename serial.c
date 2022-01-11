#include <stdio.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    int nfiles, i, tid;
    init_curl();
    if (argc < 2)
    {
        printf("Alteast one url should be passed as arguments.\nUsage:\n\t%s URL1 URL2 ... \n", *argv);
        exit(1);
    }

    nfiles = argc - 1;
    if (nfiles <= 0)
    {
        printf("Invalid value for NUM_THREADS.\nUsage:\n\t%s URL1 URL2 ... \n", *argv);
        exit(1);
    }

    for(i=0;i<nfiles;i++)
    {

        printf("Download %d starting...\n", i);

        pull_one_url(*(argv + i + 1));

    } /* end of parallel section */
    curl_global_cleanup();
    return 0;
}