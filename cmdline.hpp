#ifndef AUTOTAB_CMDLINE_HPP_
#define AUTOTAB_CMDLINE_HPP_

#include <vector>
#include <string>

namespace autotab {

    std::vector<std::string> parse_cmdline(int argc, const char** argv);

};

#endif
