#include <widget.h>
#include <utils.h>
#include <interactingcirclescene.h>

#include <QGraphicsView>
#include <QGridLayout>
#include <QResizeEvent>


Widget::Widget(int const width, int const height, size_t const N, QWidget * parent) :
    QWidget(parent),
    graphicsView(new QGraphicsView(this)),
    scene(new InteractingCircleScene(QRectF(0, 0, width, height),
                                     CircleUtils::default_radius,
                                     CircleUtils::calcTime,
                                     CircleUtils::renderTime,
                                     this)) {
    setLayout(new QGridLayout());
    layout()->addWidget(graphicsView);
    scene->setSceneRect(0, 0, width, height);
    setMinimumWidth(width);
    setMinimumHeight(height);
    graphicsView->setScene(scene);
    graphicsView->ensureVisible(scene->sceneRect());
    graphicsView->viewport()->installEventFilter(this);
    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);
    graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    graphicsView->setMouseTracking(true);

    // add N random positioned circles and start animation with calculations
    scene->addRandomCircles(N, CircleUtils::default_radius, scene->sceneRect());
    scene->start();
}

Widget::~Widget() {}

bool Widget::eventFilter(QObject * watched, QEvent * event)
{
    Q_UNUSED(watched);
    if (event->type() == QEvent::Resize) {
        QSize res_size = static_cast<QResizeEvent *>(event)->size();
        scene->setSceneRect(0, 0, res_size.width(), res_size.height());
        return true;
    }
    return false;
}
