#include "scorer.h"

bool IsFirstEventBefore(Event& e1, Event& e2) {
    return e1.time < e2.time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    Events events_to_sort = events;
    std::sort(events_to_sort.begin(), events_to_sort.end(), IsFirstEventBefore);
    ScoreTable current_score_table = ScoreTable();
    std::map<std::string, std::map<std::string, bool>> has_last_check_been_successful;
    std::map<std::string, std::map<std::string, bool>> is_there_open_mr;
    for (const Event& s1 : events_to_sort) {
        if (s1.time > score_time) {
            break;
        }
        switch (s1.event_type) {
            case EventType::CheckFailed:
                has_last_check_been_successful[s1.student_name][s1.task_name] = false;
                break;
            case EventType::CheckSuccess:
                has_last_check_been_successful[s1.student_name][s1.task_name] = true;
                break;
            case EventType::MergeRequestOpen:
                is_there_open_mr[s1.student_name][s1.task_name] = true;
                break;
            case EventType::MergeRequestClosed:
                is_there_open_mr[s1.student_name][s1.task_name] = false;
                break;
        }
    }
    std::set<std::string> student_names;
    for (const Event& s1 : events) {
        if (s1.time > score_time) {
            continue;
        }
        student_names.insert(s1.student_name);
    }
    for (const std::string& student_name : student_names) {
        for (const std::pair<std::string, bool> current_pair : has_last_check_been_successful[student_name]) {
            if (!current_pair.second) {
                continue;
            }
            if (!is_there_open_mr[student_name].count(current_pair.first) ||
                !is_there_open_mr[student_name][current_pair.first]) {
                current_score_table[student_name].insert(current_pair.first);
            }
        }
    }
    return current_score_table;  // this could be a performance problem
}