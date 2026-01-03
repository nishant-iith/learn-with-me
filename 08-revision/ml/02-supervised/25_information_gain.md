# Information Gain & Gini Impurity

> **Goal**: Learning *how* the Decision Tree decides which feature to split on.

---

### 1. Information Gain (Using Entropy)
We know that **Entropy** measures impurity (messiness).
**Information Gain (IG)** is the **decrease in impurity** after a split.

$$ \text{IG}(S, A) = \text{Entropy}(S) - \sum_{v \in \text{Values}(A)} \frac{|S_v|}{|S|} \text{Entropy}(S_v) $$

*   $H(S)$: Entropy of the Parent node.
*   The second term is the **Weighted Average Entropy** of the Children nodes.

> **Logic**: We calculate IG for *every* possible feature. The feature with the **Highest Information Gain** becomes the root (or decision) node. It means that feature reduced the uncertainty the most.

---

### 2. Gini Impurity
While ID3 uses Entropy, the **CART** algorithm (used by Sklearn) uses **Gini Impurity**.

#### A. Introduction to Gini
Gini Impurity measures the likelihood that a randomly selected element would be **incorrectly classified** if it were randomly labeled according to the distribution of labels in the subset.

**Formula**:
$$ \text{Gini} = 1 - \sum_{i=1}^{K} (p_i)^2 $$

*   **Max Gini (Impure)**: $0.5$ (for 2 classes). Occurs at 50/50 split. ($1 - [0.5^2 + 0.5^2] = 0.5$).
*   **Min Gini (Pure)**: $0.0$. Occurs at 100/0 split. ($1 - [1^2 + 0^2] = 0$).

#### B. Example Calculation
Node: 5 Samples (2 Yes, 3 No).
*   $P(\text{Yes}) = 0.4$
*   $P(\text{No}) = 0.6$
*   $\text{Gini} = 1 - (0.4^2 + 0.6^2)$
*   $\text{Gini} = 1 - (0.16 + 0.36) = 1 - 0.52 = \mathbf{0.48}$

---

### 3. Entropy vs Gini Impurity

| Feature | **Entropy** | **Gini Impurity** |
| :--- | :--- | :--- |
| **Formula** | $H = -\sum p_i \log_2(p_i)$ | $G = 1 - \sum p_i^2$ |
| **Range** | $[0, 1]$ (Binary) | $[0, 0.5]$ (Binary) |
| **Computation** | **Slow**: Uses Logarithms. | **Fast**: Uses distinct squares. |
| **Preference** | Tends to isolate balanced trees. | Tends to isolate the most frequent class. |
| **Usage** | ID3, C4.5 Algorithms. | CART (Sklearn Default). |

> **Analogy**: Entropy is the "Gold Standard" of information theory. Gini is a "Computationally Cheap Approximation" that behaves almost identically. In 95% of cases, they yield the same tree.

<!-- 
IMAGE_PROMPT: 
Type: Comparison Graph
Description: 
- X-axis: Probability P(+).
- Plot 1: Entropy (Scaled to 0.5 height for comparison, usually Gini is multiplied by 2 to match).
- Plot 2: Gini Impurity Curve.
- Result: Shapes are nearly identical parabolas (Gini is slightly flatter).
Style: Mathematical Plot.
-->

![Entropy vs Gini Impurity Curves](assets/entropy_vs_gini_curve.png)

---

### 4. Handling Different Data Types

How does the Tree decide splits for Numbers vs Categories?

#### A. Numerical Data (e.g., Salary, Age)
We cannot just say "Is Salary == 50k?". We need a **Threshold** (e.g., Salary <= 40k).

**The Algorithm**:
1.  **Sort** the unique values of the feature.
    *   Example: $[10, 20, 30, 40]$.
2.  **Calculate Midpoints** (Potential Splits).
    *   Splits: $15, 25, 35$.
3.  **Evaluate All**: Compute Information Gain (or Gini) for *every* midpoint.
4.  **Pick Best**: The midpoint with the best gain is chosen.

#### B. Categorical Data (e.g., Color: Red, Blue, Green)
Scikit-Learn (CART) supports only **Binary Splits**. It converts categories into numbers (0, 1, 2) or uses One-Hot Encoding.

*   **Approach**: Generate all binary non-redundant partitions.
    *   Split 1: {Red} vs {Blue, Green}.
    *   Split 2: {Blue} vs {Red, Green}.
    *   Split 3: {Green} vs {Red, Blue}.
*   Calculate Gain for each, pick the best.

#### C. Mixed Data (The Grand Competition)
The Decision Tree is **Greedy**.
At every node, it considers **ALL** features at once:
*   Numerical Feature A: Test all midpoints.
*   Categorical Feature B: Test all partitions.
*   Numerical Feature C: Test all midpoints.

It calculates the Information Gain for **hundreds of candidate splits** and simply picks the **Winner** (Max Gain).
This explains why trees don't need scaling—they treat each feature locally and independently!
