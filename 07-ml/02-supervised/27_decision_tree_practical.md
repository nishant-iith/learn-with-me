# Decision Trees: Practical Implementation & Pruning

> **Goal**: Mastering the Scikit-Learn implementation, controlling Overfitting via Hyperparameters, and performing Post-Pruning.

---

### 1. Classification Workflow
**Scenario**: Predict if a patient has a disease (Binary Classification).

```python
import matplotlib.pyplot as plt
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier, plot_tree
from sklearn.metrics import accuracy_score, classification_report

# 1. Load Data
data = load_breast_cancer()
X, y = data.data, data.target

# 2. Split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 3. Initialize Model (Default = Fully Grown Tree = Overfitting Risk)
clf = DecisionTreeClassifier(criterion='gini', random_state=42)

# 4. Train
clf.fit(X_train, y_train)

# 5. Evaluate
y_pred = clf.predict(X_test)
print(classification_report(y_test, y_pred))

# 6. Visualize the Tree
plt.figure(figsize=(20,10))
plot_tree(clf, filled=True, feature_names=data.feature_names, class_names=data.target_names)
plt.show()
```

---

### 2. Regression Workflow
**Scenario**: Predict House Prices (Continuous Output).

```python
from sklearn.datasets import fetch_california_housing
from sklearn.tree import DecisionTreeRegressor
from sklearn.metrics import mean_squared_error, r2_score

# 1. Load & Split
housing = fetch_california_housing()
X_train, X_test, y_train, y_test = train_test_split(housing.data, housing.target, test_size=0.2)

# 2. Initialize Model (Minimizing Squared Error)
reg = DecisionTreeRegressor(criterion='squared_error', random_state=42)

# 3. Train
reg.fit(X_train, y_train)

# 4. Evaluate
y_pred = reg.predict(X_test)
print("MSE:", mean_squared_error(y_test, y_pred))
print("R2 Score:", r2_score(y_test, y_pred))
```

---

---

### 3. Overfitting vs Underfitting in Trees
Before tuning, we must identify the problem.

#### A. Overfitting (High Variance)
*   **Symptoms**: 100% Training Accuracy, but 70% Test Accuracy.
*   **Cause**: The Tree is too deep. It has memorized every noise point (e.g., a "Leaf" for just 1 person).
*   **Solution**: **Constraint** the tree growth (Max Depth, Min Samples).

#### B. Underfitting (High Bias)
*   **Symptoms**: 60% Training Accuracy, 60% Test Accuracy.
*   **Cause**: The Tree is too shallow (e.g., Depth=1). It fails to capture patterns.
*   **Solution**: **Relax** constraints (Increase Depth, Decrease Min Samples).

---

### 4. Hyperparameters (Pre-Pruning)
Decision Trees typically **Overfit** by growing until every leaf is pure (Depth 100+). We use **Pre-Pruning** parameters to stop growth early.

| Parameter | Meaning | Recommended Tuning |
| :--- | :--- | :--- |
| `max_depth` | Max height of tree. | Limit to 3-10 to prevent memorization. |
| `min_samples_split` | Min samples required to split a node. | Higher (e.g., 50) prevents isolating noise. |
| `min_samples_leaf` | Min samples required in a Leaf. | **Most Critical**. Set to 1-5% of data size to ensure smooth predictions. |
| `max_features` | Features to consider per split. | `sqrt` or `log2`. Adds randomness (like Random Forest). |

```python
# Tuned Model (Pre-Pruned)
clf_tuned = DecisionTreeClassifier(
    max_depth=5, 
    min_samples_leaf=10, 
    min_samples_split=20
)
```

---

### 4. Post-Pruning (Cost Complexity Pruning)
Sometimes Pre-pruning is just guessing. **Post-Pruning** grows the full tree first, then cuts off weak branches.
Scikit-Learn uses **Minimal Cost-Complexity Pruning** (`ccp_alpha`).

*   **Logic**: Removes subtrees that don't decrease impurity enough to justify their complexity cost.
*   **Parameter**: `ccp_alpha` (Non-negative float).
    *   `0.0` (Default): No pruning (Full tree).
    *   `> 0.0`: The more you increase, the more branches are pruned.

#### Implementation Steps:
1.  Train a full tree.
2.  Compute the "Pruning Path" (List of effective alphas).
3.  Cross-validate to find the optimal `ccp_alpha`.

```python
# 1. Get Pruning Path
path = clf.cost_complexity_pruning_path(X_train, y_train)
ccp_alphas = path.ccp_alphas  # List of candidate alpha values

# 2. Train a tree for every alpha
clfs = []
for ccp_alpha in ccp_alphas:
    clf = DecisionTreeClassifier(random_state=42, ccp_alpha=ccp_alpha)
    clf.fit(X_train, y_train)
    clfs.append(clf)

# 3. Pick best alpha based on Test Score (or CV score)
test_scores = [clf.score(X_test, y_test) for clf in clfs]
best_alpha_index = test_scores.index(max(test_scores))
best_clf = clfs[best_alpha_index]

print(f"Best Alpha: {ccp_alphas[best_alpha_index]}")
print(f"Pruned Tree Depth: {best_clf.get_depth()}")
```

---

### 5. Summary: Pre vs Post Pruning
*   **Pre-Pruning**: Fast, easy to interpret (`max_depth=5`), but might stop too early (Underfitting).
*   **Post-Pruning (`ccp_alpha`)**: Slower (grows full tree), but finds the mathematically optimal tree structure.
