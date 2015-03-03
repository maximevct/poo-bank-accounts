NAME        = tp2
SRC         = main.cpp
OBJ         = $(SRC:.cpp=.o)
CXX         = g++
CXXFLAGS    = -W -Wall -Wextra -std=c++11
RM          = rm -vf

all:      $(NAME)
$(NAME):  $(OBJ)
					$(CXX) -o $(NAME) $(OBJ)
					@echo "\033[33;01mCompilation terminée\033[00m"

clean:
					$(RM) $(OBJ)
					@echo "\033[34;01mFichiers .o effacés\033[00m"

fclean:   clean
					$(RM) $(NAME)
					@echo "\033[35;01mBinaire effacé\033[00m"

re:       fclean all
