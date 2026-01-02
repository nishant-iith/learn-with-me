# Naive Bayes Classifier: Intuition & Categorical Data

### 1. From Bayes Theorem to Classifier
We want to find the most probable class ($y$) given a set of features ($X = x_1, x_2, ..., x_n$).
$$ P(y|X) = \frac{P(X|y) \times P(y)}{P(X)} $$

Since $P(X)$ (Evidence) is constant for all classes, we ignore it for comparison.
$$ P(y|X) \propto P(X|y) \times P(y) $$

### 2. The "Naive" Assumption
Calculating $P(X|y)$ implies calculating $P(x_1, x_2, ..., x_n | y)$.
If features are dependent, this is computationally impossible (combinatorial explosion).

**Assumption**: All features are **Conditionally Independent** given the class label.
$$ P(x_1, x_2, ... | y) \approx P(x_1|y) \times P(x_2|y) \times ... \times P(x_n|y) $$

The formula becomes:
$$ P(y|X) \propto P(y) \times \prod_{i=1}^{n} P(x_i|y) $$

> **Why "Naive"?** because in real life, features are rarely independent (e.g., "Humidity" and "Rain" are linked). Yet, the algorithm works surprisingly well!

<!-- 
IMAGE_PROMPT: 
Type: Graphical Model (Bayesian Network)
Description: 
- Central Node: Class (y).
- Surrounding Nodes: Features (x1, x2, x3, x4).
- Arrows point FROM Class TO every Feature (y -> x1, y -> x2...).
- CRITICAL: No arrows between Features (x1 and x2 are not connected).
- Label: "Conditional Independence Assumption".
Style: Network Diagram.
-->

---

### 3. Workflow: Categorical Data (Lookup Tables)
Imagine predicting if we should **Play Tennis** (Yes/No) based on Weather.

**Dataset**:
*   Sunny, Hot $\to$ No
*   Overcast, Hot $\to$ Yes
*   Rainy, Mild $\to$ Yes
*   ... (14 rows)

**Step 1: Training (Building Lookup Tables)**
We calculate Probabilities from frequency counts.
*   **Prior**: $P(Yes) = 9/14$, $P(No) = 5/14$.
*   **Likelihoods**:
    *   $P(Sunny | Yes) = 2/9$
    *   $P(Sunny | No) = 3/5$
    *   ... (Store all these counts)

**Step 2: Testing**
Query: **Outlook=Sunny, Temp=Cool**.
*   **Posterior (Yes)**: $P(Yes) \times P(Sunny|Yes) \times P(Cool|Yes)$
*   **Posterior (No)**: $P(No) \times P(Sunny|No) \times P(Cool|No)$
*   **Result**: Pick the higher probability.

---

### 4. Zero Probability Problem & Laplace Smoothing
What if a feature value (e.g., "Overcast") never appears with Class "No" in training?
*   $P(Overcast | No) = 0$.
*   This multiplies everything by 0, killing the prediction.

**Solution: Laplace Smoothing (Additive Smoothing)**
Add a dummy count ($\alpha=1$) to every frequency.
$$ P(x_i|y) = \frac{\text{count}(x_i, y) + \alpha}{\text{count}(y) + \alpha \times \text{Number of unique values}} $$
This ensures no probability is ever exactly zero.

<!-- 
IMAGE_PROMPT: 
Type: Bar Chart Comparison
Description: 
- Chart 1 (Before Smoothing): One bar has height 0 (Probability = 0).
- Chart 2 (After Smoothing): The zero bar now has a tiny height (small non-zero probability).
- Label: "Laplace Smoothing prevents Zero Frequency Problem".
Style: Data Visualization.
-->
