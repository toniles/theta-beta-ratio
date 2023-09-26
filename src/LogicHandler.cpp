#include "LogicHandler.h"
#include <QStringList>
#include <algorithm>
#include <QDebug> 

LogicHandler::LogicHandler(QObject *parent) : QObject(parent)
{
}

QString LogicHandler::exponentialFiltering(const QString &data) {
    qDebug() << "Applying Exponential Filtering";
    // Lógica para Exponential Filtering
    QString processedData = data;  // Temporal, reemplazar con datos procesados
    return processedData;
}

QString LogicHandler::dataInterpolation(const QString &data) {
    qDebug() << "Applying Data Interpolation";
    // Lógica para Data Interpolation
    QString processedData = data;  // Temporal, reemplazar con datos procesados
    return processedData;
}

QString LogicHandler::medianFiltering(const QString &data) {
    qDebug() << "Applying Median Filtering";
    // Lógica para Median Filtering
    QString processedData = data;  // Temporal, reemplazar con datos procesados
    return processedData;
}

QString LogicHandler::normalization(const QString &data) {
    qDebug() << "Applying Normalization";
    // Lógica para Normalization
    QString processedData = data;  // Temporal, reemplazar con datos procesados
    return processedData;
}

QString LogicHandler::savitzkyGolaySmoothing(const QString &data) {
    qDebug() << "Applying Savitzky-Golay Smoothing";
    // Lógica para Savitzky-Golay Smoothing
    QString processedData = data;  // Temporal, reemplazar con datos procesados
    return processedData;
}

void LogicHandler::updateAverage(
    const QString &input,
    double maxLimit,
    double multiple,
    double reductionFactor,
    QLineEdit *averageLineEdit
) {
    QStringList strList = input.split(",");
    if (strList.isEmpty() || strList.size() < 4) {
        averageLineEdit->setText("");  // Return blank average
        return;
    }

    QVector<double> values;
    foreach (const QString& str, strList) {
        bool ok;
        double value = str.toDouble(&ok);
        if (ok) {
            values.append(value);
        }
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

    for (int i = 0; i < values.size(); ++i) {
        if (values[i] > maxValue) {
            values[i] = maxValue;
        }
    }
    double sumAdjusted = std::accumulate(values.begin(), values.end(), 0.0);
    double averageAdjusted = sumAdjusted / values.size();

    averageLineEdit->setText(QString::number(averageAdjusted));
}


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

void LogicHandler::applyFiltersIfChecked(
    bool isThetaChecked, bool isBeta1Checked, bool isBeta2Checked,
    const QString &theta, const QString &beta1, const QString &beta2,
    QLineEdit *lineEdit_avg_theta, QLineEdit *lineEdit_avg_beta1, QLineEdit *lineEdit_avg_beta2,
    bool isExponentialFilteringChecked, bool isDataInterpolationChecked,
    bool isMedianFilteringChecked, bool isNormalizationChecked, bool isSavitzkyGolayChecked,
    double maxLimitTheta, double multipleTheta, double reductionFactorTheta,
    double maxLimitBeta1, double multipleBeta1, double reductionFactorBeta1,
    double maxLimitBeta2, double multipleBeta2, double reductionFactorBeta2
) {
    QString processedTheta = theta;
    QString processedBeta1 = beta1;
    QString processedBeta2 = beta2;

    // Si isThetaChecked es true, aplicar el primer filtro a theta
    if (isThetaChecked) {
        updateAverage(theta, 300, 4, 0.2, lineEdit_avg_theta);
        processedTheta = lineEdit_avg_theta->text();
    }

    // Si isBeta1Checked es true, aplicar el primer filtro a beta1
    if (isBeta1Checked) {
        updateAverage(beta1, 20, 10, 0.2, lineEdit_avg_beta1);
        processedBeta1 = lineEdit_avg_beta1->text();
    }

    // Si isBeta2Checked es true, aplicar el primer filtro a beta2
    if (isBeta2Checked) {
        updateAverage(beta2, 20, 10, 0.2, lineEdit_avg_beta2);
        processedBeta2 = lineEdit_avg_beta2->text();
    }

    // Llamadas a las funciones de post-filtrado, si los checkboxes correspondientes están marcados
    if (isExponentialFilteringChecked) {
        processedTheta = exponentialFiltering(processedTheta);
        processedBeta1 = exponentialFiltering(processedBeta1);
        processedBeta2 = exponentialFiltering(processedBeta2);
    }

    if (isDataInterpolationChecked) {
        processedTheta = dataInterpolation(processedTheta);
        processedBeta1 = dataInterpolation(processedBeta1);
        processedBeta2 = dataInterpolation(processedBeta2);
    }

    if (isMedianFilteringChecked) {
        processedTheta = medianFiltering(processedTheta);
        processedBeta1 = medianFiltering(processedBeta1);
        processedBeta2 = medianFiltering(processedBeta2);
    }

    if (isNormalizationChecked) {
        processedTheta = normalization(processedTheta);
        processedBeta1 = normalization(processedBeta1);
        processedBeta2 = normalization(processedBeta2);
    }

    if (isSavitzkyGolayChecked) {
        processedTheta = savitzkyGolaySmoothing(processedTheta);
        processedBeta1 = savitzkyGolaySmoothing(processedBeta1);
        processedBeta2 = savitzkyGolaySmoothing(processedBeta2);
    }

    // Actualizar los QLineEdit con los datos procesados
    lineEdit_avg_theta->setText(processedTheta);
    lineEdit_avg_beta1->setText(processedBeta1);
    lineEdit_avg_beta2->setText(processedBeta2);
}


void LogicHandler::filterAndAverage(const QString &input, double maxLimit, double multiple, double reductionFactor, QLineEdit *averageLineEdit)
{
    QStringList strList = input.split(",");
    if (strList.isEmpty() || strList.size() < 4) {
        averageLineEdit->setText("");  // Return blank average
        return;
    }

    QVector<double> values;
    foreach (const QString& str, strList) {
        bool ok;
        double value = str.toDouble(&ok);
        if (ok) {
            values.append(value);
        }
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

    for (int i = 0; i < values.size(); ++i) {
        if (values[i] > maxValue) {
            values[i] = maxValue;
        }
    }
    double sumAdjusted = std::accumulate(values.begin(), values.end(), 0.0);
    double averageAdjusted = sumAdjusted / values.size();

    // Paso 3: Devolver el promedio ajustado.
    averageLineEdit->setText(QString::number(averageAdjusted));
}
