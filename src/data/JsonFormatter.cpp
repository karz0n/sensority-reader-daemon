/*!
 * \file JsonFormatter.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 20, 2018
 */

#include "JsonFormatter.hpp"

#include <sstream>

#include <Poco/JSON/PrintHandler.h>

using Poco::JSON::PrintHandler;

namespace
{
void formatItems(Poco::JSON::PrintHandler& printer, const data::StorageValueItems& items)
{
    if (items.empty()) {
        return;
    }

    printer.startObject();
    for (const auto& item : items) {
        const auto& n = item.first;
        const auto& d = item.second;
        printer.key(n);
        std::visit([&] (auto&& v) {
            printer.value(v);
        }, d);
    }
    printer.endObject();
}
}

namespace data {

std::string JsonFormatter::format(const StorageValueItems& items) const
{
    std::ostringstream os;
    PrintHandler printer(os);
    formatItems(printer, items);
    return os.str();
}

std::string JsonFormatter::format(const StorageValueItemsGroup& group) const
{
    if (group.empty()) {
        return std::string{};
    }

    std::ostringstream os;
    PrintHandler printer(os);
    printer.startObject();
    for (const auto& groupPair : group) {
        const auto& n = groupPair.first;
        const auto& i = groupPair.second;
        printer.key(n);
        formatItems(printer, i);
    }
    printer.endObject();
    return os.str();
}

} // namespace data
