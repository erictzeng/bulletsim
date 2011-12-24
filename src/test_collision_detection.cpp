#include "environment.h"
#include "simplescene.h"
#include "userconfig.h"
#include <boost/shared_ptr.hpp>

int main(int argc, char **argv) {
    Config::read(argc, argv);
    CFG.scene.enableRobot = false;
    Scene s;
    s.bullet->setGravity(btVector3(0, 0, 0));

    boost::shared_ptr<btDefaultMotionState> ms (
            new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 1+0.01))));
    SphereObject::Ptr s1(new SphereObject(1, 1, ms));
    s.env->add(s1);

    ms.reset(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 2+0.001, 1+0.01))));
    SphereObject::Ptr s2(new SphereObject(1, 1, ms));
    s.env->add(s2);

    BulletInstance::CollisionObjectList ignore, out;

    ignore.push_back(s.ground->rigidBody.get());

    printf("=== first try: spheres should NOT collide ===\n");
    out.clear();
    s.bullet->detectCollisions();
    s.bullet->contactTest(s1->rigidBody.get(), out, &ignore);
    printf("collided with %d objects\n", out.size());
    if (!out.empty() && out[0] == s2->rigidBody.get())
        printf("collided with other sphere!\n");

    printf("=== second try: spheres SHOULD collide ===\n");
    s2->rigidBody->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 2, 1+0.01)));
    out.clear();
    s.bullet->detectCollisions();
    s.bullet->contactTest(s1->rigidBody.get(), out, &ignore);
    printf("collided with %d objects\n", out.size());
    if (!out.empty() && out[0] == s2->rigidBody.get())
        printf("collided with other sphere!\n");

    printf("=== third try: spheres should NOT collide ===\n");
    s2->rigidBody->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 2+0.00001, 1+0.01)));
    out.clear();
    s.bullet->detectCollisions();
    s.bullet->contactTest(s1->rigidBody.get(), out, &ignore);
    printf("collided with %d objects\n", out.size());
    if (!out.empty() && out[0] == s2->rigidBody.get())
        printf("collided with other sphere!\n");
}
