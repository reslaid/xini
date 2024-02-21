#pragma once

#include <string>
#include <sstream>
#include <map>

#include "defs.h"

/**
 * @brief Parse a string representing a dictionary into a std::map<std::string, std::string>.
 *
 * This function parses a string input representing a dictionary of key-value pairs into a std::map<std::string, std::string>.
 * The input string should have the format "{key1: value1, key2: value2}".
 * Each key and value are trimmed of leading and trailing whitespaces.
 *
 * @param input The input string representing the dictionary.
 * @return A std::map<std::string, std::string> containing the parsed key-value pairs.
 */
std::map<std::string, std::string> parseDictionaryA(const std::string& input);

/**
 * @brief Parse a Unicode string representing a dictionary into a std::map<std::wstring, std::wstring>.
 *
 * This function parses a Unicode string input representing a dictionary of key-value pairs into a std::map<std::wstring, std::wstring>.
 * The input string should have the format "{key1: value1, key2: value2}".
 * Each key and value are trimmed of leading and trailing whitespaces.
 *
 * @param input The Unicode input string representing the dictionary.
 * @return A std::map<std::wstring, std::wstring> containing the parsed key-value pairs.
 */
std::map<std::wstring, std::wstring> parseDictionaryW(const std::wstring& input);

/**
 * @brief Convert a std::map<std::string, std::string> into a string representation of a dictionary.
 *
 * This function converts a std::map<std::string, std::string> containing key-value pairs into a string representation of a dictionary.
 * Each key-value pair is separated by a comma and enclosed within curly braces.
 *
 * @param dictionary The std::map<std::string, std::string> to convert.
 * @return A string representation of the dictionary.
 */
std::string dictionaryToStringA(const std::map<std::string, std::string>& dictionary);

/**
 * @brief Convert a std::map<std::wstring, std::wstring> into a Unicode string representation of a dictionary.
 *
 * This function converts a std::map<std::wstring, std::wstring> containing key-value pairs into a Unicode string representation of a dictionary.
 * Each key-value pair is separated by a comma and enclosed within curly braces.
 *
 * @param dictionary The std::map<std::wstring, std::wstring> to convert.
 * @return A Unicode string representation of the dictionary.
 */
std::wstring dictionaryToStringW(const std::map<std::wstring, std::wstring>& dictionary);

/**
* @brief Separator character for INI format dictionaries.
*/
#define IniDictSplitCharA		','

/**
* @brief Separator character for INI format dictionaries.
*/
#define IniDictSplitCharW		IniT(',')

#ifdef _UNICODE

/**
 * @brief Macro defining the function name for parsing a Unicode string representing a dictionary.
 */
# define IniDictParse			parseDictionaryW
 /**
  * @brief Macro defining the function name for converting a dictionary to a Unicode string representation.
  */
# define IniDictToStr			dictionaryToStringW

#else

/**
 * @brief Macro defining the function name for parsing a string representing a dictionary.
 */
# define IniDictParse			parseDictionaryA
 /**
  * @brief Macro defining the function name for converting a dictionary to a string representation.
  */
# define IniDictToStr			dictionaryToStringA

#endif