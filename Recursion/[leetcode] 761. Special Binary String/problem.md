# [LeetCode] 761. Special Binary String

**Platform:** LeetCode  
**Difficulty:** Hard  
**Tags:** Recursion, String, Greedy, Sorting, Balanced Parentheses  
**Problem Link:** [https://leetcode.com/problems/special-binary-string/](https://leetcode.com/problems/special-binary-string/)  
**Date Solved:** 2026-02-25

---

## Intuition & Iterative Thinking Process

The problem asks for the lexicographical maximum by swapping consecutive special substrings. This sounds like a complex combinatorial problem, but the "nested" nature of the constraints suggests a deep structural property.

### 1. Decoding the "Special" Rules
My first realization was that a "Special String" is just a **Balanced Parenthesis** string in disguise:
* **Rule 1 (Equal 0s and 1s):** Total open brackets `(` = Total closed brackets `)`.
* **Rule 2 (Prefix count):** You can never close a bracket that hasn't been opened (at any point, $1s \ge 0s$).

> **Crucial Observation on Boundaries:**
> * A special string will **never start with '0'** (the first prefix would immediately violate Rule 2).
> * A special string will **never end with '1'** (if it did, the prefix of length $N-1$ would have had more 0s than 1s, which is forbidden).
> * **Conclusion:** Every primitive special string **must** be wrapped in a `1` and a `0`. It looks like: `1` + `{another special string}` + `0`.

---

### 2. The Thought Journey: From Strings to Folders

As I analyzed how to optimize the string, my logic evolved through three distinct mental models:

#### Model A: The Container Principle
I noticed that if a special string is wrapped in a `1` and `0` (e.g., `1 {101100} 0`), the characters inside that "container" can never "escape" to the outside. 
* We can perform optimizations *inside* the `1...0` boundary, but those internal characters will always stay between that specific outer `1` and `0`.

#### Model B: The Directory Analogy
This led me to think of the problem as a **Recursive Directory Structure**:
* A Special String is like a **Folder**.
* A Folder can contain multiple sub-folders at the same nesting level (children).
* **Goal:** To get the lexicographically largest string, we need to sort the folders at *every* level.

> **The "Directory Sorting" Insight:**
> If we have a string like `1(101100)0 1(1100)0`, it's like having two folders at the same level. If we optimize the inner contents of each folder first, we can then compare the "final names" of these folders and sort them.

#### Model C: The Merge Sort Connection
I realized this is exactly like **Merge Sort**. In Merge Sort, you cannot effectively merge two halves until those halves are themselves sorted. 
* We cannot sort the "sibling" special strings until we have recursively optimized their "inner" contents.
* Once the recursive calls return the optimal versions of the children, we treat those strings as atomic units and sort them in descending order to satisfy the "Greedy" requirement for the largest string.

---

### 3. Visual Representation of the Logic

<div style="padding: 15px; border: 1px solid #ddd; border-left: 2px solid #2196F3; background-color: #776b6b;">
<strong>Original String:</strong> <code>11011000</code><br><br>
<strong>1. Decompose into Primitive Parts:</strong><br>
&nbsp;&nbsp;&nbsp;&nbsp; Only one part found: <code>1</code> + <code>(101100)</code> + <code>0</code><br><br>
<strong>2. Recurse on Internal Content (101100):</strong><br>
&nbsp;&nbsp;&nbsp;&nbsp; <code>101100</code> splits into two siblings: <code>(10)</code> and <code>(1100)</code><br>
&nbsp;&nbsp;&nbsp;&nbsp; &bull; Optimize <code>(10)</code>: returns <code>"10"</code><br>
&nbsp;&nbsp;&nbsp;&nbsp; &bull; Optimize <code>(1100)</code>: returns <code>"1100"</code><br><br>
<strong>3. Sort Siblings at this Level:</strong><br>
&nbsp;&nbsp;&nbsp;&nbsp; Compare <code>"10"</code> vs <code>"1100"</code> &rarr; Sorted Descending: <code>"1100", "10"</code><br><br>
<strong>4. Reconstruct & Return:</strong><br>
&nbsp;&nbsp;&nbsp;&nbsp; Wrap: <code>1</code> + <code>(110010)</code> + <code>0</code> &rarr; <strong>Result:</strong> <code>11100100</code>
</div>

---

## Final Algorithm Reduction

1.  **Identify** all top-level primitive special substrings $P_1, P_2, \dots, P_n$.
2.  **Strip** the outer `1` and `0` from each $P_i$ to get the inner content.
3.  **Recurse** on that inner content to get the largest possible internal version.
4.  **Re-wrap** the optimized inner content with the `1` and `0`.
5.  **Sort** the resulting strings $P'_i$ in descending order.
6.  **Join** them together.

---
