#!/bin/bash

if [ $# -ne 1 ]; then
	echo "usage: $0 level"
	exit 1
fi
level=$1
if [ $level -lt 4 ]; then
	echo "* Only levels 4-6 implemented."
	exit 1
fi

CHESS_PROG="../bin/exe"
LOG="test.log"

leg_games="${level}-leg-*"
ill_games="${level}-ill-*"

for g in $leg_games $ill_games
do
	>&2 echo "* Testing ========== $g "
	grep -v "#" $g | $CHESS_PROG > $LOG
	# test du exit code
	if [ $? -ne 0 ]; then
		  echo "* [test error] $CHESS_PROG ended in error for game $g (around move $?)"
	fi
done

