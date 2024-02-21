#include "dict.hpp"

std::map<std::string, std::string> parseDictionaryA(const std::string& input)
{
	std::map<std::string, std::string> result;
	std::stringstream ss(input);
	char delimiter;

	ss >> delimiter;

	std::string token;
	while (std::getline(ss, token, ';')) {
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

std::map<std::wstring, std::wstring> parseDictionaryW(const std::wstring& input) {
	std::map<std::wstring, std::wstring> result;
	std::wstringstream ss(input);
	wchar_t delimiter;

	ss >> delimiter;

	std::wstring token;
	while (std::getline(ss, token, L';')) {
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

std::string dictionaryToStringA(const std::map<std::string, std::string>& dictionary)
{
	std::string result = "{";

	for (const auto& pair : dictionary) {
		result += pair.first + ": " + pair.second + ';' + " ";
	}

	if (!result.empty()) {
		result.pop_back();
		result.pop_back();
	}

	result += "}";
	return result;
}

std::wstring dictionaryToStringW(const std::map<std::wstring, std::wstring>& dictionary)
{
	std::wstring result = L"{";

	for (const auto& pair : dictionary) {
		result += pair.first + L": " + pair.second + L';' + L" ";
	}

	if (!result.empty()) {
		result.pop_back();
		result.pop_back();
	}

	result += L"}";
	return result;
}