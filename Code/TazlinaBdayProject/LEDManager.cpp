#include "LEDManager.h"


// Generic HTTP Request Format: http://192.168.xx.xx/request/<INSERT 10 CHAR REQUEST STRING>
bool LEDManager::decodeHTTPMessage(String HTTP_REQUEST_CONTENT) {
    String isolatedRequest = HTTP_REQUEST_CONTENT.substr(HTTP_REQUEST_CONTENT.find("/request/") + 9, 10);
    char *str_arr = isolatedRequest.c_str();
}
