CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		main.cpp file_util.h

LIBS =

TARGET =	main.exe

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

test:
	$(CXX) -o test_file.exe test_file.cpp

clean:
	rm -f $(OBJS) $(TARGET)
