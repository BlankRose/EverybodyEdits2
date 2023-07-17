#############################
# -- PROJECT PREPARATION -- #
#############################

# Get all source files
HEADERS     = $(shell find -E $(SRC_DIR) . -type f -iregex '.*.h(pp)?')
SOURCES     = $(shell find -E $(SRC_DIR) -type f -iregex '.*.c(pp)?')
OBJECTS     = $(SOURCES:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)

# Get all directories (uses find with regex)
PWD         = $(shell pwd)
INCLUDES    = $(shell find -E $(SEARCHDIR) . -type d -iregex '.*/inc(lude)?[s]?' 2>/dev/null)
POSSIBLELIB = $(foreach lib, $(LIBRARIES), $(shell find -E $(SEARCHDIR) . -iregex '.*/lib$(lib).*' 2>/dev/null))
LIB_FOLDERS = $(shell echo $(POSSIBLELIB) | tr ' ' '\n' | xargs -n 1 dirname | sort -u) # Idk how to make it UNIQ

# Final compositions
DEFINES     = VERSION=\"$(VERSION)\" NAME=\"$(NAME)\" #DEBUG_MODE
FINAL_LINK  = $(foreach dir, $(LIB_FOLDERS), -L$(dir)) $(foreach lib, $(LIBRARIES), -l$(lib)) $(LINKER) $(CFLAGS)
FINAL_OBJ   = $(foreach dir, $(INCLUDES), -I$(dir)) $(foreach def, $(DEFINES), -D$(def)) $(CFLAGS)
LD_EXPORT   = export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)$(foreach dir, $(LIB_FOLDERS),:$(dir))
