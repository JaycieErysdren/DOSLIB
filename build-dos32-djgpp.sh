## ========================================================
##
## FILE:			/build-dos32-djgpp.sh
##
## AUTHORS:			Jaycie Ewald
##
## PROJECT:			DOSLIB
##
## LICENSE:			ACSL 1.4
##
## DESCRIPTION:		Linux compile script (DJGPP).
##
## LAST EDITED:		November 4th, 2022
##
## ========================================================

#!/bin/bash

if [ ! -d cmake-build-dos32-djgpp ] 
then
	mkdir cmake-build-dos32-djgpp
fi

cd cmake-build-dos32-djgpp
cmake -D CMAKE_C_COMPILER_ID=DJGPP -D CMAKE_C_COMPILER=i586-pc-msdosdjgpp-gcc -D CMAKE_SYSTEM_NAME=DOS ..
make
