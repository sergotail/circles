#include <interactingcirclescene.h>
#include <utils.h>
#include <interactingcirclelist.h>
#include <graphicscircleitem.h>

#include <thread>
#include <random>

#include <QGraphicsSceneMouseEvent>


InteractingCircleScene::InteractingCircleScene(QRectF const & sceneRect, double const default_radius,
                                               double const calcTime, double const renderTime,
                                               QObject * parent) :
    QGraphicsScene(sceneRect, parent),
    backend(new InteractingCircleList()),
    default_radius(default_radius),
    calcTime(calcTime),
    renderTime(renderTime) {
    calcStop.store(true);
    calcStartTime.store(0);
}

InteractingCircleScene::~InteractingCircleScene() {
    if (!calcStop.load()) { // calcStop will be true after stop method so we check if stop called earlier
        stop();
    }
}

ic_vector InteractingCircleScene::currentState() const {
    return backend->circlesVector(); // used for tests
}

void InteractingCircleScene::addRandomCircles(size_t const N, double const radius, QRectF const & spreadArea) {
    std::uniform_real_distribution<double> xDistr(radius, spreadArea.width() - radius);
    std::uniform_real_distribution<double> yDistr(radius, spreadArea.height() - radius);
    std::mt19937 gen;
    gen.seed(std::random_device{}());
    for (size_t i = 0; i < N; ++i) {
        addCircle(xDistr(gen), yDistr(gen), radius);
    }
}

void InteractingCircleScene::addCircle(double const x, double const y, double const radius) {

    auto it = backend->emplaceFront(InteractingCircle(x, y, radius));
    QGraphicsScene::addItem(new GraphicsCircleItem(x, y, radius, it));
}

void InteractingCircleScene::removeCircle(GraphicsCircleItem * item) {
    QGraphicsScene::removeItem(item);
    backend->erase(item->backend);
}

void InteractingCircleScene::start() {
    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    animationTimer.start(renderTime);
    calcStop = false;
    detachCalcThread();
}

void InteractingCircleScene::stop() {
    if (!calcStop.load()) {
        calcStop = true; // set calcStop flag to true, so detached thread will exit its loop
        while(calcStop.load()); // wait for detached thread (it will change calcStop to false)
        calcStop = true; // assign calcStop flag to true again (destructor will use it)
    }
}

void InteractingCircleScene::updateAnimation() {
    ic_vector currentState = backend->circlesVector(); // cache current backend state
    auto currentView = items();
    uint64_t startTime = calcStartTime.load();
    // compute time remaining to next calculation iteration and extrapolate lineary items positions
    double calcTimeRemaining = std::max(0.0,
                               calcTime - (std::chrono::duration_cast<ms>(Time::now().time_since_epoch()).count() - startTime));
    double alpha = 1.0 - calcTimeRemaining / calcTime; // extrapolation coeff
    for (size_t i = 0; i < currentState.size(); ++i) {
        if (currentState[i].isInteracting()) {
            static_cast<GraphicsCircleItem *>(currentView[i])->setPos(currentState[i].x() + alpha * currentState[i].dx(),
                                                                      currentState[i].y() + alpha * currentState[i].dy());
        }
    }
}

void InteractingCircleScene::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    if (event->button() == Qt::RightButton && !itemAt(event->scenePos(), QTransform())) {
        addCircle(event->scenePos().x(), event->scenePos().y(), default_radius);
    }
    else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void InteractingCircleScene::detachCalcThread() {
    std::thread([this]{calcBackend(calcTime);}).detach();
}

void InteractingCircleScene::calcBackend(double const dt) {
    uint64_t loops = 0;
    auto startTime = std::chrono::duration_cast<ms>(Time::now().time_since_epoch()).count();
    while(!calcStop.load()) {
        calcStartTime.store(std::chrono::duration_cast<ms>(Time::now().time_since_epoch()).count());
        backend->moveCircles(1000.0 / dt, CircleUtils::scale(1.0), CircleUtils::speed(0.0005));
        auto curEndTime = std::chrono::duration_cast<ms>(Time::now().time_since_epoch()).count();
        double calcTimeRemaining = std::max(0.0, startTime + dt * (loops + 1) - curEndTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(calcTimeRemaining)));
        loops++;
    }
    calcStop = false;
}
