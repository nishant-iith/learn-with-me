# Naive Bayes: Practical Implementation

### 1. Why Naive Bayes is Popular?
Despite the "Naive" assumption, it is:
*   **Fast**: $O(n)$ training and prediction.
*   **Data Efficient**: Works well with small datasets.
*   **Text King**: The baseline model for NLP (Spam Classification, Sentiment Analysis).

---

### 2. Implementation Types (Sklearn)

| Class | Use Case |
| :--- | :--- |
| `GaussianNB` | Numerical data (Age, Height, CGPA). Assumes Normal distribution. |
| `MultinomialNB` | Discrete counts (Word frequency in emails). |
| `BernoulliNB` | Binary features (Word presence/absence). |

<!-- 
IMAGE_PROMPT: 
Type: Decision Boundary Comparison
Description: 
- Two panels showing classification boundaries on the same 2D data (Red vs Blue points).
- Panel 1 (Logistic Regression): A straight line separator (Linear).
- Panel 2 (Gaussian Naive Bayes): A curved/quadratic boundary (Non-linear).
- Highlighting that Naive Bayes can fit more complex shapes than simple Linear models.
Style: Machine Learning Comparison.
-->

![Naive Bayes vs Logistic Regression Boundary](assets/nb_vs_lr_decision_boundary.png)

---

### 3. Example: Iris Classification (GaussianNB)

```python
from sklearn.naive_bayes import GaussianNB
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

# 1. Load Data
data = load_iris()
X, y = data.data, data.target

# 2. Split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 3. Model
gnb = GaussianNB() # No hyperparameters to tune usually!
gnb.fit(X_train, y_train)

# 4. Predict
y_pred = gnb.predict(X_test)
print("Accuracy:", accuracy_score(y_test, y_pred))
```

---

### 4. Example: Spam Filter (Concept)
**Data**: Emails containing words.
**Feature Extraction**: Bag of Words (BoW).
*   Email 1: "Free Lottery" $\to$ [Free: 1, Lottery: 1, ... ]
*   Email 2: "Meeting Tomorrow" $\to$ [Meeting: 1, Tomorrow: 1, ... ]

**Algorithm**: `MultinomialNB`.
*   Calculates probability of each word appearing in "Spam" vs "Ham".
*   "Free" and "Lottery" will have high probability given Spam.
*   If a new email has these words, $P(Spam | \text{Free, Lottery})$ skyrockets.

### Interview Questions

**Q1: Why is Naive Bayes called "Naive"?**
*   **Ans**: It assumes all features are **independent** of each other given the class. This is rarely true in real life (e.g., in Spam, "Free" and "Money" often come together), but the simplification makes the math tractable and works surprisingly well.

**Q2: What is "Zero Frequency Problem" and how to fix it?**
*   **Ans**: If a categorical value appears in testing but never in training for a specific class, the probability becomes 0. Since Naive Bayes multiplies probabilities, the entire result becomes 0. We fix this using **Laplace Smoothing** (adding 1 to all counts).

**Q3: Which Naive Bayes to use for Text Data?**
*   **Ans**: `MultinomialNB` (if using word counts) or `BernoulliNB` (if using boolean word presence). `GaussianNB` is generally for continuous numerical features.
