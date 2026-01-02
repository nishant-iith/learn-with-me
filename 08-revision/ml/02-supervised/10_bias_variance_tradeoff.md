# Bias - Variance Trade-off

To understand why a model fails (Underfitting or Overfitting), we look at **Bias** and **Variance**.

### 1. Bias (Systematic Error)
> **Definition**: The inability of the model to capture the true relationship in the training data.

*   **High Bias**: The model is too simple (e.g., trying to fit a straight line to curved data).
*   **Result**: **Underfitting**.
*   **Symptoms**: High Error on Training Data AND High Error on Test Data. ($\text{Train Error} \approx \text{Test Error}$, both high).

### 2. Variance (Sensitivity)
> **Definition**: The sensitivity of the model to different training sets. How much the model changes if the training data changes slightly.

*   **High Variance**: The model is too complex (e.g., a wiggly line connecting every dot). It memorizes noise.
*   **Result**: **Overfitting**.
*   **Symptoms**: Low Error on Training Data BUT High Error on Test Data. ($\text{Train Error} < \text{Test Error}$).

---

### Visualizing the Trade-off

#### Model 1: High Bias | Low Variance (Underfitting)
*   **Analogy**: A student who studied nothing and guesses "C" for every answer.
*   **Behavior**: Consistent (Low Variance) but consistently wrong (High Bias).
*   **Graph**: A flat line through complex data.

#### Model 2: Low Bias | Low Variance (Good Fit)
*   **Analogy**: A student who studied concepts well.
*   **Behavior**: performs well on new questions.
*   **Graph**: A smooth curve capturing the trend.

#### Model 3: Low Bias | High Variance (Overfitting)
*   **Analogy**: A student who memorized the textbook word-for-word but doesn't understand concepts.
*   **Behavior**: aced the class test (Train) but fails the board exam (Test) because questions are slightly different.
*   **Graph**: A wild zig-zag line hitting every point.

<!-- 
IMAGE_PROMPT: 
Type: 3-Panel Plot
Description: 
- Panel 1 (Underfit): Straight line through curved points. Label: "High Bias".
- Panel 2 (Good Fit): Smooth curve through points. Label: "Balanced".
- Panel 3 (Overfit): Wiggly line hitting every point. Label: "High Variance".
Style: Dark educational theme.
-->

---

### How to Reduce Overfitting (High Variance)?

If your model is Overfitting (High Variance), you can use:

1.  **Bagging**: (Bootstrap Aggregating) e.g., Random Forest.
2.  **Boosting**: e.g., Gradient Boosting, XGBoost.
3.  **Regularization**: Constraining the model to keep it simple.
    *   **Ridge Regression**: Adds L2 Norm penalty.
    *   **Lasso Regression**: Adds L1 Norm penalty.
    *   **Elastic Net**: Adds (L1 + L2) penalty.

> **Next Topic**: We will deep dive into **Ridge Regularization** (L2) to fix overfitting in Linear Regression.
