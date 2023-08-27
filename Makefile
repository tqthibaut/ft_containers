NAME	=	Containers
NAME_FT		=	Containers_ft
NAME_STD	=	Containers_std
ECOLE_FT	=	ecole_ft
ECOLE_STD	=	ecole_std

# DIRECTORIES
S_DIR	=	srcs/mains/
S_NAME_FT	=	main_ft.cpp
S_NAME_STD	=	main_std.cpp
I_DIR	=	include/
M_DIR	=	srcs/mains/
BIN_DIR	=	temp/
O_DIR_FT	=	temp/obj/ft/
O_DIR_STD	=	temp/obj/std/
O_DIR_EFT	=	temp/obj/e_ft/
O_DIR_ESTD	=	temp/obj/e_std/


# COMPILE
CXX		=	g++ -std=c++98
CFLAGSXX	=	-Wall -Wextra -Werror -Iinclude/ -g3
DEPEND	=	include/vector.hpp		\
			include/map.hpp			\
			include/enable_if.hpp	\
			include/node.hpp		\
			include/pair.hpp		\
			include/utils.hpp		\
			include/random_access_iterator.hpp	\
			include/iterator_traits.hpp			\
			include/ReverseIterator.hpp			\
			include/color_define.hpp

# SOURCES
S_FILES		=	main_map.cpp
SRCS_STD	=	main_map.cpp
S_ECOLE_STD =	main_ecole.cpp
S_ECOLE		=	main_ecole.cpp


SRCS	=	$(addprefix $(S_DIR), $(S_FILES))

#OBJS
OBJECTS		=	$(S_FILES:.cpp=.opp)
OBJ_ECOLE	=	$(S_ECOLE:.cpp=.opp)
OBJS		=	$(addprefix $(O_DIR_FT), $(OBJECTS))
OBJS_STD	=	$(addprefix $(O_DIR_STD), $(OBJECTS))
O_ECOLE_FT	=	$(addprefix $(O_DIR_EFT), $(OBJ_ECOLE))
O_ECOLE_STD	=	$(addprefix $(O_DIR_ESTD), $(OBJ_ECOLE))

all			:
				@echo "Building $(NAME_FT):"
				@make --no-print-directory $(NAME_FT)
				@make --no-print-directory $(NAME_STD)


$(NAME_FT)		:	$(OBJS)
				@echo "Linking $(NAME_FT)..."
				@$(CXX) $(CFLAGSXX) $^ -o $@
				@echo "$(NAME_FT) built successfully!"

$(OBJS)		:	$(O_DIR_FT)%.opp: $(S_DIR)%.cpp $(DEPEND)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CXX) $(CFLAGSXX) -c $< -o $@


$(NAME_STD)		:	$(OBJS_STD)
				@echo "Linking $(NAME_STD)..."
				@$(CXX) $(CFLAGSXX) $^ -o $@
				@echo "$(NAME_STD) built successfully!"

$(OBJS_STD)	:	$(O_DIR_STD)%.opp: $(S_DIR)%.cpp
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CXX) $(CFLAGSXX) -c $< -D FT=1 -o $@

ecole		:
				@echo "Building TEST_ECOLE:"
				@make --no-print-directory $(ECOLE_FT)
				@make --no-print-directory $(ECOLE_STD)

$(ECOLE_FT)		:	$(O_ECOLE_FT)
				@echo "Linking $(ECOLE_FT)..."
				@$(CXX) $(CFLAGSXX) $^ -o $@
				@echo "$(ECOLE_FT) built successfully!"

$(O_ECOLE_FT)	:	$(O_DIR_EFT)%.opp: $(S_DIR)%.cpp $(DEPEND)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CXX) $(CFLAGSXX) -c $< -o $@

$(ECOLE_STD)		:	$(O_ECOLE_STD)
				@echo "Linking $(ECOLE_STD)..."
				@$(CXX) $(CFLAGSXX) $^ -o $@
				@echo "$(ECOLE_STD) built successfully!"

$(O_ECOLE_STD)	:	$(O_DIR_ESTD)%.opp: $(S_DIR)%.cpp
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CXX) $(CFLAGSXX) -c $< -D STD=1 -o $@

clean:
		rm -rf $(BIN_DIR)

fclean: clean
		rm -rf $(NAME_FT)
		rm -rf $(NAME_STD)
		rm -rf $(ECOLE_FT)
		rm -rf $(ECOLE_STD)

# quick_test:
# 		clang++ -Werror -Wextra -Werror -std=c++98 quick_main_test.cpp -o quick_test


re: fclean all

.PHONY:		all, clean, fclean, re
