
//      $$$$$$\   $$$$$$\  $$$$$$$\      $$$$$$$\                                               $$$$$$\       $$$$$$\                  $$\
//     $$ ___$$\ $$  __$$\ $$  ____|     $$  __$$\                                             $$  __$$\     $$  __$$\                 $$ |
//     \_/   $$ |$$ /  \__|$$ |          $$ |  $$ | $$$$$$\  $$\   $$\  $$$$$$$\      $$$$$$\  $$ /  \__|    $$ /  \__| $$$$$$\   $$$$$$$ | $$$$$$\
//        $$$$$ / $$$$$$$\  $$$$$$$\     $$ |  $$ | \____$$\ $$ |  $$ |$$  _____|    $$  __$$\ $$$$\         $$ |      $$  __$$\ $$  __$$ |$$  __$$\
//       \___$$\ $$  __$$\ \_____$$\     $$ |  $$ | $$$$$$$ |$$ |  $$ |\$$$$$$\      $$ /  $$ |$$  _|        $$ |      $$ /  $$ |$$ /  $$ |$$$$$$$$ |
//     $$\   $$ |$$ /  $$ |$$\   $$      $$ |  $$ |$$  __$$ |$$ |  $$ | \____$$\     $$ |  $$ |$$ |          $$ |  $$\ $$ |  $$ |$$ |  $$ |$$   ____|
//     \$$$$$$  | $$$$$$  |\$$$$$$  |    $$$$$$$  |\$$$$$$$ |\$$$$$$$ |$$$$$$$  |    \$$$$$$  |$$ |          \$$$$$$  |\$$$$$$  |\$$$$$$$ |\$$$$$$$\
//      \______/  \______/  \______/     \_______/  \_______| \____$$ |\_______/      \______/ \__|           \______/  \______/  \_______| \_______|
//                                                             $$\   $$ |
//                                                             \$$$$$$  |
//                                                              \______/
// Author : Saihaj Law
// Date : January 4th
// Project : Wikipedia Web Scraper
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
int main(int argc, char *argv[]) {

curl_global_init(CURL_GLOBAL_ALL);
char topic[256];
printf("Enter topic: ");
scanf("%s", topic);

char wikipedia_url[512];
sprintf(wikipedia_url, "https://en.wikipedia.org/wiki/%s", topic);
CURL *curl = curl_easy_init();
if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, wikipedia_url);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}
htmlDocPtr doc = htmlReadMemory(html_data, html_data_size, wikipedia_url, NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
xmlNodePtr content_node = get_node_by_class(doc->children, "mw-parser-output");
if (content_node) {
    xmlBufferPtr buffer = xmlBufferCreate();
    xmlNodeDump(buffer, doc, content_node, 0, 0);
    printf("%s\n", buffer->content);
    xmlBufferFree(buffer);
}
htmlFreeDoc(doc);
curl_global_cleanup();
    return 0;
}
