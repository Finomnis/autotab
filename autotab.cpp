#include "autotab.hpp"
#include "table.hpp"

void autotab::autotab(std::istream& input, std::ostream& output)
{
    std::string newline;

    // initialize table with first line
    table t("");

    bool previous_was_table = false;

    while(input.good())
    {
        // read next line
        std::getline(input, newline);

        // in case input is not a row of a table
        if(t.count_columns(newline) <= 1){
            
            // we are currently storing a table, flush it
            if(previous_was_table)
            {
                output << t << std::endl;

                // mark table for being invalid
                previous_was_table = false;
            }

            // write input directly to output
            output << newline;

            // add a newline if we are not at EOF, otherwise just flush
            if(input.good())
                output << std::endl;
            else
                output << std::flush;
            
        }
        else // if input is a row of a table
        {

            // if the previous line was a table, try to add it
            if(previous_was_table)
            {

                // try to add to table
                if(!t.add_row(newline))
                {
                    // if line isn't compatible with table, flush table
                    output << t << std::endl;
    
                    // create new table
                    t = table(newline);
                }        

            }
            else
            {

                // if previous line was no table, create a table
                t = table(newline);

                previous_was_table = true;

            }

        }

    }

    // flush final table. no newline.
    // (the last line of a file is by definition not followed by a newline,
    //  otherwise it wouldn't be the last line of the file.)
    if(previous_was_table)
        output << t << std::flush;
}



