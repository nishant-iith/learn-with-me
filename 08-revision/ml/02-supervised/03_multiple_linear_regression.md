# Multiple Linear Regression

> **Definition**: A linear regression model that uses **more than one** independent variable (input feature) to predict a continuous dependent variable (output).

### Geometric Intuition
*   **1 Input ($x$)**: Best Fit **Line**.
*   **2 Inputs ($x_1, x_2$)**: Best Fit **Plane** (Surface).
*   **3 Inputs ($x_1, x_2, x_3$)**: Best Fit **Hyperplane**.
*   **$n$ Inputs**: Hyperplane in $n$-dimensional space.

### Mathematical Equation
Instead of $y = mx + c$, we have multiple features:

$$y = \beta_0 + \beta_1x_1 + \beta_2x_2 + ... + \beta_nx_n$$
$$y = \beta_0 + \sum_{i=1}^{n} \beta_ix_i$$

*   $\beta_0$: Intercept (Offset).
*   $\beta_1, \beta_2...$: Coefficients (Weightage of corresponding features).
*   **Note**: For $n$ inputs, we calculate $n+1$ coefficients (including $\beta_0$).

<!-- 
IMAGE_PROMPT: 
Type: 3D Plot
Description: A 3D scatter plot showing data points in (x1, x2, y) space. A flat semi-transparent glowing plane cutting through the points representing the Linear Regression model.
Style: Dark mode, neon wireframe plane.
-->

![Multiple Linear Regression Plane](assets/multiple_lr_plane.png)

---

### Matrix Formulation (The Math Behind It)

To solve for all $\beta$ values at once, we use **Linear Algebra (Matrices)**.

#### 1. Notation
*   $Y$: Vector of actual target values ($n \times 1$).
*   $X$: Matrix of features ($n \times (m+1)$). We add a column of **1s** to handle the intercept $\beta_0$.
*   $\beta$: Vector of coefficients ($m+1 \times 1$).

$$\hat{Y} = X\beta$$

#### 2. Derivation
We want to minimize the error (residuals): $e = Y - \hat{Y}$.
Total Error (SSE) is the sum of squared residuals. In matrix form:

$$E = e^Te = (Y - \hat{Y})^T (Y - \hat{Y})$$

Substitute $\hat{Y} = X\beta$:
$$E = (Y - X\beta)^T (Y - X\beta)$$

Expand the terms (Remember $(AB)^T = B^TA^T$):
$$E = (Y^T - (X\beta)^T) (Y - X\beta)$$
$$E = (Y^T - \beta^TX^T) (Y - X\beta)$$
$$E = Y^TY - Y^TX\beta - \beta^TX^TY + \beta^TX^TX\beta$$

*Note*: $Y^TX\beta$ is a scalar (1x1), so it equals its transpose $(\beta^TX^TY)$.
$$E = Y^TY - 2\beta^TX^TY + \beta^TX^TX\beta$$

#### 3. Minimize $E$ (Differentiation)
To find the best $\beta$, take the derivative $\frac{\partial E}{\partial \beta}$ and set to 0.

$$\frac{\partial E}{\partial \beta} = 0 - 2X^TY + 2X^TX\beta = 0$$
*(Using Matrix Differentiation rules: $\frac{d}{dx}(a^Tx) = a$, $\frac{d}{dx}(x^TAx) = 2Ax$)*

$$2X^TX\beta = 2X^TY$$
$$X^TX\beta = X^TY$$

Multiply both sides by inverse $(X^TX)^{-1}$:
$$\beta = (X^TX)^{-1}X^TY$$

> **This is the Normal Equation (OLS Closed Form Solution).**

---

### Computational Complexity: OLS vs Gradient Descent

The formula $\beta = (X^TX)^{-1}X^TY$ gives the exact answer in one step. **So why do we need Gradient Descent?**

#### The Problem with OLS
*   It requires calculating the **inverse** of a matrix $(X^TX)^{-1}$.
*   **Time Complexity**: Computing the inverse of an $n \times n$ matrix is roughly **$O(n^3)$**.
*   **Scenario**:
    *   If $n$ (features) is small (e.g., 10-100), OLS is super fast.
    *   If $n$ is large (e.g., 100,000 features in NLP/Image processing), $O(n^3)$ becomes too slow/impossible.

#### The Solution: Gradient Descent (SGD)
*   It is an **iterative** method.
*   Does **not** involve matrix inversion.
*   Much faster and memory-efficient for large datasets.

| Feature Check | Small Data / Few Features | Huge Data / Many Features |
| :--- | :--- | :--- |
| **Best Method** | OLS (Normal Equation) | Gradient Descent (SGD) |
| **Scikit-Learn** | `LinearRegression` | `SGDRegressor` |

### Python Implementation (Normal Equation)

```python
import numpy as np

class MeraMultipleLR:
    def __init__(self):
        self.coef_ = None
        self.intercept_ = None
        
    def fit(self, X_train, y_train):
        # Insert column of 1s for intercept (Beta_0)
        # X_train shape: (n, m) -> (n, m+1)
        X_train = np.insert(X_train, 0, 1, axis=1)
        
        # Calculate coefficients using Normal Equation: beta = (X^T * X)^-1 * X^T * Y
        # np.linalg.inv computes the inverse
        betas = np.linalg.inv(np.dot(X_train.T, X_train)).dot(np.dot(X_train.T, y_train))
        
        self.intercept_ = betas[0]
        self.coef_ = betas[1:]
        print(f"Intercept: {self.intercept_}, Coefficients: {self.coef_}")
        
    def predict(self, X_test):
        # y_pred = beta_0 + beta_1*x_1 + ...
        # Formula: y = X_test * coef + intercept
        return np.dot(X_test, self.coef_) + self.intercept_
```

---

### Interview Questions

**Q1: What happens if the matrix $(X^TX)$ is not invertible (Singular)?**
*   **Ans**: The Normal Equation fails. This happens if:
    1.  **Multicollinearity**: Features are perfectly correlated (e.g., $x_2 = 2x_1$).
    2.  $n < p$: More features ($p$) than data samples ($n$).
    *   *Fix*: Use Regularization (Ridge Regression) or drop correlated features.

**Q2: How does the geometric interpretation change from 2D to 3D?**
*   **Ans**: In 2D (1 feature), the model is a **Line**. In 3D (2 features), it becomes a **Plane**. Beyond that, it is a **Hyperplane**.

**Q3: Why is Gradient Descent preferred for Deep Learning over OLS?**
*   **Ans**: Deep Learning models essentially do regression/classification but with millions of parameters (weights). Computing a matrix inverse for millions of dimensions is computationally impossible ($O(n^3)$). Gradient Descent scales linearly $O(n)$ or $O(n^2)$ depending on implementation, making it feasible.
