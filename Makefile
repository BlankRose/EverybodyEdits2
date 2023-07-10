# ############################################################################ #
#          .-.                                                                 #
#    __   /   \   __                                                           #
#   (  `'.\   /.'`  )   EverybodyEdits2 - Makefile                             #
#    '-._.(;;;)._.-'                                                           #
#    .-'  ,`"`,  '-.                                                           #
#   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)               #
#       //\   /         Last Updated: Monday, July 10, 2023 2:57 PM            #
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
OUT_DIR   = bin

# Target Compiler and options
CC        = c++
CFLAGS    = -Wall -Wextra -Wpedantic -Wunreachable-code -Werror -std=c++11 -Ofast -g3
LINKER    = -fsanitize=address

# Libraries to link and where to find them
LIBRARIES = sfml-graphics sfml-window sfml-system
SEARCHDIR = $(HOME)/sgoinfre/libs


#############################
# -- PROJECT PREPARATION -- #
#############################

# Get all source files
HEADERS     = $(shell find $(SRC_DIR) . -type f -iregex '.*\.h\(pp\)?')
SOURCES     = $(shell find $(SRC_DIR) -type f -iregex '.*\.c\(pp\)?')
OBJECTS     = $(SOURCES:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)

# Get all directories (uses find with regex)
PWD         = $(shell pwd)
INCLUDES    = $(shell find . $(SEARCHDIR) -type d -iregex '.*/inc\(lude\)?[s]?' 2>/dev/null)
POSSIBLELIB = $(foreach lib, $(LIBRARIES), $(shell find . $(SEARCHDIR) -iregex '.*/lib\($(lib)\).*' 2>/dev/null))
LIB_FOLDERS = $(shell dirname $(POSSIBLELIB) | uniq)

# Special sequences
ESCAPE      = 
RESET       = $(ESCAPE)[0m
BREAK	    = $(ESCAPE)[2K\r
FAILURE     = $(BREAK)$(ESCAPE)[31m
SUCCESS     = $(BREAK)$(ESCAPE)[32m
PENDING     = $(BREAK)$(ESCAPE)[33m

# Final compositions
DEFINES     = VERSION=\"$(VERSION)\" NAME=\"$(NAME)\" DEBUG_MODE
FINAL_LINK  = $(foreach dir, $(LIB_FOLDERS), -L$(dir)) $(foreach lib, $(LIBRARIES), -l$(lib)) $(LINKER) $(CFLAGS)
FINAL_OBJ   = $(foreach dir, $(INCLUDES), -I$(dir)) $(foreach def, $(DEFINES), -D$(def)) $(CFLAGS)
LD_EXPORT   = export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)$(foreach dir, $(LIB_FOLDERS),:$(dir))


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

# Clean up the object files
c: clean
clean:
	@echo -n "$(PENDING)Cleaning up object files... $(RESET)"
	@rm -f $(OBJECTS)
	@echo "$(SUCCESS)Object files cleaned up!$(RESET)"

# Clean up the executable
fc: fullclean
fullclean: clean
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
	@$(LD_EXPORT) && export ASAN_OPTIONS=detect_leaks=0 \
		&& ./$(NAME) $(ARGS)
	@echo "$(SUCCESS)$(NAME) exited successfully!$(RESET)"

# Run the executable with leak detections
# /!\ NOTE: leaks /usr/lib/x86_64-linux-gnu/dri/radeonsi_dri.so (OpenGL)
#       are caused by SFML's global variables (from: SFML's devs)
#     Oddly enough: they may not always appears ? (The fuck ?!)
rl: run-leak
run-leak: all
	@echo "$(PENDING)Running $(NAME)... OUTPUT:$(RESET)"
	@$(LD_EXPORT) && ./$(NAME) $(ARGS)
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


#################################
# -- MAKEFILE CONFIGURATIONS -- #
#################################

.DEFAULT_GOAL = all
.PHONY: all clean fullclean remake run run-leak debug
