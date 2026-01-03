# Logistic Regression (Intuition)

> **Definition**: Logistic Regression is a **Supervised Machine Learning** algorithm used for **Classification** problems. Despite its name containing "Regression", it is used to predict discrete categories (e.g., Yes/No, Spam/Not Spam) by estimating probabilities.

### 1. Two Perspectives
1.  **Geometric**: Looking at the problem as finding a Line (2D) or Plane/Hyperplane (3D+) that separates classes.
2.  **Probabilistic**: Converting predictions into probabilities (0 to 1).

### 2. Geometric Intuition
*   **Goal**: Find a boundary that separates "Positive" (e.g., Green) and "Negative" (e.g., Blue) points.
*   **The Equation**: $Ax_1 + Bx_2 + C = 0$
    *   **A & B**: Coefficients. They control the **Orientation (Rotation)** of the line (about axes).
    *   **C**: Intercept. It controls the **Shift** of the line.

> **Visual Logic**:
> *   $L(x, y) > 0 \rightarrow$ Positive Region.
> *   $L(x, y) < 0 \rightarrow$ Negative Region.

<!-- 
IMAGE_PROMPT: 
Type: Scatter Plot (2D)
Description: 
- 2D Graph with X1 and X2 axes.
- Two clusters of points: Blue (Class 0) and Green (Class 1).
- A straight Line ($Ax_1 + Bx_2 + C = 0$) separating them.
- Highlight the "Positive Region" on one side and "Negative Region" on the other.
Style: Educational, similar to the user's notes.
-->

![Linear Decision Boundary](assets/log_reg_linear_boundary.png)

---

### 3. The Perceptron Trick
"Not the best solution, but a starting point to find coefficients."

**The Algorithm**:
1.  **Start** with random values (Random line).
2.  **Loop** for `epochs` (or until convergence):
    *   Select a **random data point** $(x_i, y_i)$.
    *   **Check**: Is it correctly classified?
        *   If **Yes**: Do nothing (Continue).
        *   If **No**: Apply **Transformation** (Fix the line).

**Transformation Logic (Push and Pull)**:
We update weights ($W_{new}$) using Learning Rate ($\eta$) to gradually move the line.

*   **Case 1 (Positive Point, Predicted Negative)**:
    *   Point is in negative region, needs to be in positive.
    *   **Action**: Move line **towards** the point.
    *   **Math**: $W_{new} = W_{old} + \eta X_i$
*   **Case 2 (Negative Point, Predicted Positive)**:
    *   Point is in positive region, needs to be in negative.
    *   **Action**: Move line **away** from the point.
    *   **Math**: $W_{new} = W_{old} - \eta X_i$

**Unified Update Rule**:
$$ W_{new} = W_{old} + \eta (y_i - \hat{y}_i) x_i $$
*   $(y_i - \hat{y}_i)$ automatically handles the sign ($+1$ or $-1$).
*   $\hat{y}_i$ is the **Step Function** result (1 or 0).

<!-- 
IMAGE_PROMPT: 
Type: Diagram / Illustration
Description: 
- Visualizing the "Push and Pull" update.
- Case 1: A Misclassified Positive Point. detailed arrows showing the Line moving/rotating TOWARDS the point.
- Case 2: A Misclassified Negative Point. detailed arrows show the Line moving AWAY from the point.
- Label the vectors as "Old Weight", "Update Vector ($\eta X_i$)", and "New Weight".
Style: Conceptual Mechanics.
-->

![Perceptron Updates: Push and Pull](assets/perceptron_push_pull_vectors.png)

---

### 4. Issues with Perceptron Trick
Why do we need Logistic Regression if this works?

1.  **No "Conviction" (The stopping problem)**:
    *   The algorithm stops **the moment** all points are classified correctly.
    *   It treats a boundary that *barely* touches the points the same as a boundary that is strictly in the middle.
    *   **Result**: It might Overfit. It doesn't find the *Best* line, just *A* line.

2.  **Only "Wrong" points matter**:
    *   The line is only updated when a point is misclassified.
    *   **Correctly classified points** (even if they are very close to the line) do **nothing**.
    *   *Ideal Scenario*: Correct points should also "Push" the line away to increase the margin/confidence.

> **Conclusion**: We need a method that considers **Distance** (how far a point is) and gives a probability, rather than a hard Yes/No step function. This leads us to the **Sigmoid Function**.

---

### Python Code (Perceptron Logic)

```python
def perceptron_step(X, y, epochs=100, lr=0.1):
    X = np.insert(X, 0, 1, axis=1) # Add bias column
    weights = np.ones(X.shape[1])
    
    for _ in range(epochs):
        # 1. Pick random point
        idx = np.random.randint(0, X.shape[0])
        x_sample = X[idx]
        y_true = y[idx]
        
        # 2. Predict (Step Function)
        y_pred = 1 if np.dot(weights, x_sample) >= 0 else 0
        
        # 3. Update Rule (Combined)
        # If y_true == y_pred, term becomes 0 (No update)
        weights = weights + lr * (y_true - y_pred) * x_sample
        
    return weights
```
