
#include "RegularFile.h"


// Display details of the regular file when listing the contents
void RegularFile::ls() const
{
	cout << "F " << name << " " << getCurrentTime() << " " << content.size() << " Bytes" << endl;
}

// Display the content of the regular file
void RegularFile::cat() const
{
	cout << content << endl;
}

// Get the name of the regular file
string RegularFile::getName() const
{
	return name;
}

// Regular files don't have a parent directory, return nullptr
File *RegularFile::getParent() const
{
	return nullptr;
}

