#include "admission.h"

bool IsFirstDateBefore(const Date& d1, const Date& d2) {
    if (d1.year != d2.year) {
        return d1.year < d2.year;
    }
    if (d1.month != d2.month) {
        return d1.month < d2.month;
    }
    return d1.day < d2.day;
}

bool AreDatesEqual(const Date& d1, const Date& d2) {
    return d1.day == d2.day && d1.month == d2.month && d1.year == d2.year;
}

bool IsStudentBeforeInUniversityList(const Student& s1, const Student& s2) {
    if (s1.name != s2.name) {
        return s1.name < s2.name;
    }
    return IsFirstDateBefore(s1.birth_date, s2.birth_date);
}

bool IsStudentBeforeOnName(const Student& s1, const Student& s2) {
    if (!AreDatesEqual(s1.birth_date, s2.birth_date)) {
        return IsFirstDateBefore(s1.birth_date, s2.birth_date);
    }
    return s1.name < s2.name;
}

bool IsStudentBeforeInSortedList(const Applicant& a1, const Applicant& a2) {
    if (a1.points != a2.points) return a1.points > a2.points;
    return IsStudentBeforeOnName(a1.student, a2.student);
}

bool IsStudentBeforePointer(const Applicant*& a1, const Applicant*& a2) {
    return IsStudentBeforeInSortedList(*a1, *a2);
}

bool IsStudentBeforeInUniListPointer(const Student*& s1, const Student*& s2) {
    return IsStudentBeforeInUniversityList(*s1, *s2);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::unordered_map<std::string, size_t> university_size;
    for(const University& uni : universities) {
        university_size[uni.name] = uni.max_students;
    }
    AdmissionTable return_value;
    std::vector<const Applicant*> sorted_apllicants;
    for (const Applicant& s1 : applicants) {
        sorted_apllicants.push_back(&s1);
    }
    std::sort(sorted_apllicants.begin(), sorted_apllicants.end(), IsStudentBeforePointer);
    for (const Applicant* current_assign : sorted_apllicants) {
        for (const std::string &preferred_university : current_assign->wish_list) {
            if (return_value[preferred_university].size() != university_size[preferred_university]) {
                return_value[preferred_university].push_back(&current_assign->student);
                break;
            }
        }
    }
    for (const University& uni  : universities) {
        sort(return_value[uni.name].begin(), return_value[uni.name].end(), IsStudentBeforeInUniListPointer);
    }
    return return_value;
}
