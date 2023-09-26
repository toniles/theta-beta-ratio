#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QFont>
#include <QPalette>
#include <QTimer>
#include <QGuiApplication>
#include "LogicHandler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void setupStyle();
    void initWidgets();
    void setupLayouts(QVBoxLayout *layout);
    void setupThetaLayout(QVBoxLayout *layout);
    void setupBeta1Layout(QVBoxLayout *layout);
    void setupBeta2Layout(QVBoxLayout *layout);
    void setupCalculateButton(QVBoxLayout *layout);
    void setupResultLayout(QVBoxLayout *layout);
    void setupFilteringGroup(QVBoxLayout *layout);
    void setupConnections();
    void applyLateStyles();

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
    QCheckBox *checkBox_exponentialFiltering;
    QCheckBox *checkBox_dataInterpolation;
    QCheckBox *checkBox_medianFiltering;
    QCheckBox *checkBox_normalization;
    QCheckBox *checkBox_savitzkyGolay;
    
    QPushButton *btn_calculate;
    QLabel *label_theta;
    QLabel *label_beta1;
    QLabel *label_beta2;

    LogicHandler *logicHandler;

private slots:
    void onLineEditTextChanged();
    void onBtnCalculateClicked();
    void onCheckBoxToggled();
};

#endif // MAINWINDOW_H
