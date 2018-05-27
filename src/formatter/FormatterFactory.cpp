/*
 * FormatterFactory.cpp
 *
 *  Created on: May 27, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "FormatterFactory.hpp"

#include <Poco/Exception.h>
#include <Poco/String.h>

#include "JsonFormatter.hpp"
#include "StringFormatter.hpp"

namespace formatter {

Formatter::Ptr FormatterFactory::create(const std::string& format)
{
    std::string f = Poco::trim(Poco::toLower(format));

    if (f == "json") {
        return Formatter::create<JsonFormatter>();
    }
    if (f == "string") {
        return Formatter::create<StringFormatter>();
    }

    throw Poco::InvalidArgumentException("Unknown format type string value");
}

} // namespace formatter
