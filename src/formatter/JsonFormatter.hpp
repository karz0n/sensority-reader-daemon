/*
 * JsonFormatter.h
 *
 *  Created on: Mar 20, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef JSONFORMATTER_H_
#define JSONFORMATTER_H_

#include "Formatter.hpp"

/**
 * @brief The JsonFormatter class
 */
class JsonFormatter: public Formatter {
public:
	std::string format(const Values& values) const override;
};

#endif /* JSONFORMATTER_H_ */
