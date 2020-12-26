#include "Problem9.h"
#include <fstream>
#include <string>

using std::cin;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::stoi;

int main()
{
    Graph<Course, int> graph;
    Vector<Course> fixed_courses;
    cout << "Do you want to use the default test file?(y/n):";
    char choice;
    cin >> choice;
    string file_name = "test";
    if (choice == 'n')
    {
        cout << "Please enter the file name";
        cin >> file_name;
    }
    string INPUT_PATH = "src/Problem9/" + file_name + ".txt";
    string OUTPUT_PATH = "src/Problem9/" + file_name + "_out.txt";
    fixed_courses = ReadFile(graph, INPUT_PATH);
    Vector<Vector<Course>> unfixed_courses = graph.ToplogicalSort();
    Course course_table[8][5][4];
    Arange(course_table, fixed_courses, unfixed_courses);
    OutPut(course_table, OUTPUT_PATH);
    cout << "course table " << file_name << "_out.txt has been successfully built" << endl;
    system("pause");
    return 0;
}

Vector<Course> ReadFile(Graph<Course, int> &graph, string INPUT_PATH)
{
    ifstream ifstrm;
    ifstrm.open(INPUT_PATH, ios::in);
    if (ifstrm.fail())
    {
        cout << "打开文件失败" << endl;
        ifstrm.close();
        system("pause");
        exit(1);
    }
    Vector<string> ss;
    string s;
    while (ifstrm >> s)
    {
        ss.PushBack(s);
    }
    ss.PushBack("end");

    Vector<Course> fixed_courses;
    for (int i = 5; i < ss.Size(); ++i)
    {
        if (ss[i][0] == 'c' && ss[i + 1][0] != 'c')
        {
            Course course;
            course.serial_number_ = ss[i];
            course.name_ = ss[i + 1];
            course.learn_time_ = stoi(ss[i + 2]);
            course.start_sem = stoi(ss[i + 3]);
            if (ss[i + 3] == "0")
            {
                graph.InsertVertex(course);
            }
            else
            {
                fixed_courses.PushBack(course);
            }
        }
    }

    for (int i = 5; i < ss.Size(); ++i)
    {
        int tail = 0;
        if (ss[i][0] == 'c' && ss[i + 1][0] != 'c')
        {
            if (ss[i + 3] == "0")
            {
                Course course;
                course.serial_number_ = ss[i];
                tail = graph.GetIndex(course);
            }
            int pre = i + 4;
            while (ss[pre][0] == 'c' && ss[pre + 1][0] == 'c')
            {
                Course course;
                course.serial_number_ = ss[pre];
                int head = graph.GetIndex(course);
                graph.InsertEdge(head, tail, 1);
                pre++;
            }
        }
    }
    ifstrm.close();
    return fixed_courses;
}

void Arange(Course course_table[8][5][4],
            Vector<Course> fixed_courses, Vector<Vector<Course>> unfixed_courses)
{
    int period = 0;
    Queue<Course> queue_two[8];
    Queue<Course> queue_three[8];
    int semester = 0;
    int group = 0;
    for (int i = 0; i < fixed_courses.Size(); ++i)
    {
        Course course = fixed_courses[i];
        if (course.learn_time_ >= 4)
        {
            int learn_time = course.learn_time_;
            Course course_two = course;
            course_two.learn_time_ = 2;
            queue_two[course_two.start_sem - 1].Enqueue(course_two);
            Course new_course = course;
            course.learn_time_ = learn_time - 2;
            if (learn_time == 2)
            {
                queue_two[new_course.start_sem - 1].Enqueue(new_course);
            }
            else
            {
                queue_three[new_course.start_sem - 1].Enqueue(new_course);
            }
        }
        else
        {
            queue_three[course.start_sem - 1].Enqueue(course);
        }
    }
    for (int group = 0; group < unfixed_courses.Size(); ++group, ++semester)
    {
        for (int i = 0; i < unfixed_courses[group].Size(); ++i)
        {
            Course course = unfixed_courses[group][i];
            if (course.learn_time_ == 3)
            {
                if (queue_three[semester].Size() >= 10)
                {
                    ++semester;
                }
                queue_three[semester].Enqueue(course);
            }
            else if (course.learn_time_ == 4)
            {
                Course new_course1 = course;
                new_course1.learn_time_ = 2;
                Course new_course2 = course;
                new_course2.learn_time_ = 2;
                while (queue_two[semester].Size() >= 9)
                {
                    ++semester;
                }
                queue_two[semester].Enqueue(new_course1);
                queue_two[semester].Enqueue(new_course2);
            }
            else if (course.learn_time_ == 5)
            {
                Course new_course1 = course;
                new_course1.learn_time_ = 3;
                Course new_course2 = course;
                new_course2.learn_time_ = 2;
                while (queue_three[semester].Size() >= 9)
                {
                    ++semester;
                }
                queue_three[semester].Enqueue(new_course1);
                queue_two[semester].Enqueue(new_course2);
            }
            else if (course.learn_time_ == 6)
            {
                Course new_course1 = course;
                new_course1.learn_time_ = 3;
                Course new_course2 = course;
                new_course2.learn_time_ = 3;
                while (queue_three[semester].Size() >= 9)
                {
                    ++semester;
                }
                queue_three[semester].Enqueue(new_course1);
                queue_three[semester].Enqueue(new_course2);
            }
        }
    }
    for (int i = 0; i < 8; ++i)
    {
        int two = 0;
        int three = 1;
        int j = 0, k = 0;
        int two_num = queue_two[i].Size();
        int three_num = queue_three[i].Size();

        for (j = 0; j < two_num; ++j)
        {
            course_table[i][two / 4][two % 4] = queue_two[i].Dequeue();
            two += 2;
        }
        for (k = 0; k < three_num; ++k)
        {
            course_table[i][three / 4][three % 4] = queue_three[i].Dequeue();
            three += 2;
        }
        Course course_empty;
        course_empty.name_ = "无";
        for (; j < 10; ++j)
        {
            course_empty.learn_time_ = 2;
            course_table[i][two / 4][two % 4] = course_empty;
            two += 2;
        }
        for (; k < 10; ++k)
        {
            course_empty.learn_time_ = 3;
            course_table[i][three / 4][three % 4] = course_empty;
            three += 2;
        }
    }
    return;
}

void OutPut(Course course_table[8][5][4], string OUTPUT_PATH)
{
    ofstream ofstrm;
    ofstrm.open(OUTPUT_PATH, ios::out);
    for (int i = 0; i < 8; ++i)
    {
        ofstrm << "The " << i + 1 << "st semester:\n";
        for (int j = 0; j < 4; j++)
        {
            int num = 2;
            if (j % 2)
            {
                num = 3;
            }
            for (int m = 0; m < num; ++m)
            {
                for (int k = 0; k < 5; ++k)
                {
                    ofstrm << course_table[i][k][j].name_ << '\t';
                }
                ofstrm << '\n';
            }
        }
        ofstrm << '\n'
               << '\n';
    }
    ofstrm.close();
}