#include <stdio.h>
#include <curl/curl.h>

#define URL "https://inha.ac.kr/diet/kr/2/view.do"
#define OUTPUT_FILE "HTML.html"

size_t write_callback(void *contents, size_t size, size_t nmemb, FILE *file) {
    return fwrite(contents, size, nmemb, file);
}

int main() {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "[ INFO ] Curl 실행 실패\n");
        return 1;
    }

    FILE *file = fopen(OUTPUT_FILE, "w");
    if (!file) {
        fprintf(stderr, "[ INFO ] 파일 열기 실패\n");
        curl_easy_cleanup(curl);
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "[ INFO ] CURL 요청 실패 : %s\n", curl_easy_strerror(res));
    } else {
        printf("[ INFO ] HTML 파일 %s 저장 완료\n", OUTPUT_FILE);
    }

    fclose(file);
    curl_easy_cleanup(curl);

    return 0;
}