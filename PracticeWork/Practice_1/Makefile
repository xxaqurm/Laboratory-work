# --- Конфигурация Компилятора ---
CXX := g++
# Убираем флаги для генерации зависимостей (DEPFLAGS)
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude

# --- Пути Проекта ---
SRC_DIR := src
BUILD_DIR := build
TARGET := main

# --- Определение Исходных и Объектных Файлов ---

# Исходные файлы в src/
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Объектные файлы для исходников из src/
SRC_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Объектный файл для main.cpp
MAIN_OBJ := $(BUILD_DIR)/main.o

# Общий список всех объектных файлов
OBJS := $(MAIN_OBJ) $(SRC_OBJS)

# --- Основные Цели ---

.PHONY: all clean rebuild

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# --- Правила Компиляции Объектных Файлов ---

# 1. Правило для main.cpp:
# main.o зависит от main.cpp и всех важных заголовочных файлов!
# ВНИМАНИЕ: Если main.cpp включает, например, jsonValue.hpp, 
# вы должны добавить include/jsonValue.hpp сюда вручную:
$(MAIN_OBJ): main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 2. Правило для файлов в src/:
# build/file.o зависит от src/file.cpp
# ВНИМАНИЕ: Здесь также нужно будет вручную прописывать зависимости от .hpp, 
# если вы хотите, чтобы make знал об их изменениях.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Правило Линковки ---

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# --- Очистка и Пересборка ---

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all