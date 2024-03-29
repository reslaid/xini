# </[XIni](https://github.com/reslaid/xini.git)>
[![Version](https://img.shields.io/badge/version-0.2.3-gren.svg)](https://github.com/reslaid/xini.git) 
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/4f58ee8f44234a3497ce62b646b1c899)](https://app.codacy.com/gh/reslaid/xini/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
[![Commit activity](https://img.shields.io/github/commit-activity/m/reslaid/xini)](https://github.com/reslaid/xjson/commits)
[![Last Commit](https://img.shields.io/github/last-commit/reslaid/xini/main)](https://github.com/reslaid/xini/commits)

## **Dependencies**

  [![Git](https://skillicons.dev/icons?i=git)](https://git-scm.com/downloads)

## Installing

  ```bash
  git clone https://github.com/reslaid/xini.git
  ```

## Examples

  - **Parsing**

    *Contents of the .ini file*

    ```ini
    ; example.ini
    [fruits]
    oranges=30
    ```

    *Parsing code from the library*

    ```cpp
    IniParser ini;

    const IniChar* filename = IniT("example.ini");

    if (!(ini >> filename)) {
        std::cout << "Error opening file" << std::endl;
        return -1;
    }

    long oranges;
    oranges = IniParseInt64(
        ini.get(IniT("fruits"), IniT("oranges"))
    );

    std::wcout << oranges << std::endl;

    oranges += 100;

    ini.set<long>(
        IniT("fruits"), IniT("oranges"),
        oranges
    );

    ini.commit(filename);
    ```

  - **Parsing dictionaries and data arrays**
  
    *Contents of the .ini file*

      ```ini
      ; example.ini
      [response]
      recv={status-code: 0xC8}
      ```

    *Parsing code from the library*

      ```cpp
      IniParser ini;

      const IniChar* filename = IniT("example.ini");

      if (!(ini >> filename)) {
          std::cout << "Error opening file" << std::endl;
          return -1;
      }

      IniString dict = ini.get(IniT("response"), IniT("recv"));

      auto recv = IniDictParse(
          dict
      );

      int statusCode = IniParseInt64(
          recv[IniT("status-code")]
      );

      std::cout << "Status Code: " << statusCode << std::endl;

      statusCode = 0x194;

      recv[IniT("status-code")] = Int64ToHexString(statusCode);

      dict = IniDictToStr(recv);

      ini.set(IniT("response"), IniT("recv"), dict);

      std::cout << "New Status Code: " << statusCode << std::endl;

      ini.commit(filename);
      ```

## Docs

- **Inclusion in the project**
  
  - **Main header file**
  
    ```cpp
    #include "xini/parser.hpp"
    ```

  - **Header for working with parsers**

    ```cpp
    #include "xini/utils.hpp"
    ```

  - **Headers for parsing arrays and dictionaries**

    ```cpp
    #include "xini/array.hpp"
    #include "xini/dict.hpp"
    ```

  - **Headers for parsing numeric, hexadecimal and binary values**

    ```cpp
    #include "xini/decimal.hpp"
    ```

- **Loading content**  
  - **Creating an instance of a class**

    ```cpp
    IniParser ini;
    ```

  - **Load from file**
  
    ```cpp
    IniParser ini;

    const IniChar* filename = IniT("xconf.ini");
  
    if (!(ini >> filename)) {
        std::cout << "Error opening file" << std::endl;
        return -1;
    }
    ```

  - **Separators in arrays and dictionaries**
    
    *The keys in the dictionary are divided in this way:*

      ```cpp
      IniT("{key: value; key2: value2}");
      ```

    *Elements in arrays are divided this way:*

      ```cpp
      IniT("[value, value2]");
      ```

  - **Loading from string**

    ```cpp
    IniParser ini;

    const IniChar* data;
    data = IniT("[section]\nvar=value\nhex=0xC8\ndict={variable1: value1; variable2: value2}\narray=[value1, value2]");
  
    ini << data;
    ```

- **Working with Values**
  - **Checking the existence of a value**

    ```cpp
    bool varExist = ini.exist(IniT("section"), IniT("var"));
    ```

  - **Checking the existence of a section**

    ```cpp
    bool sectExist = ini.exist(IniT("section"));
    ```

  - **Getting value**

    ```cpp

    IniString varValue;

    if (varExist) {
        // ini.get<typename __T__>
        varValue = ini.get<IniString>(IniT("section"), IniT("var"));
    }
    ```

  - **Setting the value**

    ```cpp
    // ini.set<typename __T__>
    ini.set<const IniChar*>(IniT("section"), IniT("var"), IniT("value"));
    ```

  - **Delete a value**

    ```cpp
    ini.rem(IniT("section"), IniT("var"));
    ```

  - **Comparison of maps of two parsers**

    ```cpp
    // ini Identical to ini2 object
    bool identical = ini == ini2;
    ```

  - **Deleting a section**

    ```cpp
    ini.rem(IniT("section"));
    ```

  - **Confirmation of writing to a file**

    ```cpp
    ini.commit();
    ```

  - **Getting sections and values ​​asstd::map**

    ```cpp
    auto map = (IniMap)ini;
    // Or
    auto map = ini.map();
    ```

  - **Comparison of two maps from parsers**

    ```cpp
    bool identical = ini.map() == ini2.map();
    ```

  - **Connecting two parsers together**

    ```cpp
    IniParser mergedIni;
    mergedIni = IniMerge(ini, ini2);
    ```

  - **Parsing an array**

    ```cpp
    std::vector<IniString> arr;
    arr = IniArrayParse(ini.get<IniString>(IniT("section"), IniT("array")));
    ```

  - **Adding values ​​to an array**

    ```cpp
    arr.push_back(IniT("value"));
    ```

  - **Adding values ​​by index to an array**

    ```cpp
    const int INDEX = 0;

    arr.insert(arr.begin() + INDEX, IniT("value"));
    ```

  - **Получение значения из массива**

    ```cpp
    const int valueIndex = 0;
    IniString value = arr.at(valueIndex);
    ```

  - **Changing values ​​in an array**

    ```cpp
    const int INDEX = 0;

    arr[INDEX] = IniT("value");
    ```

  - **Removing a value by its index in anarray**

    ```cpp
    const int INDEX = 0;
        
    arr.erase(vec.begin() + INDEX);
    ```

  - **Getting the size of an array**

    ```cpp
    size_t arrSize = arr.size();
    ```

  - **Recording changes to an array**

    ```cpp
    ini.set<IniString>(IniT("section"), IniT("array"), IniArrayToStr(arr));
    ```

  - **Dictionary parsing**

    ```cpp
    std::map<IniString, IniString> dict;
    dict = IniDictParse(ini.get<IniString>(IniT("section"), IniT("section")));
    ```

  - **Getting a value from a dictionary**

    ```cpp
    IniString valKey = dict[IniT("key")];
    ```

  - **Changing/Adding values ​​in thedictionary**

    ```cpp
    dict[IniT("variable1")] = IniT("value1");
    ```

  - **Deleting values ​​in a dictionary**

    ```cpp
    dict.erase(IniT("variable1"));
    ```

  - **Getting the size of a dictionary**

    ```cpp
    size_t dictSize = dict.size();
    ```

  - **Recording changes to the dictionary**

    ```cpp
    ini.set<IniString>(IniT("section"), IniT("dict"), IniDictToStr(dict));
    ```

  - **Parsing any digital value (decimal, hex, binary)**

    ```cpp
    long decHexValue = IniParseInt64(ini.get<IniString>(IniT("section"), IniT("hex")));
    ```
