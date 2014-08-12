#include "autotab.hpp"
#include "cmdline.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>


bool is_dir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

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
    bool success = true;
    for(std::vector<std::string>::iterator file = files.begin();
            file != files.end(); file++)
    {
       
        // print errormessage if file is a directory
        if(is_dir(file->c_str()))
        {
            std::cerr << "autotab: " << (*file) << ": Is a directory"
                      << std::endl;
            success = false;
            continue;
        }

        // open file
        std::ifstream fin(file->c_str());

        // check if file was successfully opened
        if(!fin.good())
        {
            std::cerr << "autotab: " << (*file) << ": No such file or directory"
                      << std::endl;

            fin.close();
            
            success = false;
            continue;
        }

        // process
        autotab::autotab(fin, std::cout); 

        // close file
        fin.close();

    }
   
    // success?
    return success ? 0 : 1;
}
