/*!
 * \file Formatter.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 1, 2018
 */

#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <memory>

#include "FormatterCommon.hpp"
#include "StorageCommon.hpp"

namespace data {

/*!
 * \addtogroup data
 * @{
 */

/*!
 * \brief The Formatter class.
 */
class Formatter {
public:
    using Ptr = std::shared_ptr<Formatter>; //!< The pointer type of class.

    virtual ~Formatter() = default;

    /*!
     * \brief Return type of formatter.
     * \return type of formatter.
     */
    virtual OutputFormats type() const = 0;

    /*!
     * \brief Format input collection of values.
     * \param items input collection of values.
     * \return result of formatting.
     */
    virtual std::string format(const StorageValueItems& items) const = 0;

    /*!
     * \brief format
     * \param group
     * \return
     */
    virtual std::string format(const StorageValueItemsGroup& group) const = 0;

public:
    /*!
     * Formatter factory method
     */
    template <typename T, typename ...As>
    static Ptr create(As... args)
    {
        return std::make_shared<T>(std::forward<As>(args)...);
    }
};

/*! @} */

} // namespace data

#endif // FORMATTER_HPP
