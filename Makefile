# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mseinic <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/14 11:35:32 by mseinic           #+#    #+#              #
#    Updated: 2017/05/23 15:26:32 by angagnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := 42sh

SRC_PATH   := src
HDR_PATH   := include
CACHE_PATH := cache
LIBFT_PATH := libft

LIBFT := $(LIBFT_PATH)/libft.a

# =========================== Partial Compilation ============================ #
LEXER_PATH := lexer
LEXER_SRC  := tokenizer map bufferize others

PARSER_PATH := parser
PARSER_SRC  := exec_op exec_rd exec_list tree resolve antoine push shell_push

FOLDERS := $(LEXER_PATH) $(PARSER_PATH)

FILES  = main
FILES += $(addprefix $(PARSER_PATH)/,$(PARSER_SRC))
FILES += $(addprefix $(LEXER_PATH)/,$(LEXER_SRC))
# ============================================================================ #

SRC = $(addprefix $(SRC_PATH)/,$(addsuffix .c,$(FILES)))
OBJ = $(addprefix $(CACHE_PATH)/,$(addsuffix .o,$(FILES)))

# ================================= Compiler ================================= #
CC ?= gcc

CPPFLAGS = -Wall -Wextra
CPPFLAGS += $(addprefix -I,$(HDR_PATH) $(LIBFT_PATH)/include)

LDFLAGS += $(addprefix -L,$(LIBFT_PATH))
LDLIBS  += $(addprefix -l,ft)
# ============================================================================ #

all: $(NAME)

$(NAME): $(LIBFT)
$(NAME): $(OBJ)
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(CACHE_PATH)/%.o: $(SRC_PATH)/%.c | $(CACHE_PATH)
	$(CC) $(CPPFLAGS) -c -o $@ $<

$(CACHE_PATH):
	mkdir -p $(addprefix $@/,$(FOLDERS))

clean:
		$(RM) -r $(CACHE_PATH)

fclean: clean
		$(RM) $(NAME)

re: fclean
	@$(MAKE) all --no-print-directory


%.a:
		$(MAKE) -C ${@D}
		$(MAKE) -C ${@D} clean

.PHONY: all clean fclean re
