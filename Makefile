GPP=g++
FLAGS=-c -pipe -O3 -g -funsafe-math-optimizations # -Wall -W
CC=$(GPP) $(FLAGS)
LK=$(GPP)
INC=-I/opt/local/include/eigen3/ -I/usr/include/eigen3/
pn=matrixDescriber

all:	$(pn)


$(pn):
	$(LK) $(INC) $(pn).cpp -o $(pn)

###############

clean:
	[ -f $(pn) ] && rm $(pn)
