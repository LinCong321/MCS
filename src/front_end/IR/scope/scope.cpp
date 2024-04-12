#include "scope.h"

namespace mcs {
    std::ostream& operator<<(std::ostream& out, Scope scope) {
        switch (scope) {
            case Scope::GLOBAL:
                out << "global";
                return out;
            case Scope::LOCAL:
                out << "local";
                return out;
            default:
                out << "unknown";
                return out;
        }
    }
}