/*
 * StringFormatter.h
 *
 *  Created on: Mar 1, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef STRINGFORMATTER_H_
#define STRINGFORMATTER_H_

#include "Formatter.hpp"

/**
 * @brief The StringFormatter class
 */
class StringFormatter: public Formatter {
public:
    std::string format(const Values& values) const override;
};

#endif /* STRINGFORMATTER_H_ */
