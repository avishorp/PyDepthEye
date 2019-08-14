# PyDepthEye
A simple Python binding for Seeed Studio DepthEye camera

# Building
Currently, the program can only be built on Ubuntu 16.04.

## Building and installing Boost
1. Download and extract the boost libraries: `curl -L https://dl.bintray.com/boostorg/release/1.70.0/source/boost_1_70_0.tar.gz | tar xz
2. Install system dependencies: `sudo apt install -y python-dev build-essential git-core python-numpy`
3. Prepare to build the boost libaries: `cd boost_1_70_0 && ./bootstrap.sh` 
4. Build boost libraries: `./b2 --with-python`
5. Install boost libraries: `sudo ./b2 --with-python install`
6. Run `sudo ldconfig`

## Setting up DepthCam dependencies
1. Clone the DepthEye SDK: `git clone https://github.com/pointcloud-ai/DepthEyeSdk.git`
2. Set up an environment variable to point to the installation dir: `export VOXEL_SDK_PATH=${HOME}/DepthEyeSdk/third_party/voxelsdk_ubuntu_4.13`

## Building
1. Clone the PyDepthEye repository: `git clone https://github.com/avishorp/PyDepthEye.git`.
2. Build: `cd PyDepthEye && make`. The process should complete with module named `depth_eye.so`.

# Using the module
To use the Python module, voxel SDK libraries must be in the path. This can be either be done by copying the libraries to
a system library directory, or by setting LD_LIBRARY_PATH prior to execution of Python. Instructions are available at the
PyDepthSdk repository README file.

# Basic Example
```
import sys
import depth_eye

def frame_cb(phase, amplitude):
    # Phase and amplitude images are available here
    # as numpy arrays. Each array is 80x60. The value
    # of each pixel ranges between 0 to 2047
    pass

devices = depth_eye.scan()
print("Found %d devices" % len(devices))

if (len(devices) == 0):
    print("No device found, exiting")
    sys.exit(1)

# If multiple devices are connected, select one here
selected = devices[0]

frame_rate = 100
c = depth_eye.capture(selected, frame_cb, frame_rate)

```

