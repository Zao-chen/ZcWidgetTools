#include "zcstackedwidget.h"
#include <QWidget>

ZcStackedWidget::ZcStackedWidget(QWidget *parent)
    : QStackedWidget(parent)
    , m_slideAnimating(false)
    , m_animationDuration(600)
    , m_offsetFactor(1.5)
{
    setupDefaultCurve();
}

void ZcStackedWidget::setupDefaultCurve()
{
    // Win11 风格：极致蓄力 + 瞬间爆发
    m_easingCurve = QEasingCurve(QEasingCurve::BezierSpline);
    m_easingCurve.addCubicBezierSegment(
        QPointF(0.995, 0.0005),  // 前 99.5% 时间几乎完全静止
        QPointF(0.0005, 1.00),   // 最后 0.5% 瞬间完成
        QPointF(1.00, 1.00)
        );
}

void ZcStackedWidget::useWin11Curve()
{
    setupDefaultCurve();
}

void ZcStackedWidget::slideToIndex(int targetIndex)
{
    if (m_slideAnimating) return;

    const int cur = currentIndex();
    if (cur == targetIndex || targetIndex < 0 || targetIndex >= count()) return;

    QWidget* from = widget(cur);
    QWidget* to   = widget(targetIndex);
    if (!from || !to) return;

    m_slideAnimating = true;
    setEnabled(false); // 动画期间禁交互

    const QRect r = rect();
    const int w = r.width();
    const int h = r.height();

    // 方向：目标索引更大 => 向左滑
    const bool left = (targetIndex > cur);

    const int startOffset = int(w * m_offsetFactor);

    from->setGeometry(0, 0, w, h);
    to->setGeometry(0, 0, w, h);
    to->move(left ? QPoint(startOffset, 0) : QPoint(-startOffset, 0));
    to->show();
    to->raise();

    auto* aFrom = new QPropertyAnimation(from, "pos", this);
    aFrom->setDuration(m_animationDuration);
    aFrom->setStartValue(QPoint(0, 0));
    aFrom->setEndValue(left ? QPoint(-startOffset, 0) : QPoint(startOffset, 0));
    aFrom->setEasingCurve(m_easingCurve);

    auto* aTo = new QPropertyAnimation(to, "pos", this);
    aTo->setDuration(m_animationDuration);
    aTo->setStartValue(left ? QPoint(startOffset, 0) : QPoint(-startOffset, 0));
    aTo->setEndValue(QPoint(0, 0));
    aTo->setEasingCurve(m_easingCurve);

    auto* group = new QParallelAnimationGroup(this);
    group->addAnimation(aFrom);
    group->addAnimation(aTo);

    connect(group, &QParallelAnimationGroup::finished, this, [=]() {
        QStackedWidget::setCurrentIndex(targetIndex);
        from->move(0, 0);
        to->move(0, 0);

        setEnabled(true);
        m_slideAnimating = false;

        group->deleteLater();
    });

    group->start();
}

void ZcStackedWidget::slideToWidget(QWidget* widget)
{
    int index = indexOf(widget);
    if (index >= 0) {
        slideToIndex(index);
    }
}

void ZcStackedWidget::setCurrentIndexAnimated(int index)
{
    slideToIndex(index);
}

void ZcStackedWidget::setAnimationDuration(int ms)
{
    m_animationDuration = ms;
}

void ZcStackedWidget::setAnimationOffset(double factor)
{
    m_offsetFactor = factor;
}

void ZcStackedWidget::setAnimationCurve(const QEasingCurve& curve)
{
    m_easingCurve = curve;
}
