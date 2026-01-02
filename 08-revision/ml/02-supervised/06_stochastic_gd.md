# Stochastic Gradient Descent (SGD)

> **Definition**: A variation of Gradient Descent where we calculate the gradient and update the weights using **ONLY ONE** training example at a time (selected randomly).

### Key Characteristics
*   **Faster Convergence**: It updates weights $n$ times in one epoch (where $n$ is number of rows), compared to Batch GD which updates only once per epoch.
*   **Randomness**: We select the row randomly to ensure fairness and avoid cycles.
*   **Fluctuation**: The path to the minima is **noisy** (zig-zag) because each row pushes the weights in a slightly different direction. It doesn't settle exactly at the global minima but dances around it.

---

### Mathematical Algorithm

1.  **Initialize** random weights.
2.  **Loop** for `epochs`:
    3.  **Shuffle** the data (optional but recommended).
    4.  **Loop** through each row $i$ (or random $i$):
        *   Calculate Prediction for **single row**: $\hat{y}_i = \beta_0 + \beta_1 x_{i1} + ...$
        *   Calculate Gradient:
            $$ \frac{\partial J}{\partial \beta_0} = -2 (y_i - \hat{y}_i) $$
            $$ \frac{\partial J}{\partial \beta_j} = -2 (y_i - \hat{y}_i) x_{ij} $$
        *   **Update Weights immediately**:
            $$ \beta_{new} = \beta_{old} - \alpha \times \text{Gradient} $$

---

### Batch GD vs Stochastic GD

| Feature | Batch GD | Stochastic GD |
| :--- | :--- | :--- |
| **Updates per Epoch** | 1 | $n$ (Number of rows) |
| **Speed per Step** | Slow (uses all data) | Very Fast (uses 1 row) |
| **Convergence Path** | Smooth, Straight line | Noisy, Zig-Zag |
| **Final Accuracy** | Exact Global Minima | Close to Global Minima (fluctuates) |
| **Memory (RAM)** | High (Vectorization loads all data) | Low (Loads 1 row at a time) |

> **Note**: Even though SGD takes more time per epoch (due to lack of vectorization), it converges in **fewer epochs**.

<!-- 
IMAGE_PROMPT: 
Type: 2D Contour Comparison
Description: 
- Left (Batch GD): A smooth straight arrow going directly to the center (minima).
- Right (SGD): A jagged, random-looking zig-zag line eventually reaching the center but keeping moving around it.
Style: Scientific comparison.
-->

---

### The Problem of Fluctuation (And Solution)

Since SGD assumes one point represents the whole data, it might make "wrong" moves (outliers), causing fluctuations even around the minima.
*   **Solution**: **Learning Schedule** (Learning Rate Decay).
*   **Idea**: Start with a big learning rate (to jump fast towards minima) and **decrease** it over time (to settle down precisely).

$$ \alpha_t = \frac{\alpha_0}{1 + \text{decay} \times t} $$

---

### When to use SGD?
1.  **Very Big Datasets**: When data doesn't fit in RAM.
2.  **Non-Convex Functions**: The "noise" in SGD acts like a feature—it helps jump out of **Local Minima** (whereas Batch GD might get stuck).

---

### Python Implementation (From Scratch)

```python
import numpy as np
import random

class MeraSGD:
    def __init__(self, learning_rate=0.01, epochs=100):
        self.coef_ = None
        self.intercept_ = None
        self.lr = learning_rate
        self.epochs = epochs
        
    def fit(self, X_train, y_train):
        # Initialize
        self.intercept_ = 0
        self.coef_ = np.ones(X_train.shape[1])
        
        for i in range(self.epochs):
            for j in range(X_train.shape[0]):
                # Select random index (or strict sequential)
                idx = np.random.randint(0, X_train.shape[0])
                
                # Prediction for single row
                y_hat = np.dot(X_train[idx], self.coef_) + self.intercept_
                
                # Gradients (No summation, just single row error)
                intercept_der = -2 * (y_train[idx] - y_hat)
                coef_der = -2 * (y_train[idx] - y_hat) * X_train[idx]
                
                # Update weights IMMEDIATELY
                self.intercept_ = self.intercept_ - (self.lr * intercept_der)
                self.coef_ = self.coef_ - (self.lr * coef_der)
        
        print(f"Intercept: {self.intercept_}, Coef: {self.coef_}")
        
    def predict(self, X_test):
        return np.dot(X_test, self.coef_) + self.intercept_
```
