// tcbot.cpp : Defines the entry point for the console application.
//
#undef UNICODE 
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <process.h>
#include <string>
using namespace std;
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Invalid args.\n");
		exit(0);
	}

	bool running = true;
	while (running)
	{
		Sleep(1000);

		HANDLE hFind = INVALID_HANDLE_VALUE;

		string srcPath = argv[1];
		srcPath += "\\*.mkv";

		string dstPath = argv[2];

		TCHAR tcSrcDir[MAX_PATH];
		StringCchCopy(tcSrcDir, MAX_PATH, srcPath.c_str());

		WIN32_FIND_DATA ffd;

		hFind = FindFirstFile(tcSrcDir, &ffd);

		if (INVALID_HANDLE_VALUE != hFind)
		{
			do
			{
				if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					string fileName = ffd.cFileName;
					string srcFullPathToFile = argv[1];
					srcFullPathToFile += "\\";
					srcFullPathToFile += fileName;

					string baseName = fileName.substr(0, fileName.length() - 4);

					string outputFileName = "\"" + dstPath + "\\" + baseName + ".mkv" + "\"";

					string cmdLine = "tc.bat \"" + srcFullPathToFile + "\" " + outputFileName;

					printf("cmdLine = %s\n", cmdLine.c_str());

					if (system(cmdLine.c_str()) == 0)
					{
						printf("Transcode succeeded. Unlinking source file.\n");
						_unlink(srcFullPathToFile.c_str());

						//printf("baseName = %s\n", baseName.c_str());
						//printf("%s\n", srcFullPathToFile.c_str());
					}
					else
					{
						printf("Transcode failed. Moving source file to Broken.\n");
						string brokenPath = argv[1];
						brokenPath += "\\Broken\\";
						brokenPath += fileName;
						MoveFile(srcFullPathToFile.c_str(), brokenPath.c_str());
					}
				}
			} while (FindNextFile(hFind, &ffd) != 0);
		}
	}

	return 0;
}
