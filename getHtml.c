#include "getHtml.h"

inline size_t write_callback(void *contents, size_t size, size_t nmemb, FILE *file) {
    return fwrite(contents, size, nmemb, file);
}

int getHtml(char* URL ,FILE* htmlFile) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "[ ERROR ] Curl 실행 실패");
        return 1;
    }

    if (!htmlFile) {
        fprintf(stderr, "[ ERROR ] 파일 열기 실패\n");
        curl_easy_cleanup(curl);
        return 1;
    }
	printf("[ INFO ] HTTP 요청 URL : %s\n", URL);

    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, htmlFile);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "[ INFO ] CURL 요청 실패 : %s\n", curl_easy_strerror(res));
    } else {
        printf("[ INFO ] HTML 파일 저장 완료\n\n");
    }
    curl_easy_cleanup(curl);

    return 0;
}