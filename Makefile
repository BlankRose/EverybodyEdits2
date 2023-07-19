# ############################################################################ #
#          .-.                                                                 #
#    __   /   \   __                                                           #
#   (  `'.\   /.'`  )   EverybodyEdits2 - Makefile                             #
#    '-._.(;;;)._.-'                                                           #
#    .-'  ,`"`,  '-.                                                           #
#   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)               #
#       //\   /         Last Updated: Wednesday, July 19, 2023 5:51 PM         #
#      ||  '-'                                                                 #
# ############################################################################ #


###############################
# -- PROJECT CONFIGURATION -- #
###############################

# Project's name
NAME      = EverybodyEdits2
VERSION   = 0.7
ARGS      = 

# Directories of source files and where to put the object files
SRC_DIR   = src
OUT_DIR   = build/bin
PKG_DIR   = build/pkg

# Target Compiler and options
CC        = c++
CFLAGS    = -Wall -Wextra -Wpedantic -Wunreachable-code -Werror -std=c++17 -Ofast -g3
LINKER    = -fsanitize=address

# Libraries to link and where to find them
LIBRARIES = sfml-graphics sfml-window sfml-system
SEARCHDIR = $(HOME)/sgoinfre/libs $(HOME)/Downloads

# Elements required for packaging
PKG_BIN   = $(NAME)
PKG_ASSET = configs


#############################
# -- PROJECT PREPARATION -- #
#############################

# OS Specific Additions
ifeq ($(OS), Windows_NT)
include build/Windows.mk
else ifeq ($(shell uname -s), Darwin)
include build/OSX.mk
else
include build/Linux.mk
endif

# Special sequences
ESCAPE      = 
RESET       = $(ESCAPE)[0m
BREAK	    = $(ESCAPE)[2K\r
FAILURE     = $(BREAK)$(ESCAPE)[31m
SUCCESS     = $(BREAK)$(ESCAPE)[32m
PENDING     = $(BREAK)$(ESCAPE)[33m

# Final compositions
DEFINES     = VERSION=\"$(VERSION)\" NAME=\"$(NAME)\" #DEBUG_MODE
FINAL_LINK  = $(foreach dir, $(LIB_FOLDERS), -L$(dir)) $(foreach lib, $(LIBRARIES), -l$(lib)) $(LINKER) $(CFLAGS)
FINAL_OBJ   = $(foreach dir, $(INCLUDES), -I$(dir)) $(foreach def, $(DEFINES), -D$(def)) $(CFLAGS)
OBJECTS     = $(SOURCES:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)


#############################
# -- BUILDING TOOLCHAINS -- #
#############################

# Build the project
a: all
all: $(NAME)

# Compile object files (depends on headers)
$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@$(call print,$(PENDING)Compiling $<... $(RESET))
	@$(call newdir,$(dir $@))
	@$(CC) $(FINAL_OBJ) $(CFLAGS) -c $< -o $@

# Compile the executable
$(NAME): $(OBJECTS)
	@$(call print,$(PENDING)Linking $(NAME) v$(VERSION)... $(RESET))
	@$(CC) $(FINAL_LINK) -o $(NAME) $(OBJECTS)
	@$(call printret,$(SUCCESS)$(NAME) v$(VERSION) built successfully!$(RESET))

# Forces to relink the executable
# (Useful when only linking options have changed)
l: relink
relink: $(OBJECTS)
	@$(call print,$(PENDING)Linking $(NAME) v$(VERSION)... $(RESET))
	@$(CC) $(FINAL_LINK) -o $(NAME) $(OBJECTS)
	@$(call printret,$(SUCCESS)$(NAME) v$(VERSION) built successfully!$(RESET))

# Packages the final product
# Uses the package directory to store the files and the package's name
# (Some additional files may be copied aswell)
pkg: package
package: all
	@$(call print,$(PENDING)Packaging $(NAME)...$(RESET))
	@$(call newdir,$(PKG_DIR)/bin $(PKG_OSDIR))
	@$(foreach obj, $(PKG_BIN) $(POSSIBLELIB), $(call copy,$(obj),$(PKG_DIR)/bin,$(STFU);))
	@$(foreach obj, $(PKG_ASSET), $(call copy,$(obj),$(PKG_DIR),$(STFU);))
	@$(foreach obj, $(PKG_OSFILES), $(call copy,$(obj),$(PKG_OSDIR),$(STFU);))
	@$(call link,bin/$(NAME),$(PKG_DIR)/$(NAME),$(STFU))
	@$(call printret,$(SUCCESS)Package $(NAME) successfully created!$(RESET))

# Clean up the object files
c: clean
clean:
	@$(call print,$(PENDING)Cleaning up object files... $(RESET))
	@$(call delete,$(OBJECTS))
	@$(call printret,$(SUCCESS)Object files cleaned up!$(RESET))

# Removes the package directory
# NOTE: This does removes the whole package directory
cpkg: cleanpackage
cleanpackage:
	@$(call print,$(PENDING)Clearing package $(NAME)...$(RESET))
	@$(call delete,$(PKG_DIR))
	@$(call printret,$(SUCCESS)Package $(NAME) has been removed!$(RESET))

# Clean up the executable
fc: fullclean
fullclean: clean cleanpackage
	@$(call print,$(PENDING)Cleaning up executable...$(RESET))
	@$(call delete,$(NAME))
	@$(call printret,$(SUCCESS)Executable cleaned up!$(RESET))

# Recompile the project from scratch
re: remake
remake: fullclean all

# Run the executable without leaks detections
# NOTE: ensures shared library paths are set aswell
r: run
run: all
	@$(call printret,$(PENDING)Running $(NAME)... OUTPUT:$(RESET))
	@cd $(PKG_DIR) && export ASAN_OPTIONS=detect_leaks=0 \
		&& ./$(NAME) $(ARGS)
	@$(call printret,$(SUCCESS)$(NAME) exited successfully!$(RESET))

# Run the executable with leak detections
# /!\ NOTE: leaks /usr/lib/x86_64-linux-gnu/dri/radeonsi_dri.so (OpenGL)
#       are caused by SFML's global variables (from: SFML's devs)
rl: run-leak
run-leak: package
	@$(call printret,$(PENDING)Running $(NAME)... OUTPUT:$(RESET))
	@cd $(PKG_DIR) && ./$(NAME)
	@$(call printret,$(SUCCESS)$(NAME) exited successfully!$(RESET))

# Displays debug messages
d: debug
debug:
	@$(call printret,Debugging $(NAME) v$(VERSION)...)
	@$(call printret, > Sources: $(SOURCES))
	@$(call printret, > Objects: $(OBJECTS))
	@$(call printret, > Includes: $(INCLUDES))
	@$(call printret, > Libraries: $(LIBRARIES))
	@$(call printret, > Library Folders: $(LIB_FOLDERS))
	@$(call printret, > OS-Specific: $(PKG_OSFILES))


#################################
# -- MAKEFILE CONFIGURATIONS -- #
#################################

.DEFAULT_GOAL = all
.PHONY: all relink package \
	clean cleanpackage fullclean remake \
	run run-leak debug
