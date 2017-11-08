#ifndef GRAPHICSCIRCLEITEM_H
#define GRAPHICSCIRCLEITEM_H

#include <typedefs.h>

#include <QGraphicsEllipseItem>

class InteractingCircleScene;

class GraphicsCircleItem : public QGraphicsEllipseItem {
    friend class InteractingCircleScene; // for working with private backend member inside scene class

public:
    explicit GraphicsCircleItem(double const x, double const y, double const radius, ic_list::iterator backend);
    ~GraphicsCircleItem();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

private:
    ic_list::iterator backend; // iterator pointing to corresponding circle
    ic_list_ptr sceneBackend(); // pointer to circles list
};

#endif // GRAPHICSCIRCLEITEM_H
