#pragma once
#include <iostream>

void print(auto val)
{
    std::cout << val;
}

void print(auto first, auto ...args)
{
    if constexpr (sizeof ...(args) == 1)
    {
        print(first);
        std::cout << " ";
        print(args...);
        std::cout << std::endl;
    } else
    {
        print(first);
        std::cout << " ";
        print(args...);
    }
} 