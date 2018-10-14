#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

#include "Environment.hpp"
#include "Operations.hpp"
#include "Timer.hpp"


int main(int argc, char **argv)
{
    Timer tmr;
    if (argc != 3)
    {
        std::cout
                << "Program needs an operation and a graph file to operate on."
                << std::endl
                << "Available operations are:"
                << std::endl;
        printAvailableOperations();
        return 0;
    }
    Environment env = Environment(argv[2]);

    std::cerr << "Elapsed time (load env): " << tmr.elapsed() << "s"
            << std::endl;

    env.printStats();

    selectOperation(argv[1], env);

    return 0;
}
