import numpy as np

class Linear: 
    def __init__(self, nin, nout):
        self.W = np.random.normal(0, 1.0 / np.sqrt(nin), (nout, nin))
        self.b = np.zeros((1, nout))
        self.dW = np.zeros_like(self.W)
        self.db = np.zeros_like(self.b)
        
    def forward(self, x):
        self.x = x
        return np.dot(x, self.W.T) + self.b
    
    def backward(self, dz):
        dx = np.dot(dz, self.W)
        dW = np.dot(dz.T, self.x)
        db = dz.sum(axis=0)
        self.dW = dW
        self.db = db
        return dx
    
    def update(self,lr):
        self.W -= lr*self.dW
        self.b -= lr*self.db

class Softmax:
    def forward(self,z):
        self.z = z
        zmax = z.max(axis=1,keepdims=True)
        expz = np.exp(z-zmax)
        Z = expz.sum(axis=1,keepdims=True)
        return expz / Z
    def backward(self,dp):
        p = self.forward(self.z)
        pdp = p * dp
        return pdp - p * pdp.sum(axis=1, keepdims=True)
    
class CrossEntropyLoss: 
    def forward(self,p,y):
        self.p = p
        self.y = y
        p_of_y = p[np.arange(len(y)), y]
        log_prob = np.log(p_of_y)
        return -log_prob.mean()
    
    def backward(self, loss):
        dlog_softmax = np.zeros_like(self.p)
        dlog_softmax[np.arange(len(self.y)), self.y] -= 1.0 / len(self.y)
        return dlog_softmax / self.p

class Net: 
    def __init__(self):
        self.layers = []
    
    def add(self, l):
        self.layers.append(l)
        
    def forward(self, x):
        for l in self.layers:
            x = l.forward(x)
        return x
    
    def backward(self, z):
        for l in self.layers[::-1]:
            z = l.backward(z)
        return z
    
    def update(self, lr):
        for l in self.layers:
            if 'update' in l.__dir__():
                l.update(lr)

class Tanh:
    def forward(self, x):
        y = np.tanh(x)
        self.y = y
        return y
    
    def backward(self, dy):
        return (1.0 - self.y**2) * dy

class Sigmoid:
    def forward(self, x):
        y = 1 / (1 + np.exp(-x))
        self.y = y
        return y
    def backward(self, dy):
        return self.y * (1 - self.y) * dy

def get_loss_acc(net, x, y, loss = CrossEntropyLoss()):
    p = net.forward(x)
    l = loss.forward(p, y)
    pred = np.argmax(p, axis = 1)
    acc = (pred == y).mean()
    return l, acc

def train_epoch(net, train_x, train_labels, loss=CrossEntropyLoss(), batch_size = 4, lr = 0.1):
    for i in range(0, len(train_x), batch_size):
        xb = train_x[i : i + batch_size]
        yb = train_labels[i : i + batch_size]

        p = net.forward(xb)
        l = loss.forward(p, yb)
        dp = loss.backward(l)
        dx = net.backward(dp)
        net.update(lr)

def train_epochs(net, train_x, train_labels, loss=CrossEntropyLoss(), batch_size = 4, lr = 0.1, epochs = 10):
    for i in range(epochs):
        train_epoch(net, train_x, train_labels)