// Samuel Oseguera
// Date: 3/3/2025
// Assignment: Climate Data


// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
//#include "StateClimate.h"

// Class that stores climate data for state and year
class StateClimate {
    private:
        int fips; // FIPS code for state
        int year; // Year of the data
        double temp; // Temperature in Fahrenheit
        double tempc; // Temperature in Celsius
    
    public:
        // Constructor
        StateClimate(int f, int y, double t, double tc);
    
        // Getter functions
        int getFips() const;
        int getYear() const;
        double getTemp() const;
        double getTempC() const;
    
        // Setter functions 
        void setFips(int f);
        void setYear(int y);
        void setTemp(double t);
        void setTempC(double tc);
    
        // Display function
        void display() const;
};

// Constructor implementation
StateClimate::StateClimate(int f, int y, double t, double tc) : fips(f), year(y), temp(t), tempc(tc) {}

// Getter functions implementation
int StateClimate::getFips() const { return fips; }
int StateClimate::getYear() const { return year; }
double StateClimate::getTemp() const { return temp; }
double StateClimate::getTempC() const { return tempc; }

// Setter functions implementation
void StateClimate::setFips(int f) { fips = f; }
void StateClimate::setYear(int y) { year = y; }
void StateClimate::setTemp(double t) { temp = t; }
void StateClimate::setTempC(double tc) { tempc = tc; }

// Display function for climate data of a state
void StateClimate::display() const {
    std::cout << "FIPS: " << fips << ", Year: " << year 
              << ", Temp (F): " << temp << ", Temp (C): " << tempc << std::endl;
}


// Binary Search function for fips (exact match)
int binarySearch(const std::vector<StateClimate>& data, int targetFips) {
    int low = 0;
    int high = data.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (data[mid].getFips() == targetFips) {
            return mid; // Found the target FIPS
        }
        else if (data[mid].getFips() < targetFips) {
            low = mid + 1; // Search in the right half
        }
        else {
            high = mid - 1; // Search in the left half
        }
    }

    return -1; // If the FIPS is not found
}

// Main function that stores and processes climate data
int main() {
    std::vector<StateClimate> climateData;

    // Opens the climate data file
    std::ifstream file("climdiv_state_year.csv");
    
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Reads data from file and stores it in the vector
    std::string line;
    std::getline(file, line); // Skip header line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int fips, year;
        double temp, tempc;
        char comma;

        ss >> fips >> comma >> year >> comma >> temp >> comma >> tempc;
        climateData.emplace_back(fips, year, temp, tempc);
    }

    file.close();
    
    // User input loop for searching climate by FIPS code
    std::string input;
    do {
        std::cout << "Enter a state FIPS number to search (enter 'exit' to quit): ";
        std::cin >> input;

        if (input == "exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }

        int targetFips = std::stoi(input);
        int index = binarySearch(climateData, targetFips);
        if (index != -1) {
            climateData[index].display();
        } else {
            std::cout << "State not found. Please try again." << std::endl;
        }
        std::cout << std::endl; // Add a space after each run through
        std::cout << std::endl; // Add an extra space for readability
    } while (true);


   /*  // Display data
    for (const auto &entry : climateData) {
        entry.display();
    }
    */

    return 0;
}