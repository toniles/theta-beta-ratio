#ifndef LOGICHANDLER_H
#define LOGICHANDLER_H

#include <QObject>
#include <QString>
#include <QLineEdit>
#include <QVector>

class LogicHandler : public QObject {
    Q_OBJECT

public:
    explicit LogicHandler(QObject *parent = nullptr);

    // Funciones de filtrado
    QString exponentialFiltering(const QString &data);
    QString dataInterpolation(const QString &data);
    QString medianFiltering(const QString &data);
    QString normalization(const QString &data);
    QString savitzkyGolaySmoothing(const QString &data);

    // Función para aplicar filtros y calcular promedios
    void applyFiltersAndComputeAverages(
        bool isThetaChecked, 
        bool isBeta1Checked, 
        bool isBeta2Checked,
        const QString &theta, 
        const QString &beta1, 
        const QString &beta2,
        QLineEdit *lineEdit_avg_theta, 
        QLineEdit *lineEdit_avg_beta1, 
        QLineEdit *lineEdit_avg_beta2,
        bool isExponentialFilteringChecked, 
        bool isDataInterpolationChecked,
        bool isMedianFilteringChecked, 
        bool isNormalizationChecked, 
        bool isSavitzkyGolayChecked
    );

    void calculateRatio(const QString &avgTheta, const QString &avgBeta1, const QString &avgBeta2, QLineEdit *resultLineEdit);

private:
    // Funciones auxiliares
    QVector<double> convertStringToVector(const QString &data);
    QString convertVectorToString(const QVector<double> &values);  // Nueva función añadida
    QVector<double> ferraFilter(const QVector<double> &values, double maxLimit, double multiple, double reductionFactor);
    double calculateAverage(const QVector<double> &values);
};

#endif // LOGICHANDLER_H
