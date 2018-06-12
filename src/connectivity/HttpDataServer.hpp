/*!
 * \file HttpDataServer.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Feb 21, 2018
 */

#ifndef HTTPDATASERVER_HPP
#define HTTPDATASERVER_HPP

#include <memory>
#include <string>
#include <utility>

#include <Poco/Net/HTTPServer.h>

#include "common/Runnable.hpp"
#include "formatter/Formatter.hpp"
#include "sensor/SensorReadableData.hpp"

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/*!
 * \brief The HttpDataServer class.
 */
class HttpDataServer : public common::Runnable {
public:
    using Ptr = std::unique_ptr<HttpDataServer>;    //!< Pointer to the class

    /*!
     * \brief Http data server contructor.
     * \param port specific listen port.
     * \param format type of formatter in string form.
     * \param data pointer to readable data.
     */
    HttpDataServer(unsigned short port,
                   const std::string& format,
                   sensor::SensorReadableData::Ptr data);
    ~HttpDataServer() override;

    /*!
     * \brief Shutdown http server.
     */
    void shutdown();

public:
    inline bool isRunned() const override
    {
        return _runned;
    }

    void run() override;

public:
    /*!
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

/*! @} */

} // namespace connectivity

#endif // HTTPDATASERVER_HPP
