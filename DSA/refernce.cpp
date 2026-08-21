/*1.An electricity board charges the following rates to domestic users to discourage large consumption of
energy.For the first 100 units : -60 P per uni For the next 200 units : -80 P per un Beyond 300 units : -90 P per uni
All users are charged a minimum of Rs 50 if the total amount is more than Rs 300 then an additional su
is added..Implement a C++ program to read the names of users and number of units consumed and display the chargeswith names.

2.Construct a C++ program that removes a specific character from a given string and return the updated
string.Typical Input : computer science is the future
Typical Output : compuer science is he fuure

3.Implement a C++ program to find the non -repeating characters in string.Typical Input : graphic era university
 Typical Output : g p h c u n v s t y8*/

// #include <iostream>
// #include <string>
// using namespace std;
// void removeword(string str,char ch){
//     string newstr;
//     for (int i = 0; i < str.length();i++){
//         if(str[i]!=ch){
//             newstr = newstr + str[i];
//         }
//     }
//     cout << "The new string is : " << newstr << endl;
//     return;
// }
// int main(){
//     string str;
//     cout << "Ente the string :";
//     getline(cin, str);
//     char ch;
//     cout<< "Enter the character to be removed :";
//     cin >> ch;
//     removeword(str, ch);
// }

//  #include <iostream>
//  #include <string>
// using namespace std;
// int main(){
//     string str;
//     cout << "enter the string :";
//     getline(cin,str);
//     for (int i = 0; i < str.length();i++){
//         int count = 0;
//         for (int j = 0; j < str.length();j++){
//             if(str[i]==str[j]){
//                 count++;
//             }
//         }
//         if(count==1){
//             cout << str[i] << " ";
//         }
//     }
// }

// #include <iostream>
// #include <string>
// using namespace std;
// int main(){
//     int units;
//     string name;
//     cout << "Enter the name of the user : ";
//     getline(cin, name);
//     cout << "Enter the Number of units consumed : ";

//     cin >> units;
//     float charges;
//     if(units<=100){
//         charges = units * 0.60;

//     }else if(units>100 &&units<=300){
//         charges = 100 * 0.60 + (units - 100) * 0.80;
//     }
//     else if(units>300){
//         charges = 100 * 0.60 + 200 * .80 + (units - 300) * 0.90;
//     }else{
//         cout << "Invalid Input";
//     }
//     int totalcharges = charges + 50;
//     if(totalcharges>300){
//         totalcharges = totalcharges + totalcharges * 0.15;
//     }
//     cout << "The total charges for " << name << " is : " << totalcharges << endl;

// }

// pattern
/*
   *
 * * *
* * * * *
 * * *
   *

*/
// #include <iostream>
// using namespace std;
// int main()
// {
//     int n;
//     cout << "Enter the number of rows :";
//     cin >> n;
//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = 1; j <= n - i; j++)
//         {
//             cout << " ";
//         }
//         for (int j = 1; j <= i; j++)
//         {
//             cout << "*";
//         }
//         for (int j = i; j < i; j++)
//         {
//             cout << "*";
//         }
//         cout << "\n";
//     }
//     for(int i = 1 i >= 1; i--)
//     {
//         for (int j = 1; j <= n - i; j++)
//         {
//             cout << " ";
//         }
//         for (int j = 1; j <= i; j++)
//         {
//             cout << "*";
//         }
//         for (int j = i; j < i; j++)
//         {
//             cout << "*";
//         }
//         cout << "\n";
//     }
// }

// 1.⁠ ⁠Write a CPP program to reverse an integer array.
// 2.⁠ ⁠Write a CPP program to print non - repeating numbers in an array.
// 3.⁠ ⁠Write a CPP program to find sum of even numbers and odd numbers in an array.

// #include <iostream>
// using namespace std;
// void reverse(int arr[],int size){
//     int start = 0;
//     int end = size - 1;
//     while(start<end){
//         int temp = arr[start];
//         arr[start] = arr[end];
//         arr[end] = temp;
//         start++;
//         end--;
//     }
// }
// void nonrepeating(int arr[],int size){
//     for (int i = 0; i < size;i++){
//         int count = 0;
//         for (int j = 0; j < size;j++){
//             if(arr[i]==arr[j]){
//                 count++;
//             }
//         }
//         if(count==1){
//             cout << arr[i] << " "<<endl;
//         }
//     }
// }
// void sumofevenodd(int arr[],int size){
//     int even = 0;
//     int odd = 0;
//     for (int i = 0; i < size;i++){
//         if(arr[i]%2==0){
//             even += arr[i];
//         }else{
//             odd += arr[i];
//         }
//     }
//     cout << "The sum of even numbers is : " << even << endl;
//     cout << "The sum of odd numbers is : " << odd << endl;
// }
// int main(){
//     int arr[10];
//     int limit;
//     cout << "Enter the Limit of the array :";
//     cin >> limit;
//     if(limit>10){
//         cout << "Limit should be less than or equal to 10";
//         return 0;
//     }
//     for (int i = 0; i < limit;i++){
//         cin >> arr[i];
//         if(arr[i]<0){
//             cout << "please enter positive numbers only";
//         }
//     }
//     //reverse(arr, limit);
//     nonrepeating(arr, limit);

//     sumofevenodd(arr, limit);
//     // cout << "reversed array is:";
//     // for (int i = 0; i < limit;i++){
//     // cout << arr[i] << " ";

//     //}
// }
// write CPP program to store student name ,id section ,marks in 3 different subjects using array of structures and display the details of students who have scored more than 60% in all subjects.
// #include <iostream>
// #include <string>
// using namespace std;
// #define MAX 100
// struct student
// {
//     string name;
//     int id;
//     string section;
//     float marks[3];
// };
// int main()
// {
//     student students[MAX];
//     int n;
//     int sum = 0;
//     float avg = 0;
//     cout << "Enter the number of student :";
//     cin >> n;
//     for (int i = 0; i < n; i++)
//     {
//         cout << "Enter the name of student " << i + 1 << ":" << endl;
//         cin >> students[i].name;
//         cout << "Enter the id of student " << i + 1 << ":" << endl;
//         cin >> students[i].id;
//         cout << "Enter the section of student " << i + 1 << ":" << endl;
//         cin >>
//             students[i].section;
//         cout << "Enter the marks of student in 3 subjects " << i + 1 << ":" << endl;
//         for (int j = 0; j < 3; j++)
//         {
//             cin >> students[i].marks[j];
//             sum += students[i].marks[j];
//             avg = sum / 3;
//         }
//     }
//     cout << "display the details" << endl;
//     for (int i = 0; i < n; i++)
//     {
//         cout << "Name: " << students[i].name << endl;
//         cout << "Id: " << students[i].id << endl;
//         cout << "Section: " << students[i].section << endl;
//         cout << "Marks: ";
//         for (int j = 0; j < 3; j++)
//         {
//             if (avg < 33)
//             {
//                 cout << "Fail" << endl;
//             }
//             else
//             {
//                 cout << students[i].marks[j] << " "<<endl;
//             };
//         }
//     }
//     return 0;
// }

// define a class employee that contain following memmber
// 1.employye name
// 2.employee Id
// 3.employee salary
// 4. employee experinece:
// 5.employe hra
// 6.employee da
// memeber function -> input()-> to take input from user
// calaulate salary()->to calculate salary  and display()-> to display the details of employee
// hra=20% of salary
// da=10%of salary
// display function should display the employee name ,id ,salary and total salary


#include <iostream>
#include <string>
using namespace std;
class employee{
    private:
        string name;
        int id;
        float salary;
        int experience;
        float hra;
        float da;
    public:
    void input(){
        cout << "Enter the name of employee: " << endl;
        cin >> name;
        cout << "Enter the id of employee: " << endl;
        cin >> id;
        cout << "Enter the salary of employee: " << endl;
        cin >> salary;
        cout << "Enter the experience of employee: " << endl;
        cin >> experience;
    }
    void calculate_salary(){
        hra = salary * 0.2;
        da = salary * 0.1;
        salary = salary + hra + da;
    }
    void display(){
        cout << "Employee Name: " << name << endl;
        cout << "Employee Id: " << id << endl;
        cout << "Employee Salary: " << salary << endl;
        cout << "Employee Experience: " << experience << endl;
        cout << "Employee HRA: " << hra << endl;
        cout << "Employee DA: " << da << endl;
    }
};

int main()
    employee emp;
    emp.input();
    emp.calculate_salary();
    emp.display();
    return 0;
}