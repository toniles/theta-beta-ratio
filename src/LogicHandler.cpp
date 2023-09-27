#include "LogicHandler.h"
#include <QStringList>
#include <algorithm>
#include <QDebug>

LogicHandler::LogicHandler(QObject *parent) : QObject(parent)
{
}

// Función para convertir una cadena en un vector de doubles
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

// Función de filtrado de Ferra
QVector<double> LogicHandler::ferraFilter(const QVector<double> &values, double maxLimit, double multiple, double reductionFactor) {
    if (values.isEmpty() || values.size() < 4) {
        return QVector<double>();  // Retornar vector vacío si no hay suficientes datos
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

// Función para calcular el promedio de un vector de valores
double LogicHandler::calculateAverage(const QVector<double> &values) {
    if (values.isEmpty()) {
        return 0;  // Retornar 0 si el vector está vacío
    }
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    return sum / values.size();
}

QString LogicHandler::convertVectorToString(const QVector<double> &values) {
    QStringList stringList;
    for (double value : values) {
        stringList.append(QString::number(value));
    }
    return stringList.join(",");
}

void LogicHandler::applyFiltersAndComputeAverages(
    bool isThetaChecked, bool isBeta1Checked, bool isBeta2Checked,
    const QString &theta, const QString &beta1, const QString &beta2,
    QLineEdit *lineEdit_avg_theta, QLineEdit *lineEdit_avg_beta1, QLineEdit *lineEdit_avg_beta2,
    bool isExponentialFilteringChecked, bool isDataInterpolationChecked,
    bool isMedianFilteringChecked, bool isNormalizationChecked, bool isSavitzkyGolayChecked
) {
    // Convertir cadenas a vectores de valores
    QVector<double> thetaValues = convertStringToVector(theta);
    QVector<double> beta1Values = convertStringToVector(beta1);
    QVector<double> beta2Values = convertStringToVector(beta2);

    // Aplicar filtrado de Ferra si está marcado
    if (isThetaChecked) {
        thetaValues = ferraFilter(thetaValues, 300, 4, 0.2);
    }
    if (isBeta1Checked) {
        beta1Values = ferraFilter(beta1Values, 20, 10, 0.2);
    }
    if (isBeta2Checked) {
        beta2Values = ferraFilter(beta2Values, 20, 10, 0.2);
    }

    // Aplicar otros filtros si están marcados
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

    // Calcular y establecer los promedios
    lineEdit_avg_theta->setText(QString::number(calculateAverage(thetaValues)));
    lineEdit_avg_beta1->setText(QString::number(calculateAverage(beta1Values)));
    lineEdit_avg_beta2->setText(QString::number(calculateAverage(beta2Values)));
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




// POST-FILTER

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

