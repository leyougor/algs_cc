CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		fw-csa.o

LIBS =

TARGET =	fw-csa.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
