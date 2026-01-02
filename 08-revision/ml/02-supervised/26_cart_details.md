# CART: Classification and Regression Trees

> **Goal**: A deep dive into the **CART** algorithm, covering its specific mechanics for Classification vs Regression, computational complexity, and advantages.

---

### 1. The CART Philosophy
**CART** (Classification And Regression Trees) is the specific algorithm implemented in Scikit-Learn.
*   **Strictly Binary**: CART *always* splits a node into **exactly two** children (Yes/No).
    *   *Contrast*: **ID3/C4.5** can split into multiple branches (e.g., Color $\to$ Red, Green, Blue).
*   **Recursive Partitioning**: It greedily splits the data to simplify the problem at each step.

---

### 2. Classification Trees
**Goal**: Classify data into distinct categories (e.g., Spam vs Ham).

#### A. Splitting Criterion: "Purity"
How do we know if a split is good? We minimize **Impurity**.
*   **Gini Impurity** (Default):
    $$ \text{Gini} = 1 - \sum p_i^2 $$
    *   *Favors*: Large partitions. Faster to compute (no logs).
*   **Entropy** (Information Gain):
    $$ H = -\sum p_i \log_2 p_i $$
    *   *Favors*: Balanced partitions. Slower (logs).

#### B. Prediction Logic
*   **Leaf Node Output**: **Majority Vote** (Mode).
    *   Example: Node has [5 Spam, 1 Ham] $\to$ Predict **Spam**.
    *   **Probability**: The node also outputs probabilites (e.g., $P(\text{Spam}) = 5/6 = 0.83$).

---

### 3. Regression Trees
**Goal**: Predict a continuous value (e.g., House Price).

#### A. Splitting Criterion: "Error Reduction"
Since we can't calculate "Purity" for continuous numbers, we minimize **Error**.

1.  **MSE (Mean Squared Error)** - Default:
    $$ \text{MSE} = \frac{1}{n} \sum (y_i - \bar{y})^2 $$
    *   **Leaf Prediction**: The **Mean** ($\bar{y}$) of samples in the leaf.
    *   *Effect*: Standard solution, but sensitive to outliers (squaring penalizes large errors heavily).

2.  **MAE (Mean Absolute Error)**:
    $$ \text{MAE} = \frac{1}{n} \sum |y_i - \text{median}(y)| $$
    *   **Leaf Prediction**: The **Median** of samples in the leaf.
    *   *Effect*: **Robust to Outliers**. If you have one mansion worth \$100M, it won't skew the prediction as much as Mean would.

#### B. Geometry (The Step Function)
Regression trees result in a **Piecewise Constant** function.
*   $X < 5$? Predict $10$.
*   $X \ge 5$? Predict $20$.
*   This looks like a **Staircase** (Step Function), not a smooth line.

---

### 4. Comparison: Classification vs Regression

| Feature | **Classification Tree** | **Regression Tree** |
| :--- | :--- | :--- |
| **Output Type** | Discrete Class (Categories). | Continuous Number. |
| **Splitting Metric** | Gini Impurity or Entropy. | MSE (Variance) or MAE. |
| **Leaf Prediction** | **Class Mode** (Majority Vote). | **Sample Mean** (MSE) or **Median** (MAE). |
| **Performance** | Measures Accuracy, Precision/Recall. | Measures $R^2$ Score, RMSE. |

<!-- 
IMAGE_PROMPT: 
Type: Comparison Plot
Description: 
- Left (Classification): 2D Grid with Red/Blue regions. Labels "Gini".
- Right (Regression): 2D Grid showing a "Staircase" line fitting points. Labels "MSE".
Style: Clean Mathematical visualization.
-->

---

### 5. Computational Complexity
Is CART fast or slow?

*   **Training (Building)**: $O(N \cdot M \cdot \log N)$
    *   $N$: Samples, $M$: Features.
    *   Sorting numbers takes $N \log N$. We do this for every feature ($M$) at every depth.
*   **Prediction (Inference)**: $O(\text{Depth})$
    *   Very fast! Just traversing down the tree (e.g., 10-20 independent if-else checks).
    *   Much faster than KNN (which checks all points) or SVM (which calculates vector distance).

---

### 6. Code: All Scenarios

```python
from sklearn.tree import DecisionTreeClassifier, DecisionTreeRegressor

# --- SCENARIO 1: Classification (Standard) ---
# Uses Gini (Fast) and Majority Vote
clf = DecisionTreeClassifier(criterion='gini', max_depth=5)
# clf.fit(X_train, y_train)

# --- SCENARIO 2: Regression (Standard) ---
# Uses MSE and Mean Prediction
reg_mse = DecisionTreeRegressor(criterion='squared_error', max_depth=5)
# reg_mse.fit(X_train, y_train)

# --- SCENARIO 3: Regression with Outliers ---
# Uses MAE and Median Prediction (Robust)
reg_mae = DecisionTreeRegressor(criterion='absolute_error', max_depth=5)
# reg_mae.fit(X_train, y_train)
```

---

### 7. Interview Questions on CART details

**Q1: Why does Scikit-Learn only support Binary Splits?**
*   **Ans**: It simplifies the implementation and reduces Overfitting. Multi-way splits (e.g., splitting "State" into 50 branches) partitions data too quickly, leaving few samples per node. Binary splits achieve the same Result (State == 'CA'? State == 'NY'?) but more robustly.

**Q2: When would you choose MAE (Absolute Error) over MSE?**
*   **Ans**: When the data has **Outliers**. Squaring the error (MSE) penalizes outliers massively, pulling the mean prediction towards them. MAE uses the **Median**, which ignores extreme values.

**Q3: Can CART handle Missing Values?**
*   **Ans**: Theoretically, Yes (using Surrogate Splits - checking another correlated feature). Scikit-Learn's implementation currently **does not** support this natively (you must impute first), but algorithms like XGBoost do handle them automatically.
