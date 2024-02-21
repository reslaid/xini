#include "utils.hpp"

static std::map<std::string, std::map<std::string, std::string>> WMapToAMap(const std::map<std::wstring, std::map<std::wstring, std::wstring>>& wmap) {
	std::map<std::string, std::map<std::string, std::string>> amap;
	for (const auto& wsection : wmap) {
		std::string asection(wsection.first.begin(), wsection.first.end());
		std::map<std::string, std::string> ainnerMap;
		for (const auto& wpair : wsection.second) {
			std::string akey(wpair.first.begin(), wpair.first.end());
			std::string avalue(wpair.second.begin(), wpair.second.end());
			ainnerMap[akey] = avalue;
		}
		amap[asection] = ainnerMap;
	}
	return amap;
}

static std::map<std::wstring, std::map<std::wstring, std::wstring>> AMapToWMap(const std::map<std::string, std::map<std::string, std::string>>& amap) {
	std::map<std::wstring, std::map<std::wstring, std::wstring>> wmap;
	for (const auto& asection : amap) {
		std::wstring wsection(asection.first.begin(), asection.first.end());
		std::map<std::wstring, std::wstring> winnerMap;
		for (const auto& apair : asection.second) {
			std::wstring wkey(apair.first.begin(), apair.first.end());
			std::wstring wvalue(apair.second.begin(), apair.second.end());
			winnerMap[wkey] = wvalue;
		}
		wmap[wsection] = winnerMap;
	}
	return wmap;
}

IniParserW ToIniParserW(IniParserA& asciiParser) {
	IniParserW wideParser;
	wideParser.loadmap(AMapToWMap(asciiParser.map()));
	return wideParser;
}

IniParserA ToIniParserA(IniParserW& wideParser) {
	IniParserA asciiParser;
	asciiParser.loadmap(WMapToAMap(wideParser.map()));
	return asciiParser;
}

IniParserA MergeIniParsersA(IniParserA parser1, IniParserA parser2, ...) {
	IniParserA mergedParser = parser1;

	va_list args;
	va_start(args, parser2);
	IniParserA* currentParser = &parser2;

	while (currentParser != nullptr) {
		for (const auto& section : currentParser->map()) {
			for (const auto& pair : section.second) {
				mergedParser.set(section.first.c_str(), pair.first.c_str(), pair.second);
			}
		}
		currentParser = va_arg(args, IniParserA*);
	}
	va_end(args);

	return mergedParser;
}

IniParserW MergeIniParsersW(IniParserW parser1, IniParserW parser2, ...) {
	IniParserW mergedParser = parser1;

	va_list args;
	va_start(args, parser2);
	IniParserW* currentParser = &parser2;

	while (currentParser != nullptr) {
		for (const auto& section : currentParser->map()) {
			for (const auto& pair : section.second) {
				mergedParser.set(section.first.c_str(), pair.first.c_str(), pair.second);
			}
		}
		currentParser = va_arg(args, IniParserW*);
	}
	va_end(args);

	return mergedParser;
}