# Makefile para compilar el proyecto gestterm

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
LDFLAGS = -lesin

# Archivos fuente
SOURCES = driver_gestterm.cpp contenidor.cpp terminal.cpp ubicacio.cpp
HEADERS = contenidor.hpp terminal.hpp ubicacio.hpp cataleg.hpp

# Archivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Nombre del ejecutable
EXECUTABLE = gestterm

# Archivos de test
TEST_INPUT = jp_public/jp_public.in
TEST_OUTPUT = jp_public/jp_public.res
ERROR_FILE = gestterm.err

# Targets principales
all: $(EXECUTABLE)

# Compilar el ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✓ Compilación completada: $(EXECUTABLE)"

# Compilar archivos objeto
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	@echo "  ✓ Compilado: $<"

# Ejecutar los tests públicos
test: $(EXECUTABLE)
	@echo "Ejecutando tests públicos..."
	@if [ -f "$(TEST_INPUT)" ]; then \
		./$(EXECUTABLE) < $(TEST_INPUT) > output.txt; \
		echo "Comparando resultado con archivo esperado..."; \
		if diff -q output.txt $(TEST_OUTPUT) > /dev/null 2>&1; then \
			echo "✓ TESTS PASSED"; \
		else \
			echo "✗ TESTS FAILED - Diferencias encontradas:"; \
			diff output.txt $(TEST_OUTPUT) | head -20; \
		fi; \
	else \
		echo "✗ No se encontró el archivo de test: $(TEST_INPUT)"; \
	fi

# Ejecutar con salida detallada para debugging
test-verbose: $(EXECUTABLE)
	@echo "Ejecutando tests con salida detallada..."
	@if [ -f "$(TEST_INPUT)" ]; then \
		./$(EXECUTABLE) < $(TEST_INPUT) > output.txt 2>&1; \
		echo "Primeras 50 líneas de salida:"; \
		head -50 output.txt; \
		echo "\n--- Comparación con esperado ---"; \
		diff output.txt $(TEST_OUTPUT) | head -30; \
	else \
		echo "✗ No se encontró el archivo de test: $(TEST_INPUT)"; \
	fi

# Limpiar archivos compilados
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) output.txt
	@echo "✓ Archivos compilados eliminados"

# Limpiar todo incluyendo ejecutable
distclean: clean
	rm -f *.o $(EXECUTABLE)
	@echo "✓ Limpieza completa realizada"

# Mostrar ayuda
help:
	@echo "Targets disponibles:"
	@echo "  make all          - Compilar el programa (default)"
	@echo "  make test         - Compilar y ejecutar tests públicos"
	@echo "  make test-verbose - Ejecutar tests con salida detallada"
	@echo "  make clean        - Eliminar archivos compilados"
	@echo "  make distclean    - Eliminar todo lo compilado"
	@echo "  make rebuild      - Limpiar y compilar de nuevo"
	@echo "  make help         - Mostrar esta ayuda"

# Recompilar desde cero
rebuild: distclean all

.PHONY: all test test-verbose clean distclean help rebuild
