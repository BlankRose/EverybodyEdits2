# ############################################################################ #
#          .-.                                                                 #
#    __   /   \   __                                                           #
#   (  `'.\   /.'`  )   EverybodyEdits2 - OSX.mk                               #
#    '-._.(;;;)._.-'                                                           #
#    .-'  ,`"`,  '-.                                                           #
#   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)               #
#       //\   /         Last Updated: Tuesday, July 18, 2023 7:18 PM           #
#      ||  '-'                                                                 #
# ############################################################################ #

#############################
# -- PROJECT PREPARATION -- #
#############################

# Get all source files
HEADERS     = $(shell find -E $(SRC_DIR) . -type f -iregex '.*.h(pp)?')
SOURCES     = $(shell find -E $(SRC_DIR) -type f -iregex '.*.c(pp)?')
OBJECTS     = $(SOURCES:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)

# Get all directories (uses find with regex)
INCLUDES    = $(shell find -E $(SEARCHDIR) . -type d -iregex '.*/inc(lude)?[s]?' 2>/dev/null)
POSSIBLELIB = $(foreach lib, $(LIBRARIES), $(shell find -E $(SEARCHDIR) . -iregex '.*/lib$(lib).*' 2>/dev/null))
LIB_FOLDERS = $(shell echo $(POSSIBLELIB) | tr ' ' '\n' | xargs -n 1 dirname | sort -u)

# OS Specific Packages
PKG_OSFILES = $(foreach lib, $(LIB_FOLDERS), $(shell find -E $(lib)/../extlibs -type d -iregex '.*.framework' 2>/dev/null))
PKG_OSDIR   = $(PKG_DIR)/Frameworks
