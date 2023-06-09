#pragma once
#include <iostream>
#include "FileWatcher.hpp"
#include <filesystem>
#include <fstream>

bool FileDumper = false;
bool EnableWatcher = true;

DWORD WINAPI ThreadFunc(void* data) {
	if (EnableWatcher == true) {
		std::filesystem::path inputPath = "C:\\";
		std::filesystem::path pathToObeserve{ !inputPath.empty() ? inputPath : std::filesystem::current_path() };
		std::error_code error;
		FileWatcher fileWatcher(pathToObeserve,
			[](
				const std::filesystem::path filepath,
				const std::optional<std::filesystem::path> renamedNew,
				const EFileAction fileAction,
				const std::error_code ec
				) noexcept
			{
				if (fileAction == EFileAction::Error) {
					if (!filepath.empty())
						//std::wcout << filepath << '\n';
						return;
				}
		if (ec) {
			std::cerr << "File watcher error: " << ec.value() << ", " << ec.message() << '\n';
			return;
		}
		else {	
			if (filepath.string().find("C:\\ProgramData\\Watcher") != std::string::npos) {
				return;
			}
			

			std::ifstream filet("C:\\ProgramData\\Watcher\\IgnoredDirectory.log");
			if (filet.is_open()) {
				while (getline(filet, line)) {
					if (filepath.string().find(line) != std::string::npos) {
						return;
					}
				}
				filet.close();
			}
			else {
				MessageBox(NULL, L"Unable to open file\nContact Support Error: AUTO_UPDATE_filet\n\n[DEBUG] Ignore This Error", L"Watcher 2.0 [BETA]", MB_ICONEXCLAMATION | MB_OK);
			}

			switch (fileAction) {
			case EFileAction::Created:
			{
				std::ofstream savefile("C:\\ProgramData\\Watcher\\Created\\Created.txt", std::ios_base::app);
				savefile << filepath << "\n";
				savefile.close();

				std::ofstream AllDump("C:\\ProgramData\\Watcher\\AllDump.txt", std::ios_base::app);
				AllDump << "Created: " << filepath << "\n";
				AllDump.close();

				if (FileDumper == true) {
					try {
						std::filesystem::path path(filepath);
						std::string file_name = path.filename().string();
						std::filesystem::copy(filepath, "C:\\ProgramData\\Watcher\\FileDumps\\" + file_name);
					}
					catch (const std::exception& ex) {
						std::ofstream ErrorLog("C:\\ProgramData\\Watcher\\Error\\Message.txt", std::ios_base::app);
						ErrorLog << "Error: Created: | " << ex.what() << "\n";
						ErrorLog.close();
					}
				}
			}
			break;
			case EFileAction::Deleted:
			{
				std::ofstream savefile("C:\\ProgramData\\Watcher\\Deleted\\Deleted.txt", std::ios_base::app);
				savefile << filepath << "\n";
				savefile.close();

				std::ofstream AllDump("C:\\ProgramData\\Watcher\\AllDump.txt", std::ios_base::app);
				AllDump << "Deleted: " << filepath << "\n";
				AllDump.close();

				if (FileDumper == true) {
					try {
						std::filesystem::path path(filepath);
						std::string file_name = path.filename().string();
						std::filesystem::copy(filepath, "C:\\ProgramData\\Watcher\\FileDumps\\" + file_name);
					}
					catch (const std::exception& ex) {
						std::ofstream ErrorLog("C:\\ProgramData\\Watcher\\Error\\Message.txt", std::ios_base::app);
						ErrorLog << "Error: Deleted: | " << ex.what() << "\n";
						ErrorLog.close();
					}
				}
			}
			break;
			case EFileAction::Modified:
			{
				std::ofstream savefile("C:\\ProgramData\\Watcher\\Modified\\Modified.txt", std::ios_base::app);
				savefile << filepath << "\n";
				savefile.close();

				std::ofstream AllDump("C:\\ProgramData\\Watcher\\AllDump.txt", std::ios_base::app);
				AllDump << "Modified: " << filepath << "\n";
				AllDump.close();

				if (FileDumper == true) {
					try {
						std::filesystem::path path(filepath);
						std::string file_name = path.filename().string();
						std::filesystem::copy(filepath, "C:\\ProgramData\\Watcher\\FileDumps\\" + file_name);
					}
					catch (const std::exception& ex) {
						std::ofstream ErrorLog("C:\\ProgramData\\Watcher\\Error\\Message.txt", std::ios_base::app);
						ErrorLog << "Error: Modified: | " << ex.what() << "\n";
						ErrorLog.close();
					}
				}
			}
			break;
			case EFileAction::Renamed:
			{
				assert(renamedNew.has_value());
				if (filepath.string().find("C:\\ProgramData\\Watcher\\") == std::string::npos) {
					std::ofstream savefile("C:\\ProgramData\\Watcher\\Renamed\\Renamed.txt", std::ios_base::app);
					savefile << "Renamed: " << filepath << " to " << renamedNew.value() << "\n";
					savefile.close();

					std::ofstream AllDump("C:\\ProgramData\\Watcher\\AllDump.txt", std::ios_base::app);
					AllDump << "Renamed: " << filepath << " to " << renamedNew.value() << "\n";
					AllDump.close();
				}

			} break;

			case EFileAction::Error:
			{
				if (!ec) {
					std::ofstream savefile("C:\\ProgramData\\Watcher\\Error\\Unknown.txt", std::ios_base::app);
					savefile << "Unknown filewatcher error had occured" << "\n";
					savefile.close();
					exit(2);
				}
				//std::cerr << "Unknown filewatcher error had occured\n";
			}
			break;
			}
		}
			}, false, error);

		if (error)
		{
			//std::cout << error.message() << '\n';
			std::ofstream savefile("C:\\ProgramData\\Watcher\\Error\\Message.txt", std::ios_base::app);
			savefile << error.message() << "\n";
			savefile.close();
			exit(2);
		}

		while (fileWatcher.IsWatching())
		{
		}

		if (error) {
			std::ofstream savefile("C:\\ProgramData\\Watcher\\Error\\Message.txt", std::ios_base::app);
			savefile << error.message() << "\n";
			savefile.close();
			//		std::cout << error.message() << '\n';
		}
	}
}