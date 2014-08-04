#include "table.hpp"

#include <iostream>
#include <string>

using autotab::table;

int main(int argc, char **argv)
{
    std::string newline;

    // read first line
    std::getline(std::cin, newline);
    table t(newline);

    while(std::cin.good())
    {
        std::getline(std::cin, newline);

        if(!t.add_row(newline))
        {
            std::cout << t;
            t = table(newline);
            std::cout << std::endl;
        }        

    }

    std::cout << t;
    
    return 0;
}
