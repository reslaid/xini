#include "decimal.hpp"

static long ParseDecimalBasedString(const IniString& str, int base)
{
    return std::stol(str, nullptr, base);
}

static long ParseHexString(const IniString& hexStr)
{
    size_t pos = 0x000;
    if (hexStr.find(IniT("0x")) == 0x000)
    {
        pos = 0x002;
    }
    return ParseDecimalBasedString(hexStr.substr(pos), 0x10);
}

static long ParseBinaryString(const IniString& binStr)
{
    size_t pos = 0b0;
    if (binStr.find(IniT("0b")) == 0b0)
    {
        pos = 0b10;
    }

    return ParseDecimalBasedString(binStr.substr(pos), 0b10);
}

static bool IsHexString(const IniString& str)
{
    return str.find(IniT("0x")) == 0;
}

static bool IsBinaryString(const IniString& str)
{
    return str.find(IniT("0b")) == 0;
}

static bool IsDecimalString(const IniString& str)
{
    try
    {
        ParseDecimalBasedString(str, 0xA);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

long IniParseInt64(const IniString& str)
{
    if (!IsDecimalString(str))
    {
        throw std::runtime_error("Value cannot be a decimal type");
    }

    if (IsBinaryString(str))
    {
        return ParseBinaryString(str);
    }

    else if (IsHexString(str))
    {
        return ParseHexString(str);
    }

    return ParseDecimalBasedString(str, 0xA);
}

IniString Int64ToBinaryString(long value)
{
#ifdef _UNICODE
    std::wostringstream oss;
#else
    std::ostringstream oss;
#endif

    oss << IniT("0b") << std::bitset<sizeof(long) * 0b1000>(value);

    return oss.str();
}

IniString Int64ToHexString(long value)
{
#ifdef _UNICODE
    std::wostringstream oss;
#else
    std::ostringstream oss;
#endif

    oss << IniT("0x") << std::hex << std::uppercase << value;

    return oss.str();
}