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

The last main component that is needed represents the boats. Boats can have differing lengths and names and this all needs to be tracked. 
Boats also need to know whether they have been sunk or whether they are still floating. This property is especially important in the 
salvo game where this information is used to calculate how many shots a player should receive. The largest challenge with the boats is 
ensuring that the program always modifies the same instance of that boat. There should at most be 2 instances of each boat (one for each 
player) during a game. Every other reference to a boat should be a pointer to one of these instances.

## UML Diagram


a. Summary and review of the problem, overall proposed solution.
b. UML style diagram illustrating initial overall solution (linked to 1a)
c. Initial working plan, overall approach, development strategy and approach to quality (linked to 1a, 1b).
d. Analysis and decomposition of the overall problem into key ‘epic’ style tasks (linked to 1b, 1c).
e. Initial object-oriented design ideas and plan of phased breakdown into smaller tasks (linked to 1d).

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
