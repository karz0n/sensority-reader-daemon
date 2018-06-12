/*!
 * \file JsonFormatter.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 20, 2018
 */

#include "JsonFormatter.hpp"

#include <sstream>

#include <Poco/Exception.h>
#include <Poco/JSON/PrintHandler.h>

namespace formatter {

std::string JsonFormatter::format(const Values& values) const
{
    std::ostringstream os;
    Poco::JSON::PrintHandler printer(os);

    printer.startObject();
    for (auto it = values.begin(); it != values.end(); ++it) {
        const std::string& name = it->first;
        const Value& value = it->second;

        printer.key(name);

        if (std::holds_alternative<int>(value)) {
            printer.value(std::get<int>(value));
            continue;
        }

        if (std::holds_alternative<double>(value)) {
            printer.value(std::get<double>(value));
            continue;
        }

        throw Poco::LogicException("Unsupported value type");
    }
    printer.endObject();

    return os.str();
}

} // namespace formatter
