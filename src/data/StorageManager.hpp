/*!
 * \file StorageManager.hpp
 * \author Denys Asauliak <d.asauliak@gmail.com>
 * \date Sep 05, 2018
 */

#ifndef STORAGEMANAGER_HPP
#define STORAGEMANAGER_HPP

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "Storage.hpp"
#include "Formattable.hpp"

namespace data {

/*!
 * \addtogroup data
 * @{
 */

class StorageManager : public Formattable
{
public:
    using Ptr = std::shared_ptr<StorageManager>;

    /*!
     * \brief append
     * \param name
     * \param storage
     */
    void append(Storage::Ptr storage);

    /*!
     * \brief remove
     * \param name
     */
    void remove(const std::string& name);

    /*!
     * \brief has
     * \param name
     * \return
     */
    bool has(const std::string& name) const;

    /*!
     * \brief get
     * \param name
     * \return
     */
    Storage::Ptr get(const std::string& name) const;

    /*!
     * \brief names
     * \return
     */
    std::vector<std::string> names() const;

    /*!
     * \brief format
     * \param formatter
     * \return
     */
    std::string format(const Formatter& formatter) const override;

private:
    /* */
    using Storages = std::unordered_map<std::string, Storage::Ptr>;

private:
    Storages _storages;
};

/*! @} */

} // namespace data

#endif // STORAGEMANAGER_HPP
