/*!
 * \file FormatterCommon.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Sep 09, 2018
 */

#ifndef FORMATTERCOMMON_HPP
#define FORMATTERCOMMON_HPP

#include <string>

namespace data {

/*!
 * \addtogroup data
 * @{
 */

/*!
 * \brief The list of output formats.
 */
enum class OutputFormats {
    text, json
};

/*!
 * \brief Verify output format in string form.
 * \param value output type in string form.
 * \return flag which indicate the correctness state.
 */
bool verifyOutputFormat(const std::string& value);

/*!
 * \brief Convert output format from string to the enum type.
 * \param value output type in string form.
 * \return output type in enum type.
 */
OutputFormats translateOutputFormat(const std::string& value);

/*! @} */

} // namespace data

#endif // FORMATTERCOMMON_HPP
