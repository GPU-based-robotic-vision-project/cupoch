#include "cupoch/collision/primitives.h"
#include "cupoch/geometry/trianglemesh.h"
#include "cupoch/geometry/voxelgrid.h"

#include "cupoch_pybind/docstring.h"
#include "cupoch_pybind/collision/collision.h"

using namespace cupoch;
using namespace cupoch::collision;

void pybind_primitives(py::module &m) {
    py::class_<Primitive, std::shared_ptr<Primitive>>
            primitive(m, "Primitive",
                      "Primitive shape class.");
    py::detail::bind_default_constructor<Primitive>(primitive);
    py::detail::bind_copy_functions<Primitive>(primitive);
    primitive.def("get_axis_aligned_bounding_box", &Primitive::GetAxisAlignedBoundingBox)
             .def_readwrite("transform", &Primitive::transform_);

    py::class_<Box, std::shared_ptr<Box>, Primitive>
            box(m, "Box",
                "Box class. A box consists of a center point "
                "coordinate, and lengths.");
    py::detail::bind_default_constructor<Box>(box);
    py::detail::bind_copy_functions<Box>(box);
    box.def(py::init<const Eigen::Vector3f&>(),
           "Create a Box", "lengths"_a)
       .def(py::init<const Eigen::Vector3f&, const Eigen::Matrix4f&>(),
            "Create a Box", "lengths"_a, "transform"_a)
       .def_readwrite("lengths", &Box::lengths_);

    py::class_<Sphere, std::shared_ptr<Sphere>, Primitive>
            sphere(m, "Sphere",
                   "Sphere class. A sphere consists of a center point "
                   "coordinate, and radius.");
    py::detail::bind_default_constructor<Sphere>(sphere);
    py::detail::bind_copy_functions<Sphere>(sphere);
    sphere.def(py::init<float>(),
               "Create a Sphere", "radius"_a)
          .def(py::init<float, const Eigen::Vector3f&>(),
               "Create a Sphere", "radius"_a, "center"_a)
          .def_readwrite("radius", &Sphere::radius_);

    py::class_<Cylinder, std::shared_ptr<Cylinder>, Primitive>
            cylinder(m, "Cylinder",
                     "Cylinder class. A cylinder consists of a transformation, "
                     "radius, and height.");
    py::detail::bind_default_constructor<Cylinder>(cylinder);
    py::detail::bind_copy_functions<Cylinder>(cylinder);
    cylinder.def(py::init<float, float>(),
                 "Create a Cylinder", "radius"_a, "height"_a)
            .def(py::init<float, float, const Eigen::Matrix4f&>(),
                 "Create a Cylinder", "radius"_a, "height"_a, "transform"_a)
            .def_readwrite("radius", &Cylinder::radius_)
            .def_readwrite("height", &Cylinder::height_);

    py::class_<Cone, std::shared_ptr<Cone>, Primitive>
            cone(m, "Cone",
                 "Cone class. A cone consists of a transformation, "
                 "radius, and height.");
    py::detail::bind_default_constructor<Cone>(cone);
    py::detail::bind_copy_functions<Cone>(cone);
    cone.def(py::init<float, float>(),
             "Create a Cone", "radius"_a, "height"_a)
        .def(py::init<float, float, const Eigen::Matrix4f&>(),
             "Create a Cone", "radius"_a, "height"_a, "transform"_a)
        .def_readwrite("radius", &Cone::radius_)
        .def_readwrite("height", &Cone::height_);

     m.def("create_voxel_grid", &CreateVoxelGrid);
     m.def("create_voxel_grid_with_sweeping", &CreateVoxelGridWithSweeping);
     m.def("create_triangle_mesh", &CreateTriangleMesh);
}