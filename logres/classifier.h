#pragma once

#include <vector>

//!
//! \brief The BinaryClassifier class - base interface classifier class
//!

class BinaryClassifier
{
public:
    using features_t = std::vector<double>;

    virtual double predict_proba(const features_t &features) const = 0;
    virtual ~BinaryClassifier() = default;

};
