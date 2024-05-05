#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

class File
{
public:
    virtual void ls() const = 0;
    virtual void cat() const = 0;
    virtual string getName() const = 0;
    virtual File *getParent() const = 0;
    virtual ~File() {}
};


#endif // FILE_H