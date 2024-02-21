#include "array.hpp"

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