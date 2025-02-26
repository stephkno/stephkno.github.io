#include <emscripten.h>
#include <emscripten/html5.h>

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
