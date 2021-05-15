# smart-rockets

![video1](https://user-images.githubusercontent.com/42043913/118371511-38180500-b5ad-11eb-9ec1-a3ad8f239a34.gif)

Project is a simple game where a player control a rocket, try to hit a red target and avoid asteroids. But the player is an artifical inteligence which uses a neural network in order to steer rockets.

## Game Part

The game was made using SMFL library which provides fast and easy development of c++ 2d games.  

GameObject is a parent class for every object in the game and contains basic information and methods to override. There are also shape classes (like Rectangle or Circle) which extend GameObject, override method responsible for collision check and contain shape information. Thanks to that, it was simple to implement classes like Rocket. Collision system provides methods to check collision in every game object which then are added to a dynamic object list or a static object list (it demand on collision type of an object for optimalization issues) where the game is able to check collision for them per frame.

## AI Part

The aim for every rocket is to hit the red target. Every rocket have it's own neural network.

Inputs for neural network:
  - direction vector of the rocket
  - direction to target
  - distance to target
  - distances to the nearest obstacles (using raycasting)

Outputs from nerual network:
  - velocity
  - angle to rotate

AI is constantly being imporoved by genetic algorithm which was implemented in the project.
