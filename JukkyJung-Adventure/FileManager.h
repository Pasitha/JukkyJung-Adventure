#pragma once
#include "common.h"

class FileManager {
public:
	static std::vector<std::string> missingFiles;
private:
	template<typename T> static void LoadFormFile(T& t, const std::string& fileName);
	static bool getMissingFileList(std::string& fileList);

	inline static bool IsAnyFileMissing();
};

