# learning_entities_nn_ga

In this project simple entities are competing to collect as much food as possible.

**Entities :**
They are simple circles. They point in a direction, they got a field of view. The FOV is symbolized by 2 lines : red if it sees nothing, green otherwise.
They are all controlled by their own neural network. There is one entrie: a float from the fov, and 2 outputs: to go forward and to rotate.

**Food :** 
They are little points and are worth 1 point when eaten by an entity.

**Genetic algorithm :**
The neural networks of the entities evolve thanks to a genetic algorithm, kinda using a NEAT approach.
