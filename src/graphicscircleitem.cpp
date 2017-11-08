#include <graphicscircleitem.h>

#include <interactingcirclelist.h>
#include <interactingcirclescene.h>

#include <QTimer>
#include <QGraphicsSceneEvent>


GraphicsCircleItem::GraphicsCircleItem(double const x, double const y,
                                       double const radius, ic_list::iterator backend) :
    QGraphicsEllipseItem(QRectF(-radius, -radius, 2.0 * radius, 2.0 * radius), Q_NULLPTR),
    backend(backend) {
    setPos(x, y);
    setFlags(GraphicsItemFlag::ItemIsMovable);
    setZValue(std::numeric_limits<qreal>::max()); // set z-value for exact order of items (emplace front)
}

GraphicsCircleItem::~GraphicsCircleItem() {}

void GraphicsCircleItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    QGraphicsItem::mousePressEvent(event);
    if (event->button() == Qt::RightButton) {
        static_cast<InteractingCircleScene *>(scene())->removeCircle(this);
        delete this;
    }
    else if (event->button() == Qt::LeftButton) {
        sceneBackend()->setInteracting(backend, false); // disable interaction of this cirle with others
        sceneBackend()->zeroForce(backend); // selected circle must be not affected by other circles
    }
}

void GraphicsCircleItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    QGraphicsItem::mouseMoveEvent(event);
    sceneBackend()->setPos(backend, pos().x(), pos().y());
}

void GraphicsCircleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    QGraphicsEllipseItem::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton) {
        sceneBackend()->setPos(backend, pos().x(), pos().y());
        sceneBackend()->setInteracting(backend, true); // enable interaction of this cirle with others
    }
}

ic_list_ptr GraphicsCircleItem::sceneBackend() {
    return static_cast<InteractingCircleScene *>(scene())->backend;
}
