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

#include "Formatter.h"
#include "SensorReaderServer.h"
#include "SensorReader.h"

/**
 * @brief The HttpSensorReaderServer class
 */
class HttpSensorReaderServer: public SensorReaderServer {
public:
    HttpSensorReaderServer(SensorReader::Ptr reader, unsigned short port);
    ~HttpSensorReaderServer() override;

    HttpSensorReaderServer(const HttpSensorReaderServer&) = delete;
    HttpSensorReaderServer& operator=(const HttpSensorReaderServer&) = delete;

    bool isRunned() const override;
    void run() override;
	void shutdown() override;

private:
    Formatter::Ptr _formatter;
    std::unique_ptr<Poco::Net::HTTPServer> _server;
    bool _runned;
};

#endif /* HTTPSENSORREADERSERVER_H_ */
