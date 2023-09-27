#include "LogicHandler.h"
#include <QStringList>
#include <algorithm>
#include <vector>
#include <cmath>


/* Constructor for LogicHandler class */
LogicHandler::LogicHandler(QObject *parent) : QObject(parent)
{
}

/* 
 * Converts a string of comma separated values to a vector of doubles.
 * Parameters:
 *  - data: QString containing comma separated values.
 * Returns:
 *  - QVector<double> containing the values as doubles.
 */
QVector<double> LogicHandler::convertStringToVector(const QString &data) {
    QStringList strList = data.split(",");
    QVector<double> values;
    foreach (const QString& str, strList) {
        bool ok;
        double value = str.toDouble(&ok);
        if (ok) {
            values.append(value);
        }
    }
    return values;
}


/* 
 * Calculates the average of a vector of values.
 * Parameters:
 *  - values: Input data as a vector of doubles.
 * Returns:
 *  - double: The average value.
 */
double LogicHandler::calculateAverage(const QVector<double> &values) {
    if (values.isEmpty()) {
        return 0;  // Return 0 if vector is empty
    }
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    return sum / values.size();
}

/* 
 * Converts a vector of doubles to a comma separated string.
 * Parameters:
 *  - values: Input data as a vector of doubles.
 * Returns:
 *  - QString: Comma separated string of values.
 */
QString LogicHandler::convertVectorToString(const QVector<double> &values) {
    QStringList stringList;
    for (double value : values) {
        stringList.append(QString::number(value));
    }
    return stringList.join(",");
}

/* 
 * Applies various filters and computes averages based on the input parameters.
 * Parameters:
 *  - isThetaChecked, isBeta1Checked, isBeta2Checked: Flags for applying Ferra filter.
 *  - theta, beta1, beta2: Input data as comma separated strings.
 *  - lineEdit_avg_theta, lineEdit_avg_beta1, lineEdit_avg_beta2: QLineEdit objects for displaying the averages.
 *  - isExponentialFilteringChecked, isDataInterpolationChecked, isMedianFilteringChecked, isNormalizationChecked, isSavitzkyGolayChecked: Flags for applying other filters.
 */
void LogicHandler::applyFiltersAndComputeAverages(
    bool isThetaChecked, bool isBeta1Checked, bool isBeta2Checked,
    const QString &theta, const QString &beta1, const QString &beta2,
    QLineEdit *lineEdit_avg_theta, QLineEdit *lineEdit_avg_beta1, QLineEdit *lineEdit_avg_beta2,
    bool isExponentialFilteringChecked, bool isDataInterpolationChecked,
    bool isMedianFilteringChecked, bool isNormalizationChecked, bool isSavitzkyGolayChecked
) {
    // Convert strings to vectors of values
    QVector<double> thetaValues = convertStringToVector(theta);
    QVector<double> beta1Values = convertStringToVector(beta1);
    QVector<double> beta2Values = convertStringToVector(beta2);

    // Apply Ferra filtering if checked
    if (isThetaChecked) {
        thetaValues = ferraFilter(thetaValues, 300, 4, 0.2);
    }
    if (isBeta1Checked) {
        beta1Values = ferraFilter(beta1Values, 20, 10, 0.2);
    }
    if (isBeta2Checked) {
        beta2Values = ferraFilter(beta2Values, 20, 10, 0.2);
    }

    // Apply other filters if checked
    if (isExponentialFilteringChecked) {
        thetaValues = convertStringToVector(exponentialFiltering(convertVectorToString(thetaValues)));
        beta1Values = convertStringToVector(exponentialFiltering(convertVectorToString(beta1Values)));
        beta2Values = convertStringToVector(exponentialFiltering(convertVectorToString(beta2Values)));
    }

    if (isDataInterpolationChecked) {
        thetaValues = convertStringToVector(dataInterpolation(convertVectorToString(thetaValues)));
        beta1Values = convertStringToVector(dataInterpolation(convertVectorToString(beta1Values)));
        beta2Values = convertStringToVector(dataInterpolation(convertVectorToString(beta2Values)));
    }

    if (isMedianFilteringChecked) {
        thetaValues = convertStringToVector(medianFiltering(convertVectorToString(thetaValues)));
        beta1Values = convertStringToVector(medianFiltering(convertVectorToString(beta1Values)));
        beta2Values = convertStringToVector(medianFiltering(convertVectorToString(beta2Values)));
    }

    if (isNormalizationChecked) {
        thetaValues = convertStringToVector(normalization(convertVectorToString(thetaValues)));
        beta1Values = convertStringToVector(normalization(convertVectorToString(beta1Values)));
        beta2Values = convertStringToVector(normalization(convertVectorToString(beta2Values)));
    }

    if (isSavitzkyGolayChecked) {
        thetaValues = convertStringToVector(savitzkyGolaySmoothing(convertVectorToString(thetaValues)));
        beta1Values = convertStringToVector(savitzkyGolaySmoothing(convertVectorToString(beta1Values)));
        beta2Values = convertStringToVector(savitzkyGolaySmoothing(convertVectorToString(beta2Values)));
    }

    // Calculate average
    lineEdit_avg_theta->setText(QString::number(calculateAverage(thetaValues)));
    lineEdit_avg_beta1->setText(QString::number(calculateAverage(beta1Values)));
    lineEdit_avg_beta2->setText(QString::number(calculateAverage(beta2Values)));
}



// FIRST FILTER

/* 
 * Applies Ferra filtering on the input data.
 * Parameters:
 *  - values: Input data as a vector of doubles.
 *  - maxLimit, multiple, reductionFactor: Parameters for Ferra filtering.
 * Returns:
 *  - QVector<double> containing the filtered values.
 */
QVector<double> LogicHandler::ferraFilter(const QVector<double> &values, double maxLimit, double multiple, double reductionFactor) {
    if (values.isEmpty() || values.size() < 4) {
        return QVector<double>();  // Return empty vector if insufficient data
    }

    double sumOriginal = std::accumulate(values.begin(), values.end(), 0.0);
    double averageOriginal = sumOriginal / values.size();

    double maxValue = *std::max_element(values.begin(), values.end());
    if (maxValue > maxLimit) {
        maxValue = maxLimit;
    }
    if (maxValue > multiple * averageOriginal) {
        maxValue = averageOriginal;
    } else if (maxValue > 4 * averageOriginal) {
        maxValue -= reductionFactor * (maxValue - averageOriginal);
    }

    QVector<double> adjustedValues = values;
    for (int i = 0; i < adjustedValues.size(); ++i) {
        if (adjustedValues[i] > maxValue) {
            adjustedValues[i] = maxValue;
        }
    }

    return adjustedValues;
}


/* 
 * Calculates the ratio based on the input averages and displays the result in a QLineEdit object.
 * Parameters:
 *  - avgTheta, avgBeta1, avgBeta2: Input averages as strings.
 *  - resultLineEdit: QLineEdit object for displaying the result.
 */
void LogicHandler::calculateRatio(const QString &avgTheta, const QString &avgBeta1, const QString &avgBeta2, QLineEdit *resultLineEdit)
{
    bool okTheta, okBeta1, okBeta2;
    double theta = avgTheta.toDouble(&okTheta);
    double beta1 = avgBeta1.toDouble(&okBeta1);
    double beta2 = avgBeta2.toDouble(&okBeta2);

    if (!okTheta || !okBeta1 || !okBeta2)
    {
        resultLineEdit->setText("Error: Invalid number format in the averages");
        return;
    }

    double ratio = theta / (beta1 + beta2 / 2.0);
    resultLineEdit->setText(QString::number(ratio));
}


// POST-FILTER

/* 
 * Applies exponential filtering to the input data.
 * Exponential filter formula: \[ y[i] = \alpha \cdot x[i] + (1 - \alpha) \cdot y[i-1] \]
 * Parameters:
 *  - data: Input data as a comma-separated string.
 * Returns:
 *  - QString: Comma-separated string of filtered values.
 */
QString LogicHandler::exponentialFiltering(const QString &data) {
    QVector<double> values = convertStringToVector(data);
    if (values.isEmpty()) return "";

    double alpha = 0.1;  // Filter smoothing factor, this value can be adjusted
    QVector<double> filteredValues(values.size());
    filteredValues[0] = values[0];  // Initializing the first value

    for (int i = 1; i < values.size(); ++i) {
        filteredValues[i] = alpha * values[i] + (1 - alpha) * filteredValues[i-1];
    }

    return convertVectorToString(filteredValues);
}

/* 
 * Applies linear interpolation to the input data.
 * Linear interpolation formula: \[ y = \frac{x - x_0}{x_1 - x_0} \cdot (y_1 - y_0) + y_0 \]
 * Parameters:
 *  - data: Input data as a comma-separated string.
 * Returns:
 *  - QString: Comma-separated string of interpolated values.
 */
QString LogicHandler::dataInterpolation(const QString &data) {
    QVector<double> values = convertStringToVector(data);
    if (values.isEmpty()) return "";

    QVector<double> interpolatedValues;
    for (int i = 0; i < values.size() - 1; ++i) {
        interpolatedValues.append(values[i]);
        double x0 = i;
        double x1 = i + 1;
        double x = i + 0.5;  // Midpoint
        double y0 = values[i];
        double y1 = values[i + 1];
        double interpolatedValue = ((x - x0) / (x1 - x0)) * (y1 - y0) + y0;
        interpolatedValues.append(interpolatedValue);
    }
    interpolatedValues.append(values.last());  // Adding the last value

    return convertVectorToString(interpolatedValues);
}


/* 
 * Applies median filtering to the input data.
 * Median filtering is a non-linear method used to remove noise from images and signals.
 * Parameters:
 *  - data: Input data as a comma-separated string.
 * Returns:
 *  - QString: Comma-separated string of median filtered values.
 */
QString LogicHandler::medianFiltering(const QString &data) {
    QVector<double> values = convertStringToVector(data);
    if (values.isEmpty()) return "";

    int windowSize = 3;  // Window size for median filtering, this value can be adjusted
    QVector<double> medianFilteredValues;
    for (int i = 0; i < values.size(); ++i) {
        int start = std::max(0, i - windowSize / 2);
        int end = std::min(i + windowSize / 2, static_cast<int>(values.size()) - 1);
        QVector<double> window(values.begin() + start, values.begin() + end + 1);
        std::sort(window.begin(), window.end());
        medianFilteredValues.append(window[window.size() / 2]);
    }

    return convertVectorToString(medianFilteredValues);
}

/* 
 * Applies normalization to the input data.
 * Normalization formula: \[ y = \frac{x - \min}{\max - \min} \]
 * Parameters:
 *  - data: Input data as a comma-separated string.
 * Returns:
 *  - QString: Comma-separated string of normalized values.
 */
QString LogicHandler::normalization(const QString &data) {
    QVector<double> values = convertStringToVector(data);
    if (values.isEmpty()) return "";

    double minVal = *std::min_element(values.begin(), values.end());
    double maxVal = *std::max_element(values.begin(), values.end());
    QVector<double> normalizedValues;
    for (double value : values) {
        normalizedValues.append((value - minVal) / (maxVal - minVal));
    }

    return convertVectorToString(normalizedValues);
}

/* 
 * Applies a custom Savitzky-Golay smoothing to the input data.
 * This implementation is a variation of the standard Savitzky-Golay filter.
 * It attempts to fit a second-degree polynomial to a window of 3 data points
 * centered at each data point and then evaluate the polynomial at x = 0 to obtain the smoothed value.
 * 
 * Parameters:
 *  - data: Input data as a comma-separated string.
 * Returns:
 *  - QString: Comma-separated string of smoothed values.
 */
QString LogicHandler::savitzkyGolaySmoothing(const QString &data) {
    QVector<double> values = convertStringToVector(data);
    // Return original data if there are not enough points for smoothing
    if (values.size() < 3) return data;  

    QVector<double> smoothedValues(values.size());
    for (int i = 0; i < values.size(); ++i) {
        int startIdx = std::max(0, i - 1);
        int endIdx = std::min(i + 2, static_cast<int>(values.size()));

        // Ensuring the window has 3 points
        if (endIdx - startIdx < 3) {
            if (startIdx == 0) {
                endIdx = 3;
            } else {
                startIdx = values.size() - 3;
            }
        }

        QVector<double> window = values.mid(startIdx, 3);
        double y0 = window[0];
        double y1 = window[1];
        double y2 = window[2];

        // Solve the system of equations manually
        double c = y1;
        double a = (y2 + y0 - 2 * c) / 2;
        double b = y2 - a - c;

        // Evaluate the polynomial at x = 0 to get the smoothed value
        smoothedValues[i] = a*0 + b*0 + c;
    }

    return convertVectorToString(smoothedValues);
}

