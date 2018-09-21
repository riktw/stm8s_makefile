CC=sdcc
AR=sdar
CFLAGS=-c -mstm8 --out-fmt-elf --all-callee-saves --debug --verbose --stack-auto --fverbose-asm  --float-reent --no-peep -DSTM8S003 -I ../../inc -I../../src --opt-code-size -I.
LDFLAGS=-rc 
SOURCES=$(wildcard stm*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_LINK=$(SOURCES:.c=.rel)
EXECUTABLE=stm8s003.lib

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(AR) $(LDFLAGS) $(EXECUTABLE) $(OBJECTS_LINK) 

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -f *.lib *.rst *.rel *.lst *.ihx *.sym *.asm *.lk *.map
	rm -f $(EXECUTABLE)
