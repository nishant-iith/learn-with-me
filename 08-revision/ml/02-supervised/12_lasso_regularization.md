# Lasso Regression (L1 Regularization)

> **Definition**: Least Absolute Shrinkage and Selection Operator. It adds a penalty equivalent to the **absolute value of the magnitude** of coefficients.

### Mathematical Formulation

#### 1. The Loss Function
$$ \text{Loss} = \text{MSE} + \lambda \sum_{j=1}^{p} |\beta_j| $$

*   **Difference from Ridge**: We uses $|m|$ (Absolute) instead of $m^2$ (Square).
*   **Differentiation Issue**: $|m|$ is not differentiable at $m=0$. We use sub-gradients or coordinate descent to solve it.

#### 2. Intuition: How it makes Coefficients ZERO?
Let's look at the simplified formula for slope $m$ (derived using sub-gradients):

*   **Range 1 ($m > 0$)**: $m_{new} = \frac{\text{Numerator} - \lambda}{\text{Denominator}}$
*   **Range 2 ($m < 0$)**: $m_{new} = \frac{\text{Numerator} + \lambda}{\text{Denominator}}$

**Key Insight (from your notes)**:
*   In **Ridge**, $\lambda$ was in the **Denominator**. Increasing it made the result smaller, but never zero (unless $\lambda \to \infty$).
*   In **Lasso**, $\lambda$ is effectively in the **Numerator** (substracted/added).
    *   If $\lambda$ is large enough, it can completely cancel out the Numerator values.
    *   Result $\rightarrow$ **Coefficient becomes EXACTLY ZERO**.

---

### Key Properties

1.  **Feature Selection**:
    *   Since coefficients can become `0`, Lasso effectively **removes** useless features from the model.
    *   **Use Case**: High-dimensional data where you suspect many features are irrelevant.

2.  **Impact on Coefficients**:
    *   As $\lambda \uparrow$, coefficients shrink.
    *   Eventually, they hit zero and stay there.

3.  **Bias - Variance Tradeoff**:
    *   Same behavior as Ridge.
    *   $\lambda \uparrow \implies$ Bias $\uparrow$ (Underfitting), Variance $\downarrow$ (Simpler model).
    *   $\lambda \downarrow \implies$ Bias $\downarrow$, Variance $\uparrow$ (Overfitting).

<!-- 
IMAGE_PROMPT: 
Type: Comparison Plot
Description: 
- Left (Ridge): Coefficents approaching 0 asymptotically but never touching.
- Right (Lasso): Coefficients hitting 0 sharp and staying there.
Style: Educational.
-->

![Lasso vs Ridge Coefficients](assets/lasso_vs_ridge_coef_behavior.png)

---

### Python Implementation

```python
from sklearn.linear_model import Lasso

# standard scaling is MUST
lasso = Lasso(alpha=0.1)
lasso.fit(X_train_scaled, y_train)

print(f"Coefficients: {lasso.coef_}")

# Check how many are zero
import numpy as np
print(f"Features removed: {np.sum(lasso.coef_ == 0)}")
```

---

### Lasso vs Ridge (Summary)

| Feature | Ridge (L2) | Lasso (L1) |
| :--- | :--- | :--- |
| **Penalty** | Square ($\beta^2$) | Absolute ($|\beta|$) |
| **Zero Coefficients?** | No (Asymptotic) | **Yes (Exact 0)** |
| **Feature Selection** | No | **Yes** |
| **Outliers** | Squares error (sensitive) | Robust (due to absolute) |
| **Math** | Differentiable (Easy) | Not differentiable at 0 (Complex) |

### Interview Questions

**Q1: Why is Lasso used for Feature Selection?**
*   **Ans**: Because limiting the constraints creates a "diamond" shape constraint region (L1 ball) which often intersects the Loss contours at the axes (where coef = 0). Mathematically, the sub-gradient update allows the numerator to become completely zero.

**Q2: Which is better?**
*   **Ans**:
    *   Use **Ridge** if you think **all** features are somewhat useful (dense model).
    *   Use **Lasso** if you think **only a few** features are useful (sparse model).
