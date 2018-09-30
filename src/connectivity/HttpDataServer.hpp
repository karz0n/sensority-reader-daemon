/*!
 * \file HttpDataServer.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Feb 21, 2018
 */

#ifndef HTTPDATASERVER_HPP
#define HTTPDATASERVER_HPP

#include <memory>

#include <Poco/Net/HTTPServer.h>

#include "data/StorageManager.hpp"

#include "HttpCommon.hpp"

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/*!
 * \brief The HttpDataServer class.
 */
class HttpDataServer {
public:
    using Ptr = std::unique_ptr<HttpDataServer>;    //!< Pointer to the class

    /*!
     * \brief Http data server contructor.
     * \param port the number of port to listen.
     * \param format type of formatter in string form.
     * \param data pointer to readable data.
     */
    HttpDataServer(data::StorageManager::Ptr storageManager,
                   data::OutputFormats format = DEFAULT_HTTP_FORMAT,
                   unsigned short port = DEFAULT_HTTP_PORT);
    ~HttpDataServer();

    inline bool isRunned() const;

    void run();
    void stop();

public:
    HttpDataServer(const HttpDataServer&) = delete;
    HttpDataServer& operator=(const HttpDataServer&) = delete;

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

/*! @} */

} // namespace connectivity

#endif // HTTPDATASERVER_HPP
