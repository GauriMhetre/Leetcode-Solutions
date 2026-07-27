# 1464. Maximum Product of Two Elements in an Array

![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen)

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

---

## Problem

https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/

---

## Acceptance Rate

84.4%

---

## Likes

2717

---

## Dislikes

241

---

## Topics

- Array
- Sorting
- Heap (Priority Queue)

---

## Hints

- Use brute force: two loops to select i and j, then select the maximum value of (nums[i]-1)*(nums[j]-1).

---

## Solution

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int first = 0, second = 0;

        for (int num : nums) {
            if (num > first) {
                second = first;
                first = num;
            } else if (num > second) {
                second = num;
            }
        }

        return (first - 1) * (second - 1);
    }
};
```

---

Generated automatically by LeetCode Auto Sync.

Last Updated:
2026-07-27T09:29:26Z

<!-- Trace ID: SYNC-20260727-58417df9 -->
