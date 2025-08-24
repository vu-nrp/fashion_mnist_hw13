#include <cmath>
#include <numeric>
#include "logreg_classifier.h"

//!
//! \brief sigma - sigma calc template
//!

template<typename T>
auto sigma(const T x)
{
    return 1.0 / (1.0 + std::exp(-x));
}

//!
//! \brief LogregClassifier
//!

LogregClassifier::LogregClassifier(const coef_t &coefficients) :
    m_coef(coefficients)
{
}

double LogregClassifier::predict_proba(const features_t &features) const
{
    const auto s = std::inner_product(features.begin(), features.end(), ++m_coef.begin(), m_coef.front());
    return sigma(s);
}
