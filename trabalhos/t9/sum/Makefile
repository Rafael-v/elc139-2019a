FLAGS=-O3
RM=rm -f
EXEC=sum
MPICC=mpicc

all: $(EXEC)

$(EXEC):
	$(MPICC) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(MPICC) $(FLAGS) $(EXEC).o -o $(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
