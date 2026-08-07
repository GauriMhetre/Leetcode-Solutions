
class Solution {
    using Counts = array<int, 4>;

    const array<Counts, 10> digitFactors = {{{0, 0, 0, 0},
                                             {0, 0, 0, 0},
                                             {1, 0, 0, 0},
                                             {0, 1, 0, 0},
                                             {2, 0, 0, 0},
                                             {0, 0, 1, 0},
                                             {1, 1, 0, 0},
                                             {0, 0, 0, 1},
                                             {3, 0, 0, 0},
                                             {0, 2, 0, 0}}};

    Counts factorize(long long t) {
        Counts cnt{0, 0, 0, 0};
        int primes[4] = {2, 3, 5, 7};

        for (int i = 0; i < 4; i++) {
            while (t % primes[i] == 0) {
                cnt[i]++;
                t /= primes[i];
            }
        }

        if (t != 1)
            return {-1, -1, -1, -1};
        return cnt;
    }

    Counts getFactors(const string& s) {
        Counts cnt{0, 0, 0, 0};

        for (char c : s) {
            Counts cur = digitFactors[c - '0'];
            for (int i = 0; i < 4; i++) {
                cnt[i] += cur[i];
            }
        }

        return cnt;
    }

    Counts subtract(Counts a, const Counts& b) {
        for (int i = 0; i < 4; i++) {
            a[i] = max(0, a[i] - b[i]);
        }
        return a;
    }

    bool contains(const Counts& have, const Counts& need) {
        for (int i = 0; i < 4; i++) {
            if (have[i] < need[i])
                return false;
        }
        return true;
    }

    map<int, int> makeDigits(Counts cnt) {
        map<int, int> result;

        int count8 = cnt[0] / 3;
        cnt[0] %= 3;

        int count9 = cnt[1] / 2;
        cnt[1] %= 2;

        int count4 = cnt[0] / 2;
        cnt[0] %= 2;

        int count2 = cnt[0];
        int count3 = cnt[1];
        int count6 = 0;

        if (count2 && count3) {
            count2 = 0;
            count3 = 0;
            count6 = 1;
        }

        if (count3 && count4) {
            count3 = 0;
            count4 = 0;
            count6 = 1;
            count2 = 1;
        }

        result[2] = count2;
        result[3] = count3;
        result[4] = count4;
        result[5] = cnt[2];
        result[6] = count6;
        result[7] = cnt[3];
        result[8] = count8;
        result[9] = count9;

        return result;
    }

    int digitCount(const map<int, int>& digits) {
        int total = 0;
        for (auto& [digit, count] : digits) {
            total += count;
        }
        return total;
    }

    string construct(const map<int, int>& digits) {
        string result;

        for (auto& [digit, count] : digits) {
            result += string(count, char('0' + digit));
        }

        return result;
    }

public:
    string smallestNumber(string num, long long t) {
        Counts required = factorize(t);

        if (required[0] == -1)
            return "-1";

        map<int, int> minimumDigits = makeDigits(required);

        if (digitCount(minimumDigits) > (int)num.size()) {
            return construct(minimumDigits);
        }

        int firstZero = num.find('0');
        if (firstZero == string::npos) {
            firstZero = num.size();

            Counts current = getFactors(num);
            if (contains(current, required)) {
                return num;
            }
        }

        Counts suffixFactors = getFactors(num);

        for (int i = (int)num.size() - 1; i >= 0; i--) {
            int currentDigit = num[i] - '0';

            suffixFactors = subtract(suffixFactors, digitFactors[currentDigit]);

            if (i > firstZero)
                continue;

            for (int biggerDigit = currentDigit + 1; biggerDigit <= 9;
                 biggerDigit++) {

                Counts remaining = required;
                remaining = subtract(remaining, suffixFactors);
                remaining = subtract(remaining, digitFactors[biggerDigit]);

                map<int, int> remainingDigits = makeDigits(remaining);
                int needed = digitCount(remainingDigits);
                int available = (int)num.size() - 1 - i;

                if (needed <= available) {
                    string answer = num.substr(0, i);
                    answer += char('0' + biggerDigit);

                    answer += string(available - needed, '1');
                    answer += construct(remainingDigits);

                    return answer;
                }
            }
        }

        map<int, int> digits = makeDigits(required);
        int length = digitCount(digits);

        return string(num.size() + 1 - length, '1') + construct(digits);
    }
};