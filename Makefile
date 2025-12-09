# Compilateur et flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INCDIR)

# Répertoires
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Nom de l'exécutable
TARGET = program

# Trouver tous les fichiers sources et générer les fichiers objets correspondants
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Règle par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Règle pour compiler les fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Créer le répertoire obj si nécessaire
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Nettoyer les fichiers compilés
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Recompiler tout
rebuild: clean all

# Phony targets
.PHONY: all clean rebuild

