# Regression Metrics

To evaluate how good our model is, we need metrics.

#### 1. Mean Absolute Error (MAE)
$$MAE = \frac{1}{n} \sum |y_i - \hat{y}_i|$$

*   **Advantage**:
    *   Same units as the target variable (e.g., if target is salary in $, MAE is in $).
    *   **Robust to outliers** (doesn't penalize them heavily).
*   **Disadvantage**:
    *   Graph is **non-differentiable** at 0 (V-shape), making it tricky for some optimization algorithms.

<!-- 
IMAGE_PROMPT: 
Type: 2D Plot (Conceptual)
Description: 
- A scatter plot with a Best Fit Line.
- Highlight the vertical distance (residuals) between a few points and the line using dotted lines.
- Label one dotted line as "Error".
- Annotation: "MAE = Average of absolute lengths".
Style: Chalkboard or dark mode technical style.
-->

#### 2. Mean Squared Error (MSE)
$$MSE = \frac{1}{n} \sum (y_i - \hat{y}_i)^2$$

*   **Advantage**:
    *   **Differentiable** everywhere (smooth curve), great for loss functions.
*   **Disadvantage**:
    *   **Different units** (Target unit squared).
    *   **Penalizes outliers** heavily (squaring a large error makes it huge). Not robust to outliers.

<!-- 
IMAGE_PROMPT: 
Type: 2D Plot (Conceptual)
Description: 
- Similar scatter plot with Best Fit Line.
- Instead of just lines, show SQUARES formed by the residual length for a few points.
- Some squares are small, one outlier has a HUGE square.
- Annotation: "MSE = Average area of these squares".
Style: Geometric validation style.
-->

#### 3. Root Mean Squared Error (RMSE)
$$RMSE = \sqrt{MSE} = \sqrt{\frac{1}{n} \sum (y_i - \hat{y}_i)^2}$$

*   **Advantage**: Same units as $y$ (like MAE), but still penalizes outliers (like MSE).
*   **Disadvantage**: Still sensitive to outliers.

#### 4. R2 Score (Coefficient of Determination)
Tells us **how much better** our model is compared to a simple "Mean Line" (worst case prediction).

$$R^2 = 1 - \frac{SSR}{SSM} = 1 - \frac{\sum(y_i - \hat{y}_i)^2}{\sum(y_i - \bar{y})^2}$$

*   **Interpretation**:
    *   $R^2 = 1$: Perfect model.
    *   $R^2 = 0$: Same as predicting the mean (bad).
    *   $R^2 < 0$: Worse than predicting the mean (terrible).
    *   *Example*: $R^2 = 0.8$ means "CGPA explains 80% of the variance in Package".

#### 5. Adjusted R2
Problem with $R^2$: It **never decreases** when you add more features, even if they are useless (e.g., "Favorite Color" to predict "Package").

$$R^2_{adj} = 1 - \frac{(1-R^2)(n-1)}{n-1-k}$$
*   $n$: Number of rows (samples).
*   $k$: Number of columns (features).

*   **Logic**:
    *   If you add a **good feature**: $R^2 \uparrow$ significantly, so $R^2_{adj} \uparrow$.
    *   If you add a **bad feature**: $R^2$ stays same or $\uparrow$ slightly, but penalty for $k \uparrow$ makes $R^2_{adj} \downarrow$.
*   **Use**: Always use Adjusted R2 for **Multiple** Linear Regression feature selection.

### Python Implementation (From Scratch)

```python
import numpy as np

def regression_metrics(y_true, y_pred, n, k):
    # MAE
    mae = np.mean(np.abs(y_true - y_pred))
    
    # MSE
    mse = np.mean((y_true - y_pred)**2)
    
    # RMSE
    rmse = np.sqrt(mse)
    
    # R2 Score
    ss_res = np.sum((y_true - y_pred)**2) # Sum of Squared Residuals (Error)
    ss_tot = np.sum((y_true - np.mean(y_true))**2) # Sum of Squared Total (Variance)
    r2 = 1 - (ss_res / ss_tot)
    
    # Adjusted R2
    r2_adj = 1 - ((1 - r2) * (n - 1) / (n - 1 - k))
    
    return {
        "MAE": mae, "MSE": mse, "RMSE": rmse, 
        "R2": r2, "Adj_R2": r2_adj
    }
```

---

### Interview Questions

**Q1: MSE vs MAE - When to use which?**
*   **Ans**:
    *   **Use MSE**: When you want to **penalize large errors** heavily (e.g., in healthcare or finance where a big mistake is catastrophic) and need a differentiable loss function.
    *   **Use MAE**: When your data has **many outliers** that are valid data points (e.g., salary data) and you don't want them to skew the model too much.

**Q2: Can R2 Score be negative?**
*   **Ans**: Yes.
*   **Follow-up**: What does it mean?
    *   **Ans**: It means the model is **worse than a simple horizontal line** (predicting the mean of data). The model is finding patterns that don't satisfy the basic variance of the data (likely Overfitting heavily or using wrong model).

**Q3: Why is Adjusted R2 preferred over R2 in Multiple Linear Regression?**
*   **Ans**: Normal $R^2$ **never decreases** when you add a new feature, even if it's random noise. This gives a false sense of improvement.
*   **Follow-up**: How does Adjusted R2 fix this?
    *   **Ans**: It adds a **penalty term** $\frac{n-1}{n-1-k}$ that decreases the score if $k$ (number of features) increases without a significant increase in captured variance ($R^2$).

**Q4: What is the range of R2 score?**
*   **Ans**: $(-\infty, 1]$.
    *   $1$ = Perfect prediction.
    *   $0$ = Baseline model (predicting mean).
    *   Negative = Worse than baseline.

**Q5: Which metric is robust to outliers?**
*   **Ans**: **MAE (Mean Absolute Error)**. Since it doesn't square the error terms, a large deviation contributes linearly to the total error, not exponentially.
