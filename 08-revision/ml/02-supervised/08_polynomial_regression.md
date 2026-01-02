# Polynomial Regression

> **Definition**: A form of regression analysis in which the relationship between the independent variable $x$ and the dependent variable $y$ is modeled as an $n$-th degree polynomial.

### The Core Idea
*   **Problem**: What if data is non-linear? (e.g., a curved pattern like a parabola). A straight line ($y=mx+c$) will underfit.
*   **Solution**: We do **not** change the Linear Regression algorithm. Instead, we **change the data**.
*   **Transformation**: We generate new features by raising existing features to a power ($x^1, x^2, x^3...$).

### The Equation (Why is it still "Linear"?)
For a single feature $x_1$ with degree 2:
$$ y = \beta_0 + \beta_1 x_1 + \beta_2 x_1^2 $$

This looks non-linear w.r.t $x$, but it is **Linear w.r.t Coefficients ($\beta$)**.
*   Let $x_1 = A$
*   Let $x_1^2 = B$
*   Equation becomes: $y = \beta_0 + \beta_1 A + \beta_2 B$ (Standard Multiple Linear Regression).

**For 2 Features ($x_1, x_2$) with Degree 2**:
It includes interaction terms as well:
$$ y = \beta_0 + \beta_1 x_1 + \beta_2 x_1^2 + \beta_3 x_2 + \beta_4 x_2^2 + \beta_5 (x_1 x_2) $$

---

### Degree: The Hyperparameter
The "Degree" of the polynomial determines the flexibility of the curve.

*   **Degree 1 (Linear)**: Straight line.
    *   *Risk*: **Underfitting** (High Bias). Cannot capture complex patterns.
*   **Degree 2-3 (Polynomial)**: Curved line.
    *   *Result*: Good fit for curved data.
*   **Degree 50 (High Degree)**: Extremely wiggly curve passing through every single point.
    *   *Risk*: **Overfitting** (High Variance). Memorizes noise.

<!-- 
IMAGE_PROMPT: 
Type: 3D/2D Comparison
Description: 
- 3 plots side-by-side.
- Plot 1 (Degree 1): Straight line cutting through a curve (Underfit).
- Plot 2 (Degree 2): Parabola fitting the curve perfectly (Good Fit).
- Plot 3 (Degree 20): Squiggly line changing direction wildly to hit every point (Overfit).
Style: Educational comparison.
-->

![Polynomial Degrees Comparison](assets/polynomial_degrees_comparison.png)

---

### Python Implementation (Scikit-Learn)

We use `PolynomialFeatures` to transform the data, then feed it to `LinearRegression`.

```python
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.pipeline import Pipeline
import numpy as np

# 1. Create Data (Non-linear)
X = np.array([1, 2, 3, 4, 5]).reshape(-1, 1)
y = np.array([1, 4, 9, 16, 25]) # y = x^2

# 2. Polynomial Transformation
# degree=2 will create [1, x, x^2]
poly = PolynomialFeatures(degree=2, include_bias=False)
X_poly = poly.fit_transform(X)

print(f"Original X: {X.tolist()}")
print(f"Transformed X: {X_poly.tolist()}") 
# Output: [[1, 1], [2, 4], [3, 9]...] i.e., [x, x^2]

# 3. Fit Linear Regression on Transformed Data
model = LinearRegression()
model.fit(X_poly, y)

# Or better, use a Pipeline
pipe = Pipeline([
    ('poly', PolynomialFeatures(degree=2)),
    ('model', LinearRegression())
])
pipe.fit(X, y)
```

---

### Interview Questions

**Q1: Is Polynomial Regression a linear or non-linear model?**
*   **Ans**: It is a **Linear Model**. It is linear in terms of the *parameters* (coefficients $\beta$), even though it models non-linear relationships with respect to the input variables $x$.

**Q2: What happens if you choose a very high degree polynomial?**
*   **Ans**: The model will **Overfit**. It will learn the noise in the training data, leading to a complex "wiggly" boundary that fails to generalize to test data (High Variance).

**Q3: Does feature scaling matter in Polynomial Regression?**
*   **Ans**: **Yes, absolutely**. When you square or cube features (e.g., $x=1000 \rightarrow x^2=1,000,000$), the range of values explodes. Optimization algorithms like Gradient Descent will struggle to converge. Always normalize/standardize data when using Polynomial Regression.
