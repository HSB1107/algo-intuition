# [LeetCode] 3841. Palindromic Path Queries in a Tree

**Problem Link:** [Palindromic Path Queries in a Tree](https://leetcode.com/problems/palindromic-path-queries-in-a-tree/description/)

## Intuition & Iterative Thinking Process

This problem asks whether the characters on the unique simple path between two nodes in a tree can be rearranged into a palindrome. With the addition of node character updates, we need a solution that handles both path queries and subtree updates efficiently.

### 1. The Palindrome Condition & Parity

The core property of a palindrome is that at most one character can appear an odd number of times (the center character in an odd-length palindrome). 

* **Observation:** We don't need the exact count of each character. We only need to know the **parity** (odd or even).
* **XOR Property:** Using bitmasking, we can represent the 26 lowercase English letters as bits in a 32-bit integer.
    * Bit $i$ is `1` if the character ('a' + $i$) appears an odd number of times.
    * Bit $i$ is `0` if it appears an even number of times.
* **Result:** A set of characters can form a palindrome if the resulting bitmask has at most one bit set.
    * *Bitmask Trick:* `(mask & (mask - 1)) == 0` check if zero or one bit is set.

### 2. Path Logic using Prefix XORs

The XOR sum of characters on the path between $u$ and $v$ can be derived using prefix XOR sums from the root.

Let $P(x)$ be the XOR sum of all characters on the path from the **root to node $x$**.

When we calculate $P(u) \oplus P(v)$, the path from the root to the **Lowest Common Ancestor (LCA)** of $u$ and $v$ is XORed twice. Since $x \oplus x = 0$, the root-to-LCA path is canceled out.

However, this cancellation also removes the LCA node itself from the result. To fix this, we must XOR the LCA's character back into the result:
$$\text{PathMask}(u, v) = P(u) \oplus P(v) \oplus \text{mask}(\text{LCA}(u, v))$$

### 3. Handling Updates: The Roadblock

A standard "update node $u$" query would change the prefix XOR $P(x)$ for **every node $x$ in the subtree of $u$**.
* In a skewed tree, a single update could affect $O(N)$ nodes.
* A naive $O(N)$ update leads to $O(NQ)$ total complexity, which is too slow ($5 * 10^4$ constraints).

### 4. The Solution: Tree Linearization + BIT

To manage subtree updates efficiently, we linearize the tree using an **Euler Tour** (entry and exit times).

1.  **Euler Tour:** During a DFS, we record `entry[u]` and `exit[u]`. Any node $v$ in $u$'s subtree will satisfy `entry[u] <= entry[v] <= exit[u]`.
2.  **Range Updates:** A subtree update at $u$ becomes a **range update** on $[entry[u], exit[u]]$ in the linearized array.
3.  **Point Queries:** The prefix XOR $P(u)$ is simply the value at $entry[u]$ after all range updates are applied.

We use a **Binary Indexed Tree (Fenwick Tree)** to support:
* **Range Update:** `updateRange(l, r, delta)`
* **Point Query:** `query(index)` (the cumulative XOR at that position)

### Final Algorithm Summary

* **Precomputation:** DFS to find `entry`/`exit` times and Binary Lifting table for $O(\log N)$ LCA.
* **Initialization:** For each node $i$, perform a BIT range update on $[entry[i], exit[i]]$ with the bitmask of its initial character.
* **Update Query:** Calculate `delta = old_mask ^ new_mask`. Apply `BIT.updateRange(entry[u], exit[u], delta)`.
* **Path Query:**
    1.  Find $L = \text{LCA}(u, v)$.
    2.  Fetch $P(u)$ and $P(v)$ from BIT.
    3.  Evaluate `path_mask = P(u) ^ P(v) ^ current_mask[L]`.
    4.  Check `(path_mask & (path_mask - 1)) == 0`.

## Complexity Analysis

* **Time Complexity:** $O((N + Q) \log N)$
    * LCA Precomputation: $O(N \log N)$
    * BIT Updates/Queries: $O(\log N)$ per operation.
* **Space Complexity:** $O(N \log N)$ for the Binary Lifting table and $O(N)$ for the Euler Tour and BIT.

---