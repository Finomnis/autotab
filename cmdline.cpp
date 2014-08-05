#include "cmdline.hpp"

#include <iostream>
#include <cstdlib>

std::vector<std::string>
autotab::parse_cmdline(int argc, const char** argv)
{

    std::vector<std::string> filenames;

    // iterate through command line
    for(int i = 1; i < argc; i++)
    {
        // print help message and exit if one of the arguments is not a
        // filename
        if(std::string(argv[i]).find("-") == 0)
        {
            std::cerr << "Usage: " << argv[0] << " [input files]" << std::endl;
            exit(2);
        }

        // add filename to list
        filenames.push_back(std::string(argv[i]));
    }

    return filenames;

}
