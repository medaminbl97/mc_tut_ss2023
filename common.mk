# OS specifics
ifdef OS
   RM = del /Q
   CP = copy
   ConvertPath = $(subst /,\,$1)
else
    RM = rm -f
	CP = cp
	ConvertPath = $1
endif

# How we name the output
TARGET=boot.elf

# We find the SDK ROOT by examining the path
# of this file (common.mk)
SDKROOT=$(dir $(lastword $(MAKEFILE_LIST)))

# Define include paths
INCPATH= -I./
INCPATH+= -I$(SDKROOT)include
INCPATH+= -I$(SDKROOT)include/system

# Where to look for libraries
LIBPATH= -L$(SDKROOT)lib

# Export Debugger Symbols
DEBUGMODE= -ggdb3

# Optimization Settings
# Change only if you know what you're doing!
OPT= -O0


# Wildcard all .c and .s files in project dir
SRC= $(wildcard *.c)
OBJS= $(SRC:.c=.o)
ASRC= $(wildcard *.s)
OBJS+= $(ASRC:.s=.o)

# Add /system files
VPATH= $(SDKROOT)system
OBJS+= startup_tm4c.o sysclk.o init_tools.o

# Additional libraries (use LIBS+=-lmylib) to add project specific
# libraries in project Makefile;
# Note: libcdev is requred for _open, _read, _write in syscalls.c
LIBS=

# Compiler options
CFLAGS= $(DEBUGMODE) $(OPT) -mthumb -march=armv7e-m -mtune=cortex-m4 -DTM4C123GH6PM

# Assembler options
AFLAGS= $(DEBUGMODE) -mcpu=cortex-m4

# Linker options
LDFILE= $(SDKROOT)tiva.ld
LDFLAGS= --specs=nosys.specs -mthumb -march=armv7e-m -mtune=cortex-m4\
 -T $(LDFILE) -o $(TARGET) $(LIBPATH)

# A Makefile to rule them all
all: $(TARGET)

$(TARGET): $(OBJS) 
	arm-none-eabi-gcc $(LDFLAGS) $(LIBPATH) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	arm-none-eabi-gcc -std=c11 -c $(CFLAGS) $(INCPATH) -o $@ $<

%.o: %.s
	arm-none-eabi-as $(AFLAGS) -o $@ $<

.PHONY: clean

clean:
	$(RM) $(OBJS) $(TARGET)
