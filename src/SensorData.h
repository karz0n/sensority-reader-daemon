/*
 * SensorData.h
 *
 *  Created on: Mar 4, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORDATA_H_
#define SENSORDATA_H_

#include <memory>

#include "Formatter.h"
#include "SensorDataReadable.h"

/**
 * @brief The SensorData class
 */
class SensorData: public SensorDataReadable {
public:
    virtual ~SensorData() = default;

    /**
     * @brief format
     * @param formatter
     * @return
     */
    inline std::string format(const Formatter& formatter) const;

    /**
     * @brief values
     * @return
     */
    virtual Formatter::Values values() const = 0;
};

//
// Inlines
//

std::string SensorData::format(const Formatter& formatter) const
{
    return formatter.format(values());
}

#endif /* SENSORDATA_H_ */
