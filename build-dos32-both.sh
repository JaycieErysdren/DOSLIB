## ========================================================
##
## FILE:			/build-dos32-both.sh
##
## AUTHORS:			Jaycie Ewald
##
## PROJECT:			DOSLIB
##
## LICENSE:			ACSL 1.4
##
## DESCRIPTION:		Linux compile script.
##
## LAST EDITED:		November 4th, 2022
##
## ========================================================

#!/bin/bash

source ./build-dos32-watcom.sh
cd ..

source ./build-dos32-djgpp.sh
cd ..