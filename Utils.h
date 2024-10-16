#pragma once

#include <string>
#include <windows.h>

class Utils {
public:
    // 将字符串转换为unicode编码
    static wchar_t* stringToWideChar(const std::string& str);
};
