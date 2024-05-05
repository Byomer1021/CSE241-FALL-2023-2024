#ifndef REGULARFILE_H
#define REGULARFILE_H
#include "File.h"

class RegularFile : public File
{
public:
	RegularFile(const string &name, const string &content)
		: name(name), content(content) {}

	void ls() const override;

	void cat() const override;

	string getName() const override;

	File *getParent() const override;

	string getCurrentTime() const
	{
		time_t now = time(0);
		return ctime(&now);
	}
	// RegularFile.cpp

	const string getContent() const
	{
		return content;
	}

	~RegularFile() {}

private:
	string name;
	string content;
};

#endif // REGULARFILE_H