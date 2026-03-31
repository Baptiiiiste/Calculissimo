#include "storage/FileManager.hpp"
#include <fstream>
#include <sstream>

namespace calculissimo::storage {

/// Charge le fichier du user pour récupérer ses statistiques, ...
std::unordered_map<std::string, std::string> FileManager::load(const std::string& filePath) {
    std::unordered_map<std::string, std::string> data;
    std::ifstream file(filePath);

    // Fichier existe pas
    if (!file.is_open()) {
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Lecture du format CLE = VALEUR
        const auto separatorPos = line.find('=');
        if (separatorPos == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, separatorPos);
        std::string value = line.substr(separatorPos + 1);
        data[key] = value;
    }

    return data;
}

/// Sauvegarde les stats du joueur dans le fichier
void FileManager::save(const std::string& filePath, const std::unordered_map<std::string, std::string>& data) {
    std::ofstream file(filePath, std::ios::trunc);

    if (!file.is_open()) {
        return;
    }

    // Format CLE = VALEUR
    for (const auto& [key, value] : data) {
        file << key << '=' << value << '\n';
    }
}

}
