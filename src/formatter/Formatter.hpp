/*
 * Formatter.hpp
 *
 *  Created on: Mar 1, 2018
 *      Author: Denys Asauliak <d.asauliak@gmail.com>
 */

#ifndef FORMATTER_HPP_
#define FORMATTER_HPP_

#include <variant>
#include <string>
#include <unordered_map>

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
    using Value = std::variant<int, double>;
    using Values = std::unordered_map<std::string, Value>;

    virtual ~Formatter() = default;

    virtual std::string format(const Values& values) const = 0;
    virtual Formats type() const = 0;
};

#endif /* FORMATTER_HPP_ */
