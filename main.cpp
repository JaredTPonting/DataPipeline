#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct DataRow
{
    int id;
    double value;
    std::string name;
};

std::vector<DataRow> readData(const std::string& filename) {
    std::vector<DataRow> data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return data;
    }

    std::getline(file, line); // Skip header line
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        DataRow row;

        std::getline(iss, token, ',');
        row.id = std::stoi(token);

        std::getline(iss, token, ',');
        row.value = std::stod(token);

        std::getline(iss, token, ',');
        row.name = token;

        data.push_back(row);
    }

    file.close();
    return data;
}

int main() {
    std::vector<DataRow> data = readData("data.csv");
    std::cout << "Loaded " << data.size() << " rows." << std::endl;
    return 0;
}
