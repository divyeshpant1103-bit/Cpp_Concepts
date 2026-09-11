#include <iostream>
#include <string>
using namespace std;
class Employee
{
private:
    string first_name;
    string last_name;
    double monthly_salary;
    public:
    Employee(string fn, string ln, double ms)
{
    first_name = fn;
    last_name = ln;
    monthly_salary = ms;
}

    void set_fn(string fn)
    {
        first_name = fn;
    }
    void set_ln(string ln)
    {
        last_name = ln;
    }
    void set_ms(double ms)
    {
        if(ms < 0)
            monthly_salary = 0.0;
        else
            monthly_salary = ms;
    }
    string get_fn()
    {
        return first_name;
    }
    string get_ln()
    {
        return last_name;
    }
    double get_ms()
    {
        return monthly_salary;
    
    }
    
};
int main(){
    Employee emp1("John", "Doe", 5000.00);
    cout << "Employee 1: " << emp1.get_fn() << " " << emp1.get_ln() << ", Monthly Salary: $" << emp1.get_ms() << endl;
    emp1.set_ms(-1000.00); // Attempt to set a negative salary
    cout << "After attempting to set a negative salary: " << emp1.get_fn() << " " << emp1.get_ln() << ", Monthly Salary: $" << emp1.get_ms() << endl;
    emp1.set_ms(6000.00); // Set a valid salary   
    emp1.set_ms(emp1.get_ms() * 1.10);
    cout << "After a 10% raise: " << emp1.get_fn() << " " << emp1.get_ln() << ", Monthly Salary: $" << emp1.get_ms() << endl;
    return 0;
}