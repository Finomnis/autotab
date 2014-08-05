#include "table.hpp"

#include <algorithm>
#include <cassert>
#include <sstream>

using autotab::table;

size_t table::count_columns(std::string str)
{
    if(str.length() == 0)
        return 0;
    return std::count(str.begin(), str.end(), '\t') + 1;
}

static std::vector<std::string> split_columns(std::string str)
{
    std::vector<std::string> columns;

    if(str.length() == 0)
        return columns;

    size_t pos;

    while((pos = str.find_first_of('\t')) != str.npos)
    {
        // split string
        std::string cell = str.substr(0, pos);
        str = str.substr(pos+1);

        columns.push_back(cell);
    }

    // also add the last cell
    columns.push_back(str);

    return columns;
}

static size_t string_len(const std::string & str)
{
    return str.length();
}

static std::vector<size_t> get_stringlengths(const std::vector<std::string> &vec)
{
    std::vector<size_t> out(vec.size());
    
    std::transform(vec.begin(), vec.end(), out.begin(),
                          string_len);

    return out;
}

static std::vector<size_t> get_column_widths(const size_t num_columns, 
                               const std::vector< std::vector<std::string> > &t)
{
    std::vector<size_t> maxlen (num_columns, 0);

    for(size_t i = 0; i < t.size(); i++)
    {
        std::vector<size_t> curr_len = get_stringlengths(t[i]);
        assert(curr_len.size() == num_columns);
        for(int j = 0; j < curr_len.size(); j++)
        {
            if(maxlen[j] < curr_len[j]) maxlen[j] = curr_len[j];
        }
    }

    return maxlen;
}

table::table(std::string data) : columns(count_columns(data))
{
    // add the row to the table. will always succeed.
    add_row(data);
}
        
bool
table::add_row(std::string data)
{
    // can't be added if it doesn't have the same amount of columns
    if(count_columns(data) != columns)
       return false;

    // add to table
    t.push_back(split_columns(data));

    return true;
}

std::ostream & autotab::operator<<(std::ostream &os, const table& t)
{
    // determine column sizes
    std::vector<size_t> col_sizes = get_column_widths(t.columns, t.t);

    // for each row in table, print row
    for(int i = 0; i < t.t.size(); i++)
    {
        const std::vector<std::string> & curr_row = t.t[i];

        // iterate through all columns (cells)
        for(int j = 0; j < curr_row.size(); j++)
        {
            std::string curr_cell = curr_row[j];

            // resize current cell
            curr_cell.resize(col_sizes[j], ' ');

            // print current cell
            os << curr_cell;

            // print one space between cells
            if(j != curr_row.size() - 1)
                os << " ";
        }

        // add newline after row
        if(i != t.t.size() - 1)
            os << std::endl;
    }

    return os;
}

size_t
table::get_columns()
{
    return columns;
}
