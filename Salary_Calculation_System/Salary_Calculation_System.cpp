#include <iostream>
#include <list>
#include <string>
#include <string.h>
#include <stdlib.h>
using namespace std;


class Employee {
public:
    string FirstName;
    string LastName;
    string Id;
    double BasicSalary;
    double Commision_rate;
    Employee();
    Employee(string firstName, string lastName, string id, double basicSalary, double commissionRate);

    double Net_Salary(double BS, double CR)
    {
        double NetSalary;
        NetSalary = BS + BS * CR / 100;
        return NetSalary;
    }



    // Default constructor

    // Getter and setter functions for the "firstName" data member
    string getFirstName() {
        return FirstName;
    }

    void setFirstName(string firstName) {
        FirstName = firstName;
    }

    // Getter and setter functions for the "lastName" data member
    string getLastName() {
        return LastName;
    }

    void setLastName(string lastName) {
        LastName = lastName;
    }

    // Getter and setter functions for the "id" data member
    string getId() {
        return Id;
    }

    void setId(string id) {
        Id = id;
    }

    // Getter and setter functions for the "basicSalary" data member
    double getBasicSalary() {
        return BasicSalary;
    }

    void setBasicSalary(double basicSalary) {
        BasicSalary = basicSalary;
    }

    // Getter and setter functions for the "commissionRate" data member
    double getCommissionRate() {
        return Commision_rate;
    }

    void setCommissionRate(double commissionRate) {
        Commision_rate = commissionRate;
    }

    void print() {
        cout << "ID             : " << Id  ;
        cout << "FirstName      : " << FirstName ;
        cout << "LastName       : " << LastName ;
        cout << "BasicSalary    : " << BasicSalary ;
        cout << "CommissionRate : " << Commision_rate ;
    }


};
Employee::Employee()
{
    FirstName = "";
    LastName = "";
    Id = "";
    BasicSalary = 0.0;
    Commision_rate = 0.0;
}
 // Constructor to initialize the employee's data members
Employee::Employee(string firstName, string lastName, string id, double basicSalary, double commissionRate)
{
    FirstName = firstName;
    LastName = lastName;
    Id = id;
    BasicSalary = basicSalary;
    Commision_rate = commissionRate;
}


class HashTable {

private:
    static const int size = 100;
    list<Employee> table[size];

public:
    int getHash(string id);
    void insert_emp(string firstName, string lastName, string id, double basicSalary, double commissionRate);
    void remove_emp(string id);
    bool isKeyExist(string id);
    Employee search_emp(string id);
    void PrintTable();

};
int HashTable::getHash(string id)
{
    int sum = stoi(id);
   
    return sum % size;
}

void HashTable::insert_emp(string firstName, string lastName, string id, double basicSalary, double commissionRate)
{
    int index = getHash(id);
    Employee di(firstName, lastName, id, basicSalary, commissionRate);
    //check key exists - get the list of that key and check whether the key is there in the list
    if (!isKeyExist(id))
        table[index].push_back(di);
    else
        cout << "The Id Already Exist" << endl;


}
void HashTable::remove_emp(string id)
{
    if (!isKeyExist(id))
        cout << "Key does not exist" << endl;
    else {
        int index = getHash(id);
        list<Employee> this_list = table[index];
        list<Employee>::iterator itr = this_list.begin();
        while (itr != this_list.end()) {
            if (itr->Id == id) {
                //once the item is deleted, the iterator jumps to the next item
                //(so it should not be inremented in this step)
                itr = this_list.erase(itr);
            }
            else {
                itr++;
            }
        }
        table[index] = this_list;
    }
}

bool HashTable::isKeyExist(string id)
{
    int index = getHash(id);
    for (Employee d : table[index]) {
        if (d.Id == id)
            return true;
    }
    return false;
}
Employee HashTable::search_emp(string id)
{
    int index = getHash(id);
    for (Employee d : table[index]) {
        if (d.Id == id)
            return d;
    }
    
}
void HashTable::PrintTable()
{
    cout << "\n-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Index \t\t ID\t\t First Name\t\t Last Name\t\t Basic Salary\t\t Commision Rate\t\t Net Salary" << endl;
    for (int i = 0; i < 100; i++) {
        
        for (Employee d : table[i]) {
            cout <<i<<"\t\t"<< d.Id<<"\t\t" << d.FirstName << " \t\t\t " << d.LastName << " \t\t\t " << d.BasicSalary << " \t\t\t " << d.Commision_rate << "\t\t\t" << d.Net_Salary(d.BasicSalary, d.Commision_rate) << endl;
        }
        cout << endl;
    }
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
}





void addEmployee(HashTable& employeeTable)
{
    string id, firstname, lastname;
    double basicsalary, commisionrate;

    cout << "\nEnter employee ID(number between 0 and 100): " ;
    cin >> id;

    if (employeeTable.isKeyExist(id))
    {
        cout << "\nEmployee with ID " << id << " Already Exists" << endl;
    }

    cout << "\nEnter employee firstname: " ;
    cin >> firstname;

    cout << "\nEnter employee lastname: " ;
    cin >> lastname;

    cout << "\nEnter employee salary: " ;
    cin >> basicsalary;

    cout << "\nEnter employee commision rate: " ;
    cin >> commisionrate;


    //Employee employee(firstname, lastname, id, basicsalary, commisionrate);
    employeeTable.insert_emp(firstname, lastname, id, basicsalary, commisionrate);
    cout << "\nEmployee with ID " << id << " Added successfully..!!" << endl;
}

void editEmployee(HashTable& employeeTable) {
    string id;
    cout << "\nEnter employee ID: " ;
    cin >> id;
    if (!employeeTable.isKeyExist(id)) {
        cout << "\nEmployee with ID " << id << " not found." << endl;
        return;
    }

    Employee employee = employeeTable.search_emp(id);
    string name;
    double Basicsalary;
    double Commisionrate;
    system("CLS");
    cout << "\n************************************" << endl;
    cout << "\n  ~~Current employee details~~"<<endl;
    cout << "************************************" << endl;
    cout << endl;
    cout << "\nID                       : " << employee.getId() ;
    cout << "\nFirstName                : " << employee.getFirstName() ;
    cout << "\nLastName                 : " << employee.getLastName();
    cout << "\nBasicSalary              : " << employee.getBasicSalary() ;

    cout << "\nEnter new employee fisrt name (or press '0' to skip): " << endl;
    cin >> name;

    if (!name.empty()) {
        employee.setFirstName(name);
    }

    cout << "\nEnter new employee Basicsalary (or 0 to skip): " << endl;
    cin >> Basicsalary;

    cout << "\nEnter new employee CommisionRate (or 0 to skip): " << endl;
    cin >> Commisionrate;

    if (Basicsalary != 0 || Commisionrate != 0) {
        employee.Net_Salary(Basicsalary, Commisionrate);
    }

    cout << "\nEmployee with ID " << id << " Updated successfully...!!" << endl;
}

void searchEmployee(HashTable& employeeTable) {
    string id;
    cout << "\nEnter employee ID: " << endl;
    cin >> id;
    if (!employeeTable.isKeyExist(id)) {
        cout << "\nEmployee with ID " << id << " Not found..!!" << endl;
        return;
    }

    Employee employee = employeeTable.search_emp(id);
    system("CLS");
    cout << "\n************************************" << endl;
    cout << "\n     ~~Employee details~~"<<endl;
    cout << "  ************************************" << endl;
    cout << endl;
    cout << "\nID                   : " << employee.getId() ;
    cout << "\nFirst Name           : " << employee.getFirstName()  ;
    cout << "\nLast Name            : " << employee.getLastName();
    cout << "\nBasic Salary         : " << employee.getBasicSalary();
    cout<< "\nCommion Rate          : " << employee.getCommissionRate() ;
    
}

void removeEmployee(HashTable& employeeTable) {
    string id;
    cout << "\nEnter employee ID: " << endl;
    cin >> id;
    if (!employeeTable.isKeyExist(id)) {
        cout << "\nEmployee with ID " << id << " Not found..!!" << endl;
        return;
    }

    employeeTable.remove_emp(id);
    cout << "\nEmployee with ID " << id << " Removed successfully...!!"<< endl;
}

void PrintEmployee(HashTable& employeeTable) {
    string id;
    cout << "\nEnter Your ID: " << endl;
    cin >> id;
    if (!employeeTable.isKeyExist(id)) {
        cout << "\nEmployee with ID " << id << " Not Found..!!" << endl;
        return;
    }

    Employee employee = employeeTable.search_emp(id);
    cout << "\n************************************" << endl;
    cout << "\n    ~~~Employee details~~~"<<endl;
    cout << "************************************" << endl;
    cout  << endl;
    cout << "\nID                       : " << employee.getId() ;
    cout << "\nFirstName                : " << employee.getFirstName();
    cout << "\nLaststName               : " << employee.getLastName() ;
    cout << "\nBasicSalary              : " << employee.getBasicSalary();
    cout << "\nCommission Rate          : " << employee.getCommissionRate() ;
    cout << "\nNet Salary               : " << employee.Net_Salary(employee.BasicSalary, employee.Commision_rate);
}

void PrintEmployeeTable(HashTable& employeeTable) {
    employeeTable.PrintTable();
}




void adminMenu(HashTable& employeeTable)
{
    HashTable a = employeeTable;
    int choice;
    string id;

    do {
        cout << " \n****************************************"<< endl;
        cout << "\n            ~~Admin Menu~~ "<<endl;
        cout <<"\n*****************************************"<< endl;
        cout << endl;
        cout << "\n1. Add Employee" ;
        cout << "\n2. Edit Employee" ;
        cout << "\n3. Search Employee";
        cout << "\n4. Remove Employee" ;
        cout << "\n5. See All Employees" ;
        cout << "\n6. Exit" ;
        cout << "\nEnter your choice: " ;
        cin >> choice;

        switch (choice) {
        case 1:
            addEmployee(employeeTable);
            break;
        case 2:
            editEmployee(employeeTable);
            break;
        case 3:
            searchEmployee(employeeTable);
            break;
        case 4:
            removeEmployee(employeeTable);
            break;
        case 5:
            PrintEmployeeTable(employeeTable);
            break;
        case 6:
            cout << "\nExiting Admin Menu" << endl;
            break;
        default:
            cout << "\nInvalid choice..!! Please try again..." << endl;
        }

    } while (choice != 6);
}









void employeeMenu(Employee emp, HashTable& employeeTable)
{
    int choice;
    string id;

    do {
        cout << " \n****************************************" << endl;
        cout << "\n           Employee Menu" << endl;;
        cout << " ****************************************" << endl;
        cout << endl;
        cout << "\n1. View My Details" ;
        cout << "\n2. View All Employees" ;
        cout << "\n3. Exit" ;
        cout << "\nEnter your choice: " ;
        cin >> choice;

        switch (choice) {
        case 1:

            PrintEmployee(employeeTable);
            break;
        case 2:
            PrintEmployeeTable(employeeTable);
            break;
        case 3:
            cout << "\nExiting Employee Menu" << endl;
            break;
        default:
            cout << "\nInvalid choice...!! Please try again.." << endl;
        }


    } while (choice != 3);
}
void mainMenu()
{
    int choice = 0;

    Employee emp;
    //    emp("John","Doe","000",50000.0,10.0);
    emp.setId("000");
    emp.setFirstName("John");
    emp.setLastName("Doe");
    emp.setBasicSalary(50000.0);
    emp.setCommissionRate(10.0);

    HashTable employeeTable;
    



    while (choice != 3) {
        cout << "\nMain Menu: " ;
        cout << "\n1. Admin Login" ;
        cout << "\n2. Employee Login" ;
        cout << "\n3. Exit";
        cout << "\nEnter your choice: " ;
        cin >> choice;

        switch (choice) {
        case 1:
            adminMenu(employeeTable);
            break;
        case 2:
            employeeMenu(emp, employeeTable);
            break;
        case 3:
            cout << "\nExiting program..." << endl;
            break;
        default:
            cout << "\nInvalid choice...!! Please try again.." << endl;
        }

    }
}


int main()
{
    mainMenu();
    return 0;
}
