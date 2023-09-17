CC = g++
BUILD_DIR = build
SRC_DIR = src
CFLAGS = -std=c++17 -pthread -Wall -Werror

MAIN_PROCESSOR_EXECUTABLE_FILE = mainProcessor.out
MAP_PROCESSOR_EXECUTABLE_FILE = MapProcessorMain.out
REDUCE_PROCESSOR_EXECUTABLE_FILE = ReduceProcessorMain.out

MAIN_PROCESSOR_OBJECTS = \
	$(BUILD_DIR)/MainProcessorMain.o

MAP_PROCESSOR_OBJECTS = \
	$(BUILD_DIR)/MapProcessorMain.o \
	$(BUILD_DIR)/MapProcessor.o 

REDUCE_PROCESSOR_OBJECTS = \
	$(BUILD_DIR)/ReduceProcessorMain.o \
	$(BUILD_DIR)/ReduceProcessor.o

MainProcessorMainSensitivityList = \
	MainProcessorMain.cpp 
	
MapProcessorMainSensitivityList = \
	MapProcessorMain.cpp \
	MapProcessor.cpp

ReduceProcessorMainSensitivityList = \
	ReduceProcessorMain.cpp \
	ReduceProcessor.cpp

all: $(BUILD_DIR) $(MAIN_PROCESSOR_EXECUTABLE_FILE) $(MAP_PROCESSOR_EXECUTABLE_FILE) $(REDUCE_PROCESSOR_EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/MainProcessorMain.o: $(MainProcessorMainSensitivityList)
	$(CC) $(CFLAGS) -c MainProcessorMain.cpp -o $(BUILD_DIR)/MainProcessorMain.o

$(BUILD_DIR)/MapProcessorMain.o: $(MapProcessorMainSensitivityList)
	$(CC) $(CFLAGS) -c MapProcessorMain.cpp -o $(BUILD_DIR)/MapProcessorMain.o

$(BUILD_DIR)/MapProcessor.o: 
	$(CC) $(CFLAGS) -c MapProcessor.cpp -o $(BUILD_DIR)/MapProcessor.o

$(BUILD_DIR)/ReduceProcessorMain.o: $(ReduceProcessorMainSensitivityList)
	$(CC) $(CFLAGS) -c ReduceProcessorMain.cpp -o $(BUILD_DIR)/ReduceProcessorMain.o

$(BUILD_DIR)/ReduceProcessor.o: 
	$(CC) $(CFLAGS) -c ReduceProcessor.cpp -o $(BUILD_DIR)/ReduceProcessor.o


$(MAIN_PROCESSOR_EXECUTABLE_FILE): $(MAIN_PROCESSOR_OBJECTS)
	$(CC) $(CFLAGS) $(MAIN_PROCESSOR_OBJECTS) -o $(MAIN_PROCESSOR_EXECUTABLE_FILE)

$(MAP_PROCESSOR_EXECUTABLE_FILE): $(MAP_PROCESSOR_OBJECTS)
	$(CC) $(CFLAGS) $(MAP_PROCESSOR_OBJECTS) -o $(MAP_PROCESSOR_EXECUTABLE_FILE)

$(REDUCE_PROCESSOR_EXECUTABLE_FILE): $(REDUCE_PROCESSOR_OBJECTS)
	$(CC) $(CFLAGS) $(REDUCE_PROCESSOR_OBJECTS) -o $(REDUCE_PROCESSOR_EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out \
	rmdir -rf systems \
	rmdir -rf pipes/*