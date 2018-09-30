/*!
 * \file Storage.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Jul 16, 2018
 */

#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <memory>
#include <string>

#include "StorageCommon.hpp"
#include "Formattable.hpp"
#include "DataObservable.hpp"

namespace data {

/*!
 * \addtogroup data
 * @{
 */

class Storage : public Formattable,
                public DataObservable {
public:
    using Ptr = std::shared_ptr<Storage>;  //!< Type of pointer to the class.

    /*!
     * Default ctor.
     */
    Storage(const std::string& name);

    /*!
     * Default dtor.
     */
    virtual ~Storage() = default;

    /*!
     * \brief name
     * \return
     */
    inline const std::string& name() const;

    /*!
     * \brief extract
     * \return
     */
    virtual StorageValueItems extract() const = 0;

    /*!
     * \brief extract
     * \param names
     * \return
     */
    virtual StorageValueItems extract(std::initializer_list<std::string> keys) const = 0;

    /*!
     * \brief extract
     * \param name
     * \return
     */
    virtual StorageValue extract(const std::string& key) const = 0;

    /*!
     * \brief store
     * \param items
     */
    virtual void store(std::initializer_list<StorageValueItem> items) = 0;

    /*!
     * \brief store
     * \param name
     * \param data
     */
    virtual void store(const std::string& key, const StorageValue& value) = 0;

public:
    std::string format(const Formatter& formatter) const override;

private:
    std::string _name;
};

//
// Inlines
//

inline const std::string& Storage::name() const
{
    return _name;
}

/*! @} */

} // namespace data

#endif // STORAGE_HPP
