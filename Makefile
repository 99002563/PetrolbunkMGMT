PROJECT_NAME = PETROLBUNK
BUILD = build

SOURCE = SRC/*.c
INCLUDE = -IINC

PROJECT_OUT =  $(BUILD)/$(PROJECT_NAME).out

$(PROJECT_NAME):all

.PHONY: run clean object all

all:$(SRC) $(INC) $(BUILD)
		gcc -Wall -g $(SOURCE) $(INCLUDE) -o $(PROJECT_OUT) -Xlinker -zmuldefs -lpthread

object:$(SRC) $(BUILD)
		gcc -Wall -g -c $(SOURCE) $(INCLUDE) 
		
run:$(PROJECT_NAME) $(BUILD)
		./$(PROJECT_OUT)

clean:$(PROJECT_NAME)
		rm -rf $(BUILD)

$(BUILD):
		mkdir build
	