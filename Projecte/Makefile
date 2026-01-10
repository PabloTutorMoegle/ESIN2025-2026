# Opcions de compilaciÃ³
OPCIONS = -O0 -c -Wall -ansi -g -std=c++11

# Path de la biblioteca
LIB_PATH = /home/pablo/lib

# Biblioteca ESIN
LDFLAGS = -L$(LIB_PATH) -lesin

# Executable final
driver_gestterm.exe: driver_gestterm.o contenidor.o ubicacio.o terminal.o
	g++ -o driver_gestterm.exe driver_gestterm.o contenidor.o ubicacio.o terminal.o $(LDFLAGS)

driver_gestterm.o: driver_gestterm.cpp contenidor.hpp ubicacio.hpp terminal.hpp
	g++ -c driver_gestterm.cpp $(OPCIONS)

contenidor.o: contenidor.cpp contenidor.hpp
	g++ -c contenidor.cpp $(OPCIONS)

ubicacio.o: ubicacio.cpp ubicacio.hpp
	g++ -c ubicacio.cpp $(OPCIONS)

terminal.o: terminal.cpp terminal.hpp cataleg.hpp contenidor.hpp ubicacio.hpp
	g++ -c terminal.cpp $(OPCIONS)

# Neteja d'arxius temporals
clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.gch
	rm -f diff*.txt

# Regla per a fer els tests
test: 
	./driver_gestterm.exe < jp_public_contenidor.in | diff - jp_public_contenidor.res > diff_cont.txt
	./driver_gestterm.exe < jp_public_ubicacio.in | diff - jp_public_ubicacio.res > diff_ubic.txt
	./driver_gestterm.exe < jp_public_cataleg.in | diff - jp_public_cataleg.res > diff_cata.txt

# Tests mejorats del cataleg
cataleg: driver_gestterm.exe
	@echo "=== Executant tests públics de cataleg ==="
	./driver_gestterm.exe < jp_public_cataleg.in | diff - jp_public_cataleg.res > diff_cata.txt && echo "✓ Tests públics CORRECTES" || echo "✗ Tests públics FALLAREN"
	@echo ""
	@echo "=== Executant tests enhanced de cataleg ==="
	./driver_gestterm.exe < jp_public_cataleg_enhanced.in | diff - jp_public_cataleg_enhanced.res > diff_cata_enhanced.txt && echo "✓ Tests enhanced CORRECTES" || echo "✗ Tests enhanced FALLAREN"
	@echo ""
	@echo "=== Executant tests STRESS de cataleg (50 elements) ==="
	@echo "=== Executant tests STRESS de cataleg (50 elements) ==="
	./driver_gestterm.exe < jp_public_cataleg_stress.in | diff - jp_public_cataleg_stress.res > diff_cata_stress.txt && echo "✓ Tests STRESS CORRECTES" || echo "✗ Tests STRESS FALLAREN"
	@echo ""
	@echo "=== Executant tests STRESS gros (1.000 elements) ==="
	./driver_gestterm.exe < jp_public_cataleg_stress_1000.in | diff - jp_public_cataleg_stress_1000.res > diff_cata_stress_1000.txt && echo "✓ Tests STRESS 1K CORRECTES" || echo "✗ Tests STRESS 1K FALLAREN"
	@echo ""
	@echo "=== Executant tests STRESS EXTREM (100.000 elements) ==="
	./driver_gestterm.exe < jp_public_cataleg_stress_100k.in | diff - jp_public_cataleg_stress_100k.res > diff_cata_stress_100k.txt && echo "✓ Tests STRESS 100K CORRECTES" || echo "✗ Tests STRESS 100K FALLAREN"
	@echo ""
	@echo "=== Executant tests STRESS EXTREM de cataleg (1000 elements) ==="
	./driver_gestterm.exe < jp_public_cataleg_stress_1000.in | diff - jp_public_cataleg_stress_1000.res > diff_cata_stress_1000.txt && echo "✓ Tests STRESS 1000 CORRECTES" || echo "✗ Tests STRESS 1000 FALLAREN"
	@if [ -s diff_cata.txt ]; then echo "Diferències públics:"; cat diff_cata.txt; fi
	@if [ -s diff_cata_enhanced.txt ]; then echo "Diferències enhanced:"; cat diff_cata_enhanced.txt; fi
	@if [ -s diff_cata_stress.txt ]; then echo "Diferències stress:"; cat diff_cata_stress.txt; fi
		@if [ -s diff_cata_stress_1000.txt ]; then echo "Diferències stress 1K:"; cat diff_cata_stress_1000.txt; fi
		@if [ -s diff_cata_stress_100k.txt ]; then echo "Diferències stress 100K:"; cat diff_cata_stress_100k.txt; fi
	@if [ -s diff_cata_stress_1000.txt ]; then echo "Diferències stress 1000:"; cat diff_cata_stress_1000.txt; fi

# Si vols provar la classe terminal ho pots fer amb aquest metode, hauras de colocar un # en la primera linia si vols la diferencia amb la solucio o en la segona linia si vols la sortida amb el teu programa
prova:
	./driver_gestterm.exe < jp_public_terminal.in > diff_term.txt
	./driver_gestterm.exe < jp_public_terminal.in | diff - jp_public_terminal.res > diff_term.txt