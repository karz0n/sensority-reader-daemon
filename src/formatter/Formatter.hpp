/*!
 * \file Formatter.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Mar 1, 2018
 */

#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <variant>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace formatter {

/*!
 * \addtogroup formatter
 * @{
 */

/*!
 * \brief The Formats enum.
 * \details Represents types of emited values.
 */
enum class Formats {
    text, json
};

/*!
 * \brief The Formatter class.
 */
class Formatter {
public:
    using Ptr = std::shared_ptr<Formatter>;                 //!< The pointer type of class.
    using Value = std::variant<int, double>;                //!< The type of input value.
    using Values = std::unordered_map<std::string, Value>;  //!< The type of values collection.

    virtual ~Formatter() = default;

    /*!
     * \brief Return type of formatter.
     * \return type of formatter.
     */
    virtual Formats type() const = 0;

    /*!
     * \brief Format input collection of values.
     * \param values input collection of values.
     * \return result of formatting.
     */
    virtual std::string format(const Values& values) const = 0;

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

} // namespace formatter

#endif // FORMATTER_HPP
