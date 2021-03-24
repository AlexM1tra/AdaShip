# AdaShip
AdaShip AP-2 assignment

# Challenge Outline
The proposed problem was to create a simple battleships style game which became increasingly convoluted with extra requirements. 
These requirements include but aren't limited to extra game modes, fixed output and gameplay formats and restricted configuration 
logic. At the core of the problem, the game itself should have been the most difficult part of the problem. The solution should 
provide a platform for a person to place ships and attack their opponent's ships in a turn based paradigm. The game can inherently 
be broken down into its fundamental parts which can, in turn, be examined independently. These parts, from here on called 
components, form the basic file/class structure of the final solution and describe how the different classes may work together to 
achieve a working solution. 

The first part of any game like this is the game's board. Battleships usually comprises of two 10x10 grids with lettered columns 
and numbered rows. Each player has their own board and then they have an obscured view of their opponent's board whereby they are 
unable to see each other's ships until they have been hit. The board also needs to have a working and tightly integrated coordinate 
system so that squares can be easily queried and manipulated. This should be a separate but loosely coupled component as coordinates 
should have the ability to be used outside of the board itself.

The next object to consider is the player. Battleships is a 2 player game and so whether the players are computers or human, there must 
be 2 players for each game. Each player needs their own board and should be given a view of their turn (a turn view). A player's turn 
view should consist of their opponent's board above their own. The coordinate system should be printed on the top and left of the board 
so that the player can easily identify where they would like to attack. When the turn switches to the other player, these two boards are 
effectively swapped as the current player's attacking board is always the previous player's board. 

Briefly mentioned earlier was the concept of a game. We can extract the idea of a game into its own component. A game component should 
keep track of which player's turn it currently is as well as checking whether either player has won the game. It will also be the main 
method of communication between the two opposing players. This adds a level of protection between the two player components. The 
specification states that an excellent solution should support multiple game types including the salvo game and the mine game. A game 
component could house and differentiate the logic between these game variations.

### Context (aside):
The salvo game is a modification of the original game where each player can take N shots where N is the number of unsunk ships the 
player has left.
The mine game is more similar to the original game but adds 5 mines to the board which when struck, attack all adjacent squares 
including recursively attacking neighbouring mines.

With one of the project requirements being a need to read configuration settings from an external file called 'adaship_config.ini', it 
would be sensible to enclose this logic in its own component thus relieving any other component from bearing the burden of reading and 
writing to the settings in addition to its primary function. In my final solution, I called this file SettingsIO as it provides input 
and output to and from the configuration file.

The last main component that is needed represents the boats. Boats can have differing lengths and names and this all needs to be tracked. 
Boats also need to know whether they have been sunk or whether they are still floating. This property is especially important in the 
salvo game where this information is used to calculate how many shots a player should receive. The largest challenge with the boats is 
ensuring that the program always modifies the same instance of that boat. There should at most be 2 instances of each boat (one for each 
player) during a game. Every other reference to a boat should be a pointer to one of these instances.

## UML Diagram
![UML Diagram](./AdaShipUML.svg)

While this is a very basic diagram, it illustrates the rough picture of how the fundamental components would work together. In the final 
solution, things like board squares and the results of players' turns were extracted into their own small components for convenience.

## Approach
When endeavouring to create such a large solution like this, it is vital to at least partially plan the project's structure. It is good 
practice and standard in C++ development to split classes into header and source files. The class itself should be located in the header 
file with forward declarations for all of the methods. Then, in the source file, definitions should be given for each of these methods. 
This format keeps your code clean and allows somebody to see the structured outline of your classes by just looking at the header files.

Another good practice is to use header guards on your header files. A header guard checks if a unique value isn't defined and if it isn't, 
it defines it. Your class' code should follow this definition and the header file should end with an endif. The result of this is as 
follows: whenever the compiler attempts to load the header file, if it has already been loaded, the check on the unique value fails as it 
has already been defined and none of the code inside the header file is loaded. This prevents redefinitions which can lead to compiler 
errors.

It's also good to ensure that your code is consistent. This is usually impossible to do perfectly but deciding and clarifying things like 
what indentation size to use before starting the project can help make the final code much more readable.

### Epics
1. Create board and coordinate system which work together.
    - The board should have a grid which can be stored as a matrix or two dimensional vector for ease of use.
    - The board should support being able get and set the status of a board square using a coordinate for reference.
    - Coordinates should be instantiable with either a column and row value or a string value (eg. A71).
    - The board should provide views of the grid for both the owner and the opponent.
    - The board should keep track of the boats it contains: how many there are remaining and where they are.
2. Create player component which has a board and a move method for taking a turn automatically.
    - The board can be instantiated when the player is instantiated.
    - The move method can return a valid coordinate denoting where the player would like to attack on their opponent's board.
    - The move method can choose a coordinate randomly for now. 
3. Create game component which has two players and can organise the turn taking logic between the two players.
    - The players should be initialised when the game component is instantiated.
    - A while loop can be used with the exit condition of one of the players having no remaining ships.
    - Within the while loop, a boolean value can be negated to switch between each player's turn.
    - The current player's move method should be called and the result should be passed to their opponent's board.
        - May need to implement attack logic in the board component.
4. Add boat placement logic to the player component.
    - Boat placement can be done randomly with valid configurations.
    - Need to write algorithm for getting valid placements which don't go outside the bounds of the board and don't overlap with an 
      existing ship.
    - Once this is done, a rudimentary game should be able to be played between two AI players.
5. Add logic to interface with the configuration file.
    - Before this, can be mocked with a const value.
    - Add a function to read the board dimensions and list of boats from the file.
    - Add a function to add new boats to the file.
    - Add a function to remove boats from the file.
    - Add a function to update the board dimensions.
    - These functions can be made static so that the SettingsIO component does not need to be instantiated.
6. Add logic to differentiate between human and AI players.
    - Add an interface which allows a user to input a simple coordinate eg. A4 within the move method.
    - Add an interface which allows a user to place their boats.
        - This will require a method which shows the user placement options they can choose from. (Requires 4.2)
7. Add a menu.
    - This can be done in the main.cpp file. Should be simple to use. Using numerical options is easiest.
    - Should be able to instantiate a game from the menu and start it.
8. Add UI to allow interfacing between the written methods and the user
    - Show valuable information to the user like which boat is currently being placed.
    - Provide the user with options like choose another boat placement, reset all boats etc. (requirements in spec).
    - Give the user the choice to use the auto place and auto fire options.
9. Add validation to prevent erroneous data being added
    - Ensure that only valid inputs are being processed. Don't allow coordinate inputs which exceed the boundaries of the board.
    - Add fixed option validation to all numerical menus.
10. Add extensions (eg. salvo game mode and mine game mode)
    - Modify and extend the game component to add an extra for loop in salvo mode which runs for every ship the current player has 
      remaining.
    - Modify the board and game components to allow mines to be added at the beginning of the game and processed throughout the game.

# Development
a. Adoption and use of ‘good’ standards (linked to 1a, 1b, 1c).
b. Phase 1 development: tasks, code review and changes (linked to 1d,1e).
c. ..repeated for each development phase.
d. Phase n development: tasks, code review and changes (linked to 1d,1e).
e. Ensuring quality through testing and resolving bugs (linked to 1a, 1b, 2a, 2b..2c).
f. Reflection on key design challenges, innovations and how I solved them (with examples).

# Evaluation (academic standard: distinction level detail: section required for distinction)
a. Analysis with embedded examples of key code refactoring, reuse, smells.
b. Implementation and effective use of ‘advanced’ programming principles (with examples).
c. Features showcase and embedded innovations (with examples) - opportunity to ‘highlight’ best bits.
d. Improved targeting algorithm – research, design, implementation and tested confirmation (with
examples).
e. Reflective review, opportunities to improve and continued professional development.
