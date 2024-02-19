#pragma once

#pragma region              includes

#include                    <cstdarg>
#include                    <locale>
#include                    <codecvt>

#include                    "parser.hpp"

#pragma endregion

#pragma region			macros

#if defined(_UNICODE)

/**
 * @brief Macro that defines the function to merge IniParserW objects.
 */
# define IniMerge          MergeIniParsersW

/**
 * @brief Macro that defines the function to convert from IniParserA to IniParserW.
 */
# define IniParserT        ToIniParserW

#else

/**
 * @brief Macro that defines the function to merge IniParserA objects.
 */
# define IniMerge          MergeIniParsersA

/**
 * @brief Macro that defines the function to convert from IniParserW to IniParserA.
 */
# define IniParserT        ToIniParserA

#endif

#pragma endregion

/**
 * @brief Convert a wide-character map to an ASCII map.
 *
 * This function converts a map containing wide-character strings to a map containing ASCII strings.
 *
 * @param wmap The wide-character map to convert.
 * @return The corresponding ASCII map.
 */
static std::map<std::string, std::map<std::string, std::string>> WMapToAMap(const std::map<std::wstring, std::map<std::wstring, std::wstring>>& wmap);

/**
 * @brief Convert an ASCII map to a wide-character map.
 *
 * This function converts a map containing ASCII strings to a map containing wide-character strings.
 *
 * @param amap The ASCII map to convert.
 * @return The corresponding wide-character map.
 */
static std::map<std::wstring, std::map<std::wstring, std::wstring>> AMapToWMap(const std::map<std::string, std::map<std::string, std::string>>& amap);

/**
 * @brief Convert an IniParserA object to an IniParserW object.
 *
 * This function converts an IniParserA object to an IniParserW object.
 *
 * @param asciiParser The IniParserA object to convert.
 * @return The converted IniParserW object.
 */
IniParserW ToIniParserW(IniParserA& asciiParser);

/**
 * @brief Convert an IniParserW object to an IniParserA object.
 *
 * This function converts an IniParserW object to an IniParserA object.
 *
 * @param wideParser The IniParserW object to convert.
 * @return The converted IniParserA object.
 */
IniParserA ToIniParserA(IniParserW& wideParser);

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
IniParserA MergeIniParsersA(IniParserA parser1, IniParserA parser2, ...);

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
IniParserW MergeIniParsersW(IniParserW parser1, IniParserW parser2, ...);