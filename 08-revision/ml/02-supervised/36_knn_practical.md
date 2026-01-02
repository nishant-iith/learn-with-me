# KNN: Practical Implementation

### 1. Standard Implementation (Scikit-Learn)

```python
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

# 1. Scaling (CRITICAL STEP)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 2. Initialize KNN
knn = KNeighborsClassifier(n_neighbors=5)

# 3. Train (Just stores data)
knn.fit(X_train_scaled, y_train)

# 4. Predict
y_pred = knn.predict(X_test_scaled)

print("Accuracy:", accuracy_score(y_test, y_pred))
```

---

### 2. Finding the Optimal K (Cross-Validation)
The "Experimental" approach mentioned in notes.

```python
import matplotlib.pyplot as plt
from sklearn.model_selection import cross_val_score
import numpy as np

k_values = range(1, 30, 2) # 1, 3, 5... (Odd numbers)
cv_scores = []

for k in k_values:
    knn = KNeighborsClassifier(n_neighbors=k)
    # 10-Fold Cross Validation
    scores = cross_val_score(knn, X_train_scaled, y_train, cv=10, scoring='accuracy')
    cv_scores.append(scores.mean())

# Plot Error (1 - Accuracy)
errors = [1 - x for x in cv_scores]

plt.plot(k_values, errors, marker='o')
plt.xlabel("Value of K")
plt.ylabel("Misclassification Error")
plt.title("Elbow Method for Optimal K")
plt.show()
```

---

### 3. Visualizing Decision Boundary
Using `mlxtend` as recommended.

```python
from mlxtend.plotting import plot_decision_regions

# Plotting for 2 Features (e.g., X_train_scaled[:, 0] and X_train_scaled[:, 1])
plot_decision_regions(X_train_scaled, y_train.values, clf=knn, legend=2)
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.title('KNN Decision Boundary')
plt.show()
```

> **Note**: For complex visualizations from scratch (MeshGrid), refer to the snippet in the `00_utils` if needed, but `mlxtend` is the industry standard for quick plots.
