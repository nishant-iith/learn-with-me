# Logistic Regression: Gradient Descent (Topic 16 Part 2)

> **Goal**: Minimize the Log Loss using Gradient Descent. We need the derivative of Loss w.r.t Weights ($ \frac{\partial L}{\partial W} $).

### 1. Matrix Notation
*   $X$: Shape $(m, n+1)$ (Inputs + Bias).
*   $W$: Shape $(n+1, 1)$ (Coefficients).
*   $Y$: Shape $(m, 1)$ (True Labels).
*   $\hat{Y} = \sigma(Z) = \sigma(X \cdot W)$.

### 2. The Derivative Derivation (Step-by-Step)
We know the Loss for one row is:
$$ L = - [ y \log(\hat{y}) + (1-y) \log(1-\hat{y}) ] $$

We want $\frac{\partial L}{\partial w}$. Using **Chain Rule**:
$$ \frac{\partial L}{\partial w} = \frac{\partial L}{\partial \hat{y}} \cdot \frac{\partial \hat{y}}{\partial z} \cdot \frac{\partial z}{\partial w} $$

**Step A: $\frac{\partial L}{\partial \hat{y}}$**
$$ \frac{\partial}{\partial \hat{y}} (- y \log \hat{y} - (1-y) \log (1-\hat{y})) $$
$$ = - \left( \frac{y}{\hat{y}} - \frac{1-y}{1-\hat{y}} \right) $$
$$ = \frac{\hat{y} - y}{\hat{y}(1-\hat{y})} $$

**Step B: $\frac{\partial \hat{y}}{\partial z}$ (Sigmoid Derivative)**
As derived in the previous chapter:
$$ \sigma'(z) = \hat{y}(1-\hat{y}) $$

**Step C: $\frac{\partial z}{\partial w}$**
Since $z = wx + b$:
$$ \frac{\partial z}{\partial w} = x $$

**Combining them (The Magic Cancelation)**:
$$ \frac{\partial L}{\partial w} = \left( \frac{\hat{y} - y}{\hat{y}(1-\hat{y})} \right) \cdot (\hat{y}(1-\hat{y})) \cdot x $$
$$ \frac{\partial L}{\partial w} = (\hat{y} - y) x $$

---

### 3. The Final Update Rule
For all $m$ examples (Average):
$$ \frac{\partial J}{\partial W} = \frac{1}{m} X^T (\hat{Y} - Y) $$

**Gradient Descent Step**:
$$ W_{new} = W_{old} - \eta \left( \frac{\partial J}{\partial W} \right) $$
$$ W_{new} = W_{old} - \eta \left( \frac{1}{m} X^T (\hat{Y} - Y) \right) $$

> **Note on Signs**:
> *   If you write error as $(Y - \hat{Y})$, the sign flips.
> *   $W_{new} = W_{old} + \eta \frac{1}{m} X^T (Y - \hat{Y})$
> *   This logically means: If $Y=1$ and $\hat{Y}=0$, error is +1. We ADD to weights to push result up.

<!-- 
IMAGE_PROMPT: 
Type: Flowchart
Description: 
- Input X -> Dot Product (z) -> Sigmoid -> Prediction y_hat.
- Loss function compares y_hat and y.
- Backward Pass (Gradient): Error term (y_hat - y) flows back.
- Formula boxes: Shows how terms cancel out to leave simple (y_hat - y)x.
Style: Neural Network Backprop style.
-->

---

### 4. Python Implementation (From Scratch)

```python
import numpy as np

class MeraLogisticRegression:
    def __init__(self, learning_rate=0.01, epochs=1000):
        self.lr = learning_rate
        self.epochs = epochs
        self.weights = None
        self.bias = None
        
    def sigmoid(self, z):
        return 1 / (1 + np.exp(-z))
    
    def fit(self, X, y):
        m, n = X.shape
        # Initialize
        self.weights = np.zeros(n)
        self.bias = 0
        
        for _ in range(self.epochs):
            # 1. Forward Pass
            z = np.dot(X, self.weights) + self.bias
            y_pred = self.sigmoid(z)
            
            # 2. Compute Gradients
            # derivative w.r.t weights: (1/m) * X.T * (y_pred - y)
            dw = (1/m) * np.dot(X.T, (y_pred - y))
            db = (1/m) * np.sum(y_pred - y)
            
            # 3. Update Parameters
            self.weights = self.weights - self.lr * dw
            self.bias = self.bias - self.lr * db
            
    def predict(self, X):
        z = np.dot(X, self.weights) + self.bias
        y_pred = self.sigmoid(z)
        # Convert probability to class (0 or 1)
        return [1 if i > 0.5 else 0 for i in y_pred]
```
