/*!
 * \file HttpCommon.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Sep 09, 2018
 */

#ifndef HTTPCOMMON_HPP
#define HTTPCOMMON_HPP

#include "data/FormatterCommon.hpp"

namespace connectivity {

/*!
 * \addtogroup connectivity
 * @{
 */

/*!
 * \brief Default HTTP server port
 */
static constexpr int DEFAULT_HTTP_PORT = 8080;

/*!
 * \brief Default HTTP data format
 */
static constexpr data::OutputFormats DEFAULT_HTTP_FORMAT = data::OutputFormats::json;

/*! @} */

} // namespace connectivity

#endif // HTTPCOMMON_HPP
