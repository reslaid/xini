> # </[XIni](https://github.com/reslaid/xini.git)>
> [![Version](https://img.shields.io/badge/version-0.1.2-orange.svg)](https://github.com/reslaid/xini.git) [![Codacy Badge](https://app.codacy.com/project/badge/Grade/4f58ee8f44234a3497ce62b646b1c899)](https://app.codacy.com/gh/reslaid/xini/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade) [![Commit activity](https://img.shields.io/github/commit-activity/m/reslaid/xini)](https://github.com/reslaid/xjson/commits) [![Last Commit](https://img.shields.io/github/last-commit/reslaid/xini/main)](https://github.com/reslaid/xini/commits)

# **Dependencies**
- [**Git**](https://git-scm.com/downloads)

# Installing
- **Installation from repository**
    ```bash
    git clone https://github.com/reslaid/xini.git
    ```

# Docs

- **Inclusion in the project**
    ```cpp
    #include "xini/parser.hpp"
    ```

- **Loading content**
    
    - **Creating an instance of a class**:

    ```cpp
    IniParser ini;
    ```

    - **Load from file**:
    
    ```cpp
    IniParser ini;

    const IniChar* filename = IniT("main.ini");
  
    if (!(ini >> filename)) {
      std::cout << "Error opening file" << std::endl;
      return -1;
    }
    ```

    - **Loading from string**:

    ```cpp
    IniParser ini;

    const IniChar* data = IniT("[section]\nvar=value");
  
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
        // ini.get<typename T>
        varValue = ini.get<IniString>(IniT("section"), IniT("var"));
    }
    ```

    - **Setting the value**

    ```cpp
    // ini.set<typename T>
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

    - **Getting sections and values ​​as std::map**

    ```cpp
    auto map = (IniMap)ini;
    // Or
    auto map = ini.map();
    ```
