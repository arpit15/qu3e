#include <nanobind/nanobind.h>
#include "../src/q3.h"

namespace nb = nanobind;

// boxPtr
class BoxPtr {
    public:
    const q3Box* box;
    BoxPtr(const q3Box* box) : box(box) {}
    ~BoxPtr() { }
};
// bodyPtr
class BodyPtr {
    public:
    q3Body* body;
    BodyPtr(q3Body* body) : body(body) {}
    ~BodyPtr() { }
    BoxPtr add_box(const q3BoxDef& def) {
        return BoxPtr(body->AddBox(def));
    }
};

NB_MODULE(qu3e_ext, m) {
    m.doc() = "qu3e extension module";
    // vec3
    nb::class_<q3Vec3>(m, "Vec3")
        .def(nb::init<float, float, float>())
        .def("Set", &q3Vec3::Set);
    // mat3
    nb::class_<q3Mat3>(m, "Mat3")
        .def(nb::init<float, float, float, float, float, float, float, float, float>())
        .def("Set", nb::overload_cast<const q3Vec3&, float>(&q3Mat3::Set));
    // transform
    nb::class_<q3Transform>(m, "Transform")
        .def(nb::init<>())
        .def(nb::init<q3Vec3, q3Mat3>())
        .def_ro("position", &q3Transform::position)
        .def_ro("rotation", &q3Transform::rotation);

    // util functions
    m.def("q3Identity", [](q3Mat3& m) { q3Identity(m); });
    m.def("q3Identity", [](q3Transform& t) { q3Identity(t); });
    // body type enum
    nb::enum_<q3BodyType>(m, "BodyType")
    .value("Static", eStaticBody)
    .value("Dynamic", eDynamicBody)
    .value("Kinematic", eKinematicBody);
    // body def
    nb::class_<q3BodyDef>(m, "BodyDef")
    .def(nb::init<>())
    .def_ro("position", &q3BodyDef::position)
    .def_ro("axis", &q3BodyDef::axis)
    .def_ro("angle", &q3BodyDef::angle)
    .def_ro("linear_velocity", &q3BodyDef::linearVelocity)
    .def_ro("angular_velocity", &q3BodyDef::angularVelocity)
    .def_rw("body_type", &q3BodyDef::bodyType);
    // box def
    nb::class_<q3BoxDef>(m, "BoxDef")
    .def(nb::init<>())
    .def("Set", &q3BoxDef::Set)
    .def("SetDensity", &q3BoxDef::SetDensity)
    .def("SetFriction", &q3BoxDef::SetFriction)
    .def("SetRestitution", &q3BoxDef::SetRestitution);
    // box
    nb::class_<q3Box>(m, "Box");
    // boxPtr
    nb::class_<BoxPtr>(m, "BoxPtr");
    // body
    nb::class_<q3Body>(m, "Body");
    // bodyPtr
    nb::class_<BodyPtr>(m, "BodyPtr")
        .def("add_box", &BodyPtr::add_box);
    // scene
    nb::class_<q3Scene>(m, "Scene")
        .def(nb::init<float>())
        .def(nb::init<float, q3Vec3, int>())
        .def("step", &q3Scene::Step)
        .def("dump", [](q3Scene& scene, const char* filename) {
            FILE* file = fopen(filename, "w");
            scene.Dump(file);
            fclose(file);
        })
        .def("create_body", [](q3Scene& scene, const q3BodyDef& def) {
            return BodyPtr(scene.CreateBody(def));
        });
}