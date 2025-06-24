#pragma once

#ifdef MiniFileSystem_EXPORTS
#define MiniFileSystem_API __declspec(dllexport) 
#else
#define MiniFileSystem_API __declspec(dllimport) 
#endif

#ifndef MiniFileSystem
#define MiniFileSystem

#include <string>

class JPFileInfo
{
    std::wstring fullpath;

public:
    MiniFileSystem_API JPFileInfo(std::wstring);
};

#endif