# STM8 device (default is STM8 discovery board)
DEVICE=STM8S003
DEVICE_FLASH=stm8s003f3

TARGETNAME = blinky

# trap handling requires SDCC >=v3.4.3
SKIP_TRAPS = 0

# set output folder and target name
OUTPUT_DIR = ./build
TARGET     = $(OUTPUT_DIR)/$(TARGETNAME).ihx

# set project folder and files (all *.c)
PRJ_ROOT    = .
PRJ_SRC_DIR = $(PRJ_ROOT)/Src
PRJ_INC_DIR = $(PRJ_ROOT)/Inc
# all project sources included by default
PRJ_SOURCE  = $(notdir $(wildcard $(PRJ_SRC_DIR)/*.c))
PRJ_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(PRJ_SOURCE:.c=.rel))

# set SPL paths
DRIVER_DIR = ./STM8S_StdPeriph_Driver/
SPL_SRC_DIR = $(DRIVER_DIR)src
SPL_INC_DIR = $(DRIVER_DIR)inc

OBJLIB = $(OUTPUT_DIR)/stm8s103.lib

SRC_FILES = $(SPL_SRC_DIR)/stm8s_awu.c $(SPL_SRC_DIR)/stm8s_beep.c $(SPL_SRC_DIR)/stm8s_clk.c $(SPL_SRC_DIR)/stm8s_exti.c $(SPL_SRC_DIR)/stm8s_flash.c $(SPL_SRC_DIR)/stm8s_gpio.c $(SPL_SRC_DIR)/stm8s_i2c.c $(SPL_SRC_DIR)/stm8s_itc.c $(SPL_SRC_DIR)/stm8s_iwdg.c $(SPL_SRC_DIR)/stm8s_rst.c $(SPL_SRC_DIR)/stm8s_spi.c $(SPL_SRC_DIR)/stm8s_tim1.c $(SPL_SRC_DIR)/stm8s_wwdg.c

ifeq ($(DEVICE), $(filter $(DEVICE), STM8S105 STM8S005 STM8S103 STM8S003 STM8S903 STM8AF626x))
	SRC_FILES += $(SPL_SRC_DIR)/stm8s_adc1.c
endif
ifeq ($(DEVICE), $(filter $(DEVICE), STM8S208 STM8S207 STM8S007 STM8AF52Ax STM8AF62Ax))
	SRC_FILES += $(SPL_SRC_DIR)/stm8s_adc2.c
endif
ifeq ($(DEVICE), $(filter $(DEVICE), STM8S208 STM8AF52Ax))
	SRC_FILES += $(SPL_SRC_DIR)/stm8s_can.c
endif
ifneq ($(DEVICE), STM8S903)
	SRC_FILES += $(SPL_SRC_DIR)/stm8s_tim2.c
endif
ifeq ($(DEVICE), $(filter $(DEVICE), STM8S208 STM8S207 STM8S007 STM8S105 STM8S005 STM8AF52Ax STM8AF62Ax STM8AF626x))
	SRC_FILES += $(SPL_SRC_DIR)/stm8s_tim3.c
endif
ifneq ($(DEVICE), STM8S903)
	SRC_FILES += $(SPL_SRC_DIR)/stm8s_tim4.c
endif
ifeq ($(DEVICE), STM8S903)
	SRC_FILES += $(SPL_SRC_DIR)/stm8s_tim5.c $(SPL_SRC_DIR)/stm8s_tim6.c
endif
ifeq ($(DEVICE), $(filter $(DEVICE), STM8S208 STM8S207 STM8S007 STM8S103 STM8S003 STM8S903 STM8AF52Ax STM8AF62Ax))
	SRC_FILES += $(SPL_SRC_DIR)/stm8s_uart1.c
endif
ifeq ($(DEVICE), $(filter $(DEVICE), STM8S105 STM8S005 STM8AF626x))
	SRC_FILES += $(SPL_SRC_DIR)/stm8s_uart2.c
endif
ifeq ($(DEVICE), $(filter $(DEVICE), STM8S208 STM8S207 STM8S007 STM8AF52Ax STM8AF62Ax))
	SRC_FILES += $(SPL_SRC_DIR)/stm8s_uart3.c
endif

OBJ_FILES1 = $(SRC_FILES:%.c=%.rel)
OBJ_FILES =  $(OBJ_FILES1:$(SPL_SRC_DIR)%=%)

# set compiler path & parameters 
CC_ROOT =
CC      = sdcc-3.6
AR 	= sdar-3.6
CFLAGS  = -mstm8 -lstm8 --opt-code-size -l$(OBJLIB) -DUSE_STDPERIPH_DRIVER
CLFLAGS = -mstm8 -I$(INC_DIR) -I./Inc --opt-code-size -D$(DEVICE) -c
ARFLAGS = -rc

# collect all include folders
INCLUDE = -I$(PRJ_INC_DIR) -I$(SPL_INC_DIR) 

# collect all source directories
VPATH=$(PRJ_SRC_DIR):$(SPL_SRC_DIR)

.PHONY: clean

all: $(OBJLIB) $(TARGET)

$(OUTPUT_DIR)/%.rel: %.c
	$(CC) $(CFLAGS) -D$(DEVICE) -DSKIP_TRAPS=$(SKIP_TRAPS) -c $?

$(OUTPUT_DIR)/%.rel: %.c
	$(CC) $(CFLAGS) -D$(DEVICE) $(INCLUDE) -DSKIP_TRAPS=$(SKIP_TRAPS) -c $? -o $@

$(TARGET): $(PRJ_OBJECTS)
	$(CC) $(CFLAGS) --out-fmt-ihx -o $(TARGET) $^

flash: $(TARGET)
	stm8flash -c stlink -p $(DEVICE_FLASH) -s flash -w $(TARGET)

$(OBJLIB):
	cd STM8S_StdPeriph_Driver/src/; \
	./doit; \
	mv stm8s103.lib ../../build

clean:
	rm $(OUTPUT_DIR)/*

