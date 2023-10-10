#pragma once

#include <numeric>
#include <set>
#include <string_view>
#include <vector>

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count);
