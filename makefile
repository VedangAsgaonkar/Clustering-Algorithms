CLUSTER=src/cluster
PLOTTER=src/plotter
UTIL=src/util
SIMPLECPP=/home/vedang/Desktop/util/simplecpp
CFLAGS=-I/usr/include/X11 -L/usr/X11R6/lib -lX11 -std=c++11 -pthread
WORKING_DIRECTORY=.

main : main.cpp
	g++ main.cpp $(CLUSTER)/gaussianEstimator.cpp $(PLOTTER)/plotter.cpp $(UTIL)/point.cpp $(UTIL)/vec2.cpp $(UTIL)/matrix2.cpp $(SIMPLECPP)/lib/libsprite.a -I$(WORKING_DIRECTORY) -I$(SIMPLECPP)/include $(CFLAGS) -o main

wine : wine.cpp
	g++ wine.cpp $(CLUSTER)/kMeansEstimator.cpp $(PLOTTER)/plotter.cpp $(UTIL)/point.cpp -Wall $(SIMPLECPP)/lib/libsprite.a -I$(WORKING_DIRECTORY) -I$(SIMPLECPP)/include $(CFLAGS) -o wine

smile : smile.cpp
	g++ smile.cpp $(CLUSTER)/densityBasedEstimator.cpp $(PLOTTER)/plotter.cpp $(UTIL)/point.cpp $(UTIL)/range_point.cpp -Wall $(SIMPLECPP)/lib/libsprite.a -I$(WORKING_DIRECTORY) -I$(SIMPLECPP)/include $(CFLAGS) -o smile

spiral : spiral.cpp
	g++ spiral.cpp $(CLUSTER)/hierarchicalEstimator.cpp $(PLOTTER)/plotter.cpp $(UTIL)/point.cpp $(UTIL)/union_point.cpp $(UTIL)/edge.cpp -Wall $(SIMPLECPP)/lib/libsprite.a -I$(WORKING_DIRECTORY) -I$(SIMPLECPP)/include $(CFLAGS) -o spiral

.PHONY : clean

clean :
	rm -f main wine smile spiral