#!/bin/bash

# Test 0 : Test on end of game during 2 seconds
rm example/return.txt
timeout 2  cat example/quit.txt | ./bin/exe >> example/return.txt
var = $(grep -c "End of game !" example/return.txt)

if [ $? == 1 ]
then
    echo "Test 0 : OK"
else
    echo "Test 0 : ERROR"
fi

# # Test 1 : Test on check situation
# cat example/check.txt | ./bin/exe >> example/return.txt
# var = $(grep -c "Check's situation" example/return.txt)

# # Test 2 : Test on checkmate 
# cat example/checkmate.txt | ./bin/exe >> example/return.txt
# var = $(grep -c "Checkmate !" example/return.txt)

# # Test 3 : Test on stalemate 
# cat example/stalemate.txt | ./bin/exe >> example/return.txt
# var = $(grep -c "Stalemate !" example/return.txt)

# # Test 4 : Test on queeside and kingside castling 
# cat example/castling.txt | ./bin/exe >> example/return.txt
# var = $(grep -c "Castling done !" example/return.txt)