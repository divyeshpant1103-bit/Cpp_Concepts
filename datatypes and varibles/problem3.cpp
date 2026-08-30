/*Q8.Anna is a contender for valedictorian of her high school. She wants to know how
many students (if any) have scored higher than her in the exams given during this
semester.
Create a class named Student with the following specifications:
➢ An instance variable named scores holds a student's 5 exam scores.
➢ A void input () function reads 5 integers and saves them to scores.
➢ An int calculateTotalScore() function that returns the sum of the student's
scores.
Input Format
In the void Student::input() function, you must read 5 scores from standard input and
save them to your scores instance variable.
Output Format
In the int Student::calculateTotalScore() function, you must return the student's total
grade (the sum of the values in scores).
The code in the editor will determine how many scores are larger than Anna’s and
print that number to the console.
Sample Input
The first line contains n, the number of students in Anna’s class. The n subsequent
lines contain each student's 5 exam grades for this semester.
3
30 40 45 10 10
40 40 40 10 10
50 20 30 10 10
Sample Output
1*/
#include <iostream>
#include <string>
using namespace std;
class Student{
    private:
        int scores[5];
    public:
    void input(){
        for (int i = 0; i < 5;i++){
            cin >> scores[i];
        }
        cout << endl;
    }
    
    int calculateTotalScore(){
        int total = 0;
        for (int i = 0; i < 5;i++){
            total += scores[i];
        }
        return total;
    }
};
int main(){
    int n;
    cout << "Enter the number of students: ";
    cin >> n;
    Student anna;
    cout << "Enter Anna's scores: ";
    anna.input();
    int annaTotal=anna.calculateTotalScore();
    int count = 0;
    for (int i = 0; i < n;i++){
        Student otherStudent;
        cout << "Enter scores for student " << i + 1 << ": ";
        otherStudent.input();
        int otherTotal = otherStudent.calculateTotalScore();
        if (otherTotal > annaTotal){
            count++;
        }
    }
    cout << count << endl;
    return 0;
}