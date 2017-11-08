#ifndef INTERACTINGCIRCLESCENE_H
#define INTERACTINGCIRCLESCENE_H

#include <typedefs.h>

#include <QGraphicsScene>
#include <QTimer>

class InteractingCircleList;
class GraphicsCircleItem;

class InteractingCircleScene : public QGraphicsScene {

    Q_OBJECT
    friend class GraphicsCircleItem;

public:
    explicit InteractingCircleScene(QRectF const & sceneRect, double const default_radius,
                                    double const calcTime, double const renderTime,
                                    QObject * parent = Q_NULLPTR);
    virtual ~InteractingCircleScene();
    ic_vector currentState() const;
    void addRandomCircles(size_t const N, double const radius, QRectF const & spreadArea);
    void addCircle(double const x, double const y, double const radius);
    void removeCircle(GraphicsCircleItem * item);
    void start();
    void stop(); 

public slots:
    void updateAnimation();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

private:
    ic_list_ptr backend; // list of circles
    double const default_radius;
    double const calcTime; // duration of calculation iteration
    double const renderTime; // duration of rendering iteration
    std::atomic_bool calcStop; // flag for stopping detached thread with backend calculations
    std::atomic<uint64_t> calcStartTime; // start of backend calculations, used for constant time iterations
    QTimer animationTimer; // timer for animation
    void detachCalcThread();
    void calcBackend(double const dt);
};

#endif // INTERACTINGCIRCLESSCENE_H
