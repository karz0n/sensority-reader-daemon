/*!
 * \file HttpDataRequestHandlerFactory.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 22, 2018
 */

#ifndef HTTPDATAREQUESTHANDLERFACTORY_HPP
#define HTTPDATAREQUESTHANDLERFACTORY_HPP

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include "data/StorageManager.hpp"
#include "data/Formatter.hpp"

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/**
 * @brief The HttpDataRequestHandlerFactory class
 */
class HttpDataRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    /*!
     * \brief Construct http data request factory.
     * \param data pointer to the readable data object.
     * \param formatter pointer to the formatter object.
     */
    HttpDataRequestHandlerFactory(data::StorageManager::Ptr storageManager,
                                  data::Formatter::Ptr formatter);

    /*!
     * \brief Create request handler object.
     * \param request reference to the request object.
     * \return instance of the http request handler.
     */
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

private:
    data::StorageManager::Ptr _storageManager;
    data::Formatter::Ptr _formatter;
};

/*! @} */

} // namespace connectivity

#endif // HTTPDATAREQUESTHANDLERFACTORY_HPP
