CXX = g++
CXX_FLAGS = -std=c++14 -Iinclude
LDLIBS = -lUnitTest++

TARGET = cipher
TARGET_TEST = cipher_test

SOURCES = src/cipher.cpp \
		  src/main.cpp

SOURCES_TEST = src/cipher.cpp \
			   tests/unittest.cpp

all: $(TARGET) $(TARGET_TEST)

$(TARGET) : $(SOURCES)
	$(CXX) $(CXX_FLAGS) $(SOURCES) -o $(TARGET)

$(TARGET_TEST) : $(SOURCES_TEST)
	$(CXX) $(CXX_FLAGS) $(SOURCES_TEST) -o $(TARGET_TEST) $(LDLIBS)

test: $(TARGET_TEST)
	./$(TARGET_TEST)

clean:
	rm -f $(TARGET) $(TARGET_TEST)

.PHONY: all clean test
