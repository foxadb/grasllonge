/*
 * =====================================================================================
 *
 *       Filename:  connection.cxx
 *
 *    Description:  Fichier contenant les fichiers d'interaction avec Challonge
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */

#include "connection.h"

using namespace std;
using namespace JSON;

/////////////////////// GET Method /////////////////////// 

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void getRequest(string url)
{
    FILE *fp;
    const char* outputfile = "lastget.json";
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outputfile,"wb");

        curl_easy_setopt(curl, CURLOPT_URL, (char*) url.c_str());

        /*  we want to use our own write function */ 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

        /*  set the output file for writing */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        /*  perform the request */
        res = curl_easy_perform(curl);

        /*  cleanup and close the file */
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

/////////////////////// POST Method /////////////////////// 

void postRequest(string url, string post)
{
    CURL *curl;
    CURLcode res;

    /*  get a curl handle */ 
    curl = curl_easy_init();
    
    if(curl)
    {
        /*  set the URL that is about to receive our POST */
        curl_easy_setopt(curl, CURLOPT_URL, (char*) url.c_str());
        
        /*  specify the POST data */ 
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (char*) post.c_str());

        /*  perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);
        
        /*  check for errors */ 
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /*  cleanup */ 
        curl_easy_cleanup(curl);
    }
}


/////////////////////// PUT Method /////////////////////// 

size_t read_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t retcode;
    curl_off_t nread;

    retcode = fread(ptr, size, nmemb, stream);
    nread = (curl_off_t)retcode;
    return retcode;
}

void putRequest(const char *file, string url)
{
    CURL *curl;
    CURLcode res;
    FILE * hd_src;
    struct stat file_info;

    /*  get the file size of the local file */ 
    stat(file, &file_info);

    hd_src = fopen(file, "rb");

    /*  get a curl handle */ 
    curl = curl_easy_init();

    if(curl)
    {
        /*  we want to use our own read function */ 
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_data);

        /*  enable uploading and HTTP PUT method */ 
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_PUT, 1L);

        /*  specify target URL, and note that this URL should include a file
         *         name, not only a directory */ 
        curl_easy_setopt(curl, CURLOPT_URL, (char*) url.c_str());

        /*  specify which file to upload */ 
        curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);

        /*  provide the size of the upload, we specicially typecast the value
         *         to curl_off_t since we must be sure to use the correct data size */ 
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                (curl_off_t) file_info.st_size);

        /*  perform the request */ 
        res = curl_easy_perform(curl);

        /*  Check for errors */ 
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }

        /*  always cleanup */ 
        curl_easy_cleanup(curl);
    }

    fclose(hd_src);
}
