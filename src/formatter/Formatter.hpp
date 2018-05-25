/*
 * Formatter.hpp
 *
 *  Created on: Mar 1, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef FORMATTER_HPP_
#define FORMATTER_HPP_

#include <variant>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace formatter {

/**
 * @brief The Formats enum
 */
enum class Formats {
    text, json
};

/**
 * @brief The Formatter class
 */
class Formatter {
public:
    using Ptr = std::shared_ptr<Formatter>;
    using Value = std::variant<int, double>;
    using Values = std::unordered_map<std::string, Value>;

    virtual ~Formatter() = default;

    /**
     * @brief format type of this formatter
     * @return type identifier
     */
    virtual Formats type() const = 0;

    /**
     * @brief format input values
     * @param values input values
     * @return string in specified format
     */
    virtual std::string format(const Values& values) const = 0;

public:
    /**
     * Formatter factory method
     */
    template <typename T, typename ...As>
    static Ptr create(As... args)
    {
        return std::make_shared<T>(std::forward<As>(args)...);
    }
};

} // namespace formatter

#endif /* FORMATTER_HPP_ */
