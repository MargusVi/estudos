import random

class Perceptron():
    '''
        Perceptron Learning Algorithm that can be train using a 
        fit and predict methodology, without any library
    '''
    
    def __init__(self):
        self.weights = []
        
    def fit(self, X, y, learning_rate = 0.01, num_iteration = 100):
        
        num_row = len(X)
        num_feature = len(X[0]) # Here we assume that we have a rectangular matrix
        
        # Randomly initalize the weights
        for i in range(num_feature+1):
            self.weights.append(random.uniform(0,1))
        
        # Launch the training algorithm
        
        for i in range(num_iteration):
            
            # Stochastic Gradient Descent
            r_i = random.randint(0,num_row-1)
            row = X[r_i]
            yhat = self.predict(row)
            error = (y[r_i] - yhat)
            self.weights[0] = self.weights[0] + learning_rate*error

            for f_i in range(num_feature):
                self.weights[f_i] = self.weights[f_i] + learning_rate*error*row[f_i]
                
            if i % 100 == 0:
                total_error = 0
                for r_i in range(num_row):
                    row = X[r_i]
                    yhat = self.predict(row)
                    error = (y[r_i] - yhat)
                    total_error = total_error + error**2
                mean_error = total_error/num_row
                print(f"Iteration {i} with error = {mean_error}")
        
    def predict(self, row):
            
        # The activation start with the bias at weights == 0
        activation = self.weights[0]
        
        # We iterate over the weights and the features in the given row
        for weight, feature in zip(self.weights[1:], row):
            activation = activation + weight*feature
            
        if activation >= 0.0:
            return 1.0
        return 0.0