import numpy as np
from sklearn.base import BaseEstimator, ClassifierMixin
from collections import Counter
from sklearn.metrics import accuracy_score
from sklearn.metrics import precision_score
from sklearn.metrics import recall_score

def logit(x, w):
    return np.dot(x, w)

def sigmoid(h):
    return 1. / (1. + np.exp(-h))

def add_bias_feature(a):
    a_extended = np.zeros((a.shape[0],a.shape[1]+1))
    a_extended[:,:-1] = a
    a_extended[:,-1] = int(1)  
    return a_extended

class MyLogisticRegression(BaseEstimator, ClassifierMixin):
    def __init__(self):
        self.w = None
    
    def fit(self, X, y, max_iter=1000, lr=0.1, activation_function = sigmoid):
        
        n, k = X.shape
        
        if self.w is None:
            self.w = np.random.randn(k + 1)
        
        X_train = np.concatenate((np.ones((n, 1)), X), axis=1)
        
        losses = []
        
        for iter_num in range(max_iter):
            z = activation_function(logit(X_train, self.w))
            grad = np.dot(X_train.T, (z - y)) / len(y)

            self.w -= grad * lr

            losses.append(self.__loss(y, z))
        
        return losses
        
    def predict_proba(self, X, activation_function = sigmoid):
        n, k = X.shape
        X_ = np.concatenate((np.ones((n, 1)), X), axis=1)
        return np.array(activation_function(logit(X_, self.w)), dtype = "int")

    def predict(self, X, threshold=0.5):
        return self.predict_proba(X) >= threshold
    
    def get_weights(self):
        return self.w
      
    def __loss(self, y, p):
        p = np.clip(p, 1e-10, 1 - 1e-10)
        return np.mean(y * np.log(p) + (1 - y) * np.log(1 - p))

class MyKNN(BaseEstimator, ClassifierMixin):
    def __init__(self, nn=5):
        self.nn = nn

    def evklid(self, X):
        num_test = X.shape[0]
        num_train = self.X.shape[0]

        t = np.dot(X, self.X.T)
        dists = np.sqrt(-2 * t + np.square(self.X).sum(1) +
                        np.matrix(np.square(X).sum(1)).T)
        return dists

    def fit(self, X, y):  
        self.X = X.to_numpy()
        self.y = y.to_numpy()

    def predict(self, X):
        X = X.to_numpy()
        dists = self.evklid(X)
        preds = np.zeros(dists.shape[0])
        for i in range(dists.shape[0]):
            labels = self.y[np.argsort(dists[i, :])].flatten()
            top_nn_y = labels[:self.nn]
            preds[i] = Counter(top_nn_y).most_common(1)[0][0]
        return preds

class MySVM(BaseEstimator, ClassifierMixin):
    def __init__(self, etha=0.01, alpha=0.1, epochs=200):
        self._epochs = epochs
        self._etha = etha
        self._alpha = alpha
        self._w = None
        self.history_w = []
        self.train_errors = None
        self.val_errors = None
        self.train_loss = None
        self.val_loss = None

    def fit(self, X_train, Y_train, X_val, Y_val, verbose=False):
        X_train, Y_train, X_val, Y_val = X_train.to_numpy(), Y_train.to_numpy(), X_val.to_numpy(), Y_val.to_numpy()


        if len(set(Y_train)) != 2 or len(set(Y_val)) != 2:
            raise ValueError("Number of classes in Y is not equal 2!")

        X_train = add_bias_feature(X_train)
        X_val = add_bias_feature(X_val)
        self._w = np.random.normal(loc=0, scale=0.05, size=X_train.shape[1])
        self.history_w.append(self._w)
        train_errors = []
        val_errors = []
        train_loss_epoch = []
        val_loss_epoch = []

        for epoch in range(self._epochs): 
            tr_err = 0
            val_err = 0
            tr_loss = 0
            val_loss = 0
            for i,x in enumerate(X_train):
                margin = Y_train[i]*np.dot(self._w,X_train[i])
                if margin >= 1:
                    self._w = self._w - self._etha*self._alpha*self._w/self._epochs
                    tr_loss += self.soft_margin_loss(X_train[i],Y_train[i])
                else:
                    self._w = self._w +\
                    self._etha*(Y_train[i]*X_train[i] - self._alpha*self._w/self._epochs)
                    tr_err += 1
                    tr_loss += self.soft_margin_loss(X_train[i],Y_train[i])
                self.history_w.append(self._w)
            for i,x in enumerate(X_val):
                val_loss += self.soft_margin_loss(X_val[i], Y_val[i])
                val_err += (Y_val[i]*np.dot(self._w,X_val[i])<1).astype(int)
            train_errors.append(tr_err)
            val_errors.append(val_err)
            train_loss_epoch.append(tr_loss)
            val_loss_epoch.append(val_loss)
        self.history_w = np.array(self.history_w)    
        self.train_errors = np.array(train_errors)
        self.val_errors = np.array(val_errors)
        self.train_loss = np.array(train_loss_epoch)
        self.val_loss = np.array(val_loss_epoch)                    

    def predict(self, X:np.array) -> np.array:
        y_pred = []
        X_extended = add_bias_feature(X)
        for i in range(len(X_extended)):
            y_pred.append(np.sign(np.dot(self._w,X_extended[i])))
        return np.array(y_pred)         

    def hinge_loss(self, x, y):
        return max(0,1 - y*np.dot(x, self._w))

    def soft_margin_loss(self, x, y):
        return self.hinge_loss(x,y)+self._alpha*np.dot(self._w, self._w)

class MyNaive_Bayes(BaseEstimator, ClassifierMixin):
    def fit(self, X_train, y_train):
        self.classes = np.unique(y_train)
        self.n_classes = len(self.classes)
        self.prior = np.array(X_train.groupby(y_train).apply(lambda col: len(col)) / len(y_train))
        self.mean = np.array(X_train.groupby(y_train).apply(np.mean))
        self.var = np.array(X_train.groupby(y_train).apply(np.var))

    def gauss_distribution(self, class_idx, x):
        mean = self.mean[class_idx]
        var = self.var[class_idx]
        return np.exp((-1/2) * ((x-mean)**2) / (2 * var)) / np.sqrt(2 * np.pi * var)

    def predict(self, X_test):
        y_pred = []
        for x in np.array(X_test):
            posteriors = []
            for class_idx in range(self.n_classes):
                prior = np.log(self.prior[class_idx])
                conditional = np.sum(np.log(self.gauss_distribution(class_idx, x)))
                posterior = prior + conditional
                posteriors.append(posterior)
            y_pred.append(self.classes[np.argmax(posteriors)])
        return y_pred

def pipeline(model, x_train, y_train, x_test, y_test):
    if isinstance(model, MySVM):
        model.fit(x_train, y_train, x_test, y_test)
        y_pred = model.predict(x_test)
    else:
        model.fit(x_train, y_train)
        y_pred = model.predict(x_test)
    print("Confusion matrix:\n", confusion_matrix(y_test, y_pred), "\n")
    print("Acuracy score: {}".format(accuracy_score(y_test, y_pred)))
    print("Precision score: {}".format(precision_score(y_test, y_pred)))
    print("Recall score: {}".format(recall_score(y_test, y_pred)))    