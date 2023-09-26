#ifndef LOGICHANDLER_H
#define LOGICHANDLER_H

#include <QString>
#include <QLineEdit>
#include <QObject>

class LogicHandler : public QObject {
    Q_OBJECT

public:
    explicit LogicHandler(QObject *parent = nullptr);

    QString exponentialFiltering(const QString &data);
    QString dataInterpolation(const QString &data);
    QString medianFiltering(const QString &data);
    QString normalization(const QString &data);
    QString savitzkyGolaySmoothing(const QString &data);

public slots:
    void updateAverage(const QString &input, double maxLimit, double multiple, double reductionFactor, QLineEdit *averageLineEdit);
    void calculateRatio(const QString &avgTheta, const QString &avgBeta1, const QString &avgBeta2, QLineEdit *resultLineEdit);
    void applyFiltersIfChecked(
        bool isThetaChecked, bool isBeta1Checked, bool isBeta2Checked,
        const QString &theta, const QString &beta1, const QString &beta2,
        QLineEdit *lineEdit_avg_theta, QLineEdit *lineEdit_avg_beta1, QLineEdit *lineEdit_avg_beta2,
        bool isExponentialFilteringChecked, bool isDataInterpolationChecked,
        bool isMedianFilteringChecked, bool isNormalizationChecked, bool isSavitzkyGolayChecked
    );

private:
    void filterAndAverage(const QString &input, double maxLimit, double multiple, double reductionFactor, QLineEdit *averageLineEdit);
};

#endif // LOGICHANDLER_H
