#include "unixpath.h"

const char SEPARATOR = '/';
const char POINT = '.';

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    if (!path.empty() && path[0] == SEPARATOR) {
        std::deque<std::string> dir_path;
        for (size_t current_index = 0; current_index < path.size();) {
            if (path[current_index] == SEPARATOR) {
                current_index++;
                continue;
            }
            size_t dir_iter = current_index;
            std::string cur_dir;
            while (dir_iter < path.size() && path[dir_iter] != SEPARATOR) {
                cur_dir.push_back(path[dir_iter]);
                dir_iter++;
            }
            current_index = dir_iter;
            dir_path.push_back(cur_dir);
        }
        std::string abs_path;
        for (std::string& s1 : dir_path) {
            abs_path += SEPARATOR;
            abs_path += s1;
        }
        if (abs_path.empty()) {
            abs_path += SEPARATOR;
        }
        return abs_path;
    }
    std::deque<std::string> current_path;
    for (size_t str_index = 0; str_index < current_working_dir.size();) {
        if (current_working_dir[str_index] == SEPARATOR) {
            str_index++;
            continue;
        }
        size_t current_index = str_index;  // хотим выделить следующую папку
        std::string current_dir_name;
        while (current_index < current_working_dir.size() && current_working_dir[current_index] != SEPARATOR) {
            current_dir_name.push_back(current_working_dir[current_index]);
            current_index++;
        }
        current_path.push_back(current_dir_name);
        str_index = current_index;
    }
    for (size_t str_index = 0; str_index < path.size();) {
        if (path[str_index] == SEPARATOR) {
            str_index++;
            continue;
        }
        if (path[str_index] == POINT) {
            if (str_index + 1 == path.size() || path[str_index + 1] != POINT) {
                str_index++;
                continue;
            } else {
                str_index += 2;
                if (!current_path.empty()) {
                    current_path.pop_back();
                }
                continue;
            }
        }
        size_t current_index = str_index;
        std::string current_dir_name;
        while (current_index < path.size() && path[current_index] != SEPARATOR) {
            current_dir_name.push_back(path[current_index]);
            current_index++;
        }
        current_path.push_back(current_dir_name);
        str_index = current_index;
    }
    std::string absolute_path;
    for (std::string& directory : current_path) {
        absolute_path += SEPARATOR;
        absolute_path += directory;
    }
    if (absolute_path.empty()) {
        absolute_path += SEPARATOR;
    }
    return absolute_path;
}
