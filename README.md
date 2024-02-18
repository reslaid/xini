> # </[XIni](https://github.com/reslaid/xini.git)>
> [![Version](https://img.shields.io/badge/version-0.1.0-orange.svg)](https://github.com/reslaid/xini.git) [![Commit activity](https://img.shields.io/github/commit-activity/m/reslaid/xini)](https://github.com/reslaid/xjson/commits) [![Last Commit](https://img.shields.io/github/last-commit/reslaid/xini/main)](https://github.com/reslaid/xini/commits)

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
        // Perhaps the file is open by another process or does not exist
		std::cout << "Error opening file" << std::endl;
		return -1;
    }
    ```

    - **Loading from string**:

    ```cpp
    IniParser ini;

    const IniChar* data = IniT("[section]\nvar=value");
	
    if (!(ini << data)) {
		std::cout << "String loading error" << std::endl;
		return -1;
    }
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
