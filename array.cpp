#include "array.hpp"

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
std::vector<std::string> parseArrayA(const std::string& input) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    char delimiter;
    ss >> delimiter;

    std::string temp;
    while (std::getline(ss, temp, ',')) {
        temp.erase(0, temp.find_first_not_of(" "));
        temp.erase(temp.find_last_not_of(" ") + 1);
        if (!temp.empty() && temp.back() == ']') {
            temp.pop_back();
        }
        result.push_back(temp);
    }

    return result;
}

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
std::vector<std::wstring> parseArrayW(const std::wstring& input) {
    std::vector<std::wstring> result;
    std::wstringstream ss(input);
    wchar_t delimiter;
    ss >> delimiter;

    std::wstring temp;
    while (std::getline(ss, temp, L',')) {
        temp.erase(0, temp.find_first_not_of(L" "));
        temp.erase(temp.find_last_not_of(L" ") + 1);
        if (!temp.empty() && temp.back() == L']') {
            temp.pop_back();
        }
        result.push_back(temp);
    }

    return result;
}

/**
 * @brief Convert a std::vector<std::string> into a string representation of an array.
 *
 * This function converts a std::vector<std::string> containing elements into a string representation of an array,
 * where elements are separated by commas and enclosed within square brackets.
 *
 * @param elements The std::vector<std::string> to convert.
 * @return A string representation of the array.
 */
std::string arrayToStringA(const std::vector<std::string>& elements) {
    std::string result = "[";

    for (std::size_t i = 0; i < elements.size(); ++i) {
        result += elements[i];
        if (i != elements.size() - 1) {
            result += ", ";
        }
    }

    result += "]";
    return result;
}

/**
 * @brief Convert a std::vector<std::wstring> into a Unicode string representation of an array.
 *
 * This function converts a std::vector<std::wstring> containing elements into a Unicode string representation of an array,
 * where elements are separated by commas and enclosed within square brackets.
 *
 * @param elements The std::vector<std::wstring> to convert.
 * @return A Unicode string representation of the array.
 */
std::wstring arrayToStringW(const std::vector<std::wstring>& elements) {
    std::wstring result = L"[";

    for (std::size_t i = 0; i < elements.size(); ++i) {
        result += elements[i];
        if (i != elements.size() - 1) {
            result += L", ";
        }
    }

    result += L"]";
    return result;
}