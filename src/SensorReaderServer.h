/*
 * SensorReaderServer.h
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef SENSORREADERSERVER_H_
#define SENSORREADERSERVER_H_

#include "SensorReader.h"
#include "SensorDataStorage.h"

/**
 * @brief The SensorReaderServer class
 * Base class of sensor reader server
 */
class SensorReaderServer {
protected:
    SensorReaderServer(SensorReader::Ptr reader);
    virtual ~SensorReaderServer();

    SensorReaderServer(const SensorReaderServer&) = delete;
    SensorReaderServer& operator=(const SensorReaderServer&) = delete;

    virtual bool isRunned() const;
    virtual void run();
    virtual void shutdown();

    inline SensorReader& reader() const;
    inline const SensorDataStorage& storage() const;

private:
    SensorReader::Ptr _reader;
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
