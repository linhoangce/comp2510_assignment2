CC		= gcc
CFLAGS	= -Wall
LDFLAGS =
OBJFILES = student.c main.c
TARGET	 = student

all: $(TARGET)

$(TARGET): $(OBJFILES)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
		rm -f $(TARGET) *~