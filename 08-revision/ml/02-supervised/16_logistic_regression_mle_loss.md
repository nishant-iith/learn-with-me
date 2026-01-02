# Logistic Regression: Loss Function & Derivation

> **Topic 16**: From Intuition to the "Actual" Mathematical Model.

### 1. Deriving the Loss Function (MLE)
We want to finding coefficients that **maximize** the probability of correct classification.
*   **Likelihood**: The product of probabilities for all data points.
    $$ L = P(y_1|\hat{y}_1) \times P(y_2|\hat{y}_2) \times \dots \times P(y_n|\hat{y}_n) $$
*   **Problem**: Multiplying decimals ($0.9 \times 0.8 \dots$) leads to underflow (tiny numbers).
*   **Solution**: Take the **Log** of the likelihood.
    $$ \log(L) = \sum \log(\text{Probability}) $$

### 2. Binary Cross Entropy (Log Loss)
Since we want a **Loss Function** (to minimize), we take the **Negative** of the Log Likelihood.

**The Formula**:
For a single point $i$:
$$ Loss_i = - [ y_i \log(\hat{y}_i) + (1 - y_i) \log(1 - \hat{y}_i) ] $$

*   **Case 1 ($y_i = 1$)**: term becomes $-1 \cdot \log(\hat{y}_i)$. We want $\hat{y}$ close to 1 (so $\log(1)=0$ error).
*   **Case 2 ($y_i = 0$)**: term becomes $-1 \cdot \log(1 - \hat{y}_i)$. We want $\hat{y}$ close to 0 (so $1-\hat{y}=1 \implies$ error 0).

**Average Cost Function**:
$$ J(w) = - \frac{1}{m} \sum_{i=1}^{m} [ y_i \log(\hat{y}_i) + (1-y_i) \log(1 - \hat{y}_i) ] $$

---

### 3. Optimization Strategy
*   **Linear Regression**: Had a "Closed Form" solution (OLS) because the derivative was linear.
*   **Logistic Regression**: The equation is non-linear (due to Sigmoid). **There is NO closed-form solution.**
*   **Solution**: We MUST use **Gradient Descent**.

---

### 4. Prerequisite: Derivative of Sigmoid
To perform Gradient Descent, we need to differentiate the Sigmoid function.

$$ \sigma(z) = \frac{1}{1 + e^{-z}} = (1 + e^{-z})^{-1} $$

**Derivation** (Chain Rule):
1.  Apply power rule: $-(1 + e^{-z})^{-2}$
2.  Multiply by derivative of inside ($-e^{-z}$):
    $$ \frac{d\sigma}{dz} = \frac{e^{-z}}{(1 + e^{-z})^2} $$
3.  **The Magic Trick** (Algebraic manipulation):
    $$ = \frac{1}{1 + e^{-z}} \cdot \frac{e^{-z}}{1 + e^{-z}} $$
    $$ = \sigma(z) \cdot \left( \frac{1 + e^{-z} - 1}{1 + e^{-z}} \right) $$
    $$ = \sigma(z) \cdot \left( \frac{1 + e^{-z}}{1 + e^{-z}} - \frac{1}{1 + e^{-z}} \right) $$
    $$ = \sigma(z) ( 1 - \sigma(z) ) $$

> **Result**: $\sigma'(z) = \sigma(z) (1 - \sigma(z))$
> This beautiful property makes gradient calculations very clean!

<!-- 
IMAGE_PROMPT: 
Type: Line Chart
Description: 
- X-axis: Input z (-5 to 5).
- Curve 1: Sigmoid Function (S-shape, 0 to 1).
- Curve 2: Derivative of Sigmoid (Bell shape, max value 0.25 at z=0).
- Highlight that Gradient is highest near the decision boundary (0) and vanishes at extremes.
Style: Mathematical Calculation Graph.
-->

> **Next**: Applying Gradient Descent to Logistic Regression.
