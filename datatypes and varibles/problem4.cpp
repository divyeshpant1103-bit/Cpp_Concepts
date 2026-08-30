/*
Q9. Construct a Program in C++ to show the working of function
overloading(compile time polymorphism) by using a function named calculate Area
() to calculate area of square, rectangle and triangle using different signatures as
required.
*/
#include <iostream>
using namespace std;
class AreaCalulator{
    public:
    //Function to calculate area of square
    double calculateArea(double side){
        return side * side;
    }
    //Function to calculate area of rectangle
    double calculateArea(double length, double breadth){
        return length * breadth;
    }
    //Function to calculate area of triangle
    double calculateArea(double base, double height,int dummy){
        return 0.5 * base * height;
    }
};
int main(){
    AreaCalulator areaCalculator;
    double squareArea = areaCalculator.calculateArea(5.0);
    double rectangleArea = areaCalculator.calculateArea(4.0, 6.0);
    double triangleArea = areaCalculator.calculateArea(3.0, 4.0,1);

    cout << "Area of Square: " << squareArea << endl;
    cout << "Area of Rectangle: " << rectangleArea << endl;
    cout << "Area of Triangle: " << triangleArea << endl;

    return 0;
}