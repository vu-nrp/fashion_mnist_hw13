#include <fstream>
#include <iostream>
#include "logres/helpers.h"
#include "logres/logreg_classifier.h"

//!
//! \brief main - app entry point
//!

int main(int argc, char *argv[])
{
//    std::cout << "Home work #13. LogRegression inference algorithm" << std::endl;

    if (argc != 3) {
        std::cout << "Usage: fashion_mnist <test_csv_file> <logreg_coef_file>" << std::endl;
        return 1;
    }

    // read coefficients file
    std::ifstream coef_stream(argv[2]);
    if (!coef_stream.is_open()) {
        std::cout << "Error: while open coefficients file:" << argv[2] << std::endl;
        return 1;
    }

    LogregClassifier::coef_t coefs;
    std::vector<LogregClassifier> predictors;

    while (read_coefs(coef_stream, coefs))
        predictors.emplace_back(coefs);
    coef_stream.close();
	
    // read test data file
    std::ifstream test_data_stream(argv[1]);
    if (!test_data_stream.is_open()) {
        std::cout << "Error: while open test data file:" << argv[1] << std::endl;
        return 1;
    }

    int totalCount = 0;
    int targetClass = 0;
    int rightAnswerCount = 0;
    LogregClassifier::features_t features;
    const auto predictorsSize = predictors.size();

    try {
        // take features and target class
        while (read_features(test_data_stream, features, targetClass)) {
            double maxResult = -1.0;
            int maxResultClass = -1;

            // serach for best probability
            for (size_t i = 0; i < predictorsSize; ++i) {
                const auto result = predictors[i].predict_proba(features);
                if (result > maxResult) {
                    maxResult = result;
                    maxResultClass = i;
                }
            }

            if (maxResultClass == targetClass)
                rightAnswerCount++;

            totalCount++;
        }
        test_data_stream.close();

        double accuracy = 0.0;
        if (totalCount > 0)
            accuracy = static_cast<double>(rightAnswerCount) / totalCount;

        std::cout << "accuracy: " << accuracy << std::endl;
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
