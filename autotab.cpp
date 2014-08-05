#include "autotab.hpp"
#include "table.hpp"

void autotab::autotab(std::istream& input, std::ostream& output)
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



