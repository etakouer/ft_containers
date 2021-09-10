UNAME_S		=	$(shell uname -s)

C_G			=	"\033[1;96m"
C_W			=	"\033[0;39m"

NAME		=	containers

SRCS		=	tests/main_$(c).cpp

DEFINE		=	-D $(UNAME_S)

CXXFLAGS	=	-std=c++98 -g -Wall -Wextra -Werror -I includes 

CXX			=	clang++

OBJS		=	$(SRCS:.cpp=.o)

EXEC		=	echo $(C_G)"Execution" $(NAME) $(C_W) \
				&& ./$(NAME) $(seed) \
				&& echo $(C_G)"----"$(C_W)

COMP		=	echo $(C_G)"Compilation" $(NAME) $(C_W)


ifeq ($(UNAME_S),Linux)
CXX			=	g++
endif

ifdef FT
DEFINE		+=  -D FT
NAME		=	containers_ft
endif

ifndef seed
seed		= 123456789	
endif

ifdef SAN
CXXFLAGS	+=	-fsanitize=address
endif

ifdef DEBUG
DEFINE		+=	-D DEBUG
endif

CXXFLAGS	+=	$(DEFINE)

all			:	clear $(NAME)

ft			:	
				@make FT=1
ftsan		:	
				@make FT=1 SAN=1
ftvan		:	
				@make FT=1
				@valgrind ./containers_ft
san			:	
				@make SAN=1

diff		:
				@make ; make ft
				@echo $(C_G)"Diff"$(C_W)
				@time ./containers $(seed) > log
				@time ./containers_ft $(seed) > log_ft
				@diff log log_ft ; rm -f log log_ft

$(NAME)		:	$(OBJS)
				$(CXX) $(CXXFLAGS) -o $@ $^ 
				@$(EXEC)

clean		:
				rm -f tests/*.o

clear		:	clean
				rm -f $(NAME)

fclean		:	clean
				rm -rf containers_ft containers *.dSYM a.out

re			:	clear all

.PHONY: all clean fclean re
