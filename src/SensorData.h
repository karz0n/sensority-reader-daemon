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
	using Ptr = std::unique_ptr<SensorData>;

    virtual ~SensorData() = default;

    virtual std::string format(const Formatter& formatter) const = 0;
};

#endif /* SENSORDATA_H_ */
