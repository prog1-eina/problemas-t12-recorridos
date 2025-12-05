################################################################################
## Fichero «Makefile» para el programa «recorridos»
################################################################################

################################################################################
## Declaracion de variables del fichero «Makefile»

## DIRECTORIOS
SOURCE_DIR = .
PERMISOS_DIR = ../problemas-t11-registros/permisos-conducir/
BUILD_DIR = build
BIN_DIR = bin

VPATH = $(SOURCE_DIR) $(PERMISOS_DIR)

## COMPILADOR Y OPCIONES DE COMPILACIÓN:
CXX = g++
CXXFLAGS = -Og -Wall -Wextra -I$(PERMISOS_DIR)


## FICHEROS OBJETO (RESULTADOS INTERMEDIOS DE COMPILACIÓN):
RECORRIDOS_PERMISOS_OBJECTS = $(addprefix $(BUILD_DIR)/, permiso.o \
                                                recorridos-vectores-registros.o)

################################################################################
## Reglas del fichero «Makefile»

recorridos: $(RECORRIDOS_PERMISOS_OBJECTS) | $(BIN_DIR)
	$(CXX) -Og -o $(BIN_DIR)/$@ $^

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@  

$(BUILD_DIR)/recorridos-vectores-registros.o: permiso.hpp
$(BUILD_DIR)/registros.o: permiso.hpp

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
ifeq ($(OS),Windows_NT)
	if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)
	if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
else
	rm -f $(RECORRIDOS_PERMISOS_OBJECTS) $(BIN_DIR)/*
endif
