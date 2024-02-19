
#include "dict.hpp"

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
std::map<std::string, std::string> parseDictionaryA(const std::string& input) {
	std::map<std::string, std::string> result;
	std::stringstream ss(input);
	char delimiter;

	ss >> delimiter;

	std::string token;
	while (std::getline(ss, token, ',')) {
		std::string key, value;

		std::size_t pos = token.find(':');

		key = token.substr(0, pos);
		value = token.substr(pos + 1);

		key.erase(0, key.find_first_not_of(" "));
		key.erase(key.find_last_not_of(" ") + 1);
		value.erase(0, value.find_first_not_of(" "));
		value.erase(value.find_last_not_of(" ") + 1);

		if (!value.empty() && value.back() == '}') {
			value.pop_back();
		}

		result[key] = value;
	}

	return result;
}

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
std::map<std::wstring, std::wstring> parseDictionaryW(const std::wstring& input) {
	std::map<std::wstring, std::wstring> result;
	std::wstringstream ss(input);
	wchar_t delimiter;

	ss >> delimiter;

	std::wstring token;
	while (std::getline(ss, token, L',')) {
		std::wstring key, value;

		std::size_t pos = token.find(L':');

		key = token.substr(0, pos);
		value = token.substr(pos + 1);

		key.erase(0, key.find_first_not_of(L" "));
		key.erase(key.find_last_not_of(L" ") + 1);
		value.erase(0, value.find_first_not_of(L" "));
		value.erase(value.find_last_not_of(L" ") + 1);

		if (!value.empty() && value.back() == '}') {
			value.pop_back();
		}

		result[key] = value;
	}

	return result;
}

/**
 * @brief Convert a std::map<std::string, std::string> into a string representation of a dictionary.
 *
 * This function converts a std::map<std::string, std::string> containing key-value pairs into a string representation of a dictionary.
 * Each key-value pair is separated by a comma and enclosed within curly braces.
 *
 * @param dictionary The std::map<std::string, std::string> to convert.
 * @return A string representation of the dictionary.
 */
std::string dictionaryToStringA(const std::map<std::string, std::string>& dictionary) {
	std::string result = "{";

	for (const auto& pair : dictionary) {
		result += pair.first + ": " + pair.second + ", ";
	}

	if (!result.empty()) {
		result.pop_back();
		result.pop_back();
	}

	result += "}";
	return result;
}

/**
 * @brief Convert a std::map<std::wstring, std::wstring> into a Unicode string representation of a dictionary.
 *
 * This function converts a std::map<std::wstring, std::wstring> containing key-value pairs into a Unicode string representation of a dictionary.
 * Each key-value pair is separated by a comma and enclosed within curly braces.
 *
 * @param dictionary The std::map<std::wstring, std::wstring> to convert.
 * @return A Unicode string representation of the dictionary.
 */
std::wstring dictionaryToStringW(const std::map<std::wstring, std::wstring>& dictionary) {
	std::wstring result = L"{";

	for (const auto& pair : dictionary) {
		result += pair.first + L": " + pair.second + L", ";
	}

	if (!result.empty()) {
		result.pop_back();
		result.pop_back();
	}

	result += L"}";
	return result;
}

#ifdef _UNICODE

/**
 * @brief Macro defining the function name for parsing a Unicode string representing a dictionary.
 */
# define IniDictParse        parseDictionaryW
 /**
  * @brief Macro defining the function name for converting a dictionary to a Unicode string representation.
  */
# define IniDictToStr        dictionaryToStringW

#else

/**
 * @brief Macro defining the function name for parsing a string representing a dictionary.
 */
# define IniDictParse        parseDictionaryA
 /**
  * @brief Macro defining the function name for converting a dictionary to a string representation.
  */
# define IniDictToStr        dictionaryToStringA

#endif