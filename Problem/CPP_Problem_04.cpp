#include <iostream>
#include <string>
using namespace std;
class Book{
    private:
        string title;
        string author;
        double price;
        public:
        Book(string t,string a,double p){
            title = t;
            author = a;
            price = p;
        }
        void set_title(string t){
            title = t;
        }
        void set_author(string a){
            author = a;
        }
        void set_price(double p){
            price = p;
        }
        string get_title(){
            return title;
        }
        string get_author(){
            return author;  
        }
        double get_price(){
            return price;
        }
};
class Member{
    private:
        string name;
        int member_id;
        public:
        Member(string n,int id){
            name = n;
            member_id = id;
        }
        void set_name(string n){
            name = n;
        }
        void set_member_id(int id){
            member_id = id;
        }
        string get_name(){
            return name;
        }
        int get_member_id(){
            return member_id;
        }
};
