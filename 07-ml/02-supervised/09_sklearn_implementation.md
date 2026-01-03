# Scikit-Learn Implementation Guide (Topics 01-08)

This chapter focuses on the **practical implementation** of the Linear Regression family using `sklearn`.

---

### 1. Ordinary Least Squares (OLS)
**Class**: `sklearn.linear_model.LinearRegression`
Used for Simple and Multiple Linear Regression. Solves using the Closed Form solution (Normal Equation).

```python
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
import pandas as pd

# Load Data
df = pd.read_csv('data.csv')
X = df[['cgpa', 'projects', 'iq']] # Multiple features
y = df['package']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Initialize & Train
model = LinearRegression(fit_intercept=True, n_jobs=-1)
model.fit(X_train, y_train)

# Predictions
y_pred = model.predict(X_test)

# Key Attributes/Results
print(f"Beta_0 (Intercept): {model.intercept_}")
print(f"Beta_1...n (Coefficients): {model.coef_}")
```

#### Important Parameters
*   `fit_intercept` (bool, default=`True`): Whether to calculate the intercept $\beta_0$. If set to False, model assumes data is centered (passes through origin).
*   `n_jobs` (int, default=`None`): Number of CPU cores to use. `-1` means use all processors. Useful for huge datasets.

---

### 2. Gradient Descent Variations
**Class**: `sklearn.linear_model.SGDRegressor`
Used for Stochastic, Batch, and Mini-Batch Gradient Descent. Extremely efficient for large datasets.

```python
from sklearn.linear_model import SGDRegressor
from sklearn.preprocessing import StandardScaler

# IMPORTANT: SGD requires Scaled Data!
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# Initialize
sgd = SGDRegressor(
    loss='squared_error', 
    max_iter=1000, 
    learning_rate='invscaling', 
    eta0=0.01,
    random_state=42
)

sgd.fit(X_train_scaled, y_train)
```

#### Important Hyperparameters
*   `loss`: The loss function to minimize.
    *   `'squared_error'` (for Linear Regression/OLS).
    *   `'huber'` (Robust to outliers).
*   `penalty`: Regularization term (`'l2'`, `'l1'`, `'elasticnet'`). Default is `'l2'`.
*   `alpha`: Constant that multiplies the regularization term (Regularization strength).
*   `learning_rate`: Strategy for the learning rate schedule.
    *   `'constant'`: Fixed $\alpha$.
    *   `'invscaling'`: Gradually decreases (Default).
    *   `'adaptive'`: Keeps constant as long as loss decreases, reduces if stuck.
*   `eta0`: The initial learning rate.
*   `max_iter`: Maximum number of epochs (passes over data).
*   `tol`: Tolerance. The stopping criterion. If loss improves by less than `tol`, training stops (Convergence).

#### Implementing Variations
1.  **Stochastic GD**: `SGDRegressor(learning_rate='constant', eta0=0.01)` calls `fit()`.
2.  **Batch GD**: Not directly supported optimally by SGDRegressor (logic is iterative), but `LinearRegression` is preferred for Batch OLS.
3.  **Mini-Batch GD**: Use `partial_fit()`.
    ```python
    sgd = SGDRegressor()
    for i in range(epochs):
        X_batch, y_batch = next_batch(X_train, y_train)
        sgd.partial_fit(X_batch, y_batch)
    ```

---

### 3. Polynomial Regression
**Class**: `sklearn.preprocessing.PolynomialFeatures`
Used to transform data for non-linear fitting.

```python
from sklearn.preprocessing import PolynomialFeatures
from sklearn.pipeline import Pipeline

# Pipeline ensures clean workflow
poly_model = Pipeline([
    ('poly', PolynomialFeatures(degree=2, include_bias=False)),
    ('scaler', StandardScaler()),
    ('model', LinearRegression())
])

poly_model.fit(X_train, y_train)
```

#### Important Parameters
*   `degree` (int): The degree of polynomial features.
*   `interaction_only` (bool): If True, only produces interaction features ($x_1x_2$) and no powers ($x_1^2$).
*   `include_bias` (bool): If True (default), adds a column of 1s (Interceptor). Usually set to `False` if the model (`LinearRegression`) allows `fit_intercept=True`.

---

### Key Notes for Interview

*   **Scaling**: `LinearRegression` (OLS) doesn't strictly need scaling, but `SGDRegressor` **absolutely requires** standard scaling (StandardScaler) for convergence.
*   **Determinism**: `LinearRegression` is deterministic (always same result). `SGDRegressor` is non-deterministic (randomness involved) unless `random_state` is fixed.
*   **Pipeline**: Always use `Pipeline` to prevent Data Leakage (fitting scaler on train+test).

---

### Interview Questions

**Q1: What is the difference between `fit()` and `partial_fit()` in Sklearn?**
*   **Ans**:
    *   `fit(X, y)`: Loads the **entire** dataset into RAM and trains the model from scratch. Used for Batch/Standard training.
    *   `partial_fit(X, y)`: Trains the model incrementally on a **batch** of data. It updates existing weights without resetting them. Used for Mini-Batch GD or Out-of-Core learning (data too big for RAM).

**Q2: Why do we need `StandardScaler` before `SGDRegressor`?**
*   **Ans**: Gradient Descent follows the steepest slope. If features have different scales (e.g., CGPA [0-10] vs Salary [0-100k]), the loss function becomes an elongated ellipse. GD will take small steps in one direction and wild steps in another, taking forever to converge. Scaling makes the loss function spherical, ensuring fast symmetric convergence.

**Q3: What does the `tol` parameter do?**
*   **Ans**: It stands for **Tolerance**. It is the stopping criterion. If the improvement in loss (cost) between two iterations is less than `tol` (e.g., $1e-3$), the model assumes it has converged and stops training early, even if `max_iter` isn't reached.

**Q4: In `PolynomialFeatures`, what is `interaction_only=True`?**
*   **Ans**: It generates only the product of distinct features (e.g., $x_1x_2, x_1x_3$) but excludes the power terms ($x_1^2, x_2^2$). Useful if we believe features interact but don't have individual non-linear curves.
