# Naive Bayes: Handling Numerical Data (Gaussian)

### 1. The Problem with Numbers
In the previous chapter (Tennis example), data was **Categorical** (Sunny, Hot, High). We could easily count frequencies.
What if we have **Numerical Data**?
*   Feature: **Age** (25, 30, 22.5, 45...)
*   Feature: **Salary** (50k, 60k, 100k...)

We cannot make a lookup table for every possible number (Counts would be 1 for everything).

---

### 2. The Solution: Probability Density Function (PDF)
We assume the numerical feature follows a **Normal (Gaussian) Distribution**.
Instead of counting, we calculate the **Mean ($\mu$)** and **Variance ($\sigma^2$)** for each class.

Then, we use the **PDF Formula** to calculate the likelihood:
$$ P(x_i | y) = \frac{1}{\sqrt{2\pi\sigma_y^2}} \exp \left( - \frac{(x_i - \mu_y)^2}{2\sigma_y^2} \right) $$

*   $\mu_y$: Mean of feature $x$ for class $y$.
*   $\sigma_y^2$: Variance of feature $x$ for class $y$.

---

### 3. Example: Predicting "Job Offer"
**Feature**: CGPA.
*   **Class: Placed (Yes)**
    *   Mean ($\mu_{yes}$) = 8.5
    *   Std Dev ($\sigma_{yes}$) = 1.0
*   **Class: Not Placed (No)**
    *   Mean ($\mu_{no}$) = 6.0
    *   Std Dev ($\sigma_{no}$) = 1.5

**Query**: Student with **CGPA = 7.5**.
We plug $x = 7.5$ into the Gaussian formula for both classes:
1.  **Likelihood (Placed)**: How "normal" is a 7.5 CGPA for Placed students? (Closer to 8.5?)
2.  **Likelihood (Not Placed)**: How "normal" is a 7.5 CGPA for Not Placed students? (Far higher than 6.0?)

Usually, the bell curve for "Placed" will give a higher probability density for 7.5 than "Not Placed" (depending on the variance).

<!-- 
IMAGE_PROMPT: 
Type: Gaussian Distribution Plot
Description: 
- X-axis: CGPA.
- Y-axis: Probability Density.
- Two Bell Curves:
    - Left Curve (Red): 'Not Placed' (Mean=6.0).
    - Right Curve (Green): 'Placed' (Mean=8.5).
- A vertical dotted line at x=7.5 (Query Point).
- Intersection points on both curves show the Likelihoods.
Style: Statistical Visualization.
-->

---

### 4. Other Distributions
*   **Multinomial Naive Bayes**: Used for discrete counts (e.g., Word counts in Text Classification like Spam Filter).
*   **Bernoulli Naive Bayes**: Used for binary features (e.g., Word presence Yes/No).
