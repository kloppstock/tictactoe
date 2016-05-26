# tictactoe
A tic tac toe engine optimized for AI implementaion. 

A class for a human player and a class for a random player all already implemented.

The software was not yet extensively tested so there my be bugs!

## Versions

The master branch contains the last stable build, whereas the develop branch contains newly implemented features which may be not working.
In the futere there will be release branches, which contain the latest completed release. 

## Build Insctructions

To build the program use `make` or `make build`. 
`make clean` and make `make rebuild` do also work.

## Own Implementations of a Player

To create an own implementation of a player you have to create a class that inherits the Player class and overwrite the `getMove()` and `setResult()` function.

## Documentation

The UML class diagram can be found in the `uml` folder.

## License

tictactoe is licensed under the terms of the GPL version 3 (located in the LICENSE file).
