# ChessGame
[![version](https://img.shields.io/badge/version-0.0.1-blue.svg)](https://github.com/EthanAndreas/ChessGame)
[![compiler](https://img.shields.io/badge/compiler-g++-red.svg)](https://github.com/EthanAndreas/ChessGame/blob/main/Makefile)
[![license](https://img.shields.io/badge/license-GPL_3.0-yellow.svg)](https://github.com/EthanAndreas/ChessGame/blob/main/LICENSE)
[![author](https://img.shields.io/badge/author-EthanAndreas-blue)](https://github.com/EthanAndreas)

## Table of Contents
1. [Command](#command)
2. [How to play](#how-to-play)
3. [Documentation](#documentation)
4. [Tests](#tests)

## Command
- Compilation :
```bash
make
```
- Game start :
```bash
./bin/exe
 ```
 - Game end (in the game):
 ```bash
/quit
 ```

## How to play
- A stroke is defined by :
```bash
letter-number-letter-number
```
- For castling the format is :
```bash
o-o / O-O / 0-0 (kingside castling)
o-o-o / O-O-O / 0-0-0 (queenside castling)
```

## Documentation
```bash
make docs
```

## Tests
- Realized on :
|-------------------------------------------------------------|
| "/quit" command                                             |
| check situation                                             |
| checkmate                                                   |
| staleamte                                                   |
| kingside castling                                           |
| queenside castling                                          |
| pawn's take                                                 |
| 50 stroke without a take in a row                           |
| pawn's promotion                                            |
| king against king situation leading to impossible checkmate |
| display (canonical position and number of destroyed pieces) |
- Launch
```bash
./test.sh 
 ```
