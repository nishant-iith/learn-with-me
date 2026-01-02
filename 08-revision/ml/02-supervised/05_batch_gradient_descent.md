# Batch Gradient Descent

> **Definition**: A variation of Gradient Descent where we calculate the error and gradient using **ALL training examples** in the dataset before making a single update to the weights (coefficients).

### Use Case
*   Standard approach for small to medium-sized datasets.
*   Convex cost functions (guaranteed convergence to global minima).

---

### Mathematical Formulation

We initialize coefficients randomly (e.g., $\beta_0 = 0, \beta_1 = 1...$).
For each epoch, we update them using the gradients.

#### 1. Derivatives (Slopes)
For Intercept ($\beta_0$):
$$ \frac{\partial J}{\partial \beta_0} = -\frac{2}{n} \sum_{i=1}^n (y_i - \hat{y}_i) $$

For Coefficients ($\beta_j$ where $j=1...m$):
$$ \frac{\partial J}{\partial \beta_j} = -\frac{2}{n} \sum_{i=1}^n (y_i - \hat{y}_i)x_{ij} $$

#### 2. Vectorized Implementation (The Smart Way)
Instead of looping through rows (slow!) or columns to find gradients, we use **Linear Algebra (Matrices)**.

*   $X$: Matrix of features ($n \times m$).
*   $Y$: Vector of actual values ($n \times 1$).
*   $\hat{Y}$: Vector of predictions ($n \times 1$).
*   Error Matrix: $(Y - \hat{Y})$.

**The Vectorized Gradient Formula**:
$$ \frac{\partial J}{\partial \beta} = -\frac{2}{n} X^T (Y - \hat{Y}) $$

**Update Rule**:
$$ \beta_{new} = \beta_{old} - \alpha \left( -\frac{2}{n} X^T (Y - \hat{Y}) \right) $$

> **Why Vectorized?**
> Operations like `np.dot` use optimized C/C++ backends and are massively faster than Python loops.

---

### Python Implementation (From Scratch)

```python
import numpy as np

class MeraBatchGD:
    def __init__(self, learning_rate=0.01, epochs=100):
        self.coef_ = None
        self.intercept_ = None
        self.lr = learning_rate
        self.epochs = epochs
        
    def fit(self, X_train, y_train):
        # Initialize coefficients (arbitrary 1s) and intercept (0)
        self.intercept_ = 0
        self.coef_ = np.ones(X_train.shape[1])
        
        for i in range(self.epochs):
            # 1. Prediction for ALL rows (Vectorized)
            # y_hat = beta_0 + beta_1*x1 + beta_2*x2 ...
            y_hat = np.dot(X_train, self.coef_) + self.intercept_
            
            # 2. Calculate Slopes (Vectorized)
            # Derivative w.r.t intercept: -2 * mean(Error)
            intercept_der = -2 * np.mean(y_train - y_hat)
            
            # Derivative w.r.t weights: -2/n * (X.T dot Error)
            # Using dot product avoids the loop over columns
            coef_der = -2 * np.dot((y_train - y_hat), X_train) / X_train.shape[0]
            
            # 3. Update Weights
            self.intercept_ = self.intercept_ - (self.lr * intercept_der)
            self.coef_ = self.coef_ - (self.lr * coef_der)
            
        print(f"Intercept: {self.intercept_}, Coef: {self.coef_}")
    
    def predict(self, X_test):
        return np.dot(X_test, self.coef_) + self.intercept_
```

---

### Issues with Batch Gradient Descent

**1. Speed & Computation**
*   If we have **Deep Learning** models or **High Dimensional Data**, calculating the gradient requires summing errors over ALL data points for EVERY single step.
*   This makes the algorithm extremely **slow** per iteration.

**2. Hardware / Memory (RAM)**
*   Vectorization requires loading the matrices into RAM.
*   If the dataset is massive (e.g., 50GB csv), we cannot load it all into RAM for `np.dot`.
*   *Result*: "Memory Error" or crashes.

> **Solution**: Use **Stochastic Gradient Descent (SGD)** (update row-by-row) or **Mini-Batch GD** (chunk-by-chunk).

---

### Interview Questions

**Q1: Why do we divide by $n$ in the gradient calculation?**
*   **Ans**: It comes from the Mean Squared Error (MSE) formula ($\frac{1}{n}\sum...$). It keeps the gradient magnitude consistent regardless of dataset size. If we didn't divide by $n$, effective learning rate would effectively scream for large datasets, causing divergence.

**Q2: What is the complexity of one step of Batch GD?**
*   **Ans**: $O(n \times m)$ where $n$ is samples and $m$ is features. We touch every data point.

**Q3: How does Vectorization speed up Batch GD?**
*   **Ans**: It utilizes SIMD (Single Instruction, Multiple Data) instructions in the CPU/GPU, performing mathematical operations on arrays in parallel rather than sequentially processing elements in a loop.
