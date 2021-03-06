
#include <memory>
#include <iostream>
#include <CameraSystem.h>
#include <Common.h>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

namespace bp = boost::python;
namespace bn = boost::python::numpy;

using namespace Voxel;

auto sys = std::make_unique<Voxel::CameraSystem>();

class DepthCameraWrapper
{
public:
  DepthCameraWrapper(Voxel::DepthCameraPtr& camera): m_camera(camera) {}

  void stop() {
    m_camera->reset();
    sys->disconnect(m_camera);
    m_camera->stop();
    sys.reset();

  }

protected:
  Voxel::DepthCameraPtr m_camera;
};


/*
Scan devices. Return a list of devices.
*/
auto scan()
{
  bp::list deviceList;

  const Vector<DevicePtr> &devices = sys->scan();
  for (auto &d: devices) {
    auto ud = std::dynamic_pointer_cast<USBDevice>(d);
    if (d)
      deviceList.append(bp::make_tuple(ud->vendorID(), ud->productID(), ud->serialNumber()));
  }

  return deviceList;
}

auto capture(bp::tuple device, bp::object callback, uint32_t frameRate)
{
  // Create a device
  auto vid = bp::extract<uint16_t>(device[0])();
  auto pid = bp::extract<uint16_t>(device[1])();
  auto serial = bp::extract<std::string>(device[2])();
	auto voxel_device_ptr = DevicePtr(new USBDevice(vid, pid, serial, -1, "", ""));

  // Connect to the camera
  auto camera = sys->connect(voxel_device_ptr);

  // Set the frame rate
  Voxel::FrameRate fr;
  fr.numerator = frameRate; //bp::extract<uint32_t>(frameRate[0])();
  fr.denominator = 1; //bp::extract<uint32_t>(frameRate[1])();

  camera->setFrameRate(fr);

  camera->getFrameRate(fr);
  //std::cout << "framerate nom " << fr.numerator << '\n';
  //std::cout << "den " << fr.denominator << '\n'; 

  // Register a callback
  camera->registerCallback(DepthCamera::FRAME_RAW_FRAME_PROCESSED, [callback](DepthCamera &dc, const Frame &frame, DepthCamera::FrameType c) {

    // Convert the received frame to NumPy arrays
    auto tof_frame = dynamic_cast<const ToFRawFrame *>(&frame);

	  if(!tof_frame)
	  {
		  std::cout << "Null frame captured? or not of type ToFRawFrame" << std::endl;
		  return;
	  }

	  //short phaseFrame[60*80];
	  //memcpy((char *)phaseFrame, (char *)d->phase(), sizeof(short) * d->size.width * d->size.height);
	//short amplitudeFrame[60*80];
	//memcpy((char *)amplitudeFrame, (char *)d->amplitude(), sizeof(short) * d->size.width * d->size.height);
	//char ambientFrame[60*80];
	//memcpy((char *)ambientFrame, (char *)d->ambient(), sizeof(char) * d->size.width * d->size.height);
	//char flagsFrame[60*80];
	//memcpy((char *)flagsFrame, (char *)d->flags(), sizeof(char) * d->size.width * d->size.height);   

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();
{
    // Create the phase matrix
    auto phase = bn::zeros(bp::make_tuple(60, 80), bn::dtype::get_builtin<short>());
    memcpy(phase.get_data(), tof_frame->phase(), 60*80*sizeof(short));

    // Create the amplitude matrix
    auto amplitude = bn::zeros(bp::make_tuple(60, 80), bn::dtype::get_builtin<short>());
    memcpy(amplitude.get_data(), tof_frame->amplitude(), 60*80*sizeof(short));

    callback(phase, amplitude);
}
    PyGILState_Release(gstate);
    
  });

  // Start capturing
  camera->start();

  // Return a camera object
  return DepthCameraWrapper(camera);
}



BOOST_PYTHON_MODULE(depth_eye)
{
  // Initialize numpy
    Py_Initialize();
  bn::initialize();

  // Register the "Camera" class
  bp::class_<DepthCameraWrapper>("Camera", bp::no_init)
    .def("stop", &DepthCameraWrapper::stop);

  bp::def("scan", scan);
  bp::def("capture", capture);

}

