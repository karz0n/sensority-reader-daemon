/*
 * HttpDataRequestHandler.hpp
 *
 *  Created on: Mar 22, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef HTTPDATAREQUESTHANDLER_HPP_
#define HTTPDATAREQUESTHANDLER_HPP_

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandler.h>

namespace formatter {
class Formatter;
}

class SensorReadableData;

namespace connectivity {

/**
 * @brief The HttpDataRequestHandler class
 */
class HttpDataRequestHandler: public Poco::Net::HTTPRequestHandler {
public:
    HttpDataRequestHandler(
            const SensorReadableData& storage,
            const formatter::Formatter& formatter);

    void handleRequest(
            Poco::Net::HTTPServerRequest& request,
            Poco::Net::HTTPServerResponse& response);

private:
    const SensorReadableData& _data;
    const formatter::Formatter& _formatter;
};

} // namespace connectivity

#endif /* HTTPDATAREQUESTHANDLER_HPP_ */
