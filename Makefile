# ############################################################################ #
#          .-.                                                                 #
#    __   /   \   __                                                           #
#   (  `'.\   /.'`  )   EverybodyEdits2 - Makefile                             #
#    '-._.(;;;)._.-'                                                           #
#    .-'  ,`"`,  '-.                                                           #
#   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)               #
#       //\   /         Last Updated: Tuesday, July 18, 2023 8:08 PM           #
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
SEARCHDIR = .. $(HOME)/sgoinfre/libs $(HOME)/Downloads

# Elements required for packaging
PKG_BIN   = $(NAME)
PKG_ASSET = configs


#############################
# -- PROJECT PREPARATION -- #
#############################

ifeq ($(OS), Windows_NT)
include build/Windows.mk
else ifeq ($(shell uname -s), Darwin)
include build/OSX.mk
else # Linux Systems
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
FINAL_LINK  = $(foreach dir, $(LIB_FOLDERS), -L$(dir)) $(foreach lib, $(LIBRARIES), -l$(lib)) $(LINKER) $(CFLAGS) #$(foreach dir, $(LIB_FOLDERS), -Wl,-rpath=$(dir))
FINAL_OBJ   = $(foreach dir, $(INCLUDES), -I$(dir)) $(foreach def, $(DEFINES), -D$(def)) $(CFLAGS)
LD_EXPORT   = export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)$(foreach dir, $(LIB_FOLDERS),$(dir))


#############################
# -- BUILDING TOOLCHAINS -- #
#############################

# Build the project
a: all
all: $(NAME)

# Compile object files (depends on headers)
$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@echo -n "$(PENDING)Compiling $<... $(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(FINAL_OBJ) $(CFLAGS) -c $< -o $@

# Compile the executable
$(NAME): $(OBJECTS)
	@echo -n "$(PENDING)Linking $(NAME) v$(VERSION)... $(RESET)"
	@$(CC) $(FINAL_LINK) -o $(NAME) $(OBJECTS)
	@echo "$(SUCCESS)$(NAME) v$(VERSION) built successfully!$(RESET)"

# Packages the final product
# Uses the package directory to store the files and the package's name
# (Some additional files may be copied aswell)
pkg: package
package: all
	@echo "$(PENDING)Packaging $(NAME)...$(RESET)"
	@mkdir -p $(PKG_DIR)/bin $(PKG_OSDIR)
	@$(foreach obj, $(PKG_BIN) $(POSSIBLELIB), cp -R $(obj) $(PKG_DIR)/bin 2>/dev/null || true;)
	@$(foreach obj, $(PKG_ASSET), cp -R $(obj) $(PKG_DIR) 2>/dev/null || true;)
	@$(foreach obj, $(PKG_OSFILES), cp -R $(obj) $(PKG_OSDIR) 2>/dev/null || true;)
	@ln -s bin/$(NAME) $(PKG_DIR)/$(NAME) 2> /dev/null || true
	@echo "$(SUCCESS)Package $(NAME) successfully created!$(RESET)"

# Clean up the object files
c: clean
clean:
	@echo -n "$(PENDING)Cleaning up object files... $(RESET)"
	@rm -f $(OBJECTS)
	@echo "$(SUCCESS)Object files cleaned up!$(RESET)"

# Removes the package directory
# NOTE: This does removes the whole package directory
cpkg: cleanpackage
cleanpackage:
	@echo "$(PENDING)Clearing package $(NAME)...$(RESET)"
	@rm -Rf $(PKG_DIR)
	@echo "$(SUCCESS)Package $(NAME) has been removed!$(RESET)"

# Clean up the executable
fc: fullclean
fullclean: clean cleanpackage
	@echo -n "$(PENDING)Cleaning up executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(SUCCESS)Executable cleaned up!$(RESET)"

# Recompile the project from scratch
re: remake
remake: fullclean all

# Run the executable without leaks detections
# NOTE: ensures shared library paths are set aswell
r: run
run: all
	@echo "$(PENDING)Running $(NAME)... OUTPUT:$(RESET)"
	@cd $(PKG_DIR) && export ASAN_OPTIONS=detect_leaks=0 \
		&& ./$(NAME) $(ARGS)
	@echo "$(SUCCESS)$(NAME) exited successfully!$(RESET)"

# Run the executable with leak detections
# /!\ NOTE: leaks /usr/lib/x86_64-linux-gnu/dri/radeonsi_dri.so (OpenGL)
#       are caused by SFML's global variables (from: SFML's devs)
#     Oddly enough: they may not always appears ? (The fuck ?!)
rl: run-leak
run-leak: package
	@echo "$(PENDING)Running $(NAME)... OUTPUT:$(RESET)"
	@cd $(PKG_DIR) && ./$(NAME)
	@echo "$(SUCCESS)$(NAME) exited successfully!$(RESET)"

# Displays debug messages
d: debug
debug:
	@echo "Debugging $(NAME) v$(VERSION)..."
	@echo " > Sources: $(SOURCES)"
	@echo " > Objects: $(OBJECTS)"
	@echo " > Includes: $(INCLUDES)"
	@echo " > Libraries: $(LIBRARIES)"
	@echo " > Library Folders: $(LIB_FOLDERS)"
	@echo " > OS-Specific: $(PKG_OSFILES)"


#################################
# -- MAKEFILE CONFIGURATIONS -- #
#################################

.DEFAULT_GOAL = all
.PHONY: all package \
	clean cleanpackage fullclean remake \
	run run-leak debug
