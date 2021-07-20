import random
import math

# Shorthand:
# "pd_" as a variable prefix means "partial derivative"
# "d_" as a variable prefix means "derivative"
# "_wrt_" is shorthand for "with respect to"
# "w_ho" and "w_ih" are the index of weights from hidden to output layer neurons and input to hidden layer neurons respectively

class NeuralNetwork:
    LEARNING_RATE = 0.5
    def __init__(self, num_inputs, num_hidden, num_outputs, hidden_layer_weights = None, hidden_layer_bias = None, output_layer_weights = None, output_layer_bias = None):
    #Your Code Here
        self.num_inputs = num_inputs
        self.num_hidden = num_hidden
        self.num_outputs = num_outputs
        self.hidden_layer = NeuronLayer(num_hidden, hidden_layer_bias)
        self.output_layer = NeuronLayer(num_outputs, output_layer_bias)
        self.init_weights_from_inputs_to_hidden_layer_neurons(hidden_layer_weights)
        self.init_weights_from_hidden_layer_neurons_to_output_layer_neurons(output_layer_weights)

    def init_weights_from_inputs_to_hidden_layer_neurons(self, hidden_layer_weights):
    #Your Code Here
        if hidden_layer_weights is None:
            for n in self.hidden_layer.neurons:
                for i in range(self.num_inputs):
                    n.weights.append(random.random())
        else:
            index = 0
            for n in self.hidden_layer.neurons:
                index_next = index + self.num_inputs
                n.weights.extend(hidden_layer_weights[index:index_next])
                index = index_next

    def init_weights_from_hidden_layer_neurons_to_output_layer_neurons(self, output_layer_weights):    
    #Your Code Here
        if output_layer_weights is None:
            for n in self.output_layer.neurons:
                for i in range(self.num_hidden):
                    n.weights.append(random.random())
        else:
            index = 0
            for n in self.output_layer.neurons:
                index_next = index + self.num_hidden
                n.weights.extend(output_layer_weights[index:index_next])
                index = index_next

    def inspect(self):
        print('------')
        print('* Inputs: {}'.format(self.num_inputs))
        print('------')
        print('Hidden Layer')
        self.hidden_layer.inspect()
        print('------')
        print('* Output Layer')
        self.output_layer.inspect()
        print('------')

    def feed_forward(self, inputs):
        #Your Code Here
        hidden_layer_outputs = self.hidden_layer.feed_forward(inputs)
        return self.output_layer.feed_forward(hidden_layer_outputs)

    # Uses online learning, ie updating the weights after each training case
    def train(self, training_inputs, training_outputs):
        self.feed_forward(training_inputs)

        # 1. Output neuron deltas        
        #Your Code Here
        # ∂E/∂zⱼ       
        output_neuron_deltas = [n.calculate_pd_error_wrt_total_net_input(training_outputs[i]) for i, n in enumerate(self.output_layer.neurons)]

        # 2. Hidden neuron deltas        
        # We need to calculate the derivative of the error with respect to the output of each hidden layer neuron
        # dE/dyᵢ = Σ ∂E/∂zⱼ * ∂zⱼ/∂yᵢ = Σ ∂E/∂zⱼ * wᵢⱼ
        # ∂E/∂zᵢ = dE/dyᵢ * ∂yᵢ/∂zᵢ
        #Your Code Here
        hidden_neuron_deltas = [sum([output_neuron_deltas[j] * on.weights[i] for j, on in enumerate(self.output_layer.neurons)]) * hn.calculate_pd_total_net_input_wrt_input() for i, hn in enumerate(self.hidden_layer.neurons)]

        # 3. Update output neuron weights
        # ∂Eⱼ/∂wᵢⱼ = ∂E/∂zⱼ * ∂zⱼ/∂wᵢⱼ             
        # Δw = α * ∂Eⱼ/∂wᵢ
        #Your Code Here        
        for j, n in enumerate(self.output_layer.neurons):
            for i in range(self.num_hidden):
                n.weights[i] -= NeuralNetwork.LEARNING_RATE * output_neuron_deltas[j] * n.calculate_pd_total_net_input_wrt_weight(i)

        # 4. Update hidden neuron weights
        # ∂Eⱼ/∂wᵢ = ∂E/∂zⱼ * ∂zⱼ/∂wᵢ    
        # Δw = α * ∂Eⱼ/∂wᵢ
        #Your Code Here
        for j, n in enumerate(self.hidden_layer.neurons):
            for i in range(self.num_inputs):
                n.weights[i] -= NeuralNetwork.LEARNING_RATE * hidden_neuron_deltas[j] * n.calculate_pd_total_net_input_wrt_weight(i)

    def calculate_total_error(self, training_sets):
        #Your Code Here
        total_error = 0
        for inputs, outputs in training_sets:
            self.feed_forward(inputs)
            for i, n in enumerate(self.output_layer.neurons):
                total_error += n.calculate_error(outputs[i])
        return total_error

class NeuronLayer:
    def __init__(self, num_neurons, bias):

        # Every neuron in a layer shares the same bias
        self.bias = bias if bias else random.random()

        self.neurons = []
        for i in range(num_neurons):
            self.neurons.append(Neuron(self.bias))

    def inspect(self):
        print('Neurons:', len(self.neurons))
        for n in range(len(self.neurons)):
            print(' Neuron', n)
            for w in range(len(self.neurons[n].weights)):
                print('  Weight:', self.neurons[n].weights[w])
            print('  Bias:', self.bias)

    def feed_forward(self, inputs):
        outputs = []
        for neuron in self.neurons:
            outputs.append(neuron.calculate_output(inputs))
        return outputs

    def get_outputs(self):
        outputs = []
        for neuron in self.neurons:
            outputs.append(neuron.output)
        return outputs

class Neuron:
    def __init__(self, bias):
        self.bias = bias
        self.weights = []

    def calculate_output(self, inputs):
    #Your Code Here
        self.inputs = inputs
        self.output = self.squash(self.calculate_total_net_input())
        return self.output

    def calculate_total_net_input(self):
    #Your Code Here
        return sum(map(lambda x, y: x * y, self.weights, self.inputs)) + self.bias

    # Apply the logistic function to squash the output of the neuron
    # The result is sometimes referred to as 'net' [2] or 'net' [1]
    def squash(self, total_net_input):
    #Your Code Here
        return 1 / (1 + math.exp(-total_net_input))

    # Determine how much the neuron's total input has to change to move closer to the expected output
    #
    # Now that we have the partial derivative of the error with respect to the output (∂E/∂yⱼ) and
    # the derivative of the output with respect to the total net input (dyⱼ/dzⱼ) we can calculate
    # the partial derivative of the error with respect to the total net input.
    # This value is also known as the delta (δ) [1]
    # δ = ∂E/∂zⱼ = ∂E/∂yⱼ * dyⱼ/dzⱼ
    #
    def calculate_pd_error_wrt_total_net_input(self, target_output):
    #Your Code Here
        return self.calculate_pd_error_wrt_output(target_output) * self.calculate_pd_total_net_input_wrt_input()

    # The error for each neuron is calculated by the Mean Square Error method:
    def calculate_error(self, target_output):
    #Your Code Here
        return (self.output - target_output) ** 2 / 2

    # The partial derivate of the error with respect to actual output then is calculated by:
    # = 2 * 0.5 * (target output - actual output) ^ (2 - 1) * -1
    # = -(target output - actual output)
    #
    # The Wikipedia article on backpropagation [1] simplifies to the following, but most other learning material does not [2]
    # = actual output - target output
    #
    # Alternative, you can use (target - output), but then need to add it during backpropagation [3]
    #
    # Note that the actual output of the output neuron is often written as yⱼ and target output as tⱼ so:
    # = ∂E/∂yⱼ = -(tⱼ - yⱼ)
    def calculate_pd_error_wrt_output(self, target_output):
    #Your Code Here
        return self.output - target_output

    # The total net input into the neuron is squashed using logistic function to calculate the neuron's output:
    # yⱼ = φ = 1 / (1 + e^(-zⱼ))
    # Note that where ⱼ represents the output of the neurons in whatever layer we're looking at and ᵢ represents the layer below it
    #
    # The derivative (not partial derivative since there is only one variable) of the output then is:
    # dyⱼ/dzⱼ = yⱼ * (1 - yⱼ)
    def calculate_pd_total_net_input_wrt_input(self):
    #Your Code Here
        return self.output * (1 - self.output)

    # The total net input is the weighted sum of all the inputs to the neuron and their respective weights:
    # = zⱼ = netⱼ = x₁w₁ + x₂w₂ ...
    #
    # The partial derivative of the total net input with respective to a given weight (with everything else held constant) then is:
    # = ∂zⱼ/∂wᵢ = some constant + 1 * xᵢw₁^(1-0) + some constant ... = xᵢ
    def calculate_pd_total_net_input_wrt_weight(self, index):
    #Your Code Here
        return self.inputs[index]

# An example:

if __name__ == '__main__':
    nn = NeuralNetwork(2, 2, 2, hidden_layer_weights=[0.15, 0.2, 0.25, 0.3], hidden_layer_bias=0.35, output_layer_weights=[0.4, 0.45, 0.5, 0.55], output_layer_bias=0.6)
    for i in range(10000):
        nn.train([0.05, 0.1], [0.01, 0.99])
        print(i, round(nn.calculate_total_error([[[0.05, 0.1], [0.01, 0.99]]]), 9))