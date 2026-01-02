# Elastic Net Regression

> **Definition**: A hybrid regularization technique that combines both **L1 (Lasso)** and **L2 (Ridge)** penalties. It tries to get the best of both worlds: the feature selection of Lasso and the stability/handling of multicollinearity of Ridge.

### Mathematical Formulation

#### The Loss Function (User's Notation)
$$ \text{Loss} = \text{MSE} + a ||w||^2 + b ||w|| $$
*   Here, we have two separate penalties:
    *   $a ||w||^2$: The **Ridge** (L2) part.
    *   $b ||w||$: The **Lasso** (L1) part.

#### Scikit-Learn Mapping (Important)
In libraries like Sklearn, we don't pick $a$ and $b$ separately. We control them using:
1.  **Lambda ($\alpha$)**: The Total Penalty Magnitude ($a + b$).
2.  **L1 Ratio**: The mix percentage.

$$ \alpha = a + b $$
$$ \text{l1\_ratio} = \frac{\text{L1 part}}{\text{Total}} $$

*   If `l1_ratio` = 1 $\rightarrow$ Pure **Lasso** (L1).
*   If `l1_ratio` = 0 $\rightarrow$ Pure **Ridge** (L2).
*   If `l1_ratio` = 0.5 $\rightarrow$ Half Ridge, Half Lasso.

---

### When to use Elastic Net?
1.  **Middle Ground**: When you want feature selection (Lasso) but Lasso is fluctuating too much or removing too many features.
2.  **Multicollinearity**:
    *   **Ridge**: Handles correlated features well (shrinks them together).
    *   **Lasso**: Randomly picks one and sets others to 0 (unstable).
    *   **Elastic Net**: Groups correlated features and selects/shrinks them together. It fixes Lasso's instability using Ridge's L2 term.

---

### Python Implementation

We can implement this using the specific `ElasticNet` class OR the general `SGDRegressor`.

```python
from sklearn.linear_model import ElasticNet, SGDRegressor

# 1. Using ElasticNet Class
# alpha = lambda (Total penalty)
# l1_ratio = mix (1 = Lasso, 0 = Ridge)
enet = ElasticNet(alpha=0.1, l1_ratio=0.5)
enet.fit(X_train_scaled, y_train)

print(f"Coefficients: {enet.coef_}")

# 2. Using SGDRegressor
# This is preferred for LARGE datasets
sgd = SGDRegressor(
    loss='squared_error',
    penalty='elasticnet',
    alpha=0.01,
    l1_ratio=0.15
)
sgd.fit(X_train_scaled, y_train)
```

### Summary Table

| Model | Penalty | Sklearn Class | Use Case |
| :--- | :--- | :--- | :--- |
| **Ridge** | L2 ($w^2$) | `Ridge` | Prevent Overfitting, Correlated Inputs |
| **Lasso** | L1 ($\|w\|$) | `Lasso` | Feature Selection, Sparse solutions |
| **Elastic Net** | L1 + L2 | `ElasticNet` | "Best of both", correlated feature selection |

---

### Interview Questions

**Q1: In Sklearn, if I set `l1_ratio` to 0.1, what does it mean?**
*   **Ans**: It means the penalty is **10% Lasso (L1)** and **90% Ridge (L2)**. The model will behave mostly like Ridge but with a small tendency to set very weak coefficients to zero.

**Q2: Why use Elastic Net instead of just Lasso?**
*   **Ans**: Lasso can be erratic when features are highly correlated (it arbitrarily selects one). Elastic Net includes the L2 term which encourages "grouping effect"—keeping correlated features together rather than suppressing all but one.
