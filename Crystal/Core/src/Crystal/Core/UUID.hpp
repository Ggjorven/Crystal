#pragma once

#include <random>

namespace Crystal
{

    typedef uint64_t CR_UUID;

    class UUIDGenerator
    {
    public:
        static CR_UUID GenerateUUID()
        {
            std::random_device rd;
            std::mt19937_64 gen(rd());

            return gen();
        }
    };

}