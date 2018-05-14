/*
 * HttpSensorReaderServer.h
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef HTTPDATASERVER_HPP_
#define HTTPDATASERVER_HPP_

#include <memory>

#include <Poco/Net/HTTPServer.h>

#include <common/Runnable.hpp>
#include <formatter/Formatter.hpp>
#include "sensor/SensorDataReadable.hpp"

/**
 * @brief The HttpDataServer class
 */
class HttpDataServer : public Runnable {
public:
    HttpDataServer(
            unsigned short port,
            std::shared_ptr<SensorDataReadable> data);
    ~HttpDataServer() override;

    inline bool isRunned() const override;
    void run() override;
    void shutdown() override;

public:
    HttpDataServer(const HttpDataServer&) = delete;
    HttpDataServer& operator=(const HttpDataServer&) = delete;

private:
    std::shared_ptr<Formatter> getFormatter();

private:
    std::unique_ptr<Poco::Net::HTTPServer> _server;
    bool _runned;
};

//
// Inlines
//

bool HttpDataServer::isRunned() const
{
    return _runned;
}

#endif /* HTTPDATASERVER_HPP_ */
