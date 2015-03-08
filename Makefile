NAME        = tp2
SRC_DIR     = src
SRC         = $(SRC_DIR)/main.cpp 						\
							$(SRC_DIR)/AccountChild.cpp			\
							$(SRC_DIR)/Account.cpp					\
							$(SRC_DIR)/AccountFactory.cpp		\
							$(SRC_DIR)/AccountNormal.cpp		\
							$(SRC_DIR)/AccountOld.cpp				\
							$(SRC_DIR)/Date.cpp							\
							$(SRC_DIR)/God.cpp							\
							$(SRC_DIR)/Id.cpp								\
							$(SRC_DIR)/IdGenerator.cpp			\
							$(SRC_DIR)/ListAccounts.cpp			\
							$(SRC_DIR)/Transaction.cpp			\
							$(SRC_DIR)/User.cpp
INCLUDE_DIR = include
OBJ         = $(SRC:.cpp=.o)
CXX         = g++
CXXFLAGS    = -W -Wall -Wextra -std=c++11 -I $(INCLUDE_DIR) -g -ggdb
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
