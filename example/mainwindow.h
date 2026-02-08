#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "zcstackedwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ZcStackedWidget* m_stack;
    QPushButton* m_btnNext;
    QPushButton* m_btnPrev;

    void setupUI();
    void createStackedWidget();
};

#endif // MAINWINDOW_H
