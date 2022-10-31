#pragma once
#include "common.h"

class FileManager {
private:
	FileManager() {}
	static std::vector<std::string> missingFiles;
public:
	template<typename T> static void LoadFormFile(T& t, const std::string& fileName);
	static bool getMissingFileList(std::string& fileList);

	inline static bool IsAnyFileMissing();
};

