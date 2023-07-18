# ############################################################################ #
#          .-.                                                                 #
#    __   /   \   __                                                           #
#   (  `'.\   /.'`  )   EverybodyEdits2 - Linux.mk                             #
#    '-._.(;;;)._.-'                                                           #
#    .-'  ,`"`,  '-.                                                           #
#   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)               #
#       //\   /         Last Updated: Wednesday, July 19, 2023 12:24 AM        #
#      ||  '-'                                                                 #
# ############################################################################ #

#############################
# -- PROJECT PREPARATION -- #
#############################

# Get all source files
HEADERS     = $(shell find $(SRC_DIR) . -type f -iregex '.*\.h\(pp\)?')
SOURCES     = $(shell find $(SRC_DIR) -type f -iregex '.*\.c\(pp\)?')
OBJECTS     = $(SOURCES:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)

# Get all directories (uses find with regex)
INCLUDES    = $(shell find . $(SEARCHDIR) -type d -iregex '.*/inc\(lude\)?[s]?' 2>/dev/null)
POSSIBLELIB = $(foreach lib, $(LIBRARIES), $(shell find . $(SEARCHDIR) -iregex '.*/lib\($(lib)\).*' 2>/dev/null))
LIB_FOLDERS = $(shell dirname $(POSSIBLELIB) | uniq)

# OS Specific Additions
LINKER     += '-Wl,-rpath,$$ORIGIN'
