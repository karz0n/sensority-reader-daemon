/*!
 * \file FormatterFactory.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date May 27, 2018
 */

#include "FormatterFactory.hpp"

#include <Poco/Exception.h>

#include "JsonFormatter.hpp"
#include "StringFormatter.hpp"

namespace data {

Formatter::Ptr FormatterFactory::create(OutputFormats format)
{
    if (format == OutputFormats::json) {
        return Formatter::create<JsonFormatter>();
    }
    if (format == OutputFormats::text) {
        return Formatter::create<StringFormatter>();
    }

    throw Poco::InvalidArgumentException("Unknown format type string value");
}

} // namespace data
