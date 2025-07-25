#include <nanobind/nanobind.h>
#include "../src/q3.h"

namespace nb = nanobind;

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
        .def(nb::init<q3Vec3, q3Mat3>())
        .def_ro("position", &q3Transform::position)
        .def_ro("rotation", &q3Transform::rotation);
    // scene
    nb::class_<q3Scene>(m, "Scene")
        .def(nb::init<float, q3Vec3, int>())
        .def("create_body", &q3Scene::CreateBody, nb::rv_policy::reference)
        .def("step", &q3Scene::Step);
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
        .def_ro("body_type", &q3BodyDef::bodyType);
    // box def
    nb::class_<q3BoxDef>(m, "BoxDef")
        .def(nb::init<>())
        .def("Set", &q3BoxDef::Set);
    // body
    nb::class_<q3Body>(m, "Body")
        .def("add_box", &q3Body::AddBox);
}