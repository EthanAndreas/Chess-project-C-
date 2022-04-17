#!/bin/bash

# make clean
# make

# Test 0 : Test on end of game during 2 seconds
rm example/output.txt
timeout 1  cat example/quit.txt | ./bin/exe >> example/output.txt
if [ `grep -c "End of game !" example/output.txt` == 1 ]
then
    echo "Test 0 : OK"
else
    echo "Test 0 : ERROR"
fi

# # Test 1 : Test on check situation
rm example/output.txt
timeout 1 cat example/check.txt | ./bin/exe >> example/output.txt
if [ `grep -c "Check's situation" example/output.txt` == 1 ]
then
    echo "Test 1 : OK"
else
    echo "Test 1 : ERROR"
fi

# # Test 2 : Test on checkmate 
rm example/output.txt
timeout 1 cat example/checkmate.txt | ./bin/exe >> example/output.txt
if [ `grep -c "Checkmate !" example/output.txt` == 1 ]
then
    echo "Test 2 : OK"
else
    echo "Test 2 : ERROR"
fi

# # Test 3 : Test on stalemate 
rm example/output.txt
timeout 1 cat example/stalemate.txt | ./bin/exe >> example/output.txt
if [ `grep -c "Stalemate !" example/output.txt` == 1 ]
then
    echo "Test 3 : OK"
else
    echo "Test 3 : ERROR"
fi

# # Test 4 : Test on queeside and kingside castling 
rm example/output.txt
timeout 1 cat example/castling.txt | ./bin/exe >> example/output.txt
if [ `grep -c "Castling done !" example/output.txt` == 1 ]
then
    echo "Test 4 : OK"
else
    echo "Test 4 : ERROR"
fi
