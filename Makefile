SRC=depth_eye.cpp
SO=depth_eye.so
CPPFLAGS=-std=c++14

VOXEL_SDK_INCLUDE=$(VOXEL_SDK_PATH)/include/voxel-0.6.7
VOXEL_SDK_LIB=$(VOXEL_SDK_PATH)/lib

LIBS=\
  -lboost_python27 \
  -lboost_numpy27 \
  -lpython2.7 \
  -lvoxel

all: $(SO)

clean:
	rm $(SO)

$(SO): $(SRC)
	$(CXX) $(CPPFLAGS) -shared -fPIC -o $(SO) $(SRC) -I$(VOXEL_SDK_INCLUDE) -I/usr/include/python2.7 $(LIBS)


