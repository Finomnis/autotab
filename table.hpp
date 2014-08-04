#ifndef AUTOTAB_TABLE_HPP_
#define AUTOTAB_TABLE_HPP_

#include <iostream>
#include <string>
#include <vector>

namespace autotab {

    class table{

    public:
        table(std::string data);
        
        bool add_row(std::string data);

    private:
        friend std::ostream & operator<<(std::ostream &os, const table& t);
    public:
        std::vector< std::vector<std::string> > t;
        size_t columns;
    };

    std::ostream & operator<<(std::ostream &os, const table& t);

};

#endif
