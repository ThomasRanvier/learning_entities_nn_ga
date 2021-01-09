# learning_entities_nn_ga

In this project simple entities are competing to collect as much food as possible.
This project is quite old and my machine learning skills were basically non-existent, do not pay too much attention at the code.

On the top left are the current generation number, the current movement iteration, the amount of food that the best entity has collected and the total amount of food collected by the entire population.
![learning entities](learning_entities.gif "learning entities")

**Entities:**
They are simple circles. They got a field of view in front of them that gives them the distance to the closest food they can see.
The FOV is symbolized by 2 lines : red if it detects no food, green otherwise.
Each entity is controlled by its own neural network. The NN input is the FOV returned value and the output is a two values vector, the first sets the speed of the entity and the second its rotation.

**Food:**
They are little points and reward with one point the entity that eats it.

**Genetic algorithm:**
The weights and biases of the neural networks of the entities evolves thanks to a genetic algorithm, kinda using a NEAT approach.