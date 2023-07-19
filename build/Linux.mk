# ############################################################################ #
#          .-.                                                                 #
#    __   /   \   __                                                           #
#   (  `'.\   /.'`  )   EverybodyEdits2 - Linux.mk                             #
#    '-._.(;;;)._.-'                                                           #
#    .-'  ,`"`,  '-.                                                           #
#   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)               #
#       //\   /         Last Updated: Wednesday, July 19, 2023 5:53 PM         #
#      ||  '-'                                                                 #
# ############################################################################ #


######################
# -- SYSTEM CALLS -- #
######################

# Additional expension rules
STFU        = 2> /dev/null || true

# Print out message
print       = echo -n "$(1)"
printret    = echo "$(1)"

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
HEADERS     = $(shell find $(SRC_DIR) . -type f -iregex '.*\.h\(pp\)?')
SOURCES     = $(shell find $(SRC_DIR) -type f -iregex '.*\.c\(pp\)?')

# Get all directories (uses find with regex)
INCLUDES    = $(shell find . $(SEARCHDIR) -type d -iregex '.*/inc\(lude\)?[s]?' 2>/dev/null)
POSSIBLELIB = $(foreach lib, $(LIBRARIES), $(shell find . $(SEARCHDIR) -iregex '.*/lib\($(lib)\).*' 2>/dev/null))
LIB_FOLDERS = $(shell dirname $(POSSIBLELIB) | uniq)

# OS Specific Additions
LINKER     += '-Wl,-rpath,$$ORIGIN'
