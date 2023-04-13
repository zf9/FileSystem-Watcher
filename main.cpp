#define _CRT_SECURE_NO_WARNINGS
#include "UI.h"
#include <iostream>

#include <fstream>



int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd){
	CreateDirectory(L"C:\\ProgramData\\Watcher", NULL);
	CreateDirectory(L"C:\\ProgramData\\Watcher\\Created", NULL);
	CreateDirectory(L"C:\\ProgramData\\Watcher\\Deleted", NULL);
	CreateDirectory(L"C:\\ProgramData\\Watcher\\Modified", NULL);
	CreateDirectory(L"C:\\ProgramData\\Watcher\\Renamed", NULL);
	CreateDirectory(L"C:\\ProgramData\\Watcher\\Error", NULL);
	CreateDirectory(L"C:\\ProgramData\\Watcher\\FileDumps", NULL);
	std::ofstream savefile("C:\\ProgramData\\Watcher\\IgnoredDirectory.log", std::ios::out | std::ios::app);
	if (!savefile) {
		std::cerr << "Error: Unable to open file for writing." << std::endl;
		return 1;
	}
	savefile.close();

	Sleep(100);

    UI::Render();
    return 0;
}
