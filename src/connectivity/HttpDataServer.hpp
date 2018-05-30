/*
 * HttpDataServer.hpp
 *
 *  Created on: Feb 21, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef HTTPDATASERVER_HPP_
#define HTTPDATASERVER_HPP_

#include <memory>
#include <string>
#include <utility>

#include <Poco/Net/HTTPServer.h>

#include "common/Runnable.hpp"
#include "formatter/Formatter.hpp"
#include "sensor/SensorReadableData.hpp"

namespace connectivity {

/**
 * @brief The HttpDataServer class
 */
class HttpDataServer : public common::Runnable {
public:
    using Ptr = std::unique_ptr<HttpDataServer>;

    HttpDataServer(unsigned short port,
                   const std::string& format,
                   sensor::SensorReadableData::Ptr data);
    ~HttpDataServer() override;

    /**
     * @brief shutdown http server
     */
    void shutdown();

public:
    inline bool isRunned() const override;
    void run() override;

public:
    /**
     * Factory method
     */
    template<typename ...As>
    static inline Ptr create(As... args)
    {
        return std::make_unique<HttpDataServer>(std::forward<As>(args)...);
    }

public:
    HttpDataServer(const HttpDataServer&) = delete;
    HttpDataServer& operator=(const HttpDataServer&) = delete;

private:
    formatter::Formatter::Ptr getFormatter(const std::string& format);

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

} // namespace connectivity

#endif /* HTTPDATASERVER_HPP_ */
