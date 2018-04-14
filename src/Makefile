EXEC = commandRows
CC = gcc
OPT = -g -g3 -O3 -Wall -Wextra -pedantic -std=gnu11 -lm
SRC = commandRows.c main.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)


all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(OPT) $^ -o $@ && echo "$@ linked successfuly"


%.o: %.c
	@$(CC) -c $(OPT) $*.c -o $*.o && echo "$*.c compiled successfully"
	@$(CC) -MM $(OPT) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp


clean:
	@$(RM) *.o *.d && echo "Files *.d and *.o removed"

cleanall: clean
	@$(RM) $(EXEC) && echo "Executable files $(EXEC) removed"
