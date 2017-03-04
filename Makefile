# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mseinic <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/14 11:35:32 by mseinic           #+#    #+#              #
#    Updated: 2017/03/04 20:09:01 by mseinic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#----------------MODIF--------------------#
NAME := 42sh

LINE_EDITION_PATH := line_edition/
LINE_EDITION_SRC := actions print_cmd home_end go_up_and_down ctrl_right_left check_word check_space cut_cpy_paste ctrl_up_down right_left delete_backspace ctrl_l ctrl_d up_down

ERROR_MSG_PATH := error_msg/
ERROR_MSG_SRC := error_msg

AUTOCOMP_PATH := autocomp/
AUTOCOMP_SRC := autocomp

BUILTIN_PATH := builtin/
BUILTIN_SRC :=


HISTORY_PATH := builtin/builtin_history/
HISTORY_SRC := bi_history

CD_PATH := builtin/builtin_cd/
CD_SRC := bi_cd

ECHO_PATH := builtin/builtin_env/
ECHO_SRC :=

ENV_PATH := builtin/builtin_env/
ENV_SRC := env_init env_print env_char env_set env_unset

FILES = main line_init ft_term do_termcaps multi_line_init test_edit_line

#----------------MODIF--------------------#

#----------------STD--------------------#
COMPILER := gcc

SRC_PATH := src/

HDR_PATH := includes/

CACHE_PATH := cache/

INCF = -I $(HDR_PATH) -I libft/include/

CFLAGS = -g -Wextra -Wall $(INCF)

LIBFT = -L libft/ -lft -lncurses

LIB_PATH = libft/libft.a
#----------------STD--------------------#

#----------------ADDING PATH AND FORMAT TO THE FILENAMES--------------------#
FILES+=$(addprefix $(LINE_EDITION_PATH),$(LINE_EDITION_SRC))
FILES+=$(addprefix $(ERROR_MSG_PATH),$(ERROR_MSG_SRC))
FILES+=$(addprefix $(AUTOCOMP_PATH),$(AUTOCOMP_SRC))
FILES+=$(addprefix $(BUILTIN_PATH),$(BUILTIN_SRC))
FILES+=$(addprefix $(ENV_PATH),$(ENV_SRC))
FILES+=$(addprefix $(CD_PATH),$(CD_SRC))
FILES+=$(addprefix $(HISTORY_PATH),$(HISTORY_SRC))
FILES+=$(addprefix $(ECHO_PATH),$(ECHO_SRC))


SRC = $(addprefix $(SRC_PATH),$(addsuffix .c,$(FILES)))
OBJ = $(addprefix $(CACHE_PATH),$(addsuffix .o,$(FILES)))
#----------------ADDING PATH AND FORMAT TO THE FILENAMES--------------------#

#-----------------COLORS------------------#
#-------B = Bold---------#
#-------I = Intense------#
#-------U = Underline----#
Green	:= "\033[0;32m"
Red		:= "\033[1;91m"
Yellow	:= "\033[0;33m"
CYAN	:= "\033[1;36m"
YELLOW	:= "\033[1;33m"
END 	:= "\033[0m"
#-----------------COLORS------------------#

CACHE:=.cache_exists

all: $(NAME)

$(NAME): $(OBJ) $(LIB_PATH)
		@echo $(Yellow) " Compiling --> $@ <-- with $(CFLAGS) " $(END)
		@$(COMPILER) $(OBJ) -o $@ $(INCF) $(LIBFT)
		@echo $(Green) " !!! Ready !!!" $(END)

$(CACHE_PATH)%.o:$(SRC_PATH)%.c | $(CACHE)
		@echo $(Green) "Creating $(NAME) : $@ with $< " $(END);
		@$(COMPILER) $(CFLAGS) -o $@ -c $<

%.c:
	@echo $(Red) "Missing file : $@" $(END)

$(CACHE):
	@mkdir -p $(CACHE_PATH)
	@mkdir -p $(CACHE_PATH)$(LINE_EDITION_PATH)
	@mkdir -p $(CACHE_PATH)$(ERROR_MSG_PATH)
	@mkdir -p $(CACHE_PATH)$(AUTOCOMP_PATH)
	@mkdir -p $(CACHE_PATH)$(BUILTIN_PATH)
	@mkdir -p $(CACHE_PATH)$(ENV_PATH)
	@mkdir -p $(CACHE_PATH)$(CD_PATH)
	@mkdir -p $(CACHE_PATH)$(HISTORY_PATH)
	@mkdir -p $(CACHE_PATH)$(ECHO_PATH)

clean:
		@/bin/rm -rf $(CACHE_PATH)
		@/bin/rm -rf $(CACHE)
		@echo $(Red) "Deleting ---->>>> $(CACHE_PATH)" $(END)
fclean: clean
		@/bin/rm -rf $(NAME)
		@echo $(Red) "Deleting ---->>>> $(NAME)" $(END)
re: fclean all

norm:
		@echo $(Red)
		@norminette $(SRC) $(HDR_PATH) | grep -v Norme -B1 || true
		@echo $(END)

libft/libft.a:
		@echo $(CYAN) "Making $@" $(EOC)
		@make -C libft/
		@make -C libft clean
test:
		@echo $(YELLOW)"Files :\n\033[0;33m"$(HDR_PATH)
		@echo $(BLUE)"Objects :\n\033[0;34m"$(OBJ)
		@echo $(CYAN)"Sources :\n\033[0;36m"$(SRC)

.PHONY: all clean fclean re
