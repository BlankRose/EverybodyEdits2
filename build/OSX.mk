# ############################################################################ #
#          .-.                                                                 #
#    __   /   \   __                                                           #
#   (  `'.\   /.'`  )   EverybodyEdits2 - OSX.mk                               #
#    '-._.(;;;)._.-'                                                           #
#    .-'  ,`"`,  '-.                                                           #
#   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)               #
#       //\   /         Last Updated: Wednesday, July 19, 2023 5:49 PM         #
#      ||  '-'                                                                 #
# ############################################################################ #


######################
# -- SYSTEM CALLS -- #
######################

# Additional expension rules
STFU        = 2> /dev/null || true

# Print out message
print       = printf "$(1)"
printret    = printf "$(1)\n"

# Creation & Deletion
# (Extra args can be passed)
newdir      = mkdir -p $(1) $(2)
link        = ln -s $(1) $(2) $(3)
copy        = cp -R $(1) $(2) $(3)
delete      = rm -Rf $(1) $(2)


#############################
# -- PROJECT PREPARATION -- #
#############################

# Get all source files
HEADERS     = $(shell find -E $(SRC_DIR) . -type f -iregex '.*.h(pp)?')
SOURCES     = $(shell find -E $(SRC_DIR) -type f -iregex '.*.c(pp)?')

# Get all directories (uses find with regex)
INCLUDES    = $(shell find -E $(SEARCHDIR) . -type d -iregex '.*/inc(lude)?[s]?' 2>/dev/null)
POSSIBLELIB = $(foreach lib, $(LIBRARIES), $(shell find -E $(SEARCHDIR) . -iregex '.*/lib$(lib).*' 2>/dev/null))
LIB_FOLDERS = $(shell echo $(POSSIBLELIB) | tr ' ' '\n' | xargs -n 1 dirname | sort -u)

# OS Specific Additions
PKG_OSFILES = $(foreach lib, $(LIB_FOLDERS), $(shell find -E $(lib)/../extlibs -type d -iregex '.*.framework' 2>/dev/null))
PKG_OSDIR   = $(PKG_DIR)/Frameworks
