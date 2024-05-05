#include "shell.h"

// The main loop of the shell, where commands are processed.
void MyShell::run()
{
	string command;
	do
	{
		cout << "> ";
		getline(cin, command);
		processCommand(command);
		// saveDiskStatus();
	} while (command != "exit");
}
// Processes the given command and performs the corresponding action.
void MyShell::processCommand(const string &command)
{
	istringstream iss(command);
	string operation;
	iss >> operation;

	if (operation == "ls")
	{
		currentDir->ls();
	}
	else if (operation == "mkdir")
	{
		string dirName;
		iss >> dirName;
		createDirectory(dirName);
	}
	else if (operation == "cd")
	{
		string path;
		iss >> path;
		changeDirectory(path);
	}
	else if (operation == "cp")
	{
		string source, destination;
		iss >> source >> destination;
		copyFileOrDirectory(source, destination);
	}
	else if (operation == "link")
	{
		string source, destination;
		iss >> source >> destination;
		createSoftLink(source, destination);
	}
	else if (operation == "rm")
	{
		string fileName;
		iss >> fileName;
		removeFileOrDirectory(fileName);
	}
	else if (operation == "cat")
	{
		string fileName;
		iss >> fileName;
		displayFileContents(fileName);
	}
	else if (operation == "cr")
	{
		string fileName, content;
		iss >> fileName >> content;
		createRegularFile(fileName, content);
	}
	else if (operation == "exit")
	{
		// Do nothing, exit the shell
	}
	else
	{
		cout << "Invalid command." << endl;
	}
	// saveDiskStatus();
}
// Creates a new directory with the given name.
void MyShell::createDirectory(const string &dirName)
{
	Directory *newDir = new Directory(dirName, currentDir);
	currentDir->addFile(newDir);
}
// Changes the current directory based on the given path.
void MyShell::changeDirectory(const string &path)
{
	if (path == "..")
	{
		if (currentDir != root)
		{
			currentDir = static_cast<Directory *>(currentDir->getParent());
		}
	}
	else
	{
		File *target = findFile(path);
		if (target && target->getName() != "." && target->getName() != ".." && dynamic_cast<Directory *>(target))
		{
			currentDir = static_cast<Directory *>(target);
		}
		else
		{
			cout << "Invalid directory." << endl;
		}
	}
}
// Creates a new regular file with the given name and content.
void MyShell::createRegularFile(const string &fileName, const string &content)
{
	File *newFile = new RegularFile(fileName, content);
	currentDir->addFile(newFile);
}
// Copies a file or directory from the source to the destination.
void MyShell::copyFileOrDirectory(const string &source, const string &destination)
{
	File *sourceFile = findFile(source);

	if (sourceFile)
	{
		File *copy;
		if (dynamic_cast<Directory *>(sourceFile))
		{
			copy = new Directory(destination, currentDir);
			copyDirectory(static_cast<Directory *>(sourceFile), static_cast<Directory *>(copy));
		}
		else if (dynamic_cast<RegularFile *>(sourceFile))
		{
			ifstream in(source);
			ostringstream content;
			content << in.rdbuf();
			copy = new RegularFile(destination, content.str());
		}
		else if (dynamic_cast<SoftLink *>(sourceFile))
		{
			copy = new SoftLink(destination, static_cast<SoftLink *>(sourceFile)->getTarget());
		}

		currentDir->addFile(copy);
	}
	else
	{
		cout << "Source file/directory not found." << endl;
	}
}
// Recursive function to copy the contents of a directory.
void MyShell::copyDirectory(Directory *source, Directory *destination)
{
	for (const auto &file : source->getContents())
	{
		if (dynamic_cast<Directory *>(file))
		{
			Directory *subdir = static_cast<Directory *>(file);
			Directory *newSubdir = new Directory(subdir->getName(), destination);
			destination->addFile(newSubdir);
			copyDirectory(subdir, newSubdir);
		}
		else if (dynamic_cast<RegularFile *>(file))
		{
			ifstream in(file->getName());
			ostringstream content;
			content << in.rdbuf();
			RegularFile *newFile = new RegularFile(file->getName(), content.str());
			destination->addFile(newFile);
		}
		else if (dynamic_cast<SoftLink *>(file))
		{
			SoftLink *link = static_cast<SoftLink *>(file);
			SoftLink *newLink = new SoftLink(link->getName(), link->getTarget());
			destination->addFile(newLink);
		}
	}
}
// Creates a new soft link with the given source and destination.
void MyShell::createSoftLink(const string &source, const string &destination)
{
	File *sourceFile = findFile(source);
	if (sourceFile)
	{
		SoftLink *link = new SoftLink(destination, sourceFile);
		currentDir->addFile(link);
	}
	else
	{
		cout << "Source file not found." << endl;
	}
}
// Removes a file or directory with the given name.
void MyShell::removeFileOrDirectory(const string &name)
{
	File *target = findFile(name);
	if (target)
	{
		if (target != root)
		{
			currentDir->removeFile(target);
			// delete target;
		}
		else
		{
			cout << "Cannot remove root directory." << endl;
		}
	}
	else
	{
		cout << "File/directory not found." << endl;
	}
}
// Displays the contents of a regular file.
void MyShell::displayFileContents(const string &fileName)
{
	File *file = findFile(fileName);
	if (file && dynamic_cast<RegularFile *>(file))
	{
		file->cat();
	}
	else
	{
		cout << "File not found or is not a regular file." << endl;
	}
}
// Finds a file with the given name in the current directory.
File *MyShell::findFile(const string &name) const
{
	for (const auto &file : currentDir->getContents())
	{
		if (file->getName() == name)
		{
			return file;
		}
	}
	return nullptr;
}
// Saves the state of the shell, including the list of files in the root directory.
void MyShell::saveState() const
{
    ofstream stateFile("state.txt");

    if (stateFile.is_open())
    {
        for (const auto &file : root->getContents())
        {
            stateFile << file->getName() << "\n";
        }

        stateFile.close();
        logOperation("saveState");
    }
    else
    {
        cout << "Unable to open state file for writing." << endl;
    }
}

// Loads the state of the shell from a file, recovering the list of files in the root directory.
void MyShell::loadState()
{
    ifstream stateFile("state.txt");

    if (stateFile.is_open())
    {
        string fileName;

        while (getline(stateFile, fileName))
        {
            cout << "Recovered file: " << fileName << endl;
        }

        stateFile.close();
        logOperation("loadState");
    }
    else
    {
        cout << "No previous state found." << endl;
    }
}

// void MyShell::saveDiskStatus()
// {
// 	disk->saveDiskStatus();
// }

// void MyShell::loadDiskStatus()
// {
// 	disk->loadDiskStatus();
// }

// Logs an operation by appending it to the operations log file.
void MyShell::logOperation(const std::string& operation) const{
    std::ofstream logFile;
    logFile.open("operations_log.txt", std::ios::out);

    if (!logFile.is_open()) {
        // Handle error, e.g., print an error message and return
        std::cerr << "Error opening log file\n";
        return;
    }

    logFile << operation << std::endl;
    logFile.close();
}

// Destructor deletes the root directory, freeing memory.
MyShell::~MyShell()
{
	delete root;
}