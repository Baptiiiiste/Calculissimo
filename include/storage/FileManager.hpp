#pragma once

#include <string>
#include <unordered_map>

namespace calculissimo::storage {

    class FileManager {
        public:
            static std::unordered_map<std::string, std::string> load(const std::string& filePath);
            static void save(const std::string& filePath, const std::unordered_map<std::string, std::string>& data);
    };

}
