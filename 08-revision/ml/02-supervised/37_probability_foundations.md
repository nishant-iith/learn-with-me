# Probability Foundations for Naive Bayes

> **"Probability is the logic of science."** — *E.T. Jaynes*

Before diving into Naive Bayes, we must master the language of Uncertainty: **Probability**.

### 1. Fundamental Concepts

#### A. Dependent vs Independent Events
*   **Independent Events**: The outcome of one event does **not** affect the other.
    *   *Example*: Rolling a dice and flipping a coin. 
    *   Formula: $P(A \cap B) = P(A) \times P(B)$
*   **Dependent Events**: The outcome of one event **affects** the probability of the other.
    *   *Example*: Drawing a King from a deck, *not replacing it*, and drawing another King.
    *   Formula: $P(A \cap B) = P(A) \times P(B|A)$

#### B. Conditional Probability ($P(A|B)$)
The probability of Event A happening **given that** Event B has already happened.
$$ P(A|B) = \frac{P(A \cap B)}{P(B)} $$
*   **Intuition**: We restrict our "Universe" to only cases where B happened. Within that restricted universe, what is the chance of A?

<!-- 
IMAGE_PROMPT: 
Type: Venn Diagram
Description: 
- Panel 1: Standard Venn Diagram. Circle A and Circle B overlap. Universe is the whole rectangle.
- Panel 2: Conditional P(A|B). The "Universe" is now just Circle B. The "Success" area is the Overlap (A n B).
- Highlighting that we are ignoring everything outside B.
Style: Mathematical Visualization.
-->

---

### 2. Bayes' Theorem (The Holy Grail)
Deriving Bayes' Theorem from Conditional Probability is simple.

1.  $P(A|B) = \frac{P(A \cap B)}{P(B)} \implies P(A \cap B) = P(A|B) \times P(B)$
2.  $P(B|A) = \frac{P(B \cap A)}{P(A)} \implies P(B \cap A) = P(B|A) \times P(A)$

Since $P(A \cap B)$ is the same as $P(B \cap A)$:
$$ P(A|B) \times P(B) = P(B|A) \times P(A) $$

Rearranging gives us **Bayes' Theorem**:
$$ P(A|B) = \frac{P(B|A) \times P(A)}{P(B)} $$

#### The Terminology (Memorize This)
*   **$P(A|B)$**: **Posterior** (Probability of Class A given Data B). *The Goal.*
*   **$P(B|A)$**: **Likelihood** (Probability of Data B given Class A).
*   **$P(A)$**: **Prior** (Probability of Class A being true generally).
*   **$P(B)$**: **Evidence** (Probability of Data B occurring at all).

---

### 3. Example: The Medical Test Paradox
*   **Disease**: 1% of population has it ($P(D) = 0.01$).
*   **Test**: 99% accurate ($P(Pos|D) = 0.99$, $P(Neg|\neg D) = 0.99$).
*   **You test Positive**. What is the chance you actually have the disease?

Most people say 99%. **Wrong.**
Using Bayes Theorem:
$$ P(D|Pos) = \frac{P(Pos|D) \times P(D)}{P(Pos)} $$
$$ P(Pos) = P(Pos|D)P(D) + P(Pos|\neg D)P(\neg D) $$
$$ P(Pos) = (0.99 \times 0.01) + (0.01 \times 0.99) = 0.0198 $$
$$ P(D|Pos) = \frac{0.0099}{0.0198} = 0.5 $$

50% chance! This is why "Priors" matter. Naive Bayes uses this exact logic to predict classes.
