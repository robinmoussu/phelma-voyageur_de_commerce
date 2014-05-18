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

CFLAGS= -c -Wall -fdiagnostics-color=auto -ggdb
CFLAGS_NO_DEBUG= -c -Wall -fdiagnostics-color=auto -O2
LDFLAGS= -fdiagnostics-color=auto -lm -ggdb
CIBLE=voyageur
OPTION=graphe11.txt

cible : $(CIBLE)

run : ${CIBLE}
	./${CIBLE} $(OPTION)

all : voyageur

voyageur: fourmi.c memory.c graph.c data.c main.c
	gcc -o $@  $^  $(LDFLAGS)

%.o:%.c
	gcc $(CFLAGS) $< -o $@

clean:
	rm voyageur


