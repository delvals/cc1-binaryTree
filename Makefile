# Nom du binaire
EXEC = binarytree

# Répertoires
SRC_DIR = src
INCLUDE_DIR = src/build
BUILD_DIR = bin

# Options du compilateur
CC = gcc
CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR)

# Liste des fichiers source
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Génération des fichiers objets correspondants
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Règle par défaut
all: $(EXEC)

# Règle pour créer l'exécutable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Règle pour compiler les fichiers source en objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crée le dossier de build si nécessaire
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -rf $(BUILD_DIR) $(EXEC)

# Nettoyage complet
distclean: clean

# Phonies pour que Make ne cherche pas ces noms comme fichiers
.PHONY: all clean distclean
