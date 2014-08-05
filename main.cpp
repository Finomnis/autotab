#include "autotab.hpp"
#include "cmdline.hpp"

#include <iostream>
#include <fstream>
#include <string>


int main(int argc, const char **argv)
{
    // get list of files from commandline
    std::vector<std::string> files = autotab::parse_cmdline(argc, argv);

    // if no file is provided, read from std::cin
    if(files.empty())
    {
        // process
        autotab::autotab(std::cin, std::cout);

        // success!
        return 0;
    }

    // if files are provided, read from files
    for(std::vector<std::string>::iterator file = files.begin();
            file != files.end(); file++)
    {
       
        // open file
        std::ifstream fin(file->c_str());

        // check if file was successfully opened
        if(!fin.good())
        {
            std::cerr << "Error: Unable to open file '" << (*file) << "'!"
                     << std::endl;
            fin.close();
            return 1;
        }

        // process
        autotab::autotab(fin, std::cout); 

        // close file
        fin.close();

    }
   
    // success!
    return 0;
}
