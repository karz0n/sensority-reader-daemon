/*!
 * \file Storage.cpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 16, 2018
 */

#include "Storage.hpp"

namespace data {

Storage::Storage(const std::string& name)
    : _name{name}
{ }

std::string Storage::format(const Formatter& formatter) const
{
    return formatter.format(extract());
}

} // namespace data
