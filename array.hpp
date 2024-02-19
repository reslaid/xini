#pragma once

#include <vector>
#include <sstream>

/**
 * @brief Parse a string representing an array into a std::vector<std::string>.
 *
 * This function parses a string input representing an array of elements into a std::vector<std::string>.
 * The input string should have the format "[element1, element2, ...]".
 * Each element is trimmed of leading and trailing whitespaces.
 *
 * @param input The input string representing the array.
 * @return A std::vector<std::string> containing the parsed elements.
 */
std::vector<std::string> parseArrayA(const std::string& input);

/**
 * @brief Parse a Unicode string representing an array into a std::vector<std::wstring>.
 *
 * This function parses a Unicode string input representing an array of elements into a std::vector<std::wstring>.
 * The input string should have the format "[element1, element2, ...]".
 * Each element is trimmed of leading and trailing whitespaces.
 *
 * @param input The Unicode input string representing the array.
 * @return A std::vector<std::wstring> containing the parsed elements.
 */
std::vector<std::wstring> parseArrayW(const std::wstring& input);

/**
 * @brief Convert a std::vector<std::string> into a string representation of an array.
 *
 * This function converts a std::vector<std::string> containing elements into a string representation of an array,
 * where elements are separated by commas and enclosed within square brackets.
 *
 * @param elements The std::vector<std::string> to convert.
 * @return A string representation of the array.
 */
std::string arrayToStringA(const std::vector<std::string>& elements);

/**
 * @brief Convert a std::vector<std::wstring> into a Unicode string representation of an array.
 *
 * This function converts a std::vector<std::wstring> containing elements into a Unicode string representation of an array,
 * where elements are separated by commas and enclosed within square brackets.
 *
 * @param elements The std::vector<std::wstring> to convert.
 * @return A Unicode string representation of the array.
 */
std::wstring arrayToStringW(const std::vector<std::wstring>& elements);

#ifdef _UNICODE

/**
 * @brief Macro defining the function name for parsing a Unicode string representing an array.
 */
# define IniArrayParse      parseArrayW
 /**
  * @brief Macro defining the function name for converting an array to a Unicode string representation.
  */
# define IniArrayToStr      arrayToStringW

#else

/**
 * @brief Macro defining the function name for parsing a string representing an array.
 */
# define IniArrayParse      parseArrayA
 /**
  * @brief Macro defining the function name for converting an array to a string representation.
  */
# define IniArrayToStr      arrayToStringA

#endif