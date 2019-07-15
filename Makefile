# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/07 15:58:51 by sbednar           #+#    #+#              #
#    Updated: 2019/07/15 18:19:43 by edraugr-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include				Makefile.inc

NAME			=	guimp
NAME_TEST		=	guimp_test

TEXT_R			=	\033[0m
TEXT_B			=	\033[1m
TEXT_BL			=	\033[5m
TEXT_CR			=	\033[31m
TEXT_CG			=	\033[32m
TEXT_CY			=	\033[33m
TEXT_CB			=	\033[34m
TEXT_CM			=	\033[35m
TEXT_CC			=	\033[36m

FT_DIR			=	./libft
UI_DIR			=	./libui
JTOC_DIR		=	./libjtoc

INC_FT			=	$(FT_DIR)/include
INC_UI			=	$(UI_DIR)/include
INC_JTOC		=	$(JTOC_DIR)/include
INC_DIR			=	./include

SRC_DIR			=	./src
OBJ_DIR			=	./obj

SRC				=	main.c \
					ptrs.c \
					draw_main_canvas_event.c \
					draw_with_selected_tool.c \
					gm_init.c \
					ui_main_fill_default_functions.c \
					gm_generate_surfaces_id.c \
					color_sliders.c \
					get_value_from_slider.c \
					process_tmp_layer.c \
					file_managing.c \
					main_helper1.c \
					main_helper2.c \
					main_helper3.c

SRC_TOOLS		=	brush.c \
					ellipse.c \
					utils_for_ellipse.c \
					eraser.c \
					filler.c \
					hand.c \
					line.c \
					modes.c \
					pipette.c \
					rect.c \
					square.c \
					zoom.c \
					text.c

SRC_LAYERS		=	add_layer.c \
					del_layer.c \
					clear_layers.c

OBJ				=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o)) \
					$(addprefix $(OBJ_DIR)/,$(SRC_TOOLS:.c=.o)) \
					$(addprefix $(OBJ_DIR)/,$(SRC_LAYERS:.c=.o))

INCS			=	-I$(INC_DIR) \
					-I$(INC_FT) \
					-I$(INC_UI) \
					-I$(INC_JTOC) \
					-I./frameworks/SDL2.framework/Versions/A/Headers \
					-I./frameworks/SDL2_image.framework/Versions/A/Headers \
					-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \

FRAMEWORKS		=	-F./frameworks \
					-rpath ./frameworks \
					-framework OpenGL -framework AppKit -framework OpenCl \
					-framework SDL2 -framework SDL2_ttf -framework SDL2_image

LIBS			=	-L$(FT_DIR) -lft \
					-L$(UI_DIR) -lui \
					-L$(JTOC_DIR) -ljtoc

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@echo "$(TEXT_CC)$(TEXT_B)↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ all$(TEXT_R)"
	@touch $(TEMP)
	@echo "$(TEXT_CR)$(TEXT_B)LIBFT:$(TEXT_R)"
	@make -C $(FT_DIR) all
	@echo "$(TEXT_CR)$(TEXT_B)LIBUI:$(TEXT_R)"
	@make -C $(UI_DIR) all
	@echo "$(TEXT_CR)$(TEXT_B)LIBJTOC:$(TEXT_R)"
	@make -C $(JTOC_DIR) all
	@echo "$(TEXT_CR)$(TEXT_B)$(NAME):$(TEXT_R)"
	@make $(OBJ_DIR)
	@make compile
	@rm -f $(TEMP)
	@echo "$(TEXT_CG)$(TEXT_BL)$(TEXT_B)↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ success$(TEXT_R)"

compile: $(OBJ)
	@if [ $(CAT_TEMP) ] ; \
		then \
		make build;\
		fi;

build:
	$(CC) $(CFLAGS) $(OBJ) $(INCS) $(LIBS) $(FRAMEWORKS) -o $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<
	@echo "1" > $(TEMP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/tools/%.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<
	@echo "1" > $(TEMP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/layers/%.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<
	@echo "1" > $(TEMP)

clean:
	@echo "$(TEXT_CC)$(TEXT_B)↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ clean$(TEXT_R)"
	@echo "$(TEXT_CR)$(TEXT_B)LIBFT:$(TEXT_R)"
	@make -C $(FT_DIR) clean
	@echo "$(TEXT_CR)$(TEXT_B)LIBUI:$(TEXT_R)"
	@make -C $(UI_DIR) clean
	@echo "$(TEXT_CR)$(TEXT_B)LIBJTOC:$(TEXT_R)"
	@make -C $(JTOC_DIR) clean
	@echo "$(TEXT_CR)$(TEXT_B)GUIMP:$(TEXT_R)"
	@rm -f $(TEMP)
	rm -rf $(OBJ_DIR)
	@echo "$(TEXT_CG)$(TEXT_BL)$(TEXT_B)↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ success$(TEXT_R)"

fclean:
	@echo "$(TEXT_CC)$(TEXT_B)↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ fclean$(TEXT_R)"
	@echo "$(TEXT_CR)$(TEXT_B)LIBFT:$(TEXT_R)"
	@make -C $(FT_DIR) fclean
	@echo "$(TEXT_CR)$(TEXT_B)LIBUI:$(TEXT_R)"
	@make -C $(UI_DIR) fclean
	@echo "$(TEXT_CR)$(TEXT_B)LIBJTOC:$(TEXT_R)"
	@make -C $(JTOC_DIR) fclean
	@echo "$(TEXT_CR)$(TEXT_B)$(NAME):$(TEXT_R)"
	@rm -f $(TEMP)
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	@echo "$(TEXT_CG)$(TEXT_BL)$(TEXT_B)↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ success$(TEXT_R)"

re: fclean all

norm:
	@echo "$(TEXT_CC)$(TEXT_B)↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ norminette$(TEXT_R)"
	@norminette $(SRC_DIR)
	@norminette $(INC_DIR)
	@norminette $(UI_DIR)/src
	@norminette $(UI_DIR)/inc
	@echo "$(TEXT_CG)$(TEXT_BL)$(TEXT_B)↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ success$(TEXT_R)"

.PHONY: all $(NAME) clean fclean re norm
