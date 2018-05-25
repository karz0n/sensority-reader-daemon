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
#include "sensor/SensorReadableData.hpp"

namespace connectivity {

/**
 * @brief The HttpDataRequestHandlerFactory class
 */
class HttpDataRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    HttpDataRequestHandlerFactory(
            sensor::SensorReadableData::Ptr data,
            formatter::Formatter::Ptr formatter);

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

private:
    sensor::SensorReadableData::Ptr _data;
    formatter::Formatter::Ptr _formatter;
};

} // namespace connectivity

#endif /* HTTPDATAREQUESTHANDLERFACTORY_HPP_ */
