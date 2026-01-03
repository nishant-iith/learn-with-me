# Multiclass Classification Metrics

> **Goal**: How to evaluate models when there are more than 2 classes (e.g., Dog, Cat, Rabbit).

### 1. The Confusion Matrix ($N \times N$)
Instead of a simple 2x2, we have an $N \times N$ matrix.
*   **Rows**: Actual Classes.
*   **Columns**: Predicted Classes.

#### Example: Dog vs Cat vs Rabbit (From Notes)
Total Samples: $29 + 45 + 34 = 108$? No, let's sum the rows/cols.
*   Row 1 (Actual Dog): $25 (\text{True}) + 5 (\text{Cat}) + 10 (\text{Rabbit}) = 40$
*   Row 2 (Actual Cat): $0 (\text{Dog}) + 30 (\text{True}) + 4 (\text{Rabbit}) = 34$
*   Row 3 (Actual Rabbit): $4 (\text{Dog}) + 10 (\text{Cat}) + 20 (\text{True}) = 34$
*   **Total**: $40 + 34 + 34 = 108$.

| | Pred Dog | Pred Cat | Pred Rabbit | Total Actual |
| :--- | :--- | :--- | :--- | :--- |
| **Actual Dog** | **25 (TP)** | 5 | 10 | 40 |
| **Actual Cat** | 0 | **30 (TP)** | 4 | 34 |
| **Actual Rabbit** | 4 | 10 | **20 (TP)** | 34 |
| **Total Pred** | **29** | **45** | **34** | **108** |

---

### 2. Precision (The "Exactness")
$$ \text{Precision} = \frac{\text{TP}}{\text{Total Predicted for that Class}} $$

**A. Per-Class Calculation**:
*   **Dog ($P_D$)**: $25/29 = \mathbf{0.86}$
*   **Cat ($P_C$)**: $30/45 = \mathbf{0.66}$
*   **Rabbit ($P_R$)**: $20/34 = \mathbf{0.58}$

**B. Macro Precision ("Normal" Average)**
> *Treats all classes equally.*
$$ \text{Macro P} = \frac{P_D + P_C + P_R}{3} = \frac{0.86 + 0.66 + 0.58}{3} = \mathbf{0.70} $$

**C. Weighted Precision**
> *Weights by Class Size (Support). Important for Imbalanced Data.*
$$ \text{Weighted P} = \frac{40(0.86) + 34(0.66) + 34(0.58)}{108} = \mathbf{0.71} $$

---

### 3. Recall (The "Completeness")
$$ \text{Recall} = \frac{\text{TP}}{\text{Total Actual for that Class}} $$

**A. Per-Class Calculation**:
*   **Dog ($R_D$)**: $25/40 = \mathbf{0.62}$
*   **Cat ($R_C$)**: $30/34 = \mathbf{0.88}$
*   **Rabbit ($R_R$)**: $20/34 = \mathbf{0.58}$

**B. Macro Recall ("Normal" Average)**
$$ \text{Macro R} = \frac{R_D + R_C + R_R}{3} = \frac{0.62 + 0.88 + 0.58}{3} = \mathbf{0.69} $$

**C. Weighted Recall**
$$ \text{Weighted R} = \frac{40(0.62) + 34(0.88) + 34(0.58)}{108} = \mathbf{0.69} $$

---

### 4. F1-Score (Harmonic Mean)
First, calculate F1 for each class: $2 \cdot \frac{P \cdot R}{P + R}$.

**A. Per-Class Calculation**:
*   **Dog ($F1_D$)**: $2(0.86 \cdot 0.62) / (0.86 + 0.62) = \mathbf{0.72}$
*   **Cat ($F1_C$)**: $2(0.66 \cdot 0.88) / (0.66 + 0.88) = \mathbf{0.75}$
*   **Rabbit ($F1_R$)**: $2(0.58 \cdot 0.58) / (0.58 + 0.58) = \mathbf{0.58}$

**B. Macro F1 ("Normal" Average)**
$$ \text{Macro F1} = \frac{0.72 + 0.75 + 0.58}{3} = \mathbf{0.68} $$

**C. Weighted F1**
$$ \text{Weighted F1} = \frac{40(0.72) + 34(0.75) + 34(0.58)}{108} = \mathbf{0.69} $$

---

### 5. Python Implementation

```python
from sklearn.metrics import classification_report

# y_true = ['Dog', 'Cat', 'Dog', 'Rabbit' ...]
# y_pred = ['Dog', 'Dog', 'Dog', 'Rabbit' ...]

print(classification_report(y_true, y_pred, target_names=['Dog', 'Cat', 'Rabbit']))

# Output will look exactly like:
#               precision    recall  f1-score   support
#
#          Dog       0.86      0.62      0.72        40
#          Cat       0.66      0.88      0.75        34
#       Rabbit       0.58      0.58      0.58        34
#
#     accuracy                           ...       108
#    macro avg       0.70      0.70      0.68       108
# weighted avg       0.71      0.69      0.69       108
```
