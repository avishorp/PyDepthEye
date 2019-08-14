SRC=depth_eye.cpp
SO=depth_eye.so

VOXEL_SDK_INCLUDE=$(VOXEL_SDK_PATH)/include/voxel-0.6.7
VOXEL_SDK_LIB=$(VOXEL_SDK_PATH)/lib

ifeq ($(PYTHONVER),2)
PYTHON=python
else
ifeq ($(PYTHONVER),3)
PYTHON=python3
else
$(error Please specify either PYTHONVER=2 or PYTHONVER=3)
endif
endif

PYTHON_SHORTVER=$(shell python3  -c 'import sys; vi=sys.version_info; print("%d%d" % (vi.major, vi.minor))')
PYTHON_CONFIG=$(PYTHON)-config

LIBS=\
  -lboost_python$(PYTHON_SHORTVER) \
  -lboost_numpy$(PYTHON_SHORTVER) \
  -lvoxel

LDFLAGS+=-shared -L$(VOXEL_SDK_LIB)
CXXFLAGS+=-std=c++14 -fPIC -I$(VOXEL_SDK_INCLUDE)

OBJFILE=$(SRC:.cpp=.o)

all: $(SO)

clean:
	rm -f $(SO) $(OBJFILE)

$(OBJFILE): $(SRC)
	$(CXX) $(shell $(PYTHON_CONFIG) --cflags) $(CXXFLAGS) -c -o $(OBJFILE) $(SRC)
$(SO): $(OBJFILE)
	$(CXX) $(shell $(PYTHON_CONFIG) --ldflags) $(LDFLAGS) -o $(SO) $(OBJFILE) $(LIBS)



