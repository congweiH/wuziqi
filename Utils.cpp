#include "Utils.h"

wchar_t* Utils::stringToWideChar(const std::string& str) {
    int wideLength = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    wchar_t* wideString = new wchar_t[wideLength];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wideString, wideLength);
    return wideString;
}