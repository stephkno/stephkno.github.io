#include "js.h"

// Function to change the text of the div
void PutString(const std::string& newText) {
    EM_ASM({
        var div = document.getElementById('textdiv');
        if (div) {
            div.innerHTML = UTF8ToString($0);
        }
    }, newText.c_str());
}

// Function to change the text of the div
void alert(const std::string& newText) {
    EM_ASM({
        alert(UTF8ToString($0));
    }, newText.c_str());
}

unsigned int js_random(unsigned int min, unsigned int max){

    return EM_ASM_INT({
        return Math.floor( $0 + (Math.random() * ($1-$0) ) );
    }, min, max);

}
