/*
 * SensorDataReadable.hpp
 *
 *  Created on: Mar 23, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORDATAREADABLE_H
#define SENSORDATAREADABLE_H

#include <string>

#include "Formatter.hpp"

/**
 * @brief The SensorDataReadable class
 */
class SensorDataReadable {
public:
    virtual ~SensorDataReadable() = default;

    virtual std::string format(const Formatter& formatter) const = 0;
};

#endif // SENSORDATAREADABLE_H
