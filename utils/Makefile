CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		main.cpp

LIBS =

TARGET =	main.exe

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS);./main.exe

all:	$(TARGET)

test:
	$(CXX) -o test_file.exe test_file.cpp

clean:
	rm -f $(OBJS) $(TARGET)
