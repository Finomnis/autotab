#include "table.hpp"

#include <iostream>
#include <fstream>
#include <string>

namespace autotab{

    void autotab(std::istream& input, std::ostream& output)
    {
        std::string newline;
    
        // read first line
        std::getline(input, newline);
        table t(newline);
    
        while(input.good())
        {
            std::getline(input, newline);
    
            if(!t.add_row(newline))
            {
                output << t;
                t = table(newline);
                output << std::endl;
            }        
    
        }
    
        output << t;
    }

}


int main(int argc, char **argv)
{
    if(argc == 1)
    {
        autotab::autotab(std::cin, std::cout);
    }

    if(argc == 2)
    {
        if(std::string(argv[1]) == std::string("-h"))
        {
            std::cout << "Usage: " << argv[0] << " [input]" << std::endl;
            return 2;
        }

        std::ifstream fin(argv[1]);
        if(!fin.good())
        {
            std::cerr << "Error: Unable to open file '" << argv[1] << "'!"
                     << std::endl;
            return 1;
        }
        autotab::autotab(fin, std::cout); 
        fin.close();
    }
   
    return 0;
}
