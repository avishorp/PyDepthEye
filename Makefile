SRC=depth_eye.cpp
SO=depth_eye.so

VOXEL_SDK_INCLUDE=$(VOXEL_SDK_PATH)/include/voxel-0.6.7
VOXEL_SDK_LIB=$(VOXEL_SDK_PATH)/lib

LIBS=\
  -lboost_python27 \
  -lboost_numpy27 \
  -lvoxel

LDFLAGS+=-shared -L$(VOXEL_SDK_LIB)
CXXFLAGS+=-std=c++14 -fPIC -I$(VOXEL_SDK_INCLUDE)

OBJFILE=$(SRC:.cpp=.o)

all: $(SO)

clean:
	rm -f $(SO) $(OBJFILE)

$(OBJFILE): $(SRC)
	$(CXX) $(shell python-config --cflags) $(CXXFLAGS) -c -o $(OBJFILE) $(SRC)
$(SO): $(OBJFILE)
	$(CXX) $(shell python-config --ldflags) $(LDFLAGS) -o $(SO) $(OBJFILE) $(LIBS)



