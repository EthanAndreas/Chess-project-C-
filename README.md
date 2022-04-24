# Chess-Project

The project has an automatic generation of documentation (doxygen), a compilation with
the flags "-O3 -pipe -Wall -Werror -Wextra -g", and tests verifying all the expected functionalities.

## Language

C++

## Presentation

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
Test on pawn's promotion                                                                                
Test on king against king situation leading to impossible checkmate                                     
Test on display (canonical position and number of destroyed pieces)                                     
                                                                                                        
* Comment :                                                                                             
The tests show the level of requirement reached.                                                        
Only the functionality on the 3 repeated positions has not been made.                                   
The difficulties encountered were mainly the organization of methods, inheritance and also on the best  
way to implement "stalemate" and "checkmate" as optimally as possible.                                  
The executable is called "./bin/exe", the name has been modified in the directory and the script        
"test-level".                                                                                           
The stalemate situation is complete with the consideration of the 50 stroke in a row without take and   
pawn movement and the lack of pieces to do a checkmate.                                                 

## Github link

<https://github.com/EthanAndreas/Chess-project-C>
