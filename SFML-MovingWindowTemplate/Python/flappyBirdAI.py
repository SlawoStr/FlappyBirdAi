from keras.models import Sequential
from keras.layers import Dense
import numpy as np
import random
import tensorflow as tf
import pathlib


def createModel():
    model = Sequential()
    model.add(
        Dense(6, input_dim=3, kernel_initializer='he_uniform', activation='relu', use_bias=False))
    model.add(Dense(1, activation='sigmoid', kernel_initializer='he_uniform', use_bias=False))
    model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])

    return model


class GeneticAlgorithm:

    def __init__(self):
        self.totalModels = 50
        self.current_pool = []
        physical_devices = tf.config.list_physical_devices('GPU')
        tf.config.experimental.set_memory_growth(physical_devices[0], True)

    def setNumberOfModels(self, numberOfModels):
        self.totalModels = numberOfModels

    def buildModel(self):
        for i in range(self.totalModels):
            model = createModel()
            self.current_pool.append(model)

    def saveModels(self):
        for i in range(self.totalModels):
            self.current_pool[i].save_weights("SavedModels/model_new" + str(i) + ".keras")

    def loadModels(self):
        for i in range(self.totalModels):
            self.current_pool[i].load_weights("SavedModels/model_new" + str(i) + ".keras")

    def predictMove(self, modelNumber, distanceH, distanceW, velocity):
        input_values = [float(distanceH), float(distanceW), float(velocity)]
        neural_input = np.atleast_2d(input_values)
        output_prob = self.current_pool[modelNumber](neural_input)
        result = np.array(output_prob)
        if result[0] < 0.5:
            return 0
        else:
            return 1

    def modifyPopulation(self, parent1, parent2):
        new_weights = []
        for i in range(0, self.totalModels // 2):
            if random.uniform(0, 1) < 0.8:
                cross_over_weights = self.modelCrossover(parent1, parent2)
                new_weights.append(self.mutatePopulation(cross_over_weights[0]))
                new_weights.append(self.mutatePopulation(cross_over_weights[1]))
            else:
                new_weights.append(self.mutatePopulation(self.current_pool[parent1].get_weights()))
                new_weights.append(self.mutatePopulation(self.current_pool[parent2].get_weights()))
        counter = 0
        for i in range(0, self.totalModels):
            if i == parent1 or i == parent2:
                continue
            self.current_pool[i].set_weights(new_weights[counter])
            counter = counter + 1

    def modelCrossover(self, parent1, parent2):
        weight1 = self.current_pool[parent1].get_weights()
        weight2 = self.current_pool[parent2].get_weights()

        weights_list1 = []
        weights_list2 = []
        for i in range(0, len(weight1)):
            for j in range(0, len(weight1[i])):
                weights_list1.append(weight1[i][j])
                weights_list2.append(weight2[i][j])
        value = random.randint(0, len(weights_list1))
        new_weight1 = weight1.copy()
        new_weight2 = weight2.copy()

        counter = 0
        for i in range(0, len(weight1)):
            for j in range(0, len(weight1[i])):
                if counter < value:
                    new_weight1[i][j] = weights_list2[counter]
                    new_weight2[i][j] = weights_list1[counter]
                    counter = counter + 1

        return np.asarray([new_weight1, new_weight2])

    @staticmethod
    def mutatePopulation(weights):
        weights_list = []
        for i in range(0, len(weights)):
            for j in range(0, len(weights[i])):
                weights_list.append(weights[i][j])
        for i in range(0, len(weights_list)):
            value = random.uniform(0, 1)
            if value < 0.1:
                value = random.uniform(0, 1)
                if value < 0.05:
                    value2 = random.uniform(-1, 1)
                    weights_list[i] = value2
                else:
                    value2 = random.uniform(-.5, .5)
                    weights_list[i] += value2
        counter = 0
        for i in range(0, len(weights)):
            for j in range(0, len(weights[i])):
                weights[i][j] = weights_list[counter]
                counter = counter + 1

        return weights
