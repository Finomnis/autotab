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

        // initialize table with first line
        table t(newline);
    
        while(input.good())
        {
            // read next line
            std::getline(input, newline);
    
            // add to table
            if(!t.add_row(newline))
            {
                // if line isn't compatible with table, flush table
                output << t << std::endl;

                // create new table
                t = table(newline);
            }        
    
        }
    
        // flush final table. no newline.
        // (the last line of a file is by definition not followed by a newline,
        //  otherwise it wouldn't be the last line of the file.)
        output << t;
    }

}


int main(int argc, char **argv)
{
    // print help message if help is requested or more than one
    // argument is provided
    if(argc > 1)
    {
        if(std::string(argv[1]) == std::string("-h") || argc > 2)
        {
            std::cout << "Usage: " << argv[0] << " [input]" << std::endl;
            return 2;
        }
    }

    // if no file is provided, read from std::cin
    if(argc == 1)
    {
        // process
        autotab::autotab(std::cin, std::cout);

        // success!
        return 0;
    }

    // if file is provided, read from file
    if(argc == 2)
    {
       
        // open file
        std::ifstream fin(argv[1]);

        // check if file was successfully opened
        if(!fin.good())
        {
            std::cerr << "Error: Unable to open file '" << argv[1] << "'!"
                     << std::endl;
            return 1;
        }

        // process
        autotab::autotab(fin, std::cout); 

        // close file
        fin.close();

        // success!
        return 0;
    }
   
    // should never happen
    return 1;
}
