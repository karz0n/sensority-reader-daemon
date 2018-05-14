/*
 * HttpDataRequestHandlerFactory.hpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef HTTPDATAREQUESTHANDLERFACTORY_HPP_
#define HTTPDATAREQUESTHANDLERFACTORY_HPP_

#include <memory>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include "formatter/Formatter.hpp"
#include "sensor/SensorDataReadable.hpp"

/**
 * @brief The HttpDataRequestHandlerFactory class
 */
class HttpDataRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory {
public:
    HttpDataRequestHandlerFactory(
            std::shared_ptr<SensorDataReadable> data,
            std::shared_ptr<Formatter> formatter);

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

private:
    std::shared_ptr<SensorDataReadable> _data;
    std::shared_ptr<Formatter> _formatter;
};

#endif /* HTTPDATAREQUESTHANDLERFACTORY_HPP_ */
