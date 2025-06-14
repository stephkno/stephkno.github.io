#ifndef JS_H
#define JS_H

    #include <emscripten.h>
    #include <emscripten/html5.h>
    #include <string>

    // Function to change the text of the div
    void PutString(const std::string& newText);

    void alert(const std::string& newText);

    unsigned int js_random(unsigned int min, unsigned int max);

#endif
