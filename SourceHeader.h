#pragma once

std::vector<std::string> lines;
std::string line;


void removeLineFromFile(std::string fileName, std::string lineToRemove) {
	std::ifstream inputFile(fileName);
	std::ofstream outputFile("temp.txt");
	if (inputFile.is_open() && outputFile.is_open()) {
		std::string line;
		while (getline(inputFile, line)) {
			if (line == lineToRemove) {
				continue;  // skip this line
			}
			outputFile << line << std::endl;
		}
		inputFile.close();
		outputFile.close();
		remove(fileName.c_str());
		rename("temp.txt", fileName.c_str());
	}
}




std::wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}


std::string replaceDoubleBackslash(const std::string& str) {
	std::string newStr;
	for (std::size_t i = 0; i < str.size(); ++i) {
		if (str[i] == '\\' && str[i + 1] == '\\') {
			newStr += '\\';
			++i;
		}
		else {
			newStr += str[i];
		}
	}
	return newStr;
}
