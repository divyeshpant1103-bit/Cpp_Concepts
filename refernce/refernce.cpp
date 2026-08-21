#include <iostream>

int main()
{
    int int_data{33};
    double double_data{3.14};

    // refernce
    int &ref_int_data{int_data};
    double &ref_double_data{double_data};

    // print stuff out

    std::cout << "int_data: " << int_data << std::endl;
    std::cout << "&int_data: " << &int_data << std::endl;
    std::cout << "double_data: " << double_data << std::endl;
    std::cout << "&double_data: " << &double_data << std::endl;

    std::cout << "=============================================" << std::endl;
    std::cout << "ref_int_data: " << ref_int_data << std::endl;
    std::cout << "&ref_int_data: " << &ref_int_data << std::endl;
    std::cout << "ref_double_data: " << ref_double_data << std::endl;
    std::cout << "&ref_double_data: " << &ref_double_data << std::endl;
    std::cout << "=============================================" << std::endl;
    int_data = 111;
    double_data = 2.71;

    std::cout << "int_data: " << int_data << std::endl;
    std::cout << "&int_data: " << &int_data << std::endl;
    std::cout << "double_data: " << double_data << std::endl;
    std::cout << "&double_data: " << &double_data << std::endl;

    std::cout << "=============================================" << std::endl;
    std::cout << "ref_int_data: " << ref_int_data << std::endl;
    std::cout << "&ref_int_data: " << &ref_int_data << std::endl;
    std::cout << "ref_double_data: " << ref_double_data << std::endl;
    std::cout << "&ref_double_data: " << &ref_double_data << std::endl;
    std::cout << "=============================================" << std::endl;
    ref_int_data = 222;
    ref_double_data = 1.61;
    

    std::cout<< "int_data: " << int_data << std::endl;
    std::cout << "&int_data: " << &int_data << std::endl;
    std::cout << "double_data: " << double_data << std::endl;
    std::cout << "&double_data: " << &double_data << std::endl;

    std::cout << "=============================================" << std::endl;
    std::cout << "ref_int_data: " << ref_int_data << std::endl;
    std::cout << "&ref_int_data: " << &ref_int_data << std::endl;
    std::cout << "ref_double_data: " << ref_double_data << std::endl;
    std::cout << "&ref_double_data: " << &ref_double_data << std::endl;

    return 0;
}
