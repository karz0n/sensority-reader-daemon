/*
 * HttpSensorReaderServer.h
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef HTTPSENSORREADERSERVER_H_
#define HTTPSENSORREADERSERVER_H_

#include <memory>

#include <Poco/Net/HTTPServer.h>

#include "formatter/Formatter.hpp"
#include "sensor/SensorReaderServer.hpp"
#include "sensor/SensorReader.hpp"

/**
 * @brief The HttpSensorReaderServer class
 */
class HttpSensorReaderServer: public SensorReaderServer {
public:
    HttpSensorReaderServer(std::unique_ptr<SensorReader> reader, unsigned short port);
    ~HttpSensorReaderServer() override;

    HttpSensorReaderServer(const HttpSensorReaderServer&) = delete;
    HttpSensorReaderServer& operator=(const HttpSensorReaderServer&) = delete;

    bool isRunned() const override;
    void run() override;
	void shutdown() override;

private:
    std::unique_ptr<Formatter> _formatter;
    std::unique_ptr<Poco::Net::HTTPServer> _server;
    bool _runned;
};

#endif /* HTTPSENSORREADERSERVER_H_ */
