#include <string>
#include "..\MiniFilesystem\MiniFilesystem.h"
#include <tchar.h>
void _tmain(int argc, TCHAR *argv[])
{
    std::wstring path = L"\\\\?\\C:\\tmp\\empty_dir";
    JPFileInfo fi(path);
}