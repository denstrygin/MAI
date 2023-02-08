import numpy as np

def softmax(z):
        zmax = z.max(axis = 1, keepdims = True)
        expz = np.exp(z - zmax)
        Z = expz.sum(axis = 1, keepdims = True)
        return expz / Z

def cross_entropy_loss(y_pred, y_train):
        y_pred_of_y_train = y_pred[np.arange(len(y_train)), y_train]
        log_prob = np.log(y_pred_of_y_train)
        return -log_prob.mean()

class Neuron:
    
    def __init__(self, weights, bias):
        self.weights = weights
        self.bias = bias
    
    def feedforward(self, x_train, activation_function):
        outputs = np.dot(x_train, self.weights) + self.bias
        if activation_function == "nope":
            return outputs[0]
        else:  
            return activation_function(outputs)

class MyNeuralNetwork:
    
    def __init__(self, weights, bias):
        self.structure = [[]]
        self.weights = weights
        self.bias = bias

    def add_neuron(self, nlayers, weights, bias):
        neuron = Neuron(weights, bias)
        self.structure[nlayers].append(neuron)
    
    def add_layers(self):
        self.structure.append([])
    
    def info(self):
        print(self.structure)
    
    def feedforward(self, x_train, activation_function):
        for i in self.structure:
            if i:
                out_of_layers = []
                for j in i:
                    out_of_layers.append(j.feedforward(x_train, activation_function))
                x_train = np.array(out_of_layers, dtype = "float32")
        return x_train
    
    def feedbackward(self, x_train, y_pred, y_train, learn_rate):
        dlog_softmax = np.zeros_like(y_pred)
        dlog_softmax[np.arange(len(y_train)), y_train] -= 1.0/len(y_train)
        dp =  dlog_softmax / y_pred
        pdp = y_pred * dp
        dz = pdp - y_pred * pdp.sum(axis=1, keepdims=True)
        dx = np.dot(dz, self.weights)
        dw = np.dot(dz.T, x_train)
        db = dz.sum(axis=0)
        self.weights -= learn_rate * dw
        self.bias -= learn_rate * db
        for i in self.structure:
            if i:
                iter = 0
                for j in i:
                    j.weights =  self.weights[iter]
                    j.bias = self.bias[iter]
                    iter += 1
        return dx

    def train(self, x_train, y_train, activation_function, epochs, learn_rate):
        acc = []
        loss = []
        for i in range(epochs):
            output = []
            for j in x_train:
                output.append(self.feedforward([j], activation_function))
            y_pred = np.argmax(output, axis = 1)
            acc.append((y_pred == y_train).mean())
            output = softmax(np.array(output, dtype = "float32"))
            loss.append(cross_entropy_loss(output, y_train))
            self.feedbackward(x_train, output,  y_train, learn_rate)
        print("Initial accurancy: ", acc[0])
        print("Latest accurancy: ", acc[-1])
        loss = np.array(loss)
        acc = np.array(acc)
        print("Mean Loss: ", loss.mean())
        return [acc, loss]
    
    def test(self, x_test, y_test, activation_function):
        output = []
        for i in x_test:
            output.append(self.feedforward([i], activation_function))
        y_pred = np.argmax(output, axis = 1)
        acc = (y_pred == y_test).mean()
        print("Test accurancy: ", acc)
        return output

def main():
    pass

if __name__ == "__main__":
    main()