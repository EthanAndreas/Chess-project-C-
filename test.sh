#!/bin/bash

# make clean
# make

# Test 0 : Test on end of game during 2 seconds
rm example/output.txt
timeout 1  cat example/quit.txt | ./bin/exe >> example/output.txt
if [ `grep -c "End of game !" example/output.txt` == 1 ]
then
    echo "Test 0 (/quit): OK"
else
    echo "Test 0 (/quit): ERROR"
fi

# # Test 1 : Test on check situation
rm example/output.txt
timeout 1 cat example/check.txt | ./bin/exe >> example/output.txt
if [ `grep -c "Check's situation" example/output.txt` == 1 ]
then
    echo "Test 1 (check): OK"
else
    echo "Test 1 (check): ERROR"
fi

# # Test 2 : Test on checkmate 
rm example/output.txt
timeout 1 cat example/checkmate.txt | ./bin/exe >> example/output.txt
if [ `grep -c "Checkmate !" example/output.txt` == 1 ]
then
    echo "Test 2 (checkmate): OK"
else
    echo "Test 2 (checkmate): ERROR"
fi

# # Test 3 : Test on stalemate 
# rm example/output.txt
# timeout 1 cat example/stalemate.txt | ./bin/exe >> example/output.txt
# if [ `grep -c "Stalemate !" example/output.txt` == 1 ]
# then
#     echo "Test 3 (stalemate): OK"
# else
#     echo "Test 3 (stalemate): ERROR"
# fi

# # Test 4 : Test on queeside and kingside castling 
rm example/output.txt
timeout 1 cat example/kingside-castling.txt | ./bin/exe >> example/output.txt
if [ `grep -c "Castling done !" example/output.txt` == 2 ]
then
    echo "Test 4 (kingside castling): OK"
else
    echo "Test 4 (kingside castling): ERROR"
fi
rm example/output.txt
timeout 1 cat example/queenside-castling.txt | ./bin/exe >> example/output.txt
if [ `grep -c "Castling done !" example/output.txt` == 2 ]
then
    echo "Test 5 (queenside castling): OK"
else
    echo "Test 5 (queenside castling): ERROR"
fi
