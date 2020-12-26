#ifndef _PROBLEM9_H_
#define _PROBLEM9_H_

#include <string>
#include "../../include/Vector.h"
#include "../../include/Graph.h"
#include "../../include/Queue.h"

using std::string;

class Course
{
public:
    Course(){};
    ~Course(){};

    bool operator==(const Course &rhs)
    {
        return serial_number_ == rhs.serial_number_;
    }

    string serial_number_;
    string name_;
    int learn_time_;
    int start_sem;
};

Vector<Course> ReadFile(Graph<Course, int> &graph, string INPUT_PATH);
void Arange(Course course_table[8][5][4],
            Vector<Course> fixed_courses, Vector<Vector<Course>> unfixed_courses);
void OutPut(Course course_table[8][5][4], string OUTPUT_PATH);

#endif //!_PROBLEM9_H_