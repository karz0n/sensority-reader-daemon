/*!
 * \file HttpDataRequestHandler.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 22, 2018
 */

#ifndef HTTPDATAREQUESTHANDLER_HPP
#define HTTPDATAREQUESTHANDLER_HPP

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandler.h>

namespace data {
class StorageManager;
class Formatter;
}

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/**
 * @brief The HttpDataRequestHandler class
 */
class HttpDataRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
    /*!
     * \brief Construct http data request handler.
     * \param storage reference to the readable data object.
     * \param formatter reference to the formatter object.
     */
    HttpDataRequestHandler(const data::StorageManager& storageManager,
                           const data::Formatter& formatter);

    /*!
     * \brief Handler request.
     * \param request reference to the http request.
     * \param response reference to the response.
     */
    void handleRequest(Poco::Net::HTTPServerRequest& request,
                       Poco::Net::HTTPServerResponse& response);

private:
    const data::StorageManager& _storageManager;
    const data::Formatter& _formatter;
};

/*! @} */

} // namespace connectivity

#endif // HTTPDATAREQUESTHANDLER_HPP
