#include "Drawing.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "SourceHeader.h"
#include "WatcherThread.h"
#include "ImGuiTheme.h"

LPCSTR Drawing::lpWindowName = "Watcher 2.0 [BETA] github.com/zf9";
ImVec2 Drawing::vWindowSize = { 1100, 600 };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
bool Drawing::bDraw = true;
bool AutoScroll = true;
bool ABC123 = true;
char AddToFileChar[512];


void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
{
	return bDraw == true;
}



void Drawing::Draw(){
	if (isActive()){
        if (ABC123 == true) {
			const int result = MessageBox(NULL, L"Would you like to enable dumper?", L"Watcher 2.0 [BETA]", MB_YESNO);
			switch (result)
			{
			case IDYES:
				FileDumper = true;
				break;
			case IDNO:
				FileDumper = false;
				break;
			}
			CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
			EnableTheme();
            ImGui::SetNextWindowSize(vWindowSize);

			std::ifstream file("C:\\ProgramData\\Watcher\\IgnoredDirectory.log");
			lines.clear();
			if (file.is_open()) {
				while (getline(file, line)) {
					lines.push_back(line);
				}
				file.close();
			}
			else {
			}

            ABC123 = false;
        }

		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin(lpWindowName, &bDraw, WindowFlags);
		{
            if (ImGui::BeginTabBar("MyTabBar", ImGuiTabBarFlags_None)){
				if (ImGui::BeginTabItem("All")) {
					if (ImGui::BeginTable("Table", 1, ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Borders | ImGuiTableColumnFlags_Disabled)) {
						std::ifstream file("C:\\ProgramData\\Watcher\\AllDump.txt");

						if (file) {
							std::stringstream buffer;
							buffer << file.rdbuf();
							std::string content = buffer.str();
							file.close();

							std::vector<std::string> lines;
							size_t pos = 0, found;
							while ((found = content.find_first_of('\n', pos)) != std::string::npos) {
								lines.push_back(content.substr(pos, found - pos));
								pos = found + 1;
							}
							lines.push_back(content.substr(pos));

							for (const auto& line : lines) {
								ImGui::TableNextRow(ImGuiTableRowFlags_None);
								ImGui::TableNextColumn();

								if (line.find("Created") != std::string::npos) {
									ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0, 255, 0, 255).Value);
									if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
										if (ImGui::IsMouseDoubleClicked(0)) {
											ImGui::SetClipboardText(line.c_str());
										}
									}
									ImGui::PopStyleColor();
								}
								else if (line.find("Deleted") != std::string::npos) {
									ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 0, 0, 255).Value);
									if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
										if (ImGui::IsMouseDoubleClicked(0)) {
											ImGui::SetClipboardText(line.c_str());
										}
									}
									ImGui::PopStyleColor();
								}
								else if (line.find("Modified") != std::string::npos) {
									ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0, 255, 255, 255).Value);
									if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
										if (ImGui::IsMouseDoubleClicked(0)) {
											ImGui::SetClipboardText(line.c_str());
										}
									}
									ImGui::PopStyleColor();
								}
								else if (line.find("Renamed") != std::string::npos) {
									ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 0, 255).Value);
									if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
										if (ImGui::IsMouseDoubleClicked(0)) {
											ImGui::SetClipboardText(line.c_str());
										}
									}
									ImGui::PopStyleColor();
								}
								if (AutoScroll == true) {
									ImGui::SetScrollHereY(0.999f);
								}

							}
						}

						ImGui::EndTable();
					}
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Created")) {
					if (ImGui::BeginTable("Table", 1, ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Borders | ImGuiTableColumnFlags_Disabled)) {
						std::ifstream file("C:\\ProgramData\\Watcher\\Created\\Created.txt");

						if (file) {
							std::stringstream buffer;
							buffer << file.rdbuf();
							std::string content = buffer.str();
							file.close();

							std::vector<std::string> lines;
							size_t pos = 0, found;
							while ((found = content.find_first_of('\n', pos)) != std::string::npos) {
								lines.push_back(content.substr(pos, found - pos));
								pos = found + 1;
							}
							lines.push_back(content.substr(pos));

							for (const auto& line : lines) {
								ImGui::TableNextRow(ImGuiTableRowFlags_None);
								ImGui::TableNextColumn();

								if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
									if (ImGui::IsMouseDoubleClicked(0)) {
										ImGui::SetClipboardText(line.c_str());
									}
								}

								if (AutoScroll == true) {
									ImGui::SetScrollHereY(0.999f);
								}
							}
						}

						ImGui::EndTable();
					}
					ImGui::EndTabItem();
				}
                if (ImGui::BeginTabItem("Deleted")){
					if (ImGui::BeginTable("Table", 1, ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Borders | ImGuiTableColumnFlags_Disabled)) {
						std::ifstream file("C:\\ProgramData\\Watcher\\Deleted\\Deleted.txt");

						if (file) {
							std::stringstream buffer;
							buffer << file.rdbuf();
							std::string content = buffer.str();
							file.close();

							std::vector<std::string> lines;
							size_t pos = 0, found;
							while ((found = content.find_first_of('\n', pos)) != std::string::npos) {
								lines.push_back(content.substr(pos, found - pos));
								pos = found + 1;
							}
							lines.push_back(content.substr(pos));

							for (const auto& line : lines) {
								ImGui::TableNextRow(ImGuiTableRowFlags_None);
								ImGui::TableNextColumn();

								if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
									if (ImGui::IsMouseDoubleClicked(0)) {
										ImGui::SetClipboardText(line.c_str());
									}
								}

								if (AutoScroll == true) {
									ImGui::SetScrollHereY(0.999f);
								}
							}
						}

						ImGui::EndTable();
					}
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Modified")){
					if (ImGui::BeginTable("Table", 1, ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Borders | ImGuiTableColumnFlags_Disabled)) {
						std::ifstream file("C:\\ProgramData\\Watcher\\Modified\\Modified.txt");

						if (file) {
							std::stringstream buffer;
							buffer << file.rdbuf();
							std::string content = buffer.str();
							file.close();

							std::vector<std::string> lines;
							size_t pos = 0, found;
							while ((found = content.find_first_of('\n', pos)) != std::string::npos) {
								lines.push_back(content.substr(pos, found - pos));
								pos = found + 1;
							}
							lines.push_back(content.substr(pos));

							for (const auto& line : lines) {
								ImGui::TableNextRow(ImGuiTableRowFlags_None);
								ImGui::TableNextColumn();

								if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
									if (ImGui::IsMouseDoubleClicked(0)) {
										ImGui::SetClipboardText(line.c_str());
									}
								}

								if (AutoScroll == true) {
									ImGui::SetScrollHereY(0.999f);
								}
							}
						}

						ImGui::EndTable();
					}
					ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Renamed")) {
					if (ImGui::BeginTable("Table", 1, ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Borders | ImGuiTableColumnFlags_Disabled)) {
						std::ifstream file("C:\\ProgramData\\Watcher\\Renamed\\Renamed.txt");

						if (file) {
							std::stringstream buffer;
							buffer << file.rdbuf();
							std::string content = buffer.str();
							file.close();

							std::vector<std::string> lines;
							size_t pos = 0, found;
							while ((found = content.find_first_of('\n', pos)) != std::string::npos) {
								lines.push_back(content.substr(pos, found - pos));
								pos = found + 1;
							}
							lines.push_back(content.substr(pos));

							for (const auto& line : lines) {
								ImGui::TableNextRow(ImGuiTableRowFlags_None);
								ImGui::TableNextColumn();

								if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
									if (ImGui::IsMouseDoubleClicked(0)) {
										ImGui::SetClipboardText(line.c_str());
									}
								}

								if (AutoScroll == true) {
									ImGui::SetScrollHereY(0.999f);
								}
							}
						}

						ImGui::EndTable();
					}
					ImGui::EndTabItem();
                }
				if (ImGui::BeginTabItem("Error Logs")) {
					if (ImGui::BeginTable("Table", 1, ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Borders | ImGuiTableColumnFlags_Disabled)) {
						std::ifstream file("C:\\ProgramData\\Watcher\\Error\\Message.txt");

						if (file) {
							std::stringstream buffer;
							buffer << file.rdbuf();
							std::string content = buffer.str();
							file.close();

							std::vector<std::string> lines;
							size_t pos = 0, found;
							while ((found = content.find_first_of('\n', pos)) != std::string::npos) {
								lines.push_back(content.substr(pos, found - pos));
								pos = found + 1;
							}
							lines.push_back(content.substr(pos));

							for (const auto& line : lines) {
								ImGui::TableNextRow(ImGuiTableRowFlags_None);
								ImGui::TableNextColumn();

								if (line.find("Created") != std::string::npos) {
									ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0, 255, 0, 255).Value);
									if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
										if (ImGui::IsMouseDoubleClicked(0)) {
											ImGui::SetClipboardText(line.c_str());
										}
									}
									ImGui::PopStyleColor();
								}
								else if (line.find("Deleted") != std::string::npos) {
									ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 0, 0, 255).Value);
									if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
										if (ImGui::IsMouseDoubleClicked(0)) {
											ImGui::SetClipboardText(line.c_str());
										}
									}
									ImGui::PopStyleColor();
								}
								else if (line.find("Modified") != std::string::npos) {
									ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0, 255, 255, 255).Value);
									if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
										if (ImGui::IsMouseDoubleClicked(0)) {
											ImGui::SetClipboardText(line.c_str());
										}
									}
									ImGui::PopStyleColor();
								}
								else if (line.find("Renamed") != std::string::npos) {
									ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 0, 255).Value);
									if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
										if (ImGui::IsMouseDoubleClicked(0)) {
											ImGui::SetClipboardText(line.c_str());
										}
									}
									ImGui::PopStyleColor();
								}
								else{
									if (ImGui::Selectable(line.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
										if (ImGui::IsMouseDoubleClicked(0)) {
											ImGui::SetClipboardText(line.c_str());
										}
									}
								}

								if (AutoScroll == true) {
									ImGui::SetScrollHereY(0.999f);
								}
							}
						}

						ImGui::EndTable();
					}
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Other")) {
					if (ImGui::Button("Clear All Logs")) {
						system("del /f /q C:\\ProgramData\\Watcher\\Created\\Created.txt");
						system("del /f /q C:\\ProgramData\\Watcher\\Deleted\\Deleted.txt");
						system("del /f /q C:\\ProgramData\\Watcher\\Modified\\Modified.txt");
						system("del /f /q C:\\ProgramData\\Watcher\\Renamed\\Renamed.txt");
						system("del /f /q C:\\ProgramData\\Watcher\\AllDump.txt");
						system("del /f /q C:\\ProgramData\\Watcher\\Error\\Message.txt");

						TCHAR szExeFileName[MAX_PATH];
						GetModuleFileName(NULL, szExeFileName, MAX_PATH);
						MessageBox(NULL, L"Application Restart Required", L"Watcher 2.0 [BETA]", MB_ICONEXCLAMATION | MB_OK);
						std::string strtmp(&szExeFileName[0], &szExeFileName[255]);
						ShellExecuteA(NULL, "open", strtmp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
						exit(9);
					}
					if (ImGui::Button("Clear All Dumped Files")) {
						EnableWatcher = false;
						Sleep(10);
						system("del /f /q C:\\ProgramData\\Watcher\\AllDump.txt");
						system("rmdir /s /q C:\\ProgramData\\Watcher\\FileDumps");


						TCHAR szExeFileName[MAX_PATH];
						GetModuleFileName(NULL, szExeFileName, MAX_PATH);
						MessageBox(NULL, L"Application Restart Required", L"Watcher 2.0 [BETA]", MB_ICONEXCLAMATION | MB_OK);
						std::string strtmp(&szExeFileName[0], &szExeFileName[255]);
						ShellExecuteA(NULL, "open", strtmp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
						exit(9);
					}
					if (ImGui::Button("Delete All Created Files And Exit")) {
						system("rmdir /s /q C:\\ProgramData\\Watcher");
						exit(9);
					}
					ImGui::Checkbox("AutoScroll", &AutoScroll);
					ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine();
					ImGui::Text("Ignored Directories:");
					ImGui::TextColored(ImColor(255, 0, 0, 255), "C:\\ProgramData\\Watcher");
					for (const std::string& s : lines) {
						ImGui::TextColored(ImColor(255, 0, 100, 255), s.c_str());
						ImGui::SameLine();
						std::string label = "Remove##" + s;
						if (ImGui::Button(label.c_str())) {
							removeLineFromFile("C:\\ProgramData\\Watcher\\IgnoredDirectory.log", s.c_str());
							std::ifstream file("C:\\ProgramData\\Watcher\\IgnoredDirectory.log");
							lines.clear();
							if (file.is_open()) {
								while (getline(file, line)) {
									lines.push_back(line);
								}
								file.close();
							}
							else {
								MessageBox(NULL, L"Unable to open file\nContact Support Error: AUTO_UPDATE_removeLineFromFile", L"Watcher 2.0 [BETA]", MB_ICONEXCLAMATION | MB_OK);
							}
						}
					}
					ImGui::InputText("##IgnorePath", AddToFileChar, IM_ARRAYSIZE(AddToFileChar));
					if (ImGui::Button("Add Input To File")) {
						std::string AddToFile(AddToFileChar);
						size_t pos = AddToFile.find("\\\\");
						while (pos != std::string::npos) {
							AddToFile.replace(pos, 2, "\\");
							pos = AddToFile.find("\\\\", pos + 1);
						}
						std::ofstream savefile("C:\\ProgramData\\Watcher\\IgnoredDirectory.log", std::ios_base::app);
						savefile << AddToFile << "\n";
						savefile.close();
					}
					ImGui::SameLine();
					if (ImGui::Button("Manual Update Ignore Path Cache")) {
						std::ifstream file("C:\\ProgramData\\Watcher\\IgnoredDirectory.log");
						lines.clear();
						if (file.is_open()) {
							while (getline(file, line)) {
								lines.push_back(line);
							}
							file.close();
						}
						else {
							MessageBox(NULL, L"Unable to open file\nContact Support Error: AUTO_UPDATE_UpdateIgnorePathCache", L"Watcher 2.0 [BETA]", MB_ICONEXCLAMATION | MB_OK);
						}
					}

					ImGui::EndTabItem();
				}
                ImGui::EndTabBar();
            }
			//ImGui::Text("Test");
		}
		ImGui::End();
	}
}
