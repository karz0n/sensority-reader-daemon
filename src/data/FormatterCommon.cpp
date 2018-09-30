/*!
 * \file FormatterCommon.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Sep 09, 2018
 */

#include "FormatterCommon.hpp"

#include <regex>

#include <Poco/Exception.h>
#include <Poco/String.h>

namespace data {

/*!
 * \addtogroup data
 * @{
 */

bool verifyOutputFormat(const std::string& value)
{
    static std::regex re("^text|json$", std::regex_constants::icase);
    return std::regex_match(value, re);
}

OutputFormats translateOutputFormat(const std::string& value)
{
    std::string s = Poco::toLower(Poco::trim(value));

    if (s == "text") {
        return OutputFormats::text;
    }
    if (s == "json") {
        return OutputFormats::json;
    }

    throw Poco::InvalidArgumentException("Unknown format type string value");
}

/*! @} */

} // namespace data
