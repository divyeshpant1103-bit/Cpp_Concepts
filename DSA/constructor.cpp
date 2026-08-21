#include <iostream>
using namespace std;
class Date{
    int d, m, y;
    public:
        Date(int, int, int);
        Date(int, int);
        Date(int);
        Date();
        void print();
};
Date::Date(int dd, int mm, int yy){
    d = dd;
    m = mm;
    y = yy;
}
Date::Date(int dd,int mm){
    d = dd;
    m = mm;
    y = 2023;
}
Date::Date(int dd){
    d = dd;
    m = 1;
    y = 2023;
}
Date::Date(){
    d = 1;
    m = 1;
    y = 2023;
}
void Date::print(){
    cout << d << "/" << m << "/" << y << endl;
}
int main(){
    Date today(1, 1, 2023);
    Date birthday(1, 1);
    Date anniversary(1);
    Date default_date;
    today.print();
    birthday.print();
    anniversary.print();
    default_date.print();
}
