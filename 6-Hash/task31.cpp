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

class OpenHashTable
{
    private:
        std::vector<Node *> table;
        int size;
        bool IsSizeOptimal = false;

        int hashMultiplication(int key)
        {
            if (!IsSizeOptimal)
            {
                int res = 1;
                int i = size;
                while (i >>= 1) res <<= 1;
                if (size != res) res <<= 1;
                size = res / 2;
                IsSizeOptimal = true;
            }

            const double A = 0.6180339887;
            const double frac = fmod(key * A, 1.0);
            return static_cast<int>(size * frac);
        }

    public:
        OpenHashTable(int size) : table(size, nullptr), size(size) {}

        void insert(Employee &e)
        {
            int index = hashMultiplication(e.salary);
            Node *newNode = new Node(e);
            if (!table[index])
            {
                table[index] = newNode;
            }
            else
            {
                newNode->next = table[index];
                table[index]->prev = newNode;
                table[index] = newNode;
            }
        }

        Employee *search(int salary)
        {
            int index = hashMultiplication(salary);
            Node *current = table[index];
            while (current)
            {
                if (current->data.salary == salary)
                    return &current->data;
                current = current->next;
            }
            return nullptr;
        }

        void remove(int salary)
        {
            int index = hashMultiplication(salary);
            Node *current = table[index];
            while (current)
            {
                if (current->data.salary == salary)
                {
                    if (current->prev)
                        current->prev->next = current->next;
                    else
                        table[index] = current->next;

                    if (current->next)
                        current->next->prev = current->prev;

                    Node *deletingNode = current;
                    current = current->next;
                    delete deletingNode;
                }
                else
                {
                    current = current->next;
                }
            }
        }

        void print()
        {
            for (int i = 0; i < size; ++i)
            {
                std::cout << "[" << i << "]: ";
                Node *current = table[i];
                if (!current) std::cout << "NULL";
                while (current)
                {
                    std::cout << current->data.surname << " (" << current->data.salary << ") ";
                    if (current->next)
                    {
                        std::cout << "-> ";
                    }
                    current = current->next;
                }
                std::cout << std::endl;
            }
        }
};

int main()
{
    std::vector<Employee> employees = readEmployeeFile();

    OpenHashTable hashTable(employees.size());

    for (auto &employee: employees)
    {
        hashTable.insert(employee);
    }

    std::cout << "Hash-table:\n";
    hashTable.print();

    std::cout << "\nSearch an employee with salary:\n";
    int salary;
    std::cin >> salary;
    Employee *found = hashTable.search(salary);
    if (found)
    {
        found->print();
    }
    else
    {
        std::cout << "Employee not found.\n";
    }

    std::cout << "\nRemove an employee with salary:\n";
    hashTable.remove(salary);
    hashTable.print();

    return 0;
}

