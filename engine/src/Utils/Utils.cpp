
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Utils/Utils.hpp>

namespace dt {

namespace Utils {

std::string ToStdString(const QString& qstring) {
    return std::string(qstring.toLocal8Bit().data());
}

uint32_t mAutoId = 0;

uint32_t AutoId() {
    mAutoId++;
    return mAutoId;
}

QUuid GenerateUUIDRandom() {
    return QUuid::createUuid();
}

// QUuid GenerateUUIDFromString(const QString& qstring) {
//     boost::uuids::string_generator gen;
//     boost::uuids::uuid uuid = gen(ToStdString(qstring));
//     return uuid;
// }

} // namespace Utils

} // namespace dt
