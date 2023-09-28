#include "tests_checking.h"

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> current_order;
    for (const StudentAction& s1 : student_actions) {
        if (s1.side == Side::Top) {
            current_order.push_front(s1.name);
        } else {
            current_order.push_back(s1.name);
        }
    }
    std::vector<std::string> return_order;
    return_order.reserve(queries.size());
    for (size_t num : queries) {
        num--;  // >= 1
        return_order.push_back(current_order[num]);
    }
    return return_order;
}
