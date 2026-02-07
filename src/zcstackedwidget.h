#ifndef ZCSTACKEDWIDGET_H
#define ZCSTACKEDWIDGET_H

#include "ZcWidgetTools_global.h"
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QEasingCurve>

class ZCWIDGETTOOLS_EXPORT ZcStackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit ZcStackedWidget(QWidget *parent = nullptr);

    void slideToIndex(int targetIndex);
    void slideToWidget(QWidget* widget);
    void setAnimationDuration(int ms);
    void setAnimationOffset(double factor);
    void setAnimationCurve(const QEasingCurve& curve);
    void useWin11Curve();
    bool isAnimating() const { return m_slideAnimating; }

public slots:
    void setCurrentIndexAnimated(int index);

private:
    bool m_slideAnimating;
    int m_animationDuration;
    double m_offsetFactor;
    QEasingCurve m_easingCurve;

    void setupDefaultCurve();
};

#endif // ZCSTACKEDWIDGET_H
