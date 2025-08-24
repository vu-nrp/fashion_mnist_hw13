#pragma once

#include <vector>
#include <istream>
#include "classifier.h"

//!
//! \brief read_coefs - read model coefficients from file stream
//! \param stream - file stream
//! \param coefs - out coeffs
//! \return - true on success, false otherwise
//!

bool read_coefs(std::istream &stream, std::vector<double> &coefs);

//!
//! \brief read_features - read test data from file stream
//! \param stream - file stream
//! \param features - out test data
//! \param targetClass - out test data class
//! \return - true on success, false otherwise
//!

bool read_features(std::istream &stream, BinaryClassifier::features_t &features, int &targetClass);
