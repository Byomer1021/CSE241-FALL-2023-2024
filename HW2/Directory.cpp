#include "Directory.h"

#include <algorithm>

void Directory::ls() const
{
    cout << "D " << name << " " << getCurrentTime() << endl;
    for (const auto &file : contents)
    {
        file->ls();
    }
}

// Adds a file to the directory, checking if the total size limit is exceeded.
void Directory::addFile(File *file)
{
    if (canAddFile(file))
    {
        contents.push_back(file);
    }
    else
    {
        cout << "Cannot add file. Exceeds 10MB limit." << endl;
    }
}
// Checks if a file can be added to the directory without exceeding the size limit.
bool Directory::canAddFile(File *file) const
{
    // Determine the size of the file based on its type
    size_t fileSize = 0;

    if (dynamic_cast<RegularFile *>(file))
    {
        fileSize = dynamic_cast<RegularFile *>(file)->getContent().size();
    }
    else if (dynamic_cast<Directory *>(file))
    {

        fileSize = getDirectorySize(dynamic_cast<Directory *>(file));
    }
    else if (dynamic_cast<SoftLink *>(file))
    {

        fileSize = getSoftLinkSize(dynamic_cast<SoftLink *>(file));
    }

    // Check if the total size does not exceed the 10MB limit
    return getTotalSize() + fileSize <= 10 * 1024 * 1024;
}
// Returns the total size of the directory and its contents.
size_t Directory::getTotalSize() const
{
    size_t totalSize = 0;
    for (const auto &file : contents)
    {
        if (dynamic_cast<RegularFile *>(file))
        {
            totalSize += dynamic_cast<RegularFile *>(file)->getContent().size();
        }
        else if (dynamic_cast<Directory *>(file))
        {
            totalSize += getDirectorySize(dynamic_cast<Directory *>(file));
        }
        else if (dynamic_cast<SoftLink *>(file))
        {
            totalSize += getSoftLinkSize(dynamic_cast<SoftLink *>(file));
        }
    }
    return totalSize;
}
// Returns the total size of a directory and its contents.
size_t Directory::getDirectorySize(const Directory *directory) const
{
    size_t totalSize = 0;
    for (const auto &file : directory->getContents())
    {
        if (dynamic_cast<RegularFile *>(file))
        {
            totalSize += dynamic_cast<RegularFile *>(file)->getContent().size();
        }
        else if (dynamic_cast<Directory *>(file))
        {
            totalSize += getDirectorySize(dynamic_cast<Directory *>(file));
        }
        else if (dynamic_cast<SoftLink *>(file))
        {
            totalSize += getSoftLinkSize(dynamic_cast<SoftLink *>(file));
        }
    }
    return totalSize;
}
// Returns the size of a SoftLink (optional consideration of the target file's size).
size_t Directory::getSoftLinkSize(const SoftLink *softLink) const
{

    return 0;
}

// Removes a file from the directory.
void Directory::removeFile(File *file)
{
    auto it = find(contents.begin(), contents.end(), file);
    if (it != contents.end())
    {
        contents.erase(it);
        delete file; //delete the removed file.
    }
}

// Displays a message indicating that cat is not applicable to a directory.
void Directory::cat() const
{
    cout << "Cannot cat a directory." << endl;
}

// Returns the name of the directory.
string Directory::getName() const
{
    return name;
}

// Returns the parent directory.
File *Directory::getParent() const
{
    return parent;
}

// Returns a reference to the vector of contents.
const vector<File *> &Directory::getContents() const
{
    return contents;
}

// Destructor deletes all files in the directory.
Directory::~Directory()
{
    for (auto &file : contents)
    {
        delete file;
    }
}
