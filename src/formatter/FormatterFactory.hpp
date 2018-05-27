/*
 * FormatterFactory.hpp
 *
 *  Created on: May 27, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef FORMATTERFACTORY_HPP_
#define FORMATTERFACTORY_HPP_

#include "Formatter.hpp"

namespace formatter {

class FormatterFactory
{
public:
    static Formatter::Ptr create(const std::string& format);
};

} // namespace formatter

#endif // FORMATTERFACTORY_HPP_
