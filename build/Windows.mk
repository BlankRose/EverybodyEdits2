# ############################################################################ #
#          .-.                                                                 #
#    __   /   \   __                                                           #
#   (  `'.\   /.'`  )   EverybodyEdits2 - Windows.mk                           #
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
STFU        = > NUL 2>&1 || exit 0

# Print out message
print       = Write-Host -NoNewLine "$(1)"
printret    = Write-Host "$(1)"

# Creation & Deletion
# (Extra args can be passed)
newdir      = New-Item $(1) -ItemType Directory -Force $(2)
link        = New-Item $(2) -ItemType SymbolicLink -Value $(1) -Force $(3)
copy        = Copy-Item $(1) $(2) -Recurse -Force $(3)
delete      = Remove-Item $(1) -Recurse -Force $(2)


#############################
# -- PROJECT PREPARATION -- #
#############################

# Get all source files
HEADERS     = 
SOURCES     = 

# Get all directories (uses find with regex)
INCLUDES    = 
POSSIBLELIB = 
LIB_FOLDERS = 
