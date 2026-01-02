# Mini-Batch Gradient Descent

> **Definition**: A variation of Gradient Descent where we calculate the gradient and update weights using a **small random subset** (batch) of training data at a time. It strikes a balance between the stability of Batch GD and the speed of Stochastic GD.

### The Algorithm

1.  **Decide Batch Size**: e.g., $32, 64, 128$.
2.  **Calculate Number of Batches**:
    $$ \text{No. of Batches} = \frac{\text{Total Rows } (n)}{\text{Batch Size}} $$
    *   *Example*: $n=1000$, Batch Size $= 10$ $\rightarrow$ $100$ Updates per epoch.
3.  **Loop** for `epochs`:
    4.  **Shuffle** data.
    5.  **Loop** through each **batch**:
        *   Construct small matrices ($X_{batch}, Y_{batch}$).
        *   Calculate Vectorized Gradient on this batch.
            $$ \frac{\partial J}{\partial \beta} = -\frac{2}{k} X_{batch}^T (Y_{batch} - \hat{Y}_{batch}) $$
            *(where $k$ is batch size)*
        *   **Update Weights**.

---

### Comparison: The Goldilocks Zone

| Feature | Batch GD | Stochastic GD | Mini-Batch GD |
| :--- | :--- | :--- | :--- |
| **Data used** | All $n$ | 1 row | $k$ rows (e.g., 32) |
| **Speed** | Slowest | Fastest (per step) | Fast |
| **Stability** | Very Stable | Very Noisy | **Stable enough** |
| **Convergence** | Smooth curve | Zig-Zag | **Wavy** (Fluctuates slightly) |

> **Analogy**:
> *   **Batch**: Asking 1000 people for opinion before acting. (Too slow)
> *   **Stochastic**: Asking 1 person and acting immediately. (Too reactive)
> *   **Mini-Batch**: Asking a group of 10 people. (Balanced)

<!-- 
IMAGE_PROMPT: 
Type: 2D Path Comparison
Description: 
- Batch: Straight white line to center.
- Stochastic: Wild zigzag white line.
- Mini-Batch: A line that wiggles a bit but moves steadily towards center (intermediate smoothness).
Style: Dark mode comparison.
-->

---

### Python Implementation (From Scratch)

```python
import numpy as np

class MeraMiniBatchGD:
    def __init__(self, learning_rate=0.01, epochs=100, batch_size=10):
        self.coef_ = None
        self.intercept_ = None
        self.lr = learning_rate
        self.epochs = epochs
        self.batch_size = batch_size
        
    def fit(self, X_train, y_train):
        self.intercept_ = 0
        self.coef_ = np.ones(X_train.shape[1])
        
        num_batches = int(X_train.shape[0] / self.batch_size)
        
        for i in range(self.epochs):
            # Shuffle data at start of each epoch
            indices = np.random.permutation(X_train.shape[0])
            X_shuffled = X_train[indices]
            y_shuffled = y_train[indices]
            
            for j in range(num_batches):
                # Create Batch
                start_idx = j * self.batch_size
                end_idx = (j + 1) * self.batch_size
                
                X_batch = X_shuffled[start_idx : end_idx]
                y_batch = y_shuffled[start_idx : end_idx]
                
                # Vectorized update on Batch
                y_hat = np.dot(X_batch, self.coef_) + self.intercept_
                
                intercept_der = -2 * np.mean(y_batch - y_hat)
                coef_der = -2 * np.dot((y_batch - y_hat), X_batch) / self.batch_size
                
                self.intercept_ = self.intercept_ - (self.lr * intercept_der)
                self.coef_ = self.coef_ - (self.lr * coef_der)
                
        print(f"Intercept: {self.intercept_}, Coef: {self.coef_}")
        
    def predict(self, X_test):
        return np.dot(X_test, self.coef_) + self.intercept_
```

---

### Scikit-Learn Implementation

Scikit-learn's `SGDRegressor` creates a Mini-Batch GD when we use the `partial_fit` method.

```python
from sklearn.linear_model import SGDRegressor

# Normal usage (defaults to SGD/Batch depending on config, usually SGD)
model = SGDRegressor(max_iter=1000, eta0=0.01)
model.fit(X_train, y_train)

# For explicit Mini-Batch training (Simulated):
model = SGDRegressor()
# We manually feed batches
for i in range(epochs):
    x_batch, y_batch = get_next_batch(X_train, y_train)
    model.partial_fit(x_batch, y_batch)
```

### Note on Convergence
Just like SGD, Mini-Batch GD fluctuates around the minima.
*   **Solution**: Use a **Learning Schedule** (gradually decrease learning rate) to make it settle.
