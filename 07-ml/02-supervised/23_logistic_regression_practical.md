# Logistic Regression: Practical Implementation & Hyperparameters

> **Goal**: Mastering the Scikit-Learn `LogisticRegression` class, understanding every parameter, and building a production-ready pipeline.

### 1. The Core Implementation Workflow
In the real world, we rarely write Gradient Descent from scratch. We use `sklearn`.

```python
import numpy as np
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report

# 1. Load Data
data = load_breast_cancer()
X, y = data.data, data.target

# 2. Split (Always before scaling!)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 3. Scaling (MANDATORY for Logistic Regression)
# Why? Because Gradient Descent converges faster on scaled data.
# Also, 'C' (Regularization) assumes features are on the same scale.
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 4. Train Model
model = LogisticRegression(C=1.0, solver='lbfgs', max_iter=1000)
model.fit(X_train_scaled, y_train)

# 5. Evaluate
y_pred = model.predict(X_test_scaled)
print(classification_report(y_test, y_pred))
```

---

### 2. Deep Dive: Hyperparameters
The `LogisticRegression` constructor has many arguments. Here are the critical ones.

#### A. Regularization: `penalty` and `C`
This controls Overfitting vs Underfitting.

*   **`penalty`**: Type of regularization.
    *   `'l2'` (Default): Ridge. Shrinks coefficients (good for multicollinearity).
    *   `'l1'`: Lasso. Sets some coefficients to 0 (Feature Selection).
    *   `'elasticnet'`: Mix of both.
    *   `'none'`: No regularization (Standard OLS equivalent).
*   **`C`**: **Inverse** of Regularization Strength ($C = \frac{1}{\lambda}$).
    *   **High C** (e.g., 100): **Weak** Regularization. Trusts the training data more. Risk of **Overfitting**.
    *   **Low C** (e.g., 0.01): **Strong** Regularization. Constrains the weights. Risk of **Underfitting** (High Bias), but better generalization if noise is high.

> **Rule of Thumb**: Start with default `C=1.0`. If overfitting (Train >> Test), decrease C (0.1, 0.01). If underfitting, increase C.

#### B. The Solver: `solver`
The algorithm used to minimize the Loss Function.
*   **`'lbfgs'`** (Default): Robust, standard choice. Good for most cases.
*   **`'liblinear'`**: Good for **Small Datasets**. Supports `'l1'` penalty.
*   **`'sag'` / `'saga'`**: Stochastic Average Gradient. **Faster for Large Datasets**. `'saga'` supports ElasticNet.

| Solver | L1? | L2? | Multiclass? | Best For... |
| :--- | :--- | :--- | :--- | :--- |
| `lbfgs` | No | Yes | Multinomial | General Purpose |
| `liblinear` | Yes | Yes | OVR | Small Data |
| `saga` | Yes | Yes | Multinomial | Huge Data |

#### C. Handling Imbalance: `class_weight`
*   **Default** (`None`): Assumes classes are equal.
*   **`'balanced'`**: Automatically adjusts weights inversely proportional to class frequencies.
    *   If Class 0 (95%) and Class 1 (5%):
    *   Model makes the "Loss" for misclassifying Class 1 **19x higher**.
    *   Essential for Fraud Detection / Disease Prediction.

#### D. Multiclass: `multi_class`
*   `'auto'` (Default): Selects automatically.
*   `'ovr'`: One-vs-Rest (Binary scheme).
*   `'multinomial'`: Softmax Regression (True probability distribution).

---

### 3. Interview Questions on Implementation

**Q1: Why did scaling make such a big difference?**
*   **Ans**: Logistic Regression uses Gradient Descent. If one feature ranges 0-1 and another 0-1000, the gradients will be skewed (elliptical contours), making convergence slow. Regularization (L1/L2) also penalizes large weights uniformly, so features must be on the same scale for fair penalty.

**Q2: I have 1 Million rows. Which solver should I use?**
*   **Ans**: Use `'saga'`. Standard `'lbfgs'` calculates the gradient over the *entire* dataset each step, which is slow. `'saga'` is an incremental (stochastic) method optimized for speed.

**Q3: How do I tune `C`?**
*   **Ans**: Use `GridSearchCV`. Try values on a logarithmic scale: `[0.001, 0.01, 0.1, 1, 10, 100]`.
