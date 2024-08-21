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


std::vector<DataRow> filterData(const std::vector<DataRow>& data, double threshold) {
    std::vector<DataRow> result;

    for (const auto& row : data) {
        if (row.value > threshold) {
            result.push_back(row);
        }
    }
    return result;
}

double sumValues(const std::vector<DataRow>& data) {
    double sum = 0;
    for (const auto& row : data) {
        sum += row.value;
    }
    return sum;
}


int main() {
    std::vector<DataRow> data = readData("data.csv");
    std::cout << "Loaded " << data.size() << " rows." << std::endl;

    double minValue = 98.0;

    auto filteredData = filterData(data, minValue);
    std::cout << "Filtered " << filteredData.size() << " rows with value > " << minValue << std::endl;

    double sum = sumValues(filteredData);
    std::cout << "Sum of filtered values: " << sum << std::endl;

    return 0;
}
