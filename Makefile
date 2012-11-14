CC = g++
RM = rm -f
LIBS = -lm -lglut -lGL -lGLU
CFLAGS = -Wall

TARGET = scanline
OBJS = Scanline.o Quad.o Polygon.o

all: $(TARGET)

.c.o:
	$(CC) -c $(CFLAGS) $<
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)
	$(RM) $(OBJS)
clean:
	$(RM) $(TARGET) *#* *~ $(OBJS)