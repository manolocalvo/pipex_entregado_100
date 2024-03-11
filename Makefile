
DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

# variable nombre del programa
# (en otros casos era una librería .a y se compilaba con AR)
NAME = pipex

# archivos a compilar y su ruta
SRC_DIR = 		src
SRC_FILES =		ft_childs.c \
				ft_freerror.c \
				ft_parsing_split.c \
				ft_parsing.c \
				pipex.c
SRC = 			$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_SRC		=	$(SRC:.c=.o)

UTILS_DIR = 	utils
UTILS_FILES =	ft_split.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_strncmp.c
UTILS = 		$(addprefix $(UTILS_DIR)/, $(UTILS_FILES))
OBJ_UTILS	=	$(UTILS:.c=.o)

HEADER_DIR	=	includes
HEADER_SRCS	=	pipex.h \
HEADER		=	$(addprefix $(HEADER_DIR)/, $(HEADER_SRCS))

# variable que declara los archivos objeto
# los objeto van a tener el mismo nombre que los .c pero acabados en .o
# OBJECTS_DIR = objects
# OBJECTS = $(SOURCES:$(SOURCES_DIR)/%.c=$(OBJECTS_DIR)/%.o)

# indicamos nuestro compilador
CC = gcc

# declaramos las flags
# -Wall : tener en cuenta todos los warnings de construcción
# -Werror : tomar todos los warnings como error y parar la compilación
# -Wextra : aumenta aún más -Wall
CFLAGS = -Wall -Werror -Wextra -g
# LDFLAGS = -L./memory-leaks-master -memory_leaks.a


# declaramos las variables para el comando clean
# rm : remove, comando normal de terminal
# -f : force, que lo haga obligatoriamente
# -r : para eliminar directorios
RM = rm -f

# declaramos las variables para la librería estática ó archivo
# ar : comando para trabajar con archivos
# r : crea o sobreescribe el archivo
# c : crea el archivo
# s : escribe un indice de tipo objeto en el archivo (acelera el 
#		proceso de link a la librería)
# AR = ar rcs



# pattern rules: 
# %.o: %.c -> que .o se compile desde .c
# $< source file where the rule applies
# $@ target file where the rule applies
# %.o: %.c Makefile $(HEADER)
# %.o: %.c $(HEADER) // no funciona
%.o: %.c Makefile
	@echo "${YELLOW} • $(CYAN)Compiling ${RED}→ $(CYAN)$< ${GREEN}✓$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@
# %.o: %.c Makefile
# 	@echo "${YELLOW} • $(CYAN)Compiling ${RED}→ $(CYAN)$< ${GREEN}✓$(DEF_COLOR)"
# 	@$(CC) $(CFLAGS) -c $< -o $@

# compilamos la librería
# $(NAME) : $(OBJECTS)
# 			@$(AR) $(NAME) $(OBJECTS) 
# 			@echo "\n${YELLOW} ✓ $(GREEN)Created $(NAME)$(DEF_COLOR)\n"
# $(NAME):	$(OBJ_SRC) $(OBJ_UTILS)
# 			@make -s -C memory-leaks-master 
# 			@$(CC) $(OBJ_SRC) $(OBJ_UTILS) memory-leaks-master/memory_leaks.a -L./memory-leaks-master/include -o $(NAME)
# 			@echo "\n${YELLOW} ► $(YELLOW)Created $(NAME)!!$(DEF_COLOR)\n"
$(NAME):	$(OBJ_SRC) $(OBJ_UTILS)
			@$(CC) $(OBJ_SRC) $(OBJ_UTILS) -o $(NAME)
			@echo "\n${YELLOW} ► $(YELLOW)Created $(NAME)!!$(DEF_COLOR)\n"

# función principal 
all: 	$(NAME) 
#		make -C -f ./memory-leaks-master/
#		make -C -f ./memory-leaks-master/Makefile

# borrado de objetos
clean:
# 	@make clean -s -C memory-leaks-master
	@$(RM) $(OBJ_SRC) 
	@$(RM) $(OBJ_UTILS)
	@echo "\n${YELLOW} ¤ $(GREEN)All objects cleaned successfully ${GREEN}✓$(DEF_COLOR)\n"

#borrado de objetos y del ejecutable
fclean: clean	
# 	@make fclean -s -C memory-leaks-master
	@$(RM) $(NAME)
	@echo "${YELLOW} ¤ $(GREEN)All executables cleaned successfully ${GREEN}✓$(DEF_COLOR)\n"

# reinicio de todo, como si se ejecutara por primera vez
re: fclean all 

# indica que esto no son nombres sino reglas 
.PHONY: all clean fclean re 