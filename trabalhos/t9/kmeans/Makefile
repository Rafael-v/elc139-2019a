FLAGS= -O3 -std=c++11

RM=rm -f

EXEC=kmeans

all: $(EXEC)

$(EXEC):
        nvcc $(FLAGS) $(EXEC).cu -o $(EXEC)

clean:
        $(RM) $(EXEC).o $(EXEC)
