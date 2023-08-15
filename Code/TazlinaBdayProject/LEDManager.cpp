#include "LEDManager.h"


// Generic HTTP POST data needs to be extracted and deciphered.
bool LEDManager::decodeHTTPMessage(String HTTP_POST_CONTENT) {
    char *str_arr = new char[HTTP_POST_CONTENT.length() + 1];
    strcpy(str_arr, HTTP_POST_CONTENT.c_str());

    int index_placeholder = 0;
    for (index_placeholder; str_arr[index_placeholder] != '\n' && str_arr[index_placeholder + 1] != '\n'; index_placeholder++) {
        Serial.print(str_arr[index_placeholder]);
    }
    index_placeholder += 2;

    // Reading the body of the POST and acting on the instructions
    if(str_arr[index_placeholder] == 0) {
        this->animateOFF();
    } else if (str_arr[index_placeholder] == 1) {
        this->animateON();
    }
}
