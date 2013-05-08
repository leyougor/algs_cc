CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		hello_cc.cpp

LIBS =

TARGET =	hello_cc.exe

$(TARGET):	$(OBJS)
	$(CXX) -Wno-write-strings -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
