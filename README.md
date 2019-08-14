

** Experimental Python3 branch **
-----

# PyDepthEye
A simple Python binding for Seeed Studio DepthEye camera

# Building
Currently, the program can only be built on Ubuntu 16.04.

## Building and installing Boost
1. Download and extract the boost libraries: `curl -L https://dl.bintray.com/boostorg/release/1.70.0/source/boost_1_70_0.tar.gz | tar xz
2. Install system dependencies: `sudo apt install -y python-dev build-essential git-core python-numpy`
3. Prepare to build the boost libraries: `cd boost_1_70_0 && ./bootstrap.sh --with-python-version=XXX`. Replace the XXX with the Python version against which you want to build (for example, 3.5).
4. Build boost libraries: `./b2 --with-python`
5. Install boost libraries: `sudo ./b2 --with-python install`
6. Run `sudo ldconfig`

## Setting up DepthCam dependencies
1. Clone the DepthEye SDK: `git clone https://github.com/pointcloud-ai/DepthEyeSdk.git`
2. Set up an environment variable to point to the installation dir: `export VOXEL_SDK_PATH=${HOME}/DepthEyeSdk/third_party/voxelsdk_ubuntu_4.13`

## Building
1. Clone the PyDepthEye repository: `git clone https://github.com/avishorp/PyDepthEye.git`.
2. Build: `cd PyDepthEye && make PYTHON_VER=X` - replace X with the *major* Python version - 2 or 3. The process should complete with module named `depth_eye.so`.


