#include "scope.h"

namespace mcs {
    std::ostream& operator<<(std::ostream& out, Scope scope) {
        switch (scope) {
            case Scope::GLOBAL:
                out << "global";
                break;
            case Scope::LOCAL:
                out << "local";
                break;
            default:
                out << "unknown";
                break;
        }
        return out;
    }
}