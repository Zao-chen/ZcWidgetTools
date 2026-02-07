#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
    createPages();

    setWindowTitle("ZcStackedWidget 演示");
    resize(800, 600);
}

void MainWindow::setupUI()
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    // 创建 ZcStackedWidget
    m_stack = new ZcStackedWidget(this);

    // 创建按钮
    QHBoxLayout* btnLayout = new QHBoxLayout();
    m_btnPrev = new QPushButton("上一页", this);
    m_btnNext = new QPushButton("下一页", this);

    btnLayout->addStretch();
    btnLayout->addWidget(m_btnPrev);
    btnLayout->addWidget(m_btnNext);
    btnLayout->addStretch();

    mainLayout->addWidget(m_stack);
    mainLayout->addLayout(btnLayout);

    // 连接信号
    connect(m_btnNext, &QPushButton::clicked, this, [=]() {
        if (!m_stack->isAnimating()) {
            int next = (m_stack->currentIndex() + 1) % m_stack->count();
            m_stack->slideToIndex(next);
        }
    });

    connect(m_btnPrev, &QPushButton::clicked, this, [=]() {
        if (!m_stack->isAnimating()) {
            int prev = (m_stack->currentIndex() - 1 + m_stack->count()) % m_stack->count();
            m_stack->slideToIndex(prev);
        }
    });
}

void MainWindow::createPages()
{
    QStringList colors = {"#FF6B6B", "#4ECDC4", "#45B7D1", "#96CEB4"};

    for (int i = 0; i < colors.size(); ++i) {
        QWidget* page = new QWidget();
        page->setStyleSheet(QString("background-color: %1;").arg(colors[i]));

        QVBoxLayout* layout = new QVBoxLayout(page);

        QLabel* label = new QLabel(QString("页面 %1").arg(i + 1));
        label->setStyleSheet("color: white; font-size: 48px; font-weight: bold;");
        label->setAlignment(Qt::AlignCenter);

        layout->addWidget(label);
        m_stack->addWidget(page);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
