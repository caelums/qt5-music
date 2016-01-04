//STATIC
#define URL_SIZE 256
#define PATH_SIZE 16
//API URL
#define OLD_API "http://music.163.com/api/%s"
#define NEW_API "http://music.163.com/weapi/%s"

//PATH
#define DETAIL_PATH "song/detail?ids=[%s]"
#define LYRIC_PATH "song/lyric?os=android&id=%s&lv=-1&tv=-1"
#define RADIO_PATH "radio/get"
#define SEARCH_PATH "search/get/web"

int detail(char *id,struct curl_slist *headers,struct response *response);
int search(char *data,struct curl_slist *headers,struct response *response);
struct curl_slist *initHeader(struct curl_slist *headers);
