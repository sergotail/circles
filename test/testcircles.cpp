#include "gtest/gtest.h"
#include <interactingcircle.h>
#include <interactingcirclelist.h>
#include <graphicscircleitem.h>
#include <interactingcirclescene.h>

// check if circle radius is always non-negative
TEST(testCircle, radiusIsNonNegative) {
    Circle c(0.0, 6.0, 10.0);
    c.setRadius(-1.0);
    ASSERT_DOUBLE_EQ(c.getRadius(), 0.0);
    Circle cc(0.0, 6.0, -1.0);
}

// check if interacting circle dx is zero at first point of time (at init)
TEST(testInteractingCircle, dxIsZeroByInit) {
    InteractingCircle ic(1.0, 1.0, 6.5);
    ASSERT_DOUBLE_EQ(ic.dx(), 0.0);
}

// check if interacting circle dy is zero at first point of time (at init)
TEST(testInteractingCircle, dyIsZeroByInit) {
    InteractingCircle ic(1.0, 1.0, 6.5);
    ASSERT_DOUBLE_EQ(ic.dy(), 0.0);
}

// check if interacting circle interacting flag is true at first point of time (at init)
TEST(testInteractingCircle, interactingIsTrueByInit) {
    InteractingCircle ic(1.0, 1.0, 6.5);
    ASSERT_EQ(ic.isInteracting(), true);
}

// check if interacting circles interaction symmetrically affects on both circles
TEST(testInteractingCircle, interactionIsMutual) {
    InteractingCircle ic1(12.0, 6.0, 5.0);
    InteractingCircle ic2(24.0, 20.0, 5.0);
    for (size_t i = 0; i < 500; ++i) {
        // scale is 1.0, speed is 1.0, dt is 1s
        ic1.accumulateForce(ic2, 1.0);
        ic1.applyForce(1.0, 1.0);
        ic2.applyForce(1.0, 1.0);
        EXPECT_NEAR(ic1.dx(), -ic2.dx(), 0.000001);
        EXPECT_NEAR(ic1.dy(), -ic2.dy(), 0.000001);
    }
}

// check if interacting circles interaction with F = 1/r - 1/r^2 has stable state at r = 1
TEST(testInteractingCircle, interactionHasBalance) {
    InteractingCircle ic1(12.0, 6.0, 1.0);
    InteractingCircle ic2(12.0, 9.0, 1.0);
    for (size_t i = 0; i < 500; ++i) {
        // scale is 1.0, speed is 1.0, dt is 1s
        ic1.accumulateForce(ic2, 1.0);
        ic1.applyForce(1.0, 1.0);
        ic2.applyForce(1.0, 1.0);
        EXPECT_DOUBLE_EQ(ic1.dx(), 0.0);
        EXPECT_DOUBLE_EQ(ic1.dy(), 0.0);
        EXPECT_DOUBLE_EQ(ic2.dx(), 0.0);
        EXPECT_DOUBLE_EQ(ic2.dy(), 0.0);
    }
}

// check if interacting circles interaction vector has right direction (simple cases checked)
TEST(testInteractingCircle, interactionHasRightDirection) {
    //dx == 0
    InteractingCircle ic1(12.0, 6.0, 1.0);
    InteractingCircle ic2(12.0, 10.0, 1.0);
    for (size_t i = 0; i < 500; ++i) {
        // scale is 1.0, speed is 1.0, dt is 1s
        ic1.accumulateForce(ic2, 1.0);
        ic1.applyForce(1.0, 1.0);
        ic2.applyForce(1.0, 1.0);
        EXPECT_DOUBLE_EQ(ic1.dx(), 0.0);
        EXPECT_DOUBLE_EQ(ic2.dx(), 0.0);
    }
    //dy == 0
    InteractingCircle ic3(12.0, 6.0, 1.0);
    InteractingCircle ic4(17.0, 6.0, 1.0);
    for (size_t i = 0; i < 500; ++i) {
        // scale is 1.0, speed is 1.0, dt is 1s
        ic3.accumulateForce(ic4, 1.0);
        ic3.applyForce(1.0, 1.0);
        ic4.applyForce(1.0, 1.0);
        EXPECT_DOUBLE_EQ(ic3.dy(), 0.0);
        EXPECT_DOUBLE_EQ(ic4.dy(), 0.0);
    }
    //dx == dy
    InteractingCircle ic5(12.0, 6.0, 1.0);
    InteractingCircle ic6(17.0, 11.0, 1.0);
    for (size_t i = 0; i < 500; ++i) {
        // scale is 1.0, speed is 1.0, dt is 1s
        ic5.accumulateForce(ic6, 1.0);
        ic5.applyForce(1.0, 1.0);
        ic6.applyForce(1.0, 1.0);
        EXPECT_NEAR(ic5.dx(), ic5.dy(), 0.000001);
        EXPECT_NEAR(ic6.dx(), ic6.dy(), 0.000001);
    }

}

// check if interacting circle cannot interact with itself
TEST(testInteractingCircle, interactionIsNotSelfApplicable) {
    InteractingCircle ic1(12.0, 6.0, 1.0);
    InteractingCircle ic2(12.0, 9.0, 1.0);
    for (size_t i = 0; i < 500; ++i) {
        // scale is 1.0, speed is 1.0, dt is 1s
        ic1.accumulateForce(ic2, 1.0);
        ic1.accumulateForce(ic1, 1.0);
        ic1.applyForce(1.0, 1.0);
        ic2.applyForce(1.0, 1.0);
        EXPECT_DOUBLE_EQ(ic1.dx(), 0.0);
        EXPECT_DOUBLE_EQ(ic1.dy(), 0.0);
        EXPECT_DOUBLE_EQ(ic2.dx(), 0.0);
        EXPECT_DOUBLE_EQ(ic2.dy(), 0.0);
    }
}

// check if interacting circle with interacting = false flag still affects on other circles
TEST(testInteractingCircle, nonInteractingCircleIsMatter) {
    InteractingCircle ic1(12.0, 6.0, 1.0);
    InteractingCircle ic2(12.0, 9.0, 1.0);
    InteractingCircle ic3(52.0, 19.0, 1.0);
    ic3.setInteracting(false);
    for (size_t i = 0; i < 500; ++i) {
        // scale is 1.0, speed is 1.0, dt is 1s
        ic1.accumulateForce(ic2, 1.0);
        ic1.accumulateForce(ic3, 1.0);
        ic2.accumulateForce(ic3, 1.0);
        ic1.applyForce(1.0, 1.0);
        ic2.applyForce(1.0, 1.0);
        ic3.applyForce(1.0, 1.0);
        EXPECT_NE(ic1.dx(), 0.0);
        EXPECT_NE(ic1.dy(), 0.0);
        EXPECT_NE(ic2.dx(), 0.0);
        EXPECT_NE(ic2.dy(), 0.0);
    }
}

// check if interacting circles interaction doesn`t affect on circle with interacting = false flag
TEST(testInteractingCircle, nonInteractingCircleNotMoving) {
    InteractingCircle ic1(12.0, 6.0, 1.0);
    InteractingCircle ic2(36.0, 55.0, 1.0);
    InteractingCircle ic3(52.0, 9.0, 1.0);
    ic3.setInteracting(false);
    for (size_t i = 0; i < 500; ++i) {
        // scale is 1.0, speed is 1.0, dt is 1s
        ic1.accumulateForce(ic2, 1.0);
        ic1.accumulateForce(ic3, 1.0);
        ic2.accumulateForce(ic3, 1.0);
        ic1.applyForce(1.0, 1.0);
        ic2.applyForce(1.0, 1.0);
        ic3.applyForce(1.0, 1.0);
        EXPECT_DOUBLE_EQ(ic3.dx(), 0.0);
        EXPECT_DOUBLE_EQ(ic3.dy(), 0.0);
    }
}

// check if interacting circles list is empty at first point of time (at init)
TEST(testInteractingCircleList, circlesListIsEmptyByInit) {
    InteractingCircleList list;
    ASSERT_EQ(list.size(), 0);
}

// check if interacting circles list changes in proper way while emplaceFront method call
TEST(testInteractingCircleList, emplaceFrontIsCorrect) {
    InteractingCircleList list;

    // check if emlplace front correctly places object
    auto it1 = list.emplaceFront(InteractingCircle(1.0, 1.05, 6.0));
    ASSERT_EQ(list.size(), 1);
    auto it2 = list.emplaceFront(InteractingCircle(2.0, 2.05, 7.0));
    ASSERT_EQ(list.size(), 2);

    ASSERT_DOUBLE_EQ(it1->x(), 1.0);
    ASSERT_DOUBLE_EQ(it1->y(), 1.05);
    ASSERT_DOUBLE_EQ(it1->getRadius(), 6.0);
    ASSERT_DOUBLE_EQ(it2->x(), 2.0);
    ASSERT_DOUBLE_EQ(it2->y(), 2.05);
    ASSERT_DOUBLE_EQ(it2->getRadius(), 7.0);
}

// check if interacting circles list changes in proper way while erase method call
TEST(testInteractingCircleList, eraseIsCorrect) {
    InteractingCircleList list;
    // check if erase removes object from the list
    auto it = list.emplaceFront(InteractingCircle(1.0, 1.05, 6.0));
    list.erase(it);
    ASSERT_EQ(list.size(), 0);
}

// check if interacting circles list changes in proper way while setPos method call
TEST(testInteractingCircleList, setPosIsCorrect) {
    InteractingCircleList list;
    // check if setPos changes circle position correctly
    auto it = list.emplaceFront(InteractingCircle(1.0, 1.05, 6.0));
    list.setPos(it, 2.006, 2.0);
    ASSERT_DOUBLE_EQ(it->x(), 2.006);
    ASSERT_DOUBLE_EQ(it->y(), 2.0);
}

// check if interacting circles list changes in proper way while setInteracting method call
TEST(testInteractingCircleList, setInteractingIsCorrect) {
    InteractingCircleList list;
    // check if setInteracting changes circle interacting flag correctly and its default flag value is true
    auto it = list.emplaceFront(InteractingCircle(1.0, 1.05, 6.0));
    list.setInteracting(it, false);
    ASSERT_EQ(it->isInteracting(), false);
}

// check if interacting circles list changes in proper way while circlesVector method call
TEST(testInteractingCircleList, circlesVectorIsCorrect) {
    InteractingCircleList list;

    // check if emlplace front correctly places object
    auto it1 = list.emplaceFront(InteractingCircle(1.0, 1.05, 6.0));
    auto it2 = list.emplaceFront(InteractingCircle(2.0, 2.05, 7.0));
    list.setPos(it1, 3.0, 3.05);
    list.setInteracting(it2, false);
    auto circlesVector = list.circlesVector();
    ASSERT_EQ(circlesVector.size(), 2);
    ASSERT_DOUBLE_EQ(circlesVector[1].x(), 3.0);
    ASSERT_DOUBLE_EQ(circlesVector[1].y(), 3.05);
    ASSERT_DOUBLE_EQ(circlesVector[1].getRadius(), 6.0);
    ASSERT_DOUBLE_EQ(circlesVector[1].isInteracting(), true);
    ASSERT_DOUBLE_EQ(circlesVector[0].x(), 2.0);
    ASSERT_DOUBLE_EQ(circlesVector[0].y(), 2.05);
    ASSERT_DOUBLE_EQ(circlesVector[0].getRadius(), 7.0);
    ASSERT_DOUBLE_EQ(circlesVector[0].isInteracting(), false);
}

// check if interacting circles list changes in proper way while moveCircles method call
TEST(testInteractingCircleList, moveCirclesIsCorrect) {
    InteractingCircleList list;
    // check if setInteracting changes circle interacting flag correctly
    auto it1 = list.emplaceFront(InteractingCircle(1.0, 1.05, 6.0));
    auto it2 = list.emplaceFront(InteractingCircle(19.0, 15.05, 7.0));
    auto it3 = list.emplaceFront(InteractingCircle(36.0, 100.05, 8.0));
    for (size_t i = 0; i < 500; ++i) {
        list.moveCircles(1.0, 1.0, 1.0);
        EXPECT_NE(it1->dx(), 0.0);
        EXPECT_NE(it1->dy(), 0.0);
        EXPECT_NE(it2->dx(), 0.0);
        EXPECT_NE(it2->dy(), 0.0);
        EXPECT_NE(it3->dx(), 0.0);
        EXPECT_NE(it3->dy(), 0.0);
    }
}

// check if single interacting circle has constant speed
TEST(testOtherPhysics, lonelyCircleHasConstSpeed) {
    InteractingCircleList list;
    // check if setInteracting changes circle interacting flag correctly
    auto it1 = list.emplaceFront(InteractingCircle(1.0, 1.05, 6.0));
    auto it2 = list.emplaceFront(InteractingCircle(19.0, 15.05, 7.0));
    for (size_t i = 0; i < 500; ++i) {
        list.moveCircles(1.0, 1.0, 1.0);
    }
    list.erase(it1);
    //list.moveCircles(1.0, 1.0, 1.0);
    double dx = it2->dx();
    double dy = it2->dy();
    for (size_t i = 0; i < 500; ++i) {
        list.moveCircles(1.0, 1.0, 1.0);
        EXPECT_NEAR(it2->dx(), dx, 0.000001);
        EXPECT_NEAR(it2->dy(), dy, 0.000001);
    }
}

// check if GraphicsCircleItem rect initializes properly
TEST(testGraphicsCircleItem, circleRectIsCorrect) {
    GraphicsCircleItem item(0.0, 1.0, 6.0, static_cast<ic_list::iterator>(nullptr));
    ASSERT_DOUBLE_EQ(item.boundingRect().center().x(), 0.0);
    ASSERT_DOUBLE_EQ(item.boundingRect().center().y(), 0.0);
    double x, y, w, h;
    item.rect().getRect(&x, &y, &w, &h);
    ASSERT_DOUBLE_EQ(w, 12.0);
    ASSERT_DOUBLE_EQ(h, 12.0);
    ASSERT_DOUBLE_EQ(x, -6.0);
    ASSERT_DOUBLE_EQ(y, -6.0);
}

// check if GraphicsCircleItem pos initializes properly
TEST(testGraphicsCircleItem, circlePosIsCorrect) {
    GraphicsCircleItem item(0.0, 1.0, 6.0, static_cast<ic_list::iterator>(nullptr));
    ASSERT_DOUBLE_EQ(item.pos().x(), 0.0);
    ASSERT_DOUBLE_EQ(item.pos().y(), 1.0);
}

// check if empty scene is ok
TEST(testInteractingCircleScene, emptySceneIsCorrect) {
    InteractingCircleScene scene(QRectF(0.0, 0.0, 500.0, 500.0), 5.0, 40, 10);
    ASSERT_EQ(scene.currentState().size(), 0);
    ASSERT_EQ(scene.items().size(), 0);
}

// check if circle addition affects both on backend (interacting circle list) and graphics items list
TEST(testInteractingCircleScene, addCircleIsCorrect) {
    InteractingCircleScene scene(QRectF(0.0, 0.0, 500.0, 500.0), 5.0, 40, 10);
    scene.addCircle(1.0, 5.0, 6.0);
    ASSERT_EQ(scene.currentState().size(), 1);
    ASSERT_EQ(scene.items().size(), 1);
    scene.addCircle(19.0, 50.0, 7.0);
    ASSERT_EQ(scene.currentState().size(), 2);
    ASSERT_EQ(scene.items().size(), 2);
    ASSERT_DOUBLE_EQ(scene.currentState()[0].x(), scene.items()[0]->x());
    ASSERT_DOUBLE_EQ(scene.currentState()[0].y(), scene.items()[0]->y());
    ASSERT_DOUBLE_EQ(scene.currentState()[0].getRadius(), static_cast<GraphicsCircleItem *>(scene.items()[0])->rect().width() / 2);
    ASSERT_DOUBLE_EQ(scene.currentState()[1].x(), scene.items()[1]->x());
    ASSERT_DOUBLE_EQ(scene.currentState()[1].y(), scene.items()[1]->y());
    ASSERT_DOUBLE_EQ(scene.currentState()[1].getRadius(), static_cast<GraphicsCircleItem *>(scene.items()[1])->rect().width() / 2);
}

// check if circle removal affects both on backend (interacting circle list) and graphics items list
TEST(testInteractingCircleScene, removeCircleIsCorrect) {
    InteractingCircleScene scene(QRectF(0.0, 0.0, 500.0, 500.0), 5.0, 40, 10);
    scene.addCircle(1.0, 5.0, 6.0);
    scene.addCircle(19.0, 50.0, 7.0);
    scene.removeCircle(static_cast<GraphicsCircleItem *>(scene.items()[0]));
    ASSERT_EQ(scene.currentState().size(), 1);
    ASSERT_EQ(scene.items().size(), 1);

    ASSERT_DOUBLE_EQ(scene.currentState()[0].x(), 1.0);
    ASSERT_DOUBLE_EQ(scene.currentState()[0].y(), 5.0);
    ASSERT_DOUBLE_EQ(scene.currentState()[0].getRadius(), 6.0);

    scene.removeCircle(static_cast<GraphicsCircleItem *>(scene.items()[0]));
    ASSERT_EQ(scene.currentState().size(), 0);
    ASSERT_EQ(scene.items().size(), 0);
}

// check if backend (interacting circle list) and graphics items list have equal coords
TEST(testInteractingCircleScene, backendAndItemsHaveEqualCoords) {
    // calcucaltion time and render time are set to 1 second due to need of simultaneous capturing both graphic and backend states
    InteractingCircleScene scene(QRectF(0.0, 0.0, 500.0, 500.0), 5.0, 1000, 1000);
    scene.addCircle(1.0, 5.0, 6.0);
    scene.addCircle(19.0, 50.0, 7.0);
    scene.start();
    for (size_t i = 0; i < 5; ++i) {
        // sleep 1 second for finishing current calculation and rendering iteration
        sleep(1);
        auto currentState = scene.currentState();
        EXPECT_NE(currentState[0].dx(), 0.0);
        EXPECT_NE(currentState[0].dy(), 0.0);

        EXPECT_NEAR(currentState[0].x(), scene.items()[0]->x(), 0.001);
        EXPECT_NEAR(currentState[0].y(), scene.items()[0]->y(), 0.001);
        EXPECT_DOUBLE_EQ(currentState[0].getRadius(), static_cast<GraphicsCircleItem *>(scene.items()[0])->rect().width() / 2);
        EXPECT_NEAR(currentState[1].x(), scene.items()[1]->x(), 0.001);
        EXPECT_NEAR(currentState[1].y(), scene.items()[1]->y(), 0.001);
        EXPECT_DOUBLE_EQ(currentState[1].getRadius(), static_cast<GraphicsCircleItem *>(scene.items()[1])->rect().width() / 2);
    }
}
