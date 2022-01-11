#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

/* Retrieves the file name from a URL */
char * getFileName(char * url)
{
    char *path;
    path = (char *)malloc(strlen(url)*sizeof(char));
    strcpy(path,url);
    char *ssc;
    int l = 0;
    ssc = strstr(path, "/");
    while (ssc)
    {
        l = strlen(ssc) + 1;
        path = &path[strlen(path) - l + 2];
        ssc = strstr(path, "/");
    }
    return path;
}


/* Saves the downloaded data into a file */
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

/* Initializes Curl */
void init_curl()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

/* Downloads a file from a URL */
static void *pull_one_url(char *url)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;

    curl = curl_easy_init();
    
    fp = fopen(getFileName(url), "wb");
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    // curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    /* always cleanup */
    curl_easy_cleanup(curl);
    fclose(fp);

    return NULL;
}