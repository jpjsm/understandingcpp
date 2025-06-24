
#include <string>
#include <stdexcept>
#include "MiniFilesystem.h"
#include <Windows.h>

JPFileInfo::JPFileInfo(std::wstring path)
{
    if (path.empty())
    {
        throw std::invalid_argument("Path cannot be empty.");
    }

    WIN32_FIND_DATAW ffdi;
    HANDLE hfd = INVALID_HANDLE_VALUE;
    hfd = FindFirstFileW(path.c_str(), &ffdi);
    if (hfd == INVALID_HANDLE_VALUE)
    {
        throw std::invalid_argument("Path not found.");
    }

    fullpath = path;
}
