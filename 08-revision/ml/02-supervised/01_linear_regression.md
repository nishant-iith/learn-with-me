# Linear Regression

> **Definition**: A supervised learning algorithm used for regression problems where the goal is to predict a continuous output (dependent variable) based on one or more input features (independent variables).

### Types of Linear Regression
*   **Simple Linear Regression**: One input variable $\rightarrow$ One output variable.
    *   *Example*: `CGPA` $\rightarrow$ `Package`.
*   **Multiple Linear Regression**: Multiple input variables $\rightarrow$ One output variable.
    *   *Example*: `CGPA`, `Projects`, `Internships` $\rightarrow$ `Package`.
*   **Polynomial Linear Regression**: For non-linear data patterns (fits a curve).
*   **Regularization**: Techniques to prevent overfitting (Lasso, Ridge).

<!-- 
IMAGE_PROMPT: 
Type: Flowchart / Tree Diagram
Description: A hierarchical tree diagram showing 'Linear Regression' at the root. Branches: 
1. Simple LR (1 input/1 output)
2. Multiple LR (Multiple input/1 output)
3. Polynomial LR (Non-linear data)
4. Regularization (Overfitting prevention)
Style: Minimalist, professional, dark mode friendly.
-->

---

### Intuition (Simple LR)

The core idea is to find the **Best Fit Line** that passes through the data points with minimal error.

**Equation**:
$$y = mx + c$$

In our context (CPGA vs Package):
$$\text{Package} = m \times \text{CGPA} + c$$

*   **$y$ (Target)**: The value we want to predict (e.g., Package).
*   **$x$ (Feature)**: The input we have (e.g., CGPA).
*   **$m$ (Slope/Weightage)**: How much the input affects the output.
    *   *Intuition*: Weightage of CGPA on Package.
*   **$c$ (Intercept/Offset)**: The value of $y$ when $x$ is 0.
    *   *Intuition*: Base package even if CGPA is lower (or theoretical baseline).

<!-- 
IMAGE_PROMPT: 
Type: 2D Plot
Description: A scatter plot showing 'CGPA' on X-axis and 'Package' on Y-axis. 
- Plot random scattered data points moving upwards.
- Draw a distinct straight line passing through the center of points (Best Fit Line).
- Label the line 'Best Fit Line'.
- Label the equation 'y = mx + c' pointing to the line.
- Highlight the intercept 'c' on the Y-axis.
Style: Hand-drawn style or clean technical plot.
-->

---

### How to find $m$ (Slope) and $c$ (Intercept)?

There are two main approaches to find the optimal $m$ and $c$:

1.  **Closed-Form Solution (Direct Formula)**
    *   Uses a direct mathematical formula to calculate specific values.
    *   **Method**: **OLS (Ordinary Least Squares)**.
    *   **Library**: Used by `sklearn.linear_model.LinearRegression`.
    *   **Formula**:
        $$m = \frac{\sum (x_i - \bar{x})(y_i - \bar{y})}{\sum (x_i - \bar{x})^2}$$
        $$c = \bar{y} - m\bar{x}$$

2.  **Non-Closed Form Solution (Iterative)**
    *   Uses an optimization algorithm to approximate values step-by-step step.
    *   **Method**: **Gradient Descent**.
    *   **Library**: Used by `SGDRegressor`.

---

### Implementation from Scratch (Math Behind OLS)

How do we derive the formula for the best line? By minimizing the error.

#### 1. Define the Error ($E$)
For any single data point, the error is the difference between actual value ($y_i$) and predicted value ($\hat{y}_i$).
$$d_i = y_i - \hat{y}_i$$
$$d_i = y_i - (mx_i + c)$$

#### 2. Define the Loss Function ($J$)
We cannot just sum $d_i$ because positive and negative errors might cancel each other out.
*   *Solution*: Square the errors (punishes outliers more & removes negative signs).
*   **Loss Function (Sum of Squared Errors)**:
    $$J = \sum_{i=1}^{n} d_i^2 = \sum_{i=1}^{n} (y_i - \hat{y}_i)^2$$
    $$J(m, c) = \sum_{i=1}^{n} (y_i - (mx_i + c))^2$$

> **Goal**: We want to **minimize** $J(m, c)$. We need to find $m$ and $c$ where $J$ is lowest.

<!-- 
IMAGE_PROMPT: 
Type: 3D Surface Plot / 2D Curve
Description: 
- A 3D bowl-shaped curve (convex function) representing the Loss Function J.
- X and Y axes are 'm' and 'c'. Z axis is 'Error (J)'.
- Show a point at the very bottom of the bowl labeled 'Global Minima' (Best m & c).
- Alternatively, a Simple 2D parabola with 'Loss J' on Y-axis and 'm' on X-axis, showing a minimum point.
Style: Mathematical visualization.
-->

#### 3. Minimize Loss (Differentiation)
To find the minima of a curve, we take the derivative (slope) and set it to 0. Since $J$ depends on both $m$ and $c$, we take **partial derivatives**.

**Step A: Derivative w.r.t $c$**
$$\frac{\partial J}{\partial c} = \frac{\partial}{\partial c} \sum (y_i - mx_i - c)^2 = 0$$
Using Chain Rule:
$$\sum 2(y_i - mx_i - c)(-1) = 0$$
$$-2 \sum (y_i - mx_i - c) = 0$$
$$\sum y_i - m \sum x_i - \sum c = 0$$
$$\sum y_i - m \sum x_i - nc = 0$$ (Since $\sum_{1}^{n} c = nc$)
$$nc = \sum y_i - m \sum x_i$$
$$c = \frac{\sum y_i}{n} - m \frac{\sum x_i}{n}$$
$$c = \bar{y} - m\bar{x}$$  **(Equation 1)**

**Step B: Derivative w.r.t $m$**
$$\frac{\partial J}{\partial m} = \frac{\partial}{\partial m} \sum (y_i - mx_i - c)^2 = 0$$
$$\sum 2(y_i - mx_i - c)(-x_i) = 0$$
$$-2 \sum x_i(y_i - mx_i - c) = 0$$
$$\sum (x_iy_i - mx_i^2 - cx_i) = 0$$
$$\sum x_iy_i - m \sum x_i^2 - c \sum x_i = 0$$

Substitute $c = \bar{y} - m\bar{x}$:
$$\sum x_iy_i - m \sum x_i^2 - (\bar{y} - m\bar{x}) \sum x_i = 0$$
... *Solving this algebra leads to the final OLS formula:* ...

$$m = \frac{\sum (x_i - \bar{x})(y_i - \bar{y})}{\sum (x_i - \bar{x})^2}$$

---

### Interview Questions

**Q1: What are the key assumptions of Linear Regression?**
*   **Ans**:
    1.  **Linearity**: Relationship between $X$ and $Y$ is linear.
    2.  **Independence**: Observations are independent of each other.
    3.  **Homoscedasticity**: Constant variance of errors (residuals) across all levels of $X$.
    4.  **Normality**: Residuals are normally distributed.
    5.  **No Multicollinearity**: Independent variables are not highly correlated with each other.
*   **Follow-up**: What happens if Multicollinearity exists?
    *   **Ans**: The model becomes unstable. Coefficients ($m$) can swing wildly with small data changes, making interpretation difficult (though predictions might still be accurate).

**Q2: What is the difference between Simple and Multiple Linear Regression?**
*   **Ans**: Simple LR has **one** independent variable ($y=mx+c$), while Multiple LR has **two or more** independent variables ($y=b_0 + b_1x_1 + b_2x_2 + ...$).

**Q3: Why do we square the residuals (errors) in OLS ($y_{actual} - y_{pred}$)?**
*   **Ans**:
    1.  To ensure positive and negative errors don't cancel each other out.
    2.  To penalize larger errors more heavily (squaring makes large numbers much larger).
    3.  It makes the function differentiable (smooth convex curve), which is required for optimization algorithms like Gradient Descent.
*   **Follow-up**: Why not use absolute values ($|y - \hat{y}|$)?
    *   **Ans**: Absolute value function ($|x|$) has a sharp "V" shape at 0, making it **non-differentiable** at that point. Squared error is smooth and differentiable everywhere.

**Q4: Is OLS good for large datasets?**
*   **Ans**: Not always. OLS involves matrix operations (Matrix Inversion) that can be computationally expensive ($O(n^3)$) for very large datasets.
*   **Follow-up**: What do we use instead?
    *   **Ans**: **Gradient Descent** (iterative approach). It approximates the solution step-by-step and is much more memory/compute efficient for massive data.

**Q5: What if there are outliers in the data?**
*   **Ans**: Linear Regression is sensitive to outliers because of the **squared error** term in the loss function. A single far-off point can pull the best-fit line drastically.
*   **Follow-up**: How to handle them?
    *   **Ans**:
        1.  Remove outliers using Z-score or IQR.
        2.  Use **Robust Regression** techniques (like Huber Loss) which are less sensitive to outliers.
        3.  Use MAE (Mean Absolute Error) based loss instead of MSE if differentiability isn't a blocker.
