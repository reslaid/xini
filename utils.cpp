#include "utils.hpp"

/**
 * @brief Convert a wide-character map to an ASCII map.
 *
 * This function converts a map containing wide-character strings to a map containing ASCII strings.
 *
 * @param wmap The wide-character map to convert.
 * @return The corresponding ASCII map.
 */
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

/**
 * @brief Convert an ASCII map to a wide-character map.
 *
 * This function converts a map containing ASCII strings to a map containing wide-character strings.
 *
 * @param amap The ASCII map to convert.
 * @return The corresponding wide-character map.
 */
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

/**
 * @brief Convert an IniParserA object to an IniParserW object.
 *
 * This function converts an IniParserA object to an IniParserW object.
 *
 * @param asciiParser The IniParserA object to convert.
 * @return The converted IniParserW object.
 */
IniParserW ToIniParserW(IniParserA& asciiParser) {
	IniParserW wideParser;
	wideParser.loadmap(AMapToWMap(asciiParser.map()));
	return wideParser;
}

/**
 * @brief Convert an IniParserW object to an IniParserA object.
 *
 * This function converts an IniParserW object to an IniParserA object.
 *
 * @param wideParser The IniParserW object to convert.
 * @return The converted IniParserA object.
 */
IniParserA ToIniParserA(IniParserW& wideParser) {
	IniParserA asciiParser;
	asciiParser.loadmap(WMapToAMap(wideParser.map()));
	return asciiParser;
}

/**
 * @brief Merge multiple IniParserA objects into one.
 *
 * This function merges multiple IniParserA objects into one.
 *
 * @param parser1 The first IniParserA object to merge.
 * @param parser2 The second IniParserA object to merge.
 * @param ... Additional IniParserA objects to merge.
 * @return The merged IniParserA object.
 */
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

/**
 * @brief Merge multiple IniParserW objects into one.
 *
 * This function merges multiple IniParserW objects into one.
 *
 * @param parser1 The first IniParserW object to merge.
 * @param parser2 The second IniParserW object to merge.
 * @param ... Additional IniParserW objects to merge.
 * @return The merged IniParserW object.
 */
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