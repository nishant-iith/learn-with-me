# SVM: Mathematical Derivation

> **Goal**: To prove that maximizing the margin is mathematically equivalent to minimizing the weights ($||w||$).

---

### 1. The Setup: Three Equations
We define our decision boundary and margins using the vector notation $w^T x + b$.

1.  **The Hyperplane ($\pi$)**: $w^T x + b = 0$
2.  **Positive Margin ($\pi^+$)**: $w^T x + b = 1$ (Passes through +ve Support Vectors)
3.  **Negative Margin ($\pi^-$)**: $w^T x + b = -1$ (Passes through -ve Support Vectors)

> **Note**: Why $1$ and $-1$? We scale $w$ and $b$ to make the math easier. It doesn't change the plane, just the scale of numbers.

---

### 2. Deriving the Margin Distance ($d$)
We want to find difference in distance between $\pi^+$ and $\pi^-$.

1.  Let $x_1$ be a point on $\pi^-$ (Negative edge).
2.  Let $x_2$ be a point on $\pi^+$ (Positive edge).
3.  From the plane equations:
    *   $w^T x_1 + b = -1$  ...(A)
    *   $w^T x_2 + b = 1$   ...(B)
4.  Subtract (A) from (B):
    $$ w^T x_2 - w^T x_1 = 1 - (-1) $$
    $$ w^T (x_2 - x_1) = 2 $$

5.  **Distance Calculation**:
    The distance $d$ is the projection of the vector $(x_2 - x_1)$ onto the direction of $w$ (the unit normal vector).
    *   Unit Vector: $\hat{u} = \frac{w}{||w||}$
    *   Distance $d = (x_2 - x_1) \cdot \frac{w}{||w||}$
    *   Substitute $w^T(x_2 - x_1) = 2$:
    $$ d = \frac{2}{||w||} $$

> **Result**: The width of the street is $\frac{2}{||w||}$.

<!-- 
IMAGE_PROMPT: 
Type: Derivation Diagram
Description: 
- Two Parallel Lines (Pi+ and Pi-).
- Point x1 on Pi-, Point x2 on Pi+.
- A vector connecting x1 to x2.
- A normal vector 'w' perpendicular to planes.
- Show 'd' as the projection of (x2-x1) onto 'w'.
Style: Mathematical Geometry.
-->

![SVM Margin Derivation Geometry](assets/svm_margin_projection_math.png)

---

### 3. The Optimization Goal
Our intuition says: **"Maximize the Margin ($d$)"**.

*   **Maximize**: $\frac{2}{||w||}$
*   This is the same as **Minimizing**: $||w||$ (The denominator).
*   For mathematical convenience (convex optimization), we minimize the square:
    $$ \min \frac{1}{2} ||w||^2 $$

> **Why squared?** $||w||$ has a sharp point at 0 (non-differentiable). $||w||^2$ is a smooth bowl (easy to derive gradients).

---

### 4. The Constraint ($y_i$)
It's not enough to minimize $w$. We must also ensure **all points are classified correctly**.

*   For Positive points ($y=1$): We want $w^T x + b \ge 1$.
*   For Negative points ($y=-1$): We want $w^T x + b \le -1$.

We can combine these into a single "Master Constraint":
$$ y_i (w^T x_i + b) \ge 1 $$

*   *Check*:
    *   If $y=1$ and prediction is $5$ ($ \ge 1$): $1(5) \ge 1$ (True).
    *   If $y=-1$ and prediction is $-5$ ($\le -1$): $-1(-5) = 5 \ge 1$ (True).
    *   If Misclassified ($y=1$, pred $-5$): $1(-5) = -5 \ge 1$ (False!).

---

### 5. The Final Equation (Hard Margin SVM)
Putting it all together, the SVM algorithm solves this constrained optimization problem:

$$ \text{Objective: } \min_{w,b} \frac{1}{2} ||w||^2 $$
$$ \text{Subject to: } y_i (w^T x_i + b) \ge 1 \text{ for all } i $$

This is solvable using **Lagrange Multipliers** (which leads to the Kernel trick), but this form is the heart of SVM.
