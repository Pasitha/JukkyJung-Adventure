#include "FileManager.h"

std::vector<std::string> FileManager::missingFiles;

template<typename T> void FileManager::LoadFormFile(T& t, const std::string& fileName) {
	if (!t.loadFromFile(fileName)) {
		missingFiles.push_back(fileName);
	}
}

bool FileManager::getMissingFileList(std::string& fileList) {
	if (missingFiles.empty()) {
		return false;
	}
	else {
		for (auto it : missingFiles) {
			fileList += it + '\n';
		}
		return true;
	}
}

bool FileManager::IsAnyFileMissing() {
	return !missingFiles.empty();
}
