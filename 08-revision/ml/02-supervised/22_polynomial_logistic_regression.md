# Polynomial Logistic Regression

> **Goal**: How to use a Linear Classifier (Logistic Regression) to solve **Non-Linear** problems.

### 1. The Limitation (Linearity)
Standard Logistic Regression creates a **Linear Decision Boundary** (a straight line/hyperplane).
$$ z = w_1 x_1 + w_2 x_2 + b $$

*   **Scenario**: If your data is shaped like a circle (e.g., Target inside, Non-target outside), a straight line cannot separate it well.
*   **Result**: High Bias (Underfitting). Accuracy might be capped (e.g., ~80%).

<!-- 
IMAGE_PROMPT: 
Type: Comparison Plot
Description: 
- Top: Complex dataset (moon/circle shape).
- Bottom Left: Linear Logistic Regression trying to cut it with a straight line (High Error).
- Bottom Right: Polynomial Logistic Regression fitting the curve perfectly.
Style: Data Science Visualization.
-->

---

### 2. The "Trick" (Feature Transformation)
We do NOT change the Logistic Regression algorithm.
Instead, we change the **Data**.

We create **Polynomial Features**:
$$ x \rightarrow [x^0, x^1, x^2, x^3, \dots] $$

**Why does this work?**
*   The model still sees a linear equation: $z = w_1 (x) + w_2 (x^2) + b$.
*   But in the *original* 2D space, $y = ax^2 + bx + c$ plots a **Parabola** (Curve).
*   By adding higher degrees ($x^3, x^4$), we can create complex shapes like circles, ellipses, and squiggles.

> **Note**: This allows us to jump from 80% accuracy to 90%+ on complex datasets.

---

### 3. Python Implementation (Pipeline)
The best way to do this is using a Scikit-Learn `Pipeline`.

```python
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LogisticRegression
from sklearn.pipeline import Pipeline

# 1. Create a Pipeline
# Step 1: Generate Polynomial Features (Degree 3)
# Step 2: Apply Logistic Regression
model = Pipeline([
    ('poly', PolynomialFeatures(degree=3)),
    ('log_reg', LogisticRegression())
])

# 2. Train
model.fit(X_train, y_train)

# 3. Predict produces Non-Linear Boundaries!
# The model effectively learns: w1*x + w2*x^2 + w3*x*y...
```

---

### 4. Critical Reality Check
> *"This is just a workaround. There are better approaches available."*

While this trick works, it has **downsides**:
1.  **Computation**: Features explode combinatorially. With many input features, $x^3$ generates huge number of columns.
2.  **Overfitting**: High degrees (e.g., degree=15) will wiggle and fit noise perfectly.
3.  **Better Alternatives**: Algorithms like **Decision Trees**, **SVM (Kernel Trick)**, and **Neural Networks** handle non-linearity natively and often better.
