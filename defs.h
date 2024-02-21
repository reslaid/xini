#pragma once

#include <string>

#if defined(_UNICODE)

/**
 * @brief Macro that defines the string type used by IniParser based on whether the _UNICODE macro is defined.
 *
 * If _UNICODE is defined, IniString is defined as std::wstring, which is the wide-character string type.
 * Otherwise, IniString is defined as std::string, which is the ASCII-character string type.
 */
# define IniString          std::wstring

/**
 * @brief Macro that defines the character type used by IniParser based on whether the _UNICODE macro is defined.
 *
 * If _UNICODE is defined, IniChar is defined as wchar_t, which is the wide-character type.
 * Otherwise, IniChar is defined as char, which is the ASCII-character type.
 */
# define IniChar            wchar_t

/**
* @brief Macro that converts the input string literal to a wide-character string literal if _UNICODE is defined.
*
* If _UNICODE is defined, the input string literal is prefixed with 'L', indicating it's a wide-character string literal.
* Otherwise, the input string literal remains unchanged.
*
* @param x The input string literal.
*/
# define IniT(x)            L##x

/**
 * @brief Macro that converts the input value to a string literal if _UNICODE is defined.
 *
 * If _UNICODE is defined, the input value is converted to a string literal using the '#' preprocessor operator.
 * Otherwise, the input value remains unchanged.
 *
 * @param x The input value.
 */
# define IniStringify(x)    L#x

#else

/**
 * @brief Macro that defines the string type used by IniParser based on whether the _UNICODE macro is defined.
 *
 * If _UNICODE is defined, IniString is defined as std::wstring, which is the wide-character string type.
 * Otherwise, IniString is defined as std::string, which is the ASCII-character string type.
 */
# define IniString          std::string

/**
 * @brief Macro that defines the character type used by IniParser based on whether the _UNICODE macro is defined.
 *
 * If _UNICODE is defined, IniChar is defined as wchar_t, which is the wide-character type.
 * Otherwise, IniChar is defined as char, which is the ASCII-character type.
 */
# define IniChar            char

/**
* @brief Macro that converts the input string literal to a wide-character string literal if _UNICODE is defined.
*
* If _UNICODE is defined, the input string literal is prefixed with 'L', indicating it's a wide-character string literal.
* Otherwise, the input string literal remains unchanged.
*
* @param x The input string literal.
*/
# define IniT(x)            x

/**
 * @brief Macro that converts the input value to a string literal if _UNICODE is defined.
 *
 * If _UNICODE is defined, the input value is converted to a string literal using the '#' preprocessor operator.
 * Otherwise, the input value remains unchanged.
 *
 * @param x The input value.
 */
# define IniStringify(x)    #x

#endif

#define IniNullPtr			void*