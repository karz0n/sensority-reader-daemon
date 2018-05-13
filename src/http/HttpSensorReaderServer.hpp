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

#include <formatter/Formatter.hpp>
#include "sensor/SensorDataReadable.hpp"

/**
 * @brief The HttpSensorReaderServer class
 */
class HttpSensorReaderServer {
public:
    HttpSensorReaderServer(
            unsigned short port,
            std::shared_ptr<SensorDataReadable> data);
    ~HttpSensorReaderServer();

    bool isRunned() const;
    void run();
    void shutdown();

private:
    std::shared_ptr<Formatter> createFormatter();

private:
    HttpSensorReaderServer(const HttpSensorReaderServer&) = delete;
    HttpSensorReaderServer& operator=(const HttpSensorReaderServer&) = delete;

private:
    std::unique_ptr<Poco::Net::HTTPServer> _server;
    bool _runned;
};

#endif /* HTTPSENSORREADERSERVER_H_ */
