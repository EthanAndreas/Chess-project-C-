# Chess-Project

The project has an automatic generation of documentation (doxygen), a compilation with                  
the flags "-O3 -pipe -Wall -Werror -Wextra -g", and tests verifying all the expected functionalities.   

## Language

C++

## Presentation

<<<<<<< HEAD
* Project's compilation :                                                                               \n
make clean                                                                                              \n
make                                                                                                    \n
make docs (to create the documentation)                                                                 \n
                                                                                                        \n
* Project's launch :                                                                                    \n
./bin/exe                                                                                               \n
./test.sh (to test the features)                                                                        \n
                                                                                                        \n
* Information about the game :                                                                          \n
The chessboard is displayed every stroke                                                                \n
Each stroke is chosen by the format :                                                                   \n
letter-number-letter-number (Ex : a2a3)                                                                 \n
For castling the format is :                                                                            \n
o-o / O-O / 0-0 (kingside castling)                                                                     \n
o-o-o / O-O-O / 0-0-0 (queenside castling)                                                              \n
                                                                                                        \n
* Information about the test :                                                                          \n
Test on "/quit" command                                                                                 \n
Test on check situation                                                                                 \n
Test on checkmate                                                                                       \n
Test on staleamte                                                                                       \n
Test on kingside castling                                                                               \n
Test on queenside castling                                                                              \n
Test on pawn's take                                                                                     \n
Test on 50 stroke without a take in a row                                                               \n
                                                                                                        \n
* Comment :                                                                                             \n
The tests show the level of requirement reached.                                                        \n
Only the functionality on the 3 repeated positions has not been made.                                   \n
The difficulties encountered were mainly the organization of methods, inheritance and also on the best  \n
way to implement "stalemate" and "checkmate" as optimally as possible.                                  \n
The executable is called "./bin/exe", the name has been modified in the directory and the script        \n
"test-level".                                                                                           \n
The stalemate situation is complete with the consideration of the 50 stroke in a row without take and   \n
pawn movement, the 3 positions repeated and the lack of pieces to do a checkmate.                       \n
=======
* Project's compilation :                                                                               
make clean                                                                                              
make                                                                                                    
make docs (to create the documentation)                                                                 
                                                                                                        
* Project's launch :                                                                                    
./bin/exe                                                                                               
./test.sh (to test the features)                                                                        
                                                                                                        
* Information about the game :                                                                          
The chessboard is displayed every stroke                                                                
Each stroke is chosen by the format :                                                                   
letter-number-letter-number (Ex : a2a3)                                                                 
For castling the format is :                                                                            
o-o / O-O / 0-0 (kingside castling)                                                                     
o-o-o / O-O-O / 0-0-0 (queenside castling)                                                              
                                                                                                        
* Information about the test :                                                                          
Test on "/quit" command                                                                                 
Test on check situation                                                                                 
Test on checkmate                                                                                       
Test on staleamte                                                                                       
Test on kingside castling                                                                               
Test on queenside castling                                                                              
Test on pawn's take                                                                                     
Test on 50 stroke without a take in a row                                                               
                                                                                                        
* Comment :                                                                                             
The tests show the level of requirement reached.                                                        
Only the functionality on the 3 repeated positions has not been made.                                   
The difficulties encountered were mainly the organization of methods, inheritance and also on the best  
way to implement "stalemate" and "checkmate" as optimally as possible.                                  
The executable is called "./bin/exe", the name has been modified in the directory and the script        
"test-level".                                                                                           
>>>>>>> 9cec51daa8a58aaddce9ea3371ab50e22fec9347

## Github link

<https://github.com/EthanAndreas/Chess-project-C>
