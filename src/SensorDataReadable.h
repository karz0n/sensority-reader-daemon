#ifndef SENSORDATAREADABLE_H
#define SENSORDATAREADABLE_H

#include <string>

#include "Formatter.h"

/**
 * @brief The SensorDataReadable class
 */
class SensorDataReadable {
public:
    virtual ~SensorDataReadable() = default;

    virtual std::string format(const Formatter& formatter) const = 0;
};

#endif // SENSORDATAREADABLE_H
