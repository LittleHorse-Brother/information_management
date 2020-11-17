#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

class Student
{
public:
    Student(): id(""),name(""),cellphone(""){}

public:
    std::string id;
    std::string name;
    std::string cellphone;
};

#endif // STUDENT_H
