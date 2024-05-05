#ifndef SHELL_H
#define SHELL_H
#include "Directory.h"
#include "RegularFile.h"
#include "Softlink.h"
//#include "disk.h"

class MyShell
{

public:
	MyShell()
	{
		root = new Directory(".");
		currentDir = root;
	}

	void run();

	void processCommand(const string &command);

	void createDirectory(const string &dirName);

	void changeDirectory(const string &path);

	void createRegularFile(const string &fileName, const string &content);

	void copyFileOrDirectory(const string &source, const string &destination);

	void copyDirectory(Directory *source, Directory *destination);

	void createSoftLink(const string &source, const string &destination);

	void removeFileOrDirectory(const string &name);

	void displayFileContents(const string &fileName);

	void saveState() const;

	void loadState();

	File *findFile(const string &name) const;

	// void saveDiskStatus();

	// void loadDiskStatus();
	

	~MyShell();

private:
	//Disk *disk;
	Directory *root;
	Directory *currentDir;
	//size_t total_byte;
	void logOperation(const string &operation)const ;
	std::ofstream logFile;
};

#endif