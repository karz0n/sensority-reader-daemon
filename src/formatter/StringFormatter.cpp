/*
 * StringFormatter.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#include "StringFormatter.hpp"

#include <sstream>

#include <Poco/Exception.h>
#include <Poco/Format.h>

namespace formatter {

std::string StringFormatter::format(const Values& values) const
{
    std::ostringstream os;

    for (Values::const_iterator it = values.begin(); it != values.end(); ++it) {
        const std::string& name = it->first;
        const Value& value = it->second;

        if (it != values.begin()) {
            os << ", ";
        }

        if (std::holds_alternative<int>(value)) {
            os << Poco::format("%s = %d", name, std::get<int>(value));
            continue;
        }

        if (std::holds_alternative<double>(value)) {
            os << Poco::format("%s = %.1f", name, std::get<double>(value));
            continue;
        }

        throw Poco::LogicException("Unsupported value type");
    }

    return os.str();
}

} // namespace formatter
