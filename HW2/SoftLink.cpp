
#include "SoftLink.h"

// Display details of the soft link when listing the contents
void SoftLink::ls() const
{
	cout << "S " << name << " " << getCurrentTime() << endl;
}

// Display the content of the target file that the soft link points to
void SoftLink::cat() const
{
	target->cat();
}

// Get the name of the soft link
string SoftLink::getName() const
{
	return name;
}

// Soft links don't have a parent directory, return nullptr
File *SoftLink::getParent() const
{
	return nullptr;
}

// Get the target file to which the soft link points
File *SoftLink::getTarget() const
{
	return target;
}

// Destructor to properly handle memory cleanup
SoftLink::~SoftLink()
{
	delete target;
}
