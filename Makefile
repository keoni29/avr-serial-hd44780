# Makefile for AVR Projects
#
# Usage:
#   1) Specify the build/programming tools
#   2) Specify the device
#   3) Build the project and program the target
# 	- make : Generate the HEX files and show device memory usage
#   - make clean : Delete build files
#   - make purge : Delete the build and dist directory
#   - make fuses : Configure the fuses (do this once)
#   - make flash : Write the HEX file to the target program memory
#   - make reset : Resets the target

NAME = display

CC = avr-gcc

# 1. Specify programmer
AVRDUDE_PROGRAMMER_ID = usbasp

# 2. Specify device
DEVICE = atmega8
AVRDUDE_DEVICE = m8

# Unless you know what you are doing, do not touch anything past this line
OBJDIR = build
SRCDIR = src
OUTDIR = dist
INCDIR = inc

INC = -I$(INCDIR)
SRC = $(shell find $(SRCDIR)/ -type f -name '*.c')
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
ELF = $(OUTDIR)/$(NAME).elf
HEX = $(OUTDIR)/$(NAME).hex

CFLAGS = -Wall -Wextra -pedantic $(INC)

CFLAGS+= -mmcu=$(DEVICE) -DF_CPU=8000000UL -Wstrict-prototypes -mcall-prologues -DHD44780_BIT=4
LDFLAGS= -mmcu=$(DEVICE) -lprintf_flt -lm -uvfprintf

CFLAGS += -O1 -g     # For debug: optimization for size and speed and debug info
# CFLAGS += -O1 -g0  # For release: optimize and remove debug info

AVRDUDE_FLAGS = -c$(AVRDUDE_PROGRAMMER_ID) -p$(AVRDUDE_DEVICE)

all: $(HEX)

$(HEX):$(ELF)
	@mkdir -p "$(@D)"
	avr-objcopy -j .text -j .data -O ihex $< $@
	
$(ELF): $(OBJ)
	@mkdir -p "$(@D)"
	$(CC) $(LDFLAGS) $(OBJ) -o $@  && avr-size $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean purge flash reset fuses
clean:
	@rm -f $(OBJ) $(ELF) $(HEX) && echo "clean succesful" || echo "clean failed"
	
purge:
	@rm -rf $(OBJDIR) $(OUTDIR) && echo "purge succesful" || echo "purge failed"

flash:
	avrdude $(AVRDUDE_FLAGS) -U flash:w:$(HEX)
reset:
	avrdude $(AVRDUDE_FLAGS) -p$(AVRDUDE_DEVICE)

fuses:
	avrdude $(AVRDUDE_FLAGS) -U lfuse:w:0xe4:m -U hfuse:w:0xd9:m



