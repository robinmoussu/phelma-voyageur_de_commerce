#
#  Voyageur de commerce
#  Copyright (C) 2014 Robin Moussu - Jingbo Su
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.


#DIRSDL=/users/prog1a/C/librairie/2011
#DIRSDL=/home/robin_arch/cour/1ere_annee_phelma/info/sdl_phelma/

LDFLAGS = -fdiagnostics-color=auto -lm -ggdb

OPTION = graphe11.txt
#OPTION = graphe12.txt
#OPTION = graphe13.txt
#OPTION = graphe14.txt
#OPTION = berlin52.txt
#OPTION = djibouti38.txt
#OPTION = kroA100.txt
#OPTION = Quatar194.txt

#########################################################

install: release

#À n’utiliser que sur les versions récentes de gcc : -fdiagnostics-color=auto 
debug:   CFLAGS =-Wextra -Wall -ggdb -DDEBUG
debug:   voyageur

#À n’utiliser que sur les versions récentes de gcc : -fdiagnostics-color=auto 
release: CFLAGS =-O2
release: voyageur

run:	 release
	./voyageur ${OPTION}

clean:
	rm -f voyageur *.o

#########################################################

voyageur: fourmi.o memory.o graph.o data.o main.o
	gcc -o $@  $^ $(LDFLAGS)

%.o:%.c
	gcc -c $(CFLAGS) $<

