
#ifndef					__IniParser_Required_
# define                    __IniParser_Required_

#pragma region              includes

#include                    <iostream>
#include                    <fstream>
#include                    <sstream>
#include                    <cctype>
#include                    <map>
#include                    <string>

#pragma endregion

#pragma region			macros

#if defined(_UNICODE)

/**
 * @brief Macro that defines the type of IniParser based on whether the _UNICODE macro is defined.
 *
 * If _UNICODE is defined, IniParser is defined as IniParserW, which is the wide-character version of IniParser.
 * Otherwise, IniParser is defined as IniParserA, which is the ASCII-character version of IniParser.
 */
# define IniParser          IniParserW

/**
 * @brief Macro that defines the string type used by IniParser based on whether the _UNICODE macro is defined.
 *
 * If _UNICODE is defined, IniString is defined as std::wstring, which is the wide-character string type.
 * Otherwise, IniString is defined as std::string, which is the ASCII-character string type.
 */
# define IniString          std::wstring

/**
 * @brief Macro that defines the character type used by IniParser based on whether the _UNICODE macro is defined.
 *
 * If _UNICODE is defined, IniChar is defined as wchar_t, which is the wide-character type.
 * Otherwise, IniChar is defined as char, which is the ASCII-character type.
 */
# define IniChar            wchar_t

/**
* @brief Macro that converts the input string literal to a wide-character string literal if _UNICODE is defined.
*
* If _UNICODE is defined, the input string literal is prefixed with 'L', indicating it's a wide-character string literal.
* Otherwise, the input string literal remains unchanged.
*
* @param x The input string literal.
*/
# define IniT(x)            L##x

/**
 * @brief Macro that converts the input value to a string literal if _UNICODE is defined.
 *
 * If _UNICODE is defined, the input value is converted to a string literal using the '#' preprocessor operator.
 * Otherwise, the input value remains unchanged.
 *
 * @param x The input value.
 */
# define IniStringify(x)    L#x

#else

/**
 * @brief Macro that defines the type of IniParser based on whether the _UNICODE macro is defined.
 *
 * If _UNICODE is defined, IniParser is defined as IniParserW, which is the wide-character version of IniParser.
 * Otherwise, IniParser is defined as IniParserA, which is the ASCII-character version of IniParser.
 */
# define IniParser          IniParserA

/**
 * @brief Macro that defines the string type used by IniParser based on whether the _UNICODE macro is defined.
 *
 * If _UNICODE is defined, IniString is defined as std::wstring, which is the wide-character string type.
 * Otherwise, IniString is defined as std::string, which is the ASCII-character string type.
 */
# define IniString          std::string

/**
 * @brief Macro that defines the character type used by IniParser based on whether the _UNICODE macro is defined.
 *
 * If _UNICODE is defined, IniChar is defined as wchar_t, which is the wide-character type.
 * Otherwise, IniChar is defined as char, which is the ASCII-character type.
 */
# define IniChar            char

/**
* @brief Macro that converts the input string literal to a wide-character string literal if _UNICODE is defined.
*
* If _UNICODE is defined, the input string literal is prefixed with 'L', indicating it's a wide-character string literal.
* Otherwise, the input string literal remains unchanged.
*
* @param x The input string literal.
*/
# define IniT(x)            x

/**
 * @brief Macro that converts the input value to a string literal if _UNICODE is defined.
 *
 * If _UNICODE is defined, the input value is converted to a string literal using the '#' preprocessor operator.
 * Otherwise, the input value remains unchanged.
 *
 * @param x The input value.
 */
# define IniStringify(x)    #x

#endif

/**
 * @brief A macro that defines the type for INI file data.
 *
 * This macro defines the type for storing INI file data. It is a map of maps, where the outer map
 * represents the sections of the INI file, and the inner maps represent the key-value pairs within
 * each section. The type of the keys and values in the maps is determined by the IniString type.
 */
# define IniMap             std::map<IniString, std::map<IniString, IniString>>

#pragma endregion

/**
 * @brief A simple INI file parser class. <ASCII>
 */
class IniParserA {
public:
    /**
     * @brief Default constructor.
     */
    IniParserA() {}

private:

    /**
     * @brief Parse a single line from an INI file.
     *
     * This function extracts the section, key, and value from a single line
     * of an INI file and stores them in the data map.
     *
     * @param currentSection The current section being parsed.
     * @param line The line to parse.
     * @return True if the line was successfully parsed, false otherwise.
     */
    bool parse_line(std::string* currentSection, const std::string& line) {
        if (line.empty() || line[0] == ';') return false;
        if (line[0] == '[' && line.back() == ']') {
            *currentSection = line.substr(1, line.size() - 2);
            return false;
        }

        size_t equalPos = line.find('=');
        if (equalPos == std::string::npos) return false;

        std::string key = line.substr(0, equalPos);
        std::string value = line.substr(equalPos + 1);
        data[*currentSection][key] = value;
        return true;
    }

    /**
     * @brief Parse the contents of an INI file.
     *
     * This function parses the contents of an INI file and stores the key-value
     * pairs in the data map.
     *
     * @param content The content of the INI file.
     */
    void parse_raw(const std::string& content) {
        std::istringstream stringStream(content);

        std::string line;
        std::string currentSection;
        while (std::getline(stringStream, line)) {
            if (!this->parse_line(&currentSection, line)) {
                continue;
            }
        }
    }

    /**
     * @brief Parse an INI file.
     *
     * This function parses an INI file and stores the key-value pairs in the data map.
     *
     * @param filename The name of the INI file to parse.
     * @return True if the file was successfully parsed, false otherwise.
     */
    bool parse_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            //std::cerr << "Error: failed to open file " << filename << std::endl;
            return false;
        }

        std::string line;
        std::string currentSection;
        while (std::getline(file, line)) {
            if (!this->parse_line(&currentSection, line)) {
                continue;
            }
        }

        file.close();
        return true;
    }

    /**
     * @brief Get the value of a key in a section.
     *
     * This function returns the value of a key in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair.
     * @return The value of the key-value pair, or an empty string if the key does not exist.
     */
    std::string getValue(const std::string& section, const std::string& key) const {
        auto sectionIt = data.find(section);
        if (sectionIt != data.end()) {
            auto keyIt = sectionIt->second.find(key);
            if (keyIt != sectionIt->second.end()) {
                return keyIt->second;
            }
        }
        return "";
    }

    /**
     * @brief Set the value of a key in a section.
     *
     * This function sets the value of a key in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair.
     * @param value The value to set.
     */
    void setValue(const std::string& section, const std::string& key, const std::string& value) {
        data[section][key] = value;
    }

public:

    /**
     * @brief Commit changes to the INI file.
     *
     * This function writes the current data map to the specified INI file.
     *
     * @param filename The name of the INI file to write to.
     * @return True if the file was successfully written, false otherwise.
     */
    bool commit(const char* filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            //std::cerr << "Error: failed to open file " << filename << " for writing" << std::endl;
            return false;
        }

        // Write sections and key-value pairs to file
        for (const auto& section : data) {
            file << "[" << section.first << "]" << std::endl;
            for (const auto& pair : section.second) {
                file << pair.first << "=" << pair.second << std::endl;
            }
        }

        file.close();
        return true;
    }

    /**
     * @brief Parse an INI file.
     *
     * This function parses an INI file and stores the key-value pairs in the data map.
     *
     * @param filename The name of the INI file to parse.
     * @return True if the file was successfully parsed, false otherwise.
     */
    bool operator>>(const char* filename) {
        return this->parse_file(filename);
    }

    /**
     * @brief Parse an INI file.
     *
     * This function parses an INI file and stores the key-value pairs in the data map.
     *
     * @param content The content of the INI file.
     */
    void operator<<(const char* content) {
        this->parse_raw(content);
    }

    /**
     * @brief Get the value of a key in a section.
     *
     * This function returns the value of a key in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair.
     * @return The value of the key-value pair, or an empty string if the key does not exist.
     */
    template<typename __T__>
    __T__ get(const char* section, const char* var) {
        return static_cast<__T__>(this->getValue(section, var));
    }

    /**
     * @brief Set the value of a key in a section.
     *
     * This function sets the value of a key in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair.
     * @param value The value to set.
     */
    template <typename __T__>
    void set(const char* section, const char* var, const __T__& value) {

        std::ostringstream oss;
        oss << value;

        this->setValue(section, var, oss.str());
    }

    /**
     * @brief Check if a key exists in a section.
     *
     * This function checks if a key exists in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair.
     * @return True if the key exists, false otherwise.
     */
    bool exist(const char* section, const char* var) {
        return !getValue(section, var).empty();
    }

    /**
     * @brief Check if a section exists.
     *
     * This function checks if a section exists.
     *
     * @param section The section to check.
     * @return True if the section exists, false otherwise.
     */
    bool exist(const char* section) const {
        return data.find(section) != data.end();
    }

    /**
     * @brief Delete a key in a section.
     *
     * This function deletes a key in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair to delete.
     */
    void rem(const char* section, const char* key) {
        data[section].erase(key);
    }

    /**
     * @brief Delete a section.
     *
     * This function deletes a section and all its key-value pairs.
     *
     * @param section The section to delete.
     */
    void rem(const char* section) {
        data.erase(section);
    }

    /**
     * @brief Get the data map.
     *
     * This function returns the current data map.
     *
     * @return The current data map.
     */
    std::map<std::string, std::map<std::string, std::string>> map() {
        return this->data;
    }

    /**
     * @brief Conversion operator to IniMap (std::map<std::string, std::map<std::string, std::string>>).
     *
     * This conversion operator allows the IniParser class to be converted to a std::map<std::string, std::map<std::string, std::string>>.
     * It returns the current data map of the IniParser object.
     *
     * @return The current data map of the IniParser object.
     */
    operator std::map<std::string, std::map<std::string, std::string>>() {
        return this->map();
    }

    /**
     * @brief Equality comparison operator for IniParserA.
     *
     * This operator compares the data map of the current IniParserW object with that of another IniParserW object.
     * It returns true if the data maps are equal, and false otherwise.
     *
     * @param parser2 The IniParserA object to compare.
     * @return True if the data maps are equal, false otherwise.
     */
    bool operator==(IniParserA parser2) {
        return parser2.data == this->data;
    }

private:
    std::map<std::string, std::map<std::string, std::string>> data;
};

/**
 * @brief A simple INI file parser class. <WIDE>
 */
class IniParserW {
public:
    /**
     * @brief Default constructor.
     */
    IniParserW() {}

private:

    /**
     * @brief Parse a single line from an INI file.
     *
     * This function extracts the section, key, and value from a single line
     * of an INI file and stores them in the data map.
     *
     * @param currentSection The current section being parsed.
     * @param line The line to parse.
     * @return True if the line was successfully parsed, false otherwise.
     */
    bool parse_line(std::wstring* currentSection, const std::wstring& line) {
        if (line.empty() || line[0] == L';') return false;
        if (line[0] == L'[' && line.back() == L']') {
            *currentSection = line.substr(1, line.size() - 2);
            return false;
        }

        size_t equalPos = line.find(L'=');
        if (equalPos == std::wstring::npos) return false;

        std::wstring key = line.substr(0, equalPos);
        std::wstring value = line.substr(equalPos + 1);
        data[*currentSection][key] = value;
        return true;
    }

    /**
     * @brief Parse the contents of an INI file.
     *
     * This function parses the contents of an INI file and stores the key-value
     * pairs in the data map.
     *
     * @param content The content of the INI file.
     */
    void parse_raw(const std::wstring& content) {
        std::wistringstream stringStream(content);

        std::wstring line;
        std::wstring currentSection;
        while (std::getline(stringStream, line)) {
            if (!this->parse_line(&currentSection, line)) {
                continue;
            }
        }
    }

    /**
     * @brief Parse an INI file.
     *
     * This function parses an INI file and stores the key-value pairs in the data map.
     *
     * @param filename The name of the INI file to parse.
     * @return True if the file was successfully parsed, false otherwise.
     */
    bool parse_file(const std::wstring& filename) {
        std::wifstream file(filename);
        if (!file.is_open()) {
            //std::wcerr << L"Error: failed to open file " << filename << std::endl;
            return false;
        }

        std::wstring line;
        std::wstring currentSection;
        while (std::getline(file, line)) {
            if (!this->parse_line(&currentSection, line)) {
                continue;
            }
        }

        file.close();
        return true;
    }

    /**
     * @brief Get the value of a key in a section.
     *
     * This function returns the value of a key in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair.
     * @return The value of the key-value pair, or an empty string if the key does not exist.
     */
    std::wstring getValue(const std::wstring& section, const std::wstring& key) const {
        auto sectionIt = data.find(section);
        if (sectionIt != data.end()) {
            auto keyIt = sectionIt->second.find(key);
            if (keyIt != sectionIt->second.end()) {
                return keyIt->second;
            }
        }
        return L"";
    }

    /**
     * @brief Set the value of a key in a section.
     *
     * This function sets the value of a key in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair.
     * @param value The value to set.
     */
    void setValue(const std::wstring& section, const std::wstring& key, const std::wstring& value) {
        data[section][key] = value;
    }

public:

    /**
     * @brief Commit changes to the INI file.
     *
     * This function writes the current data map to the specified INI file.
     *
     * @param filename The name of the INI file to write to.
     * @return True if the file was successfully written, false otherwise.
     */
    bool commit(const wchar_t* filename) {
        std::wofstream file(filename);
        if (!file.is_open()) {
            //std::wcerr << L"Error: failed to open file " << filename << L" for writing" << std::endl;
            return false;
        }

        // Write sections and key-value pairs to file
        for (const auto& section : data) {
            file << L"[" << section.first << L"]" << std::endl;
            for (const auto& pair : section.second) {
                file << pair.first << L"=" << pair.second << std::endl;
            }
        }

        file.close();
        return true;
    }

    /**
     * @brief Parse an INI file.
     *
     * This function parses an INI file and stores the key-value pairs in the data map.
     *
     * @param filename The name of the INI file to parse.
     * @return True if the file was successfully parsed, false otherwise.
     */
    bool operator>>(const wchar_t* filename) {
        return this->parse_file(filename);
    }

    /**
     * @brief Parse an INI file.
     *
     * This function parses an INI file and stores the key-value pairs in the data map.
     *
     * @param content The content of the INI file.
     */
    void operator<<(const wchar_t* content) {
        this->parse_raw(content);
    }

    /**
     * @brief Get the value of a key in a section.
     *
     * This function returns the value of a key in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair.
     * @return The value of the key-value pair, or an empty string if the key does not exist.
     */
    template<typename __T__>
    __T__ get(const wchar_t* section, const wchar_t* var) {
        return static_cast<__T__>(this->getValue(section, var));
    }

    /**
     * @brief Set the value of a key in a section.
     *
     * This function sets the value of a key in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair.
     * @param value The value to set.
     */
    template <typename __T__>
    void set(const wchar_t* section, const wchar_t* var, const __T__& value) {

        std::wstringstream oss;
        oss << value;

        this->setValue(section, var, oss.str());
    }

    /**
     * @brief Check if a key exists in a section.
     *
     * This function checks if a key exists in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair.
     * @return True if the key exists, false otherwise.
     */
    bool exist(const wchar_t* section, const wchar_t* var) {
        return !getValue(section, var).empty();
    }

    /**
     * @brief Check if a section exists.
     *
     * This function checks if a section exists.
     *
     * @param section The section to check.
     * @return True if the section exists, false otherwise.
     */
    bool exist(const wchar_t* section) const {
        return data.find(section) != data.end();
    }

    /**
     * @brief Delete a key in a section.
     *
     * This function deletes a key in a section.
     *
     * @param section The section of the key-value pair.
     * @param key The key of the key-value pair to delete.
     */
    void rem(const wchar_t* section, const wchar_t* key) {
        data[section].erase(key);
    }

    /**
     * @brief Delete a section.
     *
     * This function deletes a section and all its key-value pairs.
     *
     * @param section The section to delete.
     */
    void rem(const wchar_t* section) {
        data.erase(section);
    }

    /**
     * @brief Get the data map.
     *
     * This function returns the current data map.
     *
     * @return The current data map.
     */
    std::map<std::wstring, std::map<std::wstring, std::wstring>> map() {
        return this->data;
    }

    /**
     * @brief Conversion operator to IniMap (std::map<std::wstring, std::map<std::wstring, std::wstring>>).
     *
     * This conversion operator allows the IniParser class to be converted to a std::map<std::wstring, std::map<std::wstring, std::wstring>>.
     * It returns the current data map of the IniParser object.
     *
     * @return The current data map of the IniParser object.
     */
    operator std::map<std::wstring, std::map<std::wstring, std::wstring>>() {
        return this->map();
    }

    /**
     * @brief Equality comparison operator for IniParserW.
     *
     * This operator compares the data map of the current IniParserW object with that of another IniParserW object.
     * It returns true if the data maps are equal, and false otherwise.
     *
     * @param parser2 The IniParserW object to compare.
     * @return True if the data maps are equal, false otherwise.
     */
    bool operator==(IniParserW parser2) {
        return parser2.data == this->data;
    }

private:
    std::map<std::wstring, std::map<std::wstring, std::wstring>> data;
};

#endif
