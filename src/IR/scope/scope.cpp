#include "scope.h"

namespace mcs {
    std::ostream& operator<<(std::ostream& out, Scope scope) {
        switch (scope) {
            case Scope::GLOBAL:
                out << "Scope::GLOBAL";
            case Scope::LOCAL:
                out << "Scope::LOCAL";
            default:
                out << "Scope::UNKNOWN";
        }
        return out;
    }
}