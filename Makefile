# ********************************************************************* #
#          .-.                                                          #
#    __   /   \   __                                                    #
#   (  `'.\   /.'`  )   Everybody Edits 2 - Makefile                    #
#    '-._.(;;;)._.-'                                                    #
#    .-'  ,`"`,  '-.                                                    #
#   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        #
#       //\   /         Last Updated: Thu Mar 30 19:21:35 CEST 2023     #
#      ||  '-'                                                          #
# ********************************************************************* #

# -- CONFIGURATIONS -- #

IN_DIR		= .
OUT_DIR		= build
LOG_DIR		= logs

EXE_NAME	= EverybodyEdits2
EXE_ARGS	= 


# -- COMPILATION -- #

SUB_MAKE	= $(MAKE) -sC $(OUT_DIR)
ifeq ($(OS), Windows_NT)
WIN_GEN		= -G "MinGW Makefiles"
WIN_IDC		= > NUL 2>&1 || exit 0
else
UNIX_RECURS	= -p
endif

a: all
all: compile

b: build
build:
	@mkdir $(UNIX_RECURS) $(LOG_DIR) $(WIN_IDC)
	@cmake -S $(IN_DIR) -B $(OUT_DIR) $(WIN_GEN)

c: compile
compile: build
	@$(SUB_MAKE) all

clean:
	@$(SUB_MAKE) clean

fc: fullclean
fullclean:
ifeq ($(OS), Windows_NT)
	@del /f /q /s $(OUT_DIR) $(WIN_IDC)
else
	@rm -Rf $(OUT_DIR)/**
endif

re: remake
remake: fullclean all

r: run
run: compile
	@$(OUT_DIR)/$(EXE_NAME) $(EXE_ARGS)


# -- MAKEFILE CONFIGS -- #

.DEFAULT_GOAL = all
.PHONY: all build compile fullclean remake run