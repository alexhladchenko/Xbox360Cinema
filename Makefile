# FINAL WORKING MAKEFILE для Xenon (32-bit PowerPC)
DEVKITXENON ?= /usr/local/xenon

CC = $(DEVKITXENON)/bin/xenon-gcc
LD = $(DEVKITXENON)/bin/xenon-ld
OBJCOPY = $(DEVKITXENON)/bin/xenon-objcopy

# Пути к заголовочным файлам
XENON_INC = $(DEVKITXENON)/usr/include
XENON_XENOS_INC = $(XENON_INC)/xenos
XENON_SOC_INC = $(XENON_INC)/xenon_soc
XENON_STD_INC = $(DEVKITXENON)/xenon/include
GCC_INC = $(DEVKITXENON)/lib/gcc/xenon/9.2.0/include

# Флаги компиляции для 32-bit PowerPC
CFLAGS = -mcpu=cell -mtune=cell -m32 -O2 -Wall \
         -nostdlib -ffreestanding -fno-builtin \
         -I$(XENON_INC) \
         -I$(XENON_XENOS_INC) \
         -I$(XENON_SOC_INC) \
         -I$(XENON_STD_INC) \
         -I$(GCC_INC)

# ПРАВИЛЬНЫЕ 32-bit библиотеки
LIBXENON = $(DEVKITXENON)/usr/lib/libxenon.a
LIBC_32 = $(DEVKITXENON)/xenon/lib/32/libc.a
LIBM_32 = $(DEVKITXENON)/xenon/lib/32/libm.a
LIBGCC_32 = $(DEVKITXENON)/lib/gcc/xenon/9.2.0/32/libgcc.a  # 32-bit!

TARGET = MovieCore
BUILD_DIR = build
SOURCE_DIR = source
# 1. Ищем исходники правильно (без обратного слэша)
SOURCES = $(wildcard $(SOURCE_DIR)/*.c) $(wildcard $(SOURCE_DIR)/ui/*.c)
# 2. Правильное преобразование .c -> .o с сохранением структуры
OBJS = $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Правило для создания build директорий
$(shell mkdir -p $(BUILD_DIR) $(BUILD_DIR)/ui)

all: $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(OBJS)
	@echo "=== Линковка с 32-bit библиотеками ==="
	@echo "libxenon.a: $(notdir $(LIBXENON))"
	@echo "libc.a (32-bit): $(notdir $(LIBC_32))"
	@echo "libm.a (32-bit): $(notdir $(LIBM_32))"
	@echo "libgcc.a (32-bit): $(notdir $(LIBGCC_32))"
	
	$(LD) -nostdlib -m elf32ppc \
	  -T$(DEVKITXENON)/app.lds \
	  $(OBJS) \
	  --start-group $(LIBXENON) $(LIBC_32) $(LIBM_32) $(LIBGCC_32) --end-group \
	  -o $@
	
	@echo "✓ Успешно создан: $(TARGET).elf"

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@
	@echo "✓ Создан бинарный файл: $(TARGET).bin"
	@echo "Размер: $$(stat -c%s $(TARGET).bin) байт"

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET).elf $(TARGET).bin *.map

# Проверка всех библиотек
check-all:
	@echo "=== ПРОВЕРКА ВСЕХ БИБЛИОТЕК ==="
	@echo ""
	@echo "1. 32-bit библиотеки (должны использоваться):"
	@file $(LIBC_32) 2>/dev/null || echo "libc.a не найден"
	@file $(LIBM_32) 2>/dev/null || echo "libm.a не найден"
	@file $(LIBGCC_32) 2>/dev/null || echo "libgcc.a (32-bit) не найден"
	@echo ""
	@echo "2. 64-bit библиотеки (НЕ должны использоваться):"
	@file $(DEVKITXENON)/xenon/lib/libc.a 2>/dev/null | head -1 || echo "64-bit libc.a не найден"
	@file $(DEVKITXENON)/lib/gcc/xenon/9.2.0/libgcc.a 2>/dev/null | head -1 || echo "64-bit libgcc.a не найден"
	@echo ""
	@echo "3. Заголовочные файлы:"
	@test -f "$(XENON_XENOS_INC)/xenos.h" && echo "✓ xenos.h найден" || echo "✗ xenos.h не найден"
	@test -f "$(GCC_INC)/stddef.h" && echo "✓ stddef.h найден" || echo "✗ stddef.h не найден"

.PHONY: all clean check-all
