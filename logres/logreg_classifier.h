#pragma once

#include "classifier.h"

//!
//! \brief The LogregClassifier class - logregression calc class
//!

class LogregClassifier : public BinaryClassifier
{
public:
    using coef_t = features_t;

    LogregClassifier(const coef_t &coefficients);

    double predict_proba(const features_t &features) const override;

protected:
    coef_t m_coef;

};
