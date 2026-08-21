#include <iostream>
using namespace std;

class Date
{
    int d, m, y;

public:
    void init(int dd, int mm, int yy);
    void add_year(int n);
    void add_month(int n);
    void add_day(int n);
    void print();
};

// ---- function definitions ----

void Date::init(int dd, int mm, int yy)
{ //{I'm now defining init, and it belongs to the Date struct's scope
    d = dd;
    m = mm;
    y = yy;
}

void Date::add_year(int n)
{
    y = y + n;
}

void Date::add_month(int n)
{
    m = m + n;
    while (m > 12)
    {
        m = m - 12;
        y = y + 1;
    }
}

void Date::add_day(int n)
{
    d = d + n;
    // simple version, not handling exact days-in-month
    while (d > 30)
    {
        d = d - 30;
        add_month(1);
    }
}

void Date::print()
{
    cout << d << "/" << m << "/" << y << endl;
}
// error for using private members of Date class in main function, so we need to use public member functions to access them.
void print_date(Date &d)
{
    d.y = d.y + 1; // ERROR: "int Date::" is                                                                                                        private memeber of date"
}

// ---- global object ----
Date my_birthday;

void f()
{
    Date today;
    today.init(16, 10, 1996);
    my_birthday.init(30, 12, 1950);

    cout << "Today: ";
    today.print();

    cout << "My birthday: ";
    my_birthday.print();
    print_date(today);
}

int main()
{
    f();
    return 0;
}