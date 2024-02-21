#pragma once

#include <sstream>
#include <bitset>

#include "defs.h"

/**
 * @brief Parses a string representing a decimal-based number into a long integer.
 *
 * @param str The string to parse.
 * @param base The base of the number system used in the string.
 * @return The parsed long integer value.
 */
static long ParseDecimalBasedString(const IniString& str, int base);

/**
 * @brief Parses a string representing a hexadecimal number into a long integer.
 *
 * @param hexStr The string to parse.
 * @return The parsed long integer value.
 */
static long ParseHexString(const IniString& hexStr);

/**
 * @brief Parses a string representing a binary number into a long integer.
 *
 * @param binStr The string to parse.
 * @return The parsed long integer value.
 */
static long ParseBinaryString(const IniString& binStr);

/**
 * @brief Checks if a string represents a hexadecimal number.
 *
 * @param str The string to check.
 * @return True if the string represents a hexadecimal number, otherwise false.
 */
static bool IsHexString(const IniString& str);

/**
 * @brief Checks if a string represents a binary number.
 *
 * @param str The string to check.
 * @return True if the string represents a binary number, otherwise false.
 */
static bool IsBinaryString(const IniString& str);

/**
 * @brief Checks if a string represents a decimal number.
 *
 * @param str The string to check.
 * @return True if the string represents a decimal number, otherwise false.
 */
static bool IsDecimalString(const IniString& str);

/**
 * @brief Parses a string representing a number into a long integer.
 *
 * @param str The string to parse.
 * @return The parsed long integer value.
 */
long IniParseInt64(const IniString& str);

/**
 * @brief Converts a long integer value into a binary string representation.
 *
 * @param value The long integer value to convert.
 * @return The binary string representation of the value.
 */
IniString Int64ToBinaryString(long value);

/**
 * @brief Converts a long integer value into a hexadecimal string representation.
 *
 * @param value The long integer value to convert.
 * @return The hexadecimal string representation of the value.
 */
IniString Int64ToHexString(long value);
