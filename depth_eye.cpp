
#include <memory>
#include <iostream>
#include <CameraSystem.h>
#include <Common.h>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

namespace bp = boost::python;
namespace np = boost::python::numpy;

using namespace Voxel;

/*
Scan devices. Return a list of devices.
*/
auto scan()
{
  bp::list deviceList;

  Voxel::CameraSystem sys;
  const Vector<DevicePtr> &devices = sys.scan();
  for (auto &d: devices) {
    auto ud = std::dynamic_pointer_cast<USBDevice>(d);
    if (d)
      deviceList.append(bp::make_tuple(ud->vendorID(), ud->productID(), ud->serialNumber()));
  }

  return deviceList;
}

BOOST_PYTHON_MODULE(depth_eye)
{
  // Initialize numpy
  np::initialize();

  using namespace boost::python;
  bp::def("scan", scan);
}

