#include <sstream>
#include "helpers.h"

//!
//! \brief read_coefs
//!

bool read_coefs(std::istream &stream, std::vector<double> &coefs)
{
    double value;
    std::string line;
    std::getline(stream, line);
    std::istringstream linestream(line);

    coefs.clear();
    while (linestream >> value)
        coefs.push_back(value);
    return stream.good();
}

//!
//! \brief read_features
//!

bool read_features(std::istream &stream, BinaryClassifier::features_t &features, int &targetClass)
{
    std::string line;
    std::getline(stream, line);
    std::istringstream linestream(line);

    std::string str;
    bool first = true;

    features.clear();
    while (std::getline(linestream, str, ',')) {
        if (first) {
            first = false;
            targetClass = std::stoi(str);
        } else {
            features.push_back(std::stoi(str));
        }
    }
    return stream.good();
}
