#ifndef SOFTLINK_H
#define SOFTLINK_H
#include "File.h"


class SoftLink : public File
{

public:
	SoftLink(const string &name, File *target)
		: name(name), target(target) {}

	void ls() const override;

	void cat() const override;

	string getName() const override;
	File *getParent() const override;

	File *getTarget() const;
	

	~SoftLink();

private:
	string name;
	File *target;

	string getCurrentTime() const
	{
		time_t now = time(0);
		return ctime(&now);
	}
};

#endif //SOFTLINK_H