#include "tests_checking.h"

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> currentOrder;
    for (const StudentAction& s1 : student_actions) {
        if (s1.side == Side::Top) {
            currentOrder.push_front(s1.name);
        } else {
            currentOrder.push_back(s1.name);
        }
    }
    std::vector<std::string> returnOrder;
    returnOrder.reserve(queries.size());
    for (size_t num : queries) {
        num--;  // >= 1
        returnOrder.push_back(currentOrder[num]);
    }
    return returnOrder;
}
