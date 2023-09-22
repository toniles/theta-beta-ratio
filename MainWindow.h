#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>  // <-- Añadido para usar QTimer

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void calculateRatio();
    void updateAverage();
    void applyFiltersIfChecked();  // <-- Añadido: declaración de la nueva función

private:
    void filterAndAverage(const QString &input, bool isFiltered, QLineEdit *averageLineEdit);
    void initWidgets();
    void setupLayouts(QVBoxLayout *layout);
    void setupConnections();
    void setupStyle();

private:
    QLineEdit *lineEdit_theta;
    QLineEdit *lineEdit_avg_theta;    
    QLineEdit *lineEdit_beta1;
    QLineEdit *lineEdit_avg_beta1;   
    QLineEdit *lineEdit_beta2;
    QLineEdit *lineEdit_avg_beta2;    
    QLineEdit *lineEdit_result;
    QCheckBox *checkBox_theta;
    QCheckBox *checkBox_beta1;
    QCheckBox *checkBox_beta2;
    QPushButton *btn_calculate;
    QLabel *label_result;

    QString errorStyle;   
    QString normalStyle;  

    QTimer *filterTimer;  // <-- Añadido: declaración del QTimer
};

#endif // MAINWINDOW_H
