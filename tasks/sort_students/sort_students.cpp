#include "sort_students.h"

bool AreDatesEqual(const Date& d1, const Date& d2) {
    return d1.year == d2.year && d1.day == d2.day && d1.month == d2.month;
}

bool IsFirstDateSmaller(const Date& d1, const Date& d2) {
    if (d1.year != d2.year) {
        return d1.year < d2.year;
    }
    if (d1.month != d2.month) {
        return d1.month < d2.month;
    }
    return d1.day < d2.day;
}

bool CompareDate(const Student& s1, const Student & s2) { // сравниваем вначале по дате, потом по остальному
    if (!AreDatesEqual(s1.birth_date, s2.birth_date)) {
        return IsFirstDateSmaller(s1.birth_date, s2.birth_date);
    }
    if (s1.name != s2.name) {
        return s1.name < s2.name;
    }
    return s1.last_name < s2.last_name; 
}

bool CompareName(const Student& s1, const Student& s2) {
    if (s1.name != s2.name) {
        return s1.name < s2.name;
    }
    if (s1.last_name != s2.last_name) {
        return s1.last_name < s2.last_name;
    }
    return IsFirstDateSmaller(s1.birth_date, s2.birth_date);
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), CompareDate);
    } else {
        std::sort(students.begin(), students.end(), CompareName);
    }
}
