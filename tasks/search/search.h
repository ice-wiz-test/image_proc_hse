#pragma once

#include <algorithm>
#include <cctype>
#include <cmath>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count);
