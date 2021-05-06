CXX=g++
CXXFLAGS=-O3 -g -Wall -fPIC -std=c++1y `root-config --cflags` -I${PYTHIA8_INCLUDE_DIR} -I${FASTJET_INCLUDE_DIR} -I${ATLAS_PATH}/include -I${ROOT_UTILS_PATH}/include
LDFLAGS=-Wl,-rpath `root-config --libdir --glibs` -L${ATLAS_PATH}/lib -L${ROOT_UTILS_PATH}/lib -L${PYTHIA8_LIBRARY} -L${FASTJET_LIBRARY} -lGlobalParams -lUtilities -lfastjet -lAtlasUtils -lAtlasStyle -ldl

reqdirs= bin outputs logs errors Plots

.PHONY: directories all clean

all: directories gen analyze plotter

directories:
	mkdir -p ${reqdirs}

gen: src/gen.cxx
	$(CXX) $< $(CXXFLAGS) $(LDFLAGS) $(PYTHIA8_DIR)/lib/libpythia8.a -o bin/gen

analyze: src/analyze.cxx
	$(CXX) $< $(CXXFLAGS) $(LDFLAGS) -o bin/analyze

plotter: src/plotter.cxx
	$(CXX) $< $(CXXFLAGS) $(LDFLAGS) -o bin/plotter

clean:
	rm -rf bin logs errors
