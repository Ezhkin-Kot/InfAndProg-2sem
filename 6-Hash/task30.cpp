#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>

std::ifstream inputFile("employees.txt");

struct Date
{
    int day, month, year;
};

struct Employee
{
    std::string surname;
    std::string position;
    Date dateOfBirth{};
    int experience = 0;
    double salary = 0.0;

    void print()
    {
        std::cout << surname << " " << position << " " << dateOfBirth.day << "-" <<
            dateOfBirth.month << "-" << dateOfBirth.year << " " << experience << " " << salary << std::endl;
    }
};

Date StringToDate(std::string str)
{
    Date date{};

    std::string temp = str.substr(0, 4); // Year
    date.year = atoi(temp.c_str());

    temp = str.substr(5, 2); // Month
    date.month = atoi(temp.c_str());

    temp = str.substr(8, 2); // Day
    date.day = atoi(temp.c_str());

    return date;
}

std::vector<Employee> readEmployeeFile()
{
    if (!inputFile.is_open())
    {
        std::cerr << "File not opened" << std::endl;
        return std::vector<Employee>{};
    }

    std::vector<Employee> employees;
    Employee newEmployee;
    while (inputFile.peek() != EOF)
    {
        inputFile >> newEmployee.surname;
        inputFile >> newEmployee.position;

        std::string tmp; // Date of birth
        inputFile >> tmp;
        newEmployee.dateOfBirth = StringToDate(tmp);

        inputFile >> newEmployee.experience;
        inputFile >> newEmployee.salary;

        employees.push_back(newEmployee);
    }
    inputFile.close();
    return employees;
}

struct Node
{
    Employee data;
    Node *prev;
    Node *next;

    Node(Employee &e) : data(e), prev(nullptr), next(nullptr) {}
};

class ClosedHashTable
{
    private:
        struct Cell
        {
            Employee data;
            bool occupied = false;
            bool deleted = false;
        };

        std::vector<Cell> table;
        int size;

        int primaryHash(int key)
        {
            return key % size;
        }

        int secondaryHash(int key)
        {
            double A = 0.6180339887;
            double frac = fmod(key * A, 1.0);
            int step = static_cast<int>(size * frac);
            return step == 0 ? 1 : step; // Avoid 0 step
        }

    public:
        ClosedHashTable(int size) : table(size), size(size) {}

        void insert(const Employee &e)
        {
            int h1 = primaryHash(e.salary);
            int h2 = secondaryHash(e.salary);

            for (int i = 0; i < size; ++i)
            {
                int index = (h1 + i * h2) % size;
                if (!table[index].occupied || table[index].deleted)
                {
                    table[index].data = e;
                    table[index].occupied = true;
                    table[index].deleted = false;
                    return;
                }
            }
            std::cout << "Table is filled, unable to add\n";
        }

        Employee *search(int salary)
        {
            int h1 = primaryHash(salary);
            int h2 = secondaryHash(salary);

            for (int i = 0; i < size; ++i)
            {
                int index = (h1 + i * h2) % size;
                if (!table[index].occupied && !table[index].deleted)
                    return nullptr;
                if (table[index].occupied && !table[index].deleted && table[index].data.salary == salary)
                    return &table[index].data;
            }
            return nullptr;
        }

        void print()
        {
            for (int i = 0; i < size; ++i)
            {
                std::cout << "[" << i << "]: ";
                if (table[i].occupied && !table[i].deleted)
                    std::cout << table[i].data.surname << " (" << table[i].data.salary << ")";
                else
                    std::cout << "Empty";
                std::cout << "\n";
            }
        }
};

int main()
{
    std::vector<Employee> employees = readEmployeeFile();

    ClosedHashTable closedHash(employees.size());

    for (const auto &employee: employees)
    {
        closedHash.insert(employee);
    }

    std::cout << "Hash-table:\n";
    closedHash.print();

    std::cout << "\nSearch an employee with salary 55000:\n";
    Employee *foundClosed = closedHash.search(55000);
    if (foundClosed)
    {
        foundClosed->print();
    }
    else
    {
        std::cout << "Employee not found.\n";
    }

    return 0;
}

