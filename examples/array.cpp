#include <iostream>
#include "xini/parser.hpp"
#include "xini/array.hpp"

int main() {

    IniParser ini;

    ini << IniT("[array-example]\narray=[value, value2]");

    std::vector<IniString> arr;

    arr = IniArrayParse(ini.get<IniString>(IniT("array-example"), IniT("array")));

    int i = 0;
    for (const auto& value : arr) {
        std::wcout << std::to_wstring(i) << L" : " << value << std::endl;
        i++;
    }

    return i;
}
