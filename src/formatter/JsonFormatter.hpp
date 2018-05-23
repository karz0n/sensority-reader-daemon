/*
 * JsonFormatter.hpp
 *
 *  Created on: Mar 20, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef JSONFORMATTER_HPP_
#define JSONFORMATTER_HPP_

#include "Formatter.hpp"

namespace formatter {

/**
 * @brief The JsonFormatter class
 */
class JsonFormatter : public Formatter {
public:
    inline Formats type() const override;
    std::string format(const Values& values) const override;
};

//
// Inlines
//

Formats JsonFormatter::type() const
{
    return Formats::json;
}

} // namespace formatter

#endif /* JSONFORMATTER_HPP_ */
