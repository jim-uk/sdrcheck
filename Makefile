CFLAGS?=-O2 -g -Wall  
LD_EXTRA_PATHS= -L /usr/lib/arm-linux-gnueabihf/ -L /usr/lib/i386-linux-gnu/ -L /usr/lib/x86_64-linux-gnu/
LDFLAGS+=-lpthread -lm $(LD_EXTRA_PATHS)
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif
UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
#Conditional for Linux
CFLAGS+= $(shell pkg-config --cflags librtlsdr)
LD_LIBRTLSDR=$(shell pkg-config --libs librtlsdr)
#Ugly hack. Check if the output of pkg-config is long enough to be valid
LD_LIBRTLSDR_LENGTH := $(shell echo "$(LD_LIBRTLSDR)" | wc -c)
ifeq ($(shell test $(LD_LIBRTLSDR_LENGTH) -gt 13; echo $$?),0)
#The  pkg-config output seem to be ok, let's use it
	LDFLAGS+=$(shell pkg-config --libs librtlsdr)
else
#The  pkg-config output seem to be too short, use the default lib name and default paths
	LDFLAGS+=-lrtlsdr
endif

else
#
#ADD THE CORRECT PATH FOR LIBUSB AND RTLSDR
#TODO:
#    CMAKE will be much better or create a conditional pkg-config


# RTLSDR
RTLSDR_INCLUDE=/mingw64/include
RTLSDR_LIB=/mingw64/lib

# LIBUSB
LIBUSB_INCLUDE=/mingw64/include/libusb-1.0
LIBUSB_LIB=/mingw64/lib

ifeq ($(UNAME),Darwin)
#Conditional for OSX
CFLAGS+= -I/usr/local/include/ -I/opt/homebrew/include -I$(LIBUSB_INCLUDE) -I$(RTLSDR_INCLUDE)
LDFLAGS+= -L/usr/local/lib -L/opt/homebrew/lib -L$(LIBUSB_LIB) -L$(RTLSDR_LIB) -lrtlsdr -lusb-1.0 
else
#Conditional for Windows
CFLAGS+=-I $(LIBUSB_INCLUDE) -I $(RTLSDR_INCLUDE)
LDFLAGS+=-L$(LIBUSB_INCLUDE) -L$(RTLSDR_LIB) -L/usr/lib -lusb-1.0 -lrtlsdr -lWs2_32
endif


endif

CC?=gcc
SOURCES= \
	main.c rtl_ais.c convenience.c 

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=sdrcheck

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE).exe

install:
	install -d -m 755 $(DESTDIR)/$(PREFIX)/bin
	install -m 755 $(EXECUTABLE) "$(DESTDIR)/$(PREFIX)/bin/"


