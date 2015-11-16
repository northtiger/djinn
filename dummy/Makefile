CAFFE=/home/ypkang/git/caffe-mobile/distribute
CUDA=/home/ypkang/lib/cuda-6.5
CXX = g++
CXX_FLAGS = -w -fpermissive -I$(CAFFE)/include -I$(CUDA)/include -O3
LINK_FLAGS = -L$(CUDA)/lib64 \
			 -lcudart \
			 $(CAFFE)/lib/libcaffe.so \
			 -lpthread \
			 -ldl \
			 -lrt \
			 -lboost_timer \
			 -lboost_chrono \
			 -lboost_program_options \
			 -lboost_filesystem \
			 -lboost_system \
			 -lglog \

SRC=src

# File names
EXEC = dummy
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) -o $(EXEC) $(LINK_FLAGS)

# To obtain object files
%.o: %.cpp Makefile
	$(CXX) -c $(CXX_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) *.o
