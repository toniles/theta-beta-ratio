#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QStringList>
#include <QGuiApplication>
#include <QPalette>
#include <QTimer>
#include <QGroupBox>  
#include <QFont>  

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    logicHandler(new LogicHandler(this))  // Inicializa logicHandler
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *innerWidget = new QWidget(centralWidget);
    innerWidget->setLayout(layout);

    setupStyle();
    initWidgets();
    setupLayouts(layout);

    // Establecer un tamaño mínimo solo para el ancho
    setMinimumWidth(400);

    setupConnections();

    QHBoxLayout *centerLayout = new QHBoxLayout(centralWidget);
    centerLayout->addWidget(innerWidget);
    centralWidget->setLayout(centerLayout);

    QTimer::singleShot(0, this, &MainWindow::applyLateStyles);
}

void MainWindow::applyLateStyles()
{
    QPalette palette;
    palette.setColor(QPalette::PlaceholderText, Qt::gray);

    lineEdit_theta->setPalette(palette);
    lineEdit_beta1->setPalette(palette);
    lineEdit_beta2->setPalette(palette);
}

void MainWindow::setupStyle()
{
    bool isDarkTheme = QGuiApplication::palette().color(QPalette::Window).lightness() < 128;
    QString textColor = isDarkTheme ? "white" : "black";

    QString stylesheet = QString(
        "QLineEdit, QLabel, QCheckBox, QPushButton { color: %1; font-size: 14px; } "
        "QLineEdit::placeholder { color: grey; }"
    ).arg(textColor);
    
    this->setStyleSheet(stylesheet);
}

void MainWindow::initWidgets()
{
    // Inicialización de widgets
    label_theta = new QLabel(" θ ", this);
    lineEdit_theta = new QLineEdit(this);
    lineEdit_avg_theta = new QLineEdit(this);
    checkBox_theta = new QCheckBox("Apply Ferra's Filtering to θ waves ", this);
    
    label_beta1 = new QLabel("β₁ ", this);
    lineEdit_beta1 = new QLineEdit(this);
    lineEdit_avg_beta1 = new QLineEdit(this);
    checkBox_beta1 = new QCheckBox("Apply Ferra's Filtering to β₁ waves", this);

    label_beta2 = new QLabel("β₂ ", this);
    lineEdit_beta2 = new QLineEdit(this);
    lineEdit_avg_beta2 = new QLineEdit(this);
    checkBox_beta2 = new QCheckBox("Apply Ferra's Filtering to β₂ waves", this);
    
    lineEdit_theta->setPlaceholderText("100.1, 100, 100, 100, 100");  
    lineEdit_beta1->setPlaceholderText("1.2, 1.1, 1.1, 1.1, 1.1, 1.2");  
    lineEdit_beta2->setPlaceholderText("1.2, 1.1, 1.1, 1.1, 1.1, 1.2"); 
    lineEdit_theta->setMinimumWidth(400);
    lineEdit_beta1->setMinimumWidth(400);
    lineEdit_beta2->setMinimumWidth(400);

    btn_calculate = new QPushButton("Calculate θ/β ratio", this);
    lineEdit_result = new QLineEdit(this);


    checkBox_exponentialFiltering = new QCheckBox("Exponential Filtering", this);
    checkBox_dataInterpolation = new QCheckBox("Data Interpolation", this);
    checkBox_medianFiltering = new QCheckBox("Median Filtering", this);
    checkBox_normalization = new QCheckBox("Normalization", this);
    checkBox_savitzkyGolay = new QCheckBox("Savitzky-Golay Smoothing", this);
    

}

void MainWindow::setupLayouts(QVBoxLayout *layout)
{
    setupThetaLayout(layout);
    setupBeta1Layout(layout);
    setupBeta2Layout(layout);
    setupFilteringGroup(layout);  // Mover setupFilteringGroup antes de setupCalculateButton y setupResultLayout
    setupCalculateButton(layout);
    setupResultLayout(layout);
    layout->addStretch(1);  // Añadir un stretch al final para empujar todo hacia arriba
}

void MainWindow::setupThetaLayout(QVBoxLayout *layout)
{
    QHBoxLayout *thetaLayout = new QHBoxLayout;
    thetaLayout->addWidget(label_theta);
    thetaLayout->addWidget(lineEdit_theta, 1);
    thetaLayout->addWidget(lineEdit_avg_theta, 1);  // Asegúrate de que esta línea esté solo una vez
    thetaLayout->addStretch(1);  // Mueve el stretch aquí
    thetaLayout->addWidget(checkBox_theta);  // Este checkbox se moverá a la derecha
    layout->addLayout(thetaLayout);
}

void MainWindow::setupBeta1Layout(QVBoxLayout *layout)
{
    QHBoxLayout *beta1Layout = new QHBoxLayout;
    beta1Layout->addWidget(label_beta1);
    beta1Layout->addWidget(lineEdit_beta1, 1);
    beta1Layout->addWidget(lineEdit_avg_beta1, 1);  // Asegúrate de que esta línea esté solo una vez
    beta1Layout->addStretch(1);  // Mueve el stretch aquí
    beta1Layout->addWidget(checkBox_beta1);  // Este checkbox se moverá a la derecha
    layout->addLayout(beta1Layout);
}

void MainWindow::setupBeta2Layout(QVBoxLayout *layout)
{
    QHBoxLayout *beta2Layout = new QHBoxLayout;
    beta2Layout->addWidget(label_beta2);
    beta2Layout->addWidget(lineEdit_beta2, 1);
    beta2Layout->addWidget(lineEdit_avg_beta2, 1);  // Asegúrate de que esta línea esté solo una vez
    beta2Layout->addStretch(1);  // Mueve el stretch aquí
    beta2Layout->addWidget(checkBox_beta2);  // Este checkbox se moverá a la derecha
    layout->addLayout(beta2Layout);
}

void MainWindow::setupCalculateButton(QVBoxLayout *layout)
{
    layout->addWidget(btn_calculate);
}


void MainWindow::setupResultLayout(QVBoxLayout *layout)
{
    QHBoxLayout *resultLayout = new QHBoxLayout;
    resultLayout->addStretch(1);
    resultLayout->addWidget(lineEdit_result);
    resultLayout->addStretch(1);
    layout->addLayout(resultLayout);
}

void MainWindow::setupFilteringGroup(QVBoxLayout *layout)
{
    QGroupBox *filteringGroupBox = new QGroupBox("POST FILTERING");
    QFont font = filteringGroupBox->font();
    font.setItalic(true);
    filteringGroupBox->setFont(font);

    QGridLayout *filteringLayout = new QGridLayout;  // Usa QGridLayout en lugar de QVBoxLayout
    filteringLayout->addWidget(checkBox_exponentialFiltering, 0, 0);
    filteringLayout->addWidget(checkBox_dataInterpolation, 0, 1);
    filteringLayout->addWidget(checkBox_medianFiltering, 1, 0);
    filteringLayout->addWidget(checkBox_normalization, 1, 1);
    filteringLayout->addWidget(checkBox_savitzkyGolay, 2, 0);
    filteringGroupBox->setLayout(filteringLayout);

    layout->addWidget(filteringGroupBox);

    // Centra el texto "POST FILTERING"
    filteringGroupBox->setAlignment(Qt::AlignHCenter);
}


void MainWindow::setupConnections()
{
    connect(lineEdit_theta, &QLineEdit::textChanged, this, &MainWindow::onLineEditTextChanged);
    connect(lineEdit_beta1, &QLineEdit::textChanged, this, &MainWindow::onLineEditTextChanged);
    connect(lineEdit_beta2, &QLineEdit::textChanged, this, &MainWindow::onLineEditTextChanged);
    connect(btn_calculate, &QPushButton::clicked, this, &MainWindow::onBtnCalculateClicked);
    connect(checkBox_theta, &QCheckBox::toggled, this, &MainWindow::onCheckBoxToggled);
    connect(checkBox_beta1, &QCheckBox::toggled, this, &MainWindow::onCheckBoxToggled);
    connect(checkBox_beta2, &QCheckBox::toggled, this, &MainWindow::onCheckBoxToggled);

    connect(checkBox_exponentialFiltering, &QCheckBox::toggled, this, &MainWindow::onCheckBoxToggled);
    connect(checkBox_dataInterpolation, &QCheckBox::toggled, this, &MainWindow::onCheckBoxToggled);
    connect(checkBox_medianFiltering, &QCheckBox::toggled, this, &MainWindow::onCheckBoxToggled);
    connect(checkBox_normalization, &QCheckBox::toggled, this, &MainWindow::onCheckBoxToggled);
    connect(checkBox_savitzkyGolay, &QCheckBox::toggled, this, &MainWindow::onCheckBoxToggled);

}

void MainWindow::onBtnCalculateClicked()
{
    logicHandler->calculateRatio(lineEdit_avg_theta->text(), lineEdit_avg_beta1->text(), lineEdit_avg_beta2->text(), lineEdit_result);
}

void MainWindow::onLineEditTextChanged()
{
    logicHandler->applyFiltersAndComputeAverages(
        checkBox_theta->isChecked(),
        checkBox_beta1->isChecked(),
        checkBox_beta2->isChecked(),
        lineEdit_theta->text(),
        lineEdit_beta1->text(),
        lineEdit_beta2->text(),
        lineEdit_avg_theta,
        lineEdit_avg_beta1,
        lineEdit_avg_beta2,
        checkBox_exponentialFiltering->isChecked(),
        checkBox_dataInterpolation->isChecked(),
        checkBox_medianFiltering->isChecked(),
        checkBox_normalization->isChecked(),
        checkBox_savitzkyGolay->isChecked()
    );
}

void MainWindow::onCheckBoxToggled()
{
    logicHandler->applyFiltersAndComputeAverages(
        checkBox_theta->isChecked(),
        checkBox_beta1->isChecked(),
        checkBox_beta2->isChecked(),
        lineEdit_theta->text(),
        lineEdit_beta1->text(),
        lineEdit_beta2->text(),
        lineEdit_avg_theta,
        lineEdit_avg_beta1,
        lineEdit_avg_beta2,
        checkBox_exponentialFiltering->isChecked(),
        checkBox_dataInterpolation->isChecked(),
        checkBox_medianFiltering->isChecked(),
        checkBox_normalization->isChecked(),
        checkBox_savitzkyGolay->isChecked()
    );
}

