#include <iostream>
#include "xini/parser.hpp"
#include "xini/dict.hpp"

int main() {

    IniParser ini;

    ini << IniT("[dict-example]\ndict={key: value, key2: value2}");

    std::map<IniString, IniString> dict;

    dict = IniDictParse(ini.get<IniString>(IniT("dict-example"), IniT("dict")));

    for (const auto& pair : dict) {
        std::wcout << pair.first << " : " << pair.second << std::endl;
    }

    return dict.size();
}
