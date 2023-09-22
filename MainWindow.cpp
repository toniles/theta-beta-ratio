#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QStringList>
// #include <QDebug>
#include <QGuiApplication>
#include <QPalette>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    // Set the style based on the theme
    setupStyle();

    // Initialize LineEdits and other widgets
    initWidgets();

    // Configure the layouts
    setupLayouts(layout);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Set minimum width
    setMinimumWidth(1000);
    setFixedHeight(350);


    // Establish connections between widgets
    setupConnections();
    
    // qDebug() << "MainWindow initialized correctly.";
}

void MainWindow::setupStyle()
{
    QPalette palette = QGuiApplication::palette();
    QColor bgColor = palette.color(QPalette::Window);
    
    bool isDarkTheme = bgColor.lightness() < 128;
    QString textColor = isDarkTheme ? "white" : "black";

    this->setStyleSheet(QString("QLineEdit, QLabel, QCheckBox, QPushButton { color: %1; font-size: 14px; }").arg(textColor));
    errorStyle = QString("color: red; font-size: 14px;");
    normalStyle = QString("color: %1; font-size: 14px;").arg(textColor);

    // qDebug() << "Style set.";
}

void MainWindow::initWidgets()
{
    lineEdit_theta = new QLineEdit(this);
    lineEdit_avg_theta = new QLineEdit(this);
    lineEdit_beta1 = new QLineEdit(this);
    lineEdit_avg_beta1 = new QLineEdit(this);
    lineEdit_beta2 = new QLineEdit(this);
    lineEdit_avg_beta2 = new QLineEdit(this);
    lineEdit_result = new QLineEdit(this);
    lineEdit_result->setStyleSheet(
        "font-size: 24px; "
        "color: black; "
        "background-color: white; "
        "border-radius: 5px;"
    );

    QList<QLineEdit*> lineEdits = { 
        lineEdit_theta, lineEdit_avg_theta, lineEdit_beta1, 
        lineEdit_avg_beta1, lineEdit_beta2, lineEdit_avg_beta2, 
        lineEdit_result 
    };

    for(QLineEdit* edit : lineEdits) {
        edit->setAlignment(Qt::AlignCenter);
    }

    checkBox_theta = new QCheckBox("Filter Theta", this);
    checkBox_beta1 = new QCheckBox("Filter Beta1", this);
    checkBox_beta2 = new QCheckBox("Filter Beta2", this);

    btn_calculate = new QPushButton("Calculate Ratio", this);
    label_result = new QLabel("Result:", this);

    // qDebug() << "Widgets initialized.";
}

void MainWindow::setupLayouts(QVBoxLayout *layout)
{
    QHBoxLayout *thetaLayout = new QHBoxLayout;
    thetaLayout->addWidget(lineEdit_theta);
    thetaLayout->addWidget(lineEdit_avg_theta);
    thetaLayout->addWidget(checkBox_theta);

    QHBoxLayout *beta1Layout = new QHBoxLayout;
    beta1Layout->addWidget(lineEdit_beta1);
    beta1Layout->addWidget(lineEdit_avg_beta1);
    beta1Layout->addWidget(checkBox_beta1);

    QHBoxLayout *beta2Layout = new QHBoxLayout;
    beta2Layout->addWidget(lineEdit_beta2);
    beta2Layout->addWidget(lineEdit_avg_beta2);
    beta2Layout->addWidget(checkBox_beta2);

    //Set placeholders
    lineEdit_theta->setPlaceholderText("54.61, 60.6, 55, 65, 90.12");
    lineEdit_beta1->setPlaceholderText("1.2, 1.3, 0.01, 0.1, 2.10, 1, 1, 2");
    lineEdit_beta2->setPlaceholderText("1.2, 1.3, 0.01, 0.1, 2.10, 1, 1, 2");


    // Margin and spacing adjustments
    layout->setContentsMargins(15, 15, 15, 15);
    layout->setSpacing(10);
    thetaLayout->setSpacing(10);
    beta1Layout->setSpacing(10);
    beta2Layout->setSpacing(10);

    layout->addLayout(thetaLayout);
    layout->addLayout(beta1Layout);
    layout->addLayout(beta2Layout);
    layout->addWidget(btn_calculate);
    layout->addWidget(label_result);
    layout->addWidget(lineEdit_result);

    // qDebug() << "Layouts set.";
}

void MainWindow::setupConnections()
{
    connect(lineEdit_theta, &QLineEdit::textChanged, this, &MainWindow::updateAverage);
    connect(lineEdit_beta1, &QLineEdit::textChanged, this, &MainWindow::updateAverage);
    connect(lineEdit_beta2, &QLineEdit::textChanged, this, &MainWindow::updateAverage);
    connect(btn_calculate, &QPushButton::clicked, this, &MainWindow::calculateRatio);
    connect(checkBox_theta, &QCheckBox::stateChanged, this, &MainWindow::updateAverage);
    connect(checkBox_beta1, &QCheckBox::stateChanged, this, &MainWindow::updateAverage);
    connect(checkBox_beta2, &QCheckBox::stateChanged, this, &MainWindow::updateAverage);
    
    // qDebug() << "Connections established.";
}

void MainWindow::updateAverage()
{
    filterAndAverage(lineEdit_theta->text(), checkBox_theta->isChecked(), lineEdit_avg_theta);
    filterAndAverage(lineEdit_beta1->text(), checkBox_beta1->isChecked(), lineEdit_avg_beta1);
    filterAndAverage(lineEdit_beta2->text(), checkBox_beta2->isChecked(), lineEdit_avg_beta2);

    // qDebug() << "Averages updated.";
}

/**
 * @brief Computes the average of a list of numbers, potentially filtering out outliers.
 * 
 * This function accepts a comma-separated string of numbers and computes their average.
 * If filtering is activated (isFiltered = true), it applies fixed threshold criteria based on the mean:
 * 1. If the mean is below 2, any number above 8.5 is considered an outlier.
 * 2. If the mean is below 5, any number above 10 is considered an outlier.
 * 3. If the mean is between 5 and 10, any number above 20 is considered an outlier.
 * 
 * If none of these criteria are met, the function applies a median filter for outlier detection.
 * If there are fewer than 4 numbers, a blank average is returned.
 * 
 * @param input A string containing comma-separated numbers.
 * @param isFiltered A flag determining whether outliers should be filtered.
 * @param averageLineEdit Pointer to the QLineEdit where the resulting average will be displayed.
 */
void MainWindow::filterAndAverage(const QString &input, bool isFiltered, QLineEdit *averageLineEdit) {
    QStringList strList = input.split(",");
    // qDebug() << "-----------------------";
    // qDebug() << "Received Input:" << input;

    if (strList.isEmpty() || strList.size() < 4)
    {
        averageLineEdit->setText("");  // Return blank average
        // qDebug() << "ERROR: Insufficient number of values (less than 5). Returning blank average.";
        return;
    }

    QList<double> values;
    for (const QString &str : strList)
    {
        bool ok;
        double val = str.toDouble(&ok);
        if (!ok)
        {
            // qDebug() << "ERROR: Invalid number format in:" << str;
            return;
        }
        values.append(val);
    }

    double sum = 0.0;
    for (double val : values)
    {
        sum += val;
    }
    double initialAverage = sum / values.size();
    // qDebug() << "Initial Average (before filtering):" << initialAverage;

    if (isFiltered)
    {
        if (initialAverage < 2)
        {
            values.erase(std::remove_if(values.begin(), values.end(),
                        [](double val) { return val > 8.5; }), values.end());
        }
        else if (initialAverage < 5)
        {
            values.erase(std::remove_if(values.begin(), values.end(),
                        [](double val) { return val > 10; }), values.end());
        }
        else if (initialAverage >= 5 && initialAverage < 10)
        {
            values.erase(std::remove_if(values.begin(), values.end(),
                        [](double val) { return val > 20; }), values.end());
        }
        else  // Apply median filtering
        {
            QList<double> filteredValues;
            for (int i = 0; i < values.size(); ++i)
            {
                if (i == 0 || i == values.size() - 1)
                {
                    filteredValues.append(values[i]);
                }
                else
                {
                    QList<double> window = {values[i - 1], values[i], values[i + 1]};
                    std::sort(window.begin(), window.end());
                    filteredValues.append(window[1]);  // Median value
                }
            }
            values = filteredValues;
        }
    }

    sum = 0.0;
    for (double val : values)
    {
        sum += val;
    }
    double average = sum / values.size();
    // qDebug() << "Average after filtering (if applied):" << average;

    averageLineEdit->setText(QString::number(average, 'f', 2));  // Display with 2 decimal places
    // qDebug() << "-----------------------";
}

/**
 * Calculates the ratio based on the average values of theta, beta1, and beta2.
 * If any of the average values have an invalid format, it displays an error message.
 * 
 * Ratio formula: ratio = theta / (beta1 + beta2 / 2)
 */
void MainWindow::calculateRatio()
{
    bool okTheta, okBeta1, okBeta2;

    // Convert average values to double
    double theta = lineEdit_avg_theta->text().toDouble(&okTheta);
    double beta1 = lineEdit_avg_beta1->text().toDouble(&okBeta1);
    double beta2 = lineEdit_avg_beta2->text().toDouble(&okBeta2);

    // Debug: display the converted values
    // qDebug() << "Average Theta:" << theta;
    // qDebug() << "Average Beta1:" << beta1;
    // qDebug() << "Average Beta2:" << beta2;

    // Check if any of the values have an invalid format
    if (!okTheta || !okBeta1 || !okBeta2)
    {
        QMessageBox::warning(this, "Error", "Invalid number format in the averages");
        // qDebug() << "ERROR: Invalid number format detected.";
        return;
    }

    // Calculate the ratio
    double ratio = theta / (beta1 + beta2 / 2.0);

    // Display the ratio in the corresponding QLineEdit
    lineEdit_result->setText(QString::number(ratio));

    // qDebug() << "Calculated Ratio:" << ratio;
}

/**
 * Applies the filters to calculate the averages if the corresponding checkboxes are checked.
 * 
 * If any checkbox is checked, it calls the updateAverage() function to update the averages.
 */
void MainWindow::applyFiltersIfChecked()
{
    // Debug: display the current state of the checkboxes
    // qDebug() << "Status of checkBox_theta:" << checkBox_theta->isChecked();
    // qDebug() << "Status of checkBox_beta1:" << checkBox_beta1->isChecked();
    // qDebug() << "Status of checkBox_beta2:" << checkBox_beta2->isChecked();

    // Check if any checkbox is checked
    if (checkBox_theta->isChecked() || checkBox_beta1->isChecked() || checkBox_beta2->isChecked())
    {
        // If any checkbox is checked, update the averages
        updateAverage();
        // qDebug() << "Averages updated since at least one checkbox is checked.";
    }
    else
    {
        // qDebug() << "No filters applied since all checkboxes are unchecked.";
    }
}
