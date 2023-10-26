#include <iostream>
#include <fstream> // Required for the ofstream class
#include <string>  // Required for using to_string()
#include <ctime>
#pragma warning(disable : 4996)
using namespace std;

class DateTime
{
    int day;
    int month;
    int year;
    static time_t t;
    static struct tm* now;

public:
    // Set the day of the DateTime object
    void SetDay(int day)
    {
        if (day > 0 && day <= 31) // To-Do: Handle February (28-29) and months with 30 days
        {
            this->day = day;
        }
        else
        {
            cout << "Invalid value!" << endl;
            throw "ERROR!\n";
        }
    }

    // Get the day of the DateTime object
    int GetDay() const
    {
        return day;
    }

    // Set the month of the DateTime object
    void SetMonth(int month)
    {
        if (month >= 1 && month <= 12)
        {
            this->month = month;
        }
        else
        {
            cout << "Invalid value!" << endl;
            throw "ERROR!\n";
        }
    }

    // Get the month of the DateTime object
    int GetMonth() const
    {
        return month;
    }

    // Set the year of the DateTime object
    void SetYear(int year)
    {
        this->year = year;
    }

    // Get the year of the DateTime object
    int GetYear() const
    {
        return year;
    }

    // Default constructor for DateTime
    DateTime()
    {
        SetDay(11);
        SetMonth(10);
        SetYear(2023);
    }

    // Constructor for DateTime with day and month
    DateTime(int day, int month)
    {
        SetDay(day);
        SetMonth(month);
        SetYear(2023);
    }

    // Constructor for DateTime with day, month, and year
    DateTime(int day, int month, int year)
    {
        SetDay(day);
        SetMonth(month);
        SetYear(year);
    }

    // Copy constructor for DateTime
    DateTime(const DateTime& original)
    {
        this->day = original.day;
        this->month = original.month;
        this->year = original.year;
    }

    // Destructor for DateTime
    ~DateTime()
    {
    }

    // Print the date in the DateTime object
    void Print() const
    {
        cout << "Date: " << day << "." << month << "." << year << endl;
    }

    // Print the current hour
    int PrintHours()
    {
        return now->tm_hour;
    }

    // Print the current minute
    int PrintMinutes()
    {
        return now->tm_min;
    }

    // Print the current second
    int PrintSeconds()
    {
        return now->tm_sec;
    }
};

class Logger
{
    static Logger* instance;
    int log_count = 0;
    string path = "C:/test/test3.txt";
    DateTime* date_time;

    Logger()
    {
    }

public:
    // Get the Logger instance (singleton pattern)
    static Logger* GetInstance()
    {
        return instance == nullptr ? instance = new Logger() : instance;
    }

    // Write a message to the log
    void Write(string message)
    {
        log_count++;
        int hours = date_time->PrintHours(), minutes = date_time->PrintMinutes(), seconds = date_time->PrintSeconds();
        string time = to_string(hours);
        time += ':';
        time += to_string(minutes);
        time += ':';
        time += to_string(seconds);

        ofstream output_file(path, ios::app);
        if (output_file.is_open())
        {
            output_file << message << " at " << time << "\n";
            cout << message << " at " << time << '\n';
            output_file.close();
        }
        else
        {
        }
    }

    // Write an integer value to the log
    void Write(int value)
    {
        Write(to_string(value));
    }
};

class Student
{
    string name;
    string surname;
    DateTime birthday;
    DateTime study_start;

    int* hometask_rates = nullptr;
    int hometask_rates_count = 0;
    int* practice_rates = nullptr;
    int practice_rates_count = 0;
    int* exam_rates = nullptr;
    int exam_rates_count = 0;

public:
    static int student_count;

    // Check if student count is below a limit
    bool CountError()
    {
        return student_count <= 15;
    }

    // Handle the case when the student count limit is exceeded
    void ThrowError()
    {
        try {
            if (CountError())
                student_count++;
            else
                throw 1;
        }
        catch (int)
        {
            cout << "Student counter overloaded" << endl;
        }
    }

    // Default constructor for Student
    Student()
    {
        SetName("Veronika");
        SetSurname("Geyna");
        SetBirthday({ 14, 07, 2005 });
        SetStudyStart({ 1, 9, 2022 });
        ThrowError();
        Logger::GetInstance()->Write("Student created ");
    }

    // Print student information
    void PrintStudent()
    {
        cout << "Name: " << name << endl;
        cout << "Surname: " << surname << endl;
        cout << "Birthday: ";
        birthday.Print();
        cout << "Study start date";
        study_start.Print();
    }

    // Copy constructor for Student
    Student(const Student& original)
    {
        this->name = original.name;
        this->surname = original.surname;
        this->birthday = original.birthday;
        this->study_start = original.study_start;

        this->hometask_rates_count = original.hometask_rates_count;

        this->hometask_rates = new int[this->hometask_rates_count];
        for (int i = 0; i < this->hometask_rates_count; i++)
        {
            this->hometask_rates[i] = original.hometask_rates[i];
        }
        ThrowError();
        Logger::GetInstance()->Write("Student created");
    }

    // Destructor for Student
    ~Student()
    {
        if (hometask_rates != nullptr)
        {
            delete[] hometask_rates;
            hometask_rates = nullptr;
        }
        Logger::GetInstance()->Write("Student destroyed");
    }

    // Set the student's name
    void SetName(string name)
    {
        this->name = name;
    }

    // Get the student's name
    string GetName() const
    {
        return name;
    }

    void SetSurname(string surname)
    {
        this->surname = surname;
    }

    string GetSurname() const
    {
        return surname;
    }

private:

    // Set the student's birthday
    void SetBirthday(const DateTime& birthday)
    {
        this->birthday = birthday;
    }

public:

    // Get the student's birthday
    DateTime GetBirthday() const
    {
        return birthday;
    }

    // Set the student's study start date
    void SetStudyStart(const DateTime& study_start)
    {
        this->study_start = study_start;
    }

    // Get the student's study start date
    DateTime GetStudyStart() const
    {
        return study_start;
    }

    // Add a hometask rate for the student
    void AddHometaskRate(unsigned int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "Incorrect value for parameter rate. Value must be from 1 to 12\n";
            throw "ERROR!";
        }

        if (hometask_rates_count == 0)
        {
            hometask_rates = new int[1];
            hometask_rates[0] = rate;
        }
        else
        {
            int* temp = new int[hometask_rates_count + 1];
            for (int i = 0; i < hometask_rates_count; i++)
                temp[i] = hometask_rates[i];
            temp[hometask_rates_count] = rate;
            delete[] hometask_rates;
            hometask_rates = temp;
        }
        hometask_rates_count++;
    }

    // Print the hometask rates of the student
    void PrintHometaskRates() const
    {
        cout << "Hometasks rates: ";
        for (int i = 0; i < hometask_rates_count; i++)
        {
            cout << hometask_rates[i] << ", ";
        }
        cout << "\n";
    }

    // Get a hometask rate by index
    int GetHometaskRateByIndex(unsigned int index)
    {
        if (index >= hometask_rates_count)
        {
            cout << "Incorrect index when accessing the evaluation array\n";
            throw "ERROR!";
        }
        return hometask_rates[index];
    }

    // Get the count of hometask rates
    int GetHometaskRatesCount() const
    {
        return hometask_rates_count;
    }

    // Add a practice rate for the student
    void AddPracticeRate(int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "Incorrect value for parameter rate. Value must be from 1 to 12" << endl;
            throw "ERROR!";
        }

        if (practice_rates_count == 0)
        {
            cout << "Add first rate!" << endl;
            practice_rates = new int[1];
            practice_rates[0] = rate;
        }
        else
        {
            cout << "Add yet another rate" << endl;
            int* temp = new int[practice_rates_count + 1];
            for (int i = 0; i < practice_rates_count; i++)
            {
                temp[i] = practice_rates[i];
                temp[i + 1] = rate;
            }
            delete[] practice_rates;
            practice_rates = temp;
        }

        practice_rates_count++;
    }

    // Get a practice rate by index
    int GetPracticeRateByIndex(unsigned int index)
    {
        if (index >= practice_rates_count)
        {
            cout << "Incorrect index when accessing the evaluation array\n";
            throw "ERROR!";
        }
        return practice_rates[index];
    }

    // Get the count of practice rates
    int GetPracticeRatesCount() const
    {
        return practice_rates_count;
    }

    // Add an exam rate for the student
    void AddExamRate(int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "Incorrect value for parameter rate. Value must be from 1 to 12" << endl;
            throw "ERROR!";
        }

        if (exam_rates_count == 0)
        {
            cout << "Add first rate!" << endl;
            exam_rates = new int[1];
            exam_rates[0] = rate;
        }
        else
        {
            cout << "Add yet another rate" << endl;
            int* temp = new int[exam_rates_count + 1];
            for (int i = 0; i < exam_rates_count; i++)
            {
                temp[i] = exam_rates[i];
                temp[i + 1] = rate;
            }
            delete[] exam_rates;
            exam_rates = temp;
        }

        exam_rates_count++;
    }

    // Get the count of exam rates
    int GetExamRatesCount() const
    {
        return exam_rates_count;
    }

    // Get an exam rate by index
    int GetExamRateByIndex(unsigned int index)
    {
        if (index >= exam_rates_count)
        {
            cout << "Incorrect index when accessing the evaluation array\n";
            throw "ERROR!";
        }
        return exam_rates[index];
    }

    // Print the practice task rates of the student
    void PrintPracticeTaskRates() const
    {
        for (int i = 0; i < practice_rates_count; i++)
        {
            cout << practice_rates_count << ")" << practice_rates[i] << endl;
        }
    }
};

class Group
{
    Student* group;
    int groupSize, courseN;
    string groupName, specialty;

public:
    static int group_count;

    // Check if group count is below a limit
    bool CountError()
    {
        return group_count <= 15;
    }

    // Handle the case when the group count limit is exceeded
    void ThrowError()
    {
        try {
            if (CountError())
                group_count++;
            else
                throw 1;
        }
        catch (int)
        {
            cout << "Group counter overloaded" << endl;
        }
    }

    // Default constructor for Group
    Group() : Group(0)
    {
        ThrowError();
    }

    // Constructor for Group with a given group size
    Group(int groupSize)
    {
        this->groupSize = groupSize;
        courseN = 1;
        groupName = "KN-0";
        specialty = "Designer";
        group = new Student[groupSize];
        ThrowError();
        Logger::GetInstance()->Write("Group created");
    }

    // Copy constructor for Group
    Group(const Group& obj)
    {
        this->group = new Student[obj.groupSize];
        this->groupSize = obj.groupSize;
        this->courseN = obj.courseN;
        this->groupName = obj.groupName;
        this->specialty = obj.specialty;
        for (int i = 0; i < obj.groupSize; i++)
            this->group[i] = obj.group[i];
        ThrowError();
        Logger::GetInstance()->Write("Group created");
    }

    // Destructor for Group
    ~Group()
    {
        if (group != nullptr)
        {
            delete[] group;
            group_count++;
            cout << "Total count of groups: " << group_count << "\n";
        }
        Logger::GetInstance()->Write("Group destroyed");
    }

    // Print information about the group
    void PrintGroup()
    {
        cout << "Group name: " << groupName << endl;
        cout << "Specialty: " << specialty << endl;
        int f;
        Student temp;
        for (int i = 1; i < groupSize; i++)
        {
            f = 0;
            for (int r = 0; r < groupSize - i; r++)
            {
                if (group[r].GetSurname() > group[r + 1].GetSurname())
                {
                    temp = group[r];
                    group[r] = group[r + 1];
                    group[r + 1] = temp;
                    f = 1;
                }
            }
            if (f == 0)
            {
                break;
            }
        }
        for (int i = 0; i < groupSize; i++)
        {
            cout << i + 1 << ' ' << group[i].GetSurname() << ' ' << group[i].GetName();
            cout << endl;
        }
    }

    // Get the size of the group
    int GetGroupSize() const
    {
        return groupSize;
    }

    // Get a student from the group by index
    Student GetStudentByIndex(int index) const
    {
        return group[index];
    }

    // Add a new student to the group
    void AddStudent(const Student& new_student)
    {
        Student* tmp = new Student[groupSize + 1];
        for (int i = 0; i < groupSize; i++)
            tmp[i] = group[i];

        tmp[groupSize] = new_student;

        delete[] group;
        group = tmp;
        groupSize++;
    }

    // Merge the current group with another group
    void MergeWithGroup(Group& another_group)
    {
        for (int i = 0; i < another_group.GetGroupSize(); i++)
        {
            this->AddStudent(another_group.GetStudentByIndex(i));
        }

        int k = another_group.GetGroupSize();
        for (int i = 0; i < k; i++)
        {
            another_group.DeleteTheWorstStudent();
        }
    }

    // Transfer a student from the current group to another group
    void TransferStudent(Group& other, int index)
    {
        if (index >= 0 && index < groupSize)
        {
            other.AddStudent(group[index]);
            for (int i = index; i < groupSize - 1; i++)
                group[i] = group[i + 1];
            groupSize--;
        }
    }

    // Delete students who failed their exams
    void DeleteFailedStudents()
    {
        int failedExams = 0, newSize = 0;
        for (int i = 0; i < groupSize; i++)
        {
            if (!(group[i].GetExamRateByIndex(i) > 4)) // Pass-grade is 4
                failedExams++;
        }
        newSize = failedExams;
        Student* tmp = new Student[groupSize + 1];
        for (int i = 0, j = 0; i < groupSize; i++)
        {
            if (group[i].GetExamRateByIndex(i))
            {
                tmp[j] = group[i];
                j++;
            }
        }
        delete[] group;
        group = tmp;
        groupSize -= failedExams;
    }

    // Delete the worst-performing student
    void DeleteTheWorstStudent()
    {
        int worst = 0, tmp1 = 0, first = 0, index = 0;
        Student* tmp = new Student[groupSize - 1];
        for (int i = 0; i < groupSize; i++)
        {
            int gradesCount = group[i].GetHometaskRatesCount();
            for (int j = 0; j < gradesCount; i++)
                tmp1 = group[i].GetHometaskRateByIndex(j);
            if (gradesCount > 0 && first == 0)
            {
                worst = tmp1 / gradesCount;
                index = i;
            }
            else if (gradesCount > 0 && first > 0)
            {
                worst = (tmp1 / gradesCount) < worst ? (tmp1 / gradesCount) : worst;
                index = i;
            }
            tmp1 = 0;
            first++;
        }
        for (int i = 0; i < groupSize; i++)
        {
            if (i < index)
                tmp[i] = group[i];
            else if (i == index)
                continue;
            else
                tmp[i - 1] = group[i];
        }
        delete[] group;
        group = tmp;
    }
};

int Student::student_count = 0;
int Group::group_count = 0;

time_t DateTime::t = time(0);
tm* DateTime::now = localtime(&t);
Logger* Logger::instance = nullptr;

int main()
{
    Logger::GetInstance()->Write("Main started by Alex");
    Student original;
    Logger::GetInstance()->Write("Main ended by Alex");
}
