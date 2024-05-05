#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "File.h"
#include "RegularFile.h"
#include "SoftLink.h"

class Directory : public File
{
public:
	Directory(const string &name, Directory *parent = nullptr) : name(name), parent(parent) {}

	void ls() const override;

	void addFile(File *file);

	void removeFile(File *file);

	void cat() const override;

	string getName() const override;

	File *getParent() const override;

	const vector<File *> &getContents() const;

	~Directory();

private:
	string name;
	Directory *parent;
	vector<File *> contents;
	string getCurrentTime() const
	{
		time_t now = time(0);
		return ctime(&now);
	}
	bool canAddFile(File *file) const;
	size_t getTotalSize() const;
	size_t getDirectorySize(const Directory *directory) const;
	size_t getSoftLinkSize(const SoftLink *softLink) const;
};

#endif // DIRECTORY_H