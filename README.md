# smart-rockets

![video1](https://user-images.githubusercontent.com/42043913/118371511-38180500-b5ad-11eb-9ec1-a3ad8f239a34.gif)

Project is a simple game where player controll rocket, try to hit red target and avoid asteroids. But the player is Artifical Inteligence which use neural network to steer rockets.

## Game Part

Game was made using SMFL, which provides fast and easy development.  

GameObject is a parent class for every object in the game and contain basic information and functions to overwrite. There are also shape classes (like Rectangle or Circle) which expand GameObject, overwrite function responsible for collision check and contain shape information. With it that was simple to implement classes like Rocket. Collision system provides functions to check collision in every game object which then are added to dynamic object list or static object list (it demends on collision type of object for optimalization reasons) where game can check collision for theme per frame.

## AI Part

The aim for every rocket is to hit the red target. Every rocket have it's own neural network.

Inputs for neural network:
  - direction vector of the rocket
  - direction to target
  - distance to target
  - distances to nearest obstacles (using raycasting)

Outputs from nerual network:
  - velocity
  - angle to rotate

AI is imporoving by Genetic Algorithm, which was implemented into the project.
