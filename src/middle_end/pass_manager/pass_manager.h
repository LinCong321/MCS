#pragma once

namespace mcs {
    class PassManager {
    public:
        static PassManager& getInstance();

    public:
        void run();

    private:
        PassManager() = default;
        ~PassManager() = default;
    };
}