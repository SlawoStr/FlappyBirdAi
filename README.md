# FlappyBirdAI

Using  genetic algorithm and neural network to teach birds how to fly. Neural network take 3 inputs. Bird velocity,distance to next gate, difference between bird height and empty space of next gate. Output consist of one neuron. If output value is greater than 0.5 bird will fly. Genetic algorithm is written in python and use keras deep neural network to make predictions. Rest is made in c++. Prediction and mutation are made by calling python functions from c++ code.  

Simulation Settings:  
- POPULATION_SIZE - number of birds in generation
- SPAWN_RATIO - How many frames till next gate will spawn

Gate Settings:
- FREE_SPACE - How wide is opening in gate for birds to fly in.
- MOVING_SPEED - How fast gate is moving toward bird
- PIPE_WIDTH - Width of the gate
- UPPER_BOUND - Max height for free space
- LOWER_BOUND - Min height for free space

![Bird](https://github.com/SlawekSt/FlappyBirdAI/blob/main/Bird.PNG)
