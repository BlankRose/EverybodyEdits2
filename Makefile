# ********************************************************************* #
#          .-.                                                          #
#    __   /   \   __                                                    #
#   (  `'.\   /.'`  )   Everybody Edits 2 - Makefile                    #
#    '-._.(;;;)._.-'                                                    #
#    .-'  ,`"`,  '-.                                                    #
#   (__.-'/   \'-.__)   BY: Rosie (https://github.com/BlankRose)        #
#       //\   /         Last Updated: Wed Mar 29 17:21:52 CEST 2023     #
#      ||  '-'                                                          #
# ********************************************************************* #

# -- CONFIGURATIONS -- #

IN_DIR		= .
OUT_DIR		= build

EXE_NAME	= EverybodyEdits2
EXE_ARGS	= 


# -- COMPILATION -- #

SUB_MAKE	= $(MAKE) -C $(OUT_DIR)

a: all
all: compile

b: build
build:
	@cmake -S $(IN_DIR) -B $(OUT_DIR)

c: compile
compile: build
	@$(SUB_MAKE) all

clean:
	@$(SUB_MAKE) clean

fc: fullclean
fullclean:
	@rm -Rf build/**

re: remake
remake: fullclean all

r: run
run: compile
	@$(OUT_DIR)/$(EXE_NAME) $(EXE_ARGS)


# -- MAKEFILE CONFIGS -- #

.DEFAULT_GOAL = all
.PHONY: all build compile fullclean remake run