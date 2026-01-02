# Evaluation Metrics for Classification

> **Goal**: Understanding how to evaluate a classifier beyond just "Accuracy".


### 1. Confusion Matrix
A 2x2 table showing correct and incorrect predictions.

| | Predicted Positive (1) | Predicted Negative (0) |
| :--- | :--- | :--- |
| **Actual Positive (1)** | **TP** (True Positive) | **FN** (False Negative) <br> *(Type-II Error)* |
| **Actual Negative (0)** | **FP** (False Positive) <br> *(Type-I Error)* | **TN** (True Negative) |

*   **Type-I Error (FP)**: "False Alarm". (e.g., Man told he is pregnant).
*   **Type-II Error (FN)**: "Missed Detail". (e.g., Pregnant woman told she is NOT pregnant).

**Notation Logic**:
- **First Letter (T/F)**: Was the prediction correct? i.e. Predicted == Actual? (**T**rue / **F**alse)
- **Second Letter (P/N)**: What was the predicted class? (**P**ositive / **N**egative)

<!-- 
IMAGE_PROMPT: 
Type: Matrix Diagram
Description: 
- 2x2 Grid.
- Rows: Actual 1, Actual 0.
- Cols: Predict 1, Predict 0.
- Cells: TP (Green check), FN (Red X, Danger), FP (Red X, False Alarm), TN (Green check).
- Annotations for "Type I" and "Type II".
Style: Educational standard.
-->

---

### 2. Accuracy (and why it fails)
$$ \text{Accuracy} = \frac{\text{Correct Predictions}}{\text{Total Predictions}} = \frac{TP + TN}{TP + TN + FP + FN} $$

*   **The Trap**: Imbalanced Data.
    *   Example: 900 Normal, 100 Cancer.
    *   Model predicts **ALL Normal**.
    *   Accuracy = 900/1000 = **90%**.
    *   But it missed all cancer cases! **High Accuracy, Useless Model.**

---

### 3. Precision (Focus: "Don't Spam Me")
> **Question**: "Out of all predictions you claimed were Positive, how many were actually Positive?"

$$ \text{Precision} = \frac{TP}{TP + FP} = \frac{\text{Correct Positive Predictions}}{\text{Total Positive Predictions}} $$

#### Example: Spam Classifier (Model A vs Model B)
Assume we have two models with the **same Accuracy** (e.g., 80%).

| | Model A | Model B |
| :--- | :--- | :--- |
| **FP (Not Spam $\to$ Spam)** | **30** (High) | **10** (Low) |
| **FN (Spam $\to$ Inbox)** | 170 | 190 |
| **Conclusion** | Dangerous! Missed important mails. | Better. Few false alarms. |

*   **Logic**: In Spam detection, **FP** (Classifying a Job Offer as Spam) is more dangerous than FN.
*   **Result**: We prefer **Model B** because it has higher Precision (lower FP).

<!-- 
IMAGE_PROMPT: 
Type: Comparison Table (Visual)
Description: 
- Visualizing the Spam Example.
- Left: Model A (High FP). Icon of a "Important Job Offer" in Trash. Label: "Low Precision".
- Right: Model B (Low FP). Icon of "Spam" in Inbox. Label: "High Precision".
- Bottom text: "Precision matters when False Positives are costly."
Style: Case Study Illustration.
-->

---

### 4. Recall (Focus: "Don't Miss It")
> **Question**: "Out of all actual Positives, how many did you find?"

$$ \text{Recall} = \frac{TP}{TP + FN} = \frac{\text{Correct Positive Predictions}}{\text{Total Actual Positives}} $$

#### Example: Cancer Detection (Model A vs Model B)
| | Model A | Model B |
| :--- | :--- | :--- |
| **FN (Cancer $\to$ Healthy)** | **200** (Low) | **500** (High) |
| **FP (Healthy $\to$ Cancer)** | 1000 | 200 |
| **Conclusion** | **Better**. Catches more cases. | Dangerous! Missed 500 patients. |

*   **Logic**: In Disease detection, **FN** (Telling a cancer patient they are healthy) is fatal.
*   **Result**: We prefer **Model A** because it has higher Recall (lower FN).

<!-- 
IMAGE_PROMPT: 
Type: Comparison Table (Visual)
Description: 
- Visualizing the Cancer Example.
- Left: Model A (Low FN). Doctor finding the disease. Label: "High Recall".
- Right: Model B (High FN). Doctor sending a sick patient home saying "You are fine". Label: "Low Recall (Dangerous)".
- Bottom text: "Recall matters when False Negatives are costly."
Style: Case Study Illustration.
-->

---

### 5. F1 Score (The Balance)
When you need to balance Precision and Recall (e.g., Cat vs Dog classifier where neither error is fatal).

$$ \text{F1 Score} = \frac{2 \times P \times R}{P + R} = \frac{2PR}{P+R} $$

*   **Why Harmonic Mean?**
    *   Arithmetic Mean ($P+R/2$) is biased by high outliers.
    *   Harmonic Mean **penalizes the lower value**. Use this when you can't decide between Precision or Recall (e.g., Cat vs Dog classifier).

<!-- 
IMAGE_PROMPT: 
Type: Comparison Table
Description: 
- Scenario 1 (Cancer): Highlight Recall (Minimize FN).
- Scenario 2 (Spam): Highlight Precision (Minimize FP).
- Scenario 3 (General): F1 Score.
Style: Infographic.
-->

### Python Implementation

Here are the two ways to calculate metrics in Scikit-Learn.

#### Method 1: Individual Metrics (Good for specific checks)
```python
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

print("Accuracy:", accuracy_score(y_true, y_pred))
print("Precision:", precision_score(y_true, y_pred))
print("Recall:", recall_score(y_true, y_pred))
print("F1 Score:", f1_score(y_true, y_pred))
```

#### Method 2: The Professional Way (All-in-One)
The `classification_report` gives you everything at a glance.

```python
from sklearn.metrics import classification_report, confusion_matrix

# 1. Confusion Matrix
print("Confusion Matrix:\n", confusion_matrix(y_true, y_pred))

# 2. Detailed Report
print("\nClassification Report:\n")
print(classification_report(y_true, y_pred, target_names=['Class 0', 'Class 1']))
```

> **Note**: The report gives metrics for both classes (0 and 1). For binary classification, focus on the row for **Class 1 (Positive)**.

### Interview Questions

**Q1: Which is worse: Type I or Type II error?**
*   **Ans**: It depends on the business case! In Cancer prediction, Type II (FN) is worse (Death). In Spam classification, Type I (FP) is worse (Lost Job Offer).

**Q2: Can we maximize both Precision and Recall?**
*   **Ans**: Generally No. There is a tradeoff. Increasing the threshold increases Precision but decreases Recall (misses more). Decreasing threshold increases Recall but decreases Precision (more false alarms).

**Q3: Why F1 Score and not Average?**
*   **Ans**: As shown in the notes, if we just average (e.g., Precision=1.0, Recall=0.0), we get 0.5, which is misleading. F1 Score drops to 0 if *either* is 0, ensuring a robust model.
