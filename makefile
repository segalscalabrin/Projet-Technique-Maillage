# Variables
G++ = g++
CXXFLAGS = -Wall -O2 -I src         # Options de compilation
SRC = src/**/*.cpp src/*.cpp      # Inclut tous les fichiers .cpp dans les sous-dossiers
OUT = run                           # Nom de l'exécutable

# Compilation
all: $(OUT)

$(OUT): $(SRC)
	$(G++) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)