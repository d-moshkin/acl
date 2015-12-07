#include "stdafx.h"
#include "string_utils.h"

std::string string_utils::trim(const std::string& input)
{
    size_t first_non_space = input.find_first_not_of(" \t");
    size_t last_non_space = input.find_last_not_of(" \t");

    if (first_non_space == std::string::npos)
        return "";
    else
        return input.substr(first_non_space, last_non_space - first_non_space + 1);
}
