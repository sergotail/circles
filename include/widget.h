#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QGraphicsView;
class InteractingCircleScene;

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(int const width, int const height, size_t const N, QWidget * parent = Q_NULLPTR);
    virtual ~Widget();
    virtual bool eventFilter(QObject * watched, QEvent * event) override;

private:
    QGraphicsView * graphicsView;
    InteractingCircleScene * scene;
};

#endif // WIDGET_H
