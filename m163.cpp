#include "m163.h"
#include "requests.h"


struct curl_slist *initHeader(struct curl_slist *headers)
{
    headers = curl_slist_append(headers, "Accept: */*");
    headers = curl_slist_append(headers, "Accept-Language: zh-CN,en-US;q=0.7,en;q=0.3");
    headers = curl_slist_append(headers, "Connection: keep-alive");
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
    headers = curl_slist_append(headers, "Host: music.163.com");
    headers = curl_slist_append(headers, "Referer: http://music.163.com/");
    headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:39.0) Gecko/20100101 Firefox/39.0");
    return headers;
}

int detail(char *id,struct curl_slist *headers,struct response *response)
{
    char path[URL_SIZE];
    char url[URL_SIZE];

    snprintf(path,URL_SIZE,DETAIL_PATH,id);
    snprintf(url,URL_SIZE,OLD_API,path);


    if(get(url,headers,response))
    {
        return 1;
    }
    return 0;
}


int search(char *data,struct curl_slist *headers,struct response *response)
{
    char url[URL_SIZE];
    snprintf(url,URL_SIZE,OLD_API,SEARCH_PATH);

    if(post(url,data,headers,response))
    {
        return 1;
    }
    return 0;

}
