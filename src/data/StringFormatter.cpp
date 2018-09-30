/*!
 * \file StringFormatter.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 1, 2018
 */

#include "StringFormatter.hpp"

#include <type_traits>
#include <sstream>

#include <Poco/Exception.h>
#include <Poco/Format.h>

template<class T>
struct always_false : std::false_type {};

namespace
{
void formatItems(std::ostringstream& os, const data::StorageValueItems& items)
{
    if (items.empty()) {
        return;
    }

    for (const auto& item : items) {
        const auto& n = item.first;
        const auto& d = item.second;
        std::visit([&] (auto&& v) {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, int>) {
                os << Poco::format("%s = %d", n, v);
            }
            else if constexpr (std::is_same_v<T, double>) {
                os << Poco::format("%s = %.1f", n, v);
            }
            else {
                static_assert(always_false<T>::value, "unsupported type");
            }
        }, d);
    }
}
}

namespace data {

std::string StringFormatter::format(const StorageValueItems& items) const
{
    std::ostringstream os;
    formatItems(os, items);
    return os.str();
}

std::string StringFormatter::format(const StorageValueItemsGroup& group) const
{
    if (group.empty()) {
        return std::string{};
    }

    std::ostringstream os;
    for (const auto& groupPair : group) {
        const auto& n = groupPair.first;
        const auto& i = groupPair.second;
        os << "[" << n << "]" << std::endl;
        formatItems(os, i);
    }
    return os.str();
}

} // namespace data
