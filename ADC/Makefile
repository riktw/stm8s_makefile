# STM8 device (default is STM8 discovery board)
DEVICE=STM8S003
DEVICE_FLASH=stm8s003f3

TARGETNAME = adc

# trap handling requires SDCC >=v3.4.3
SKIP_TRAPS = 0

# set output folder and target name
OUTPUT_DIR = ./build
TARGET     = $(OUTPUT_DIR)/$(TARGETNAME).elf

# set project folder and files (all *.c)
PRJ_ROOT    = .
PRJ_SRC_DIR = $(PRJ_ROOT)/Src
PRJ_INC_DIR = $(PRJ_ROOT)/Inc
# all project sources included by default
PRJ_SOURCE  = $(notdir $(wildcard $(PRJ_SRC_DIR)/*.c))
PRJ_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(PRJ_SOURCE:.c=.rel))

# set SPL paths
DRIVER_DIR = ./STM8S_StdPeriph_Driver/
SPL_INC_DIR = $(DRIVER_DIR)inc

OBJLIB = $(PRJ_INC_DIR)/stm8s003.lib
OBJLIBNDB = $(PRJ_INC_DIR)/stm8s003nodebug.lib


# set compiler path & parameters 
CC      = sdcc
AR 	= sdar
ifeq ($(NODEBUG), 1)
    CFLAGS =-mstm8  -l$(OBJLIBNDB) --out-fmt-ihx -DUSE_STDPERIPH_DRIVER --all-callee-saves --verbose --stack-auto --fverbose-asm --no-peep
    TARGET = $(OUTPUT_DIR)/$(TARGETNAME).ihx
else
	CFLAGS =-mstm8  -l$(OBJLIB) --debug --out-fmt-elf -DUSE_STDPERIPH_DRIVER --all-callee-saves --verbose --stack-auto --fverbose-asm --no-peep
    TARGET = $(OUTPUT_DIR)/$(TARGETNAME).elf
endif

# collect all include folders
INCLUDE = -I$(PRJ_INC_DIR) -I$(SPL_INC_DIR) 

# collect all source directories
VPATH=$(PRJ_SRC_DIR):$(SPL_SRC_DIR)

.PHONY: clean

all: $(OBJLIB) $(TARGET)

$(OUTPUT_DIR)/%.rel: %.c
	$(CC)  $(CFLAGS) -D$(DEVICE) $(INCLUDE) -DSKIP_TRAPS=$(SKIP_TRAPS) -c $? -o $@

$(TARGET): $(PRJ_OBJECTS)
	$(CC)  $(CFLAGS) -o $(TARGET) $^
	

flash: $(TARGET)
	stm8flash -c stlink -p $(DEVICE_FLASH) -s flash -w $(TARGET)

$(OBJLIB):
	cd STM8S_StdPeriph_Driver/src/; \
	./doit; \
	mv stm8s003.lib ../../Inc; \
	mv stm8s003nodebug.lib ../../Inc

clean:
	rm $(OUTPUT_DIR)/*

