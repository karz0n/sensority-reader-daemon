/*
 * SensorReaderServer.h
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADERSERVER_H_
#define SENSORREADERSERVER_H_

#include <memory>

#include "sensor/SensorReader.hpp"
#include "sensor/SensorDataStorage.hpp"

/**
 * @brief The SensorReaderServer class
 * Base class of sensor reader server
 */
class SensorReaderServer {
protected:
    SensorReaderServer(std::unique_ptr<SensorReader> reader);
    virtual ~SensorReaderServer();

    SensorReaderServer(const SensorReaderServer&) = delete;
    SensorReaderServer& operator=(const SensorReaderServer&) = delete;

    virtual bool isRunned() const;
    virtual void run();
    virtual void shutdown();

    inline SensorReader& reader() const;
    inline const SensorDataStorage& storage() const;

private:
    std::unique_ptr<SensorReader> _reader;
};

//
// Inlines
//

SensorReader& SensorReaderServer::reader() const
{
    return *_reader;
}

const SensorDataStorage& SensorReaderServer::storage() const
{
    return *_reader->storage();
}

#endif /* SENSORREADERSERVER_H_ */
