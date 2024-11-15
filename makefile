# Variables
MPICXX = g++                  # Utilisation du compilateur g++
CXXFLAGS = -Wall -O2  # Options de compilation, ajout de -Iinclude pour inclure le dossier `include`

SRC = src/*.cpp
OUT = run

# Compilation
all: $(OUT)

$(OUT): $(SRC)
	$(MPICXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)