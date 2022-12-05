#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

unordered_map<string, int> rToa;
unordered_map<int, string> aTor;
vector<string> roms;

void init() {
	rToa["I"] = 1;
	rToa["V"] = 5;
	rToa["X"] = 10;
	rToa["L"] = 50;
	rToa["C"] = 100;
	rToa["D"] = 500;
	rToa["M"] = 1000;
	rToa["IV"] = 4;
	rToa["IX"] = 9;
	rToa["XL"] = 40;
	rToa["XC"] = 90;
	rToa["CD"] = 400;
	rToa["CM"] = 900;

	aTor[1] = "I";
	aTor[5] = "V";
	aTor[10] = "X";
	aTor[50] = "L";
	aTor[100] = "C";
	aTor[500] = "D";
	aTor[1000] = "M";
	aTor[4] = "IV";
	aTor[9] = "IX";
	aTor[40] = "XL";
	aTor[90] = "XC";
	aTor[400] = "CD";
	aTor[900] = "CM";
}

void input() {
	string str;
	cin >> str;
	roms.push_back(str);
	cin >> str;
	roms.push_back(str);
}

int changeToArab(string str) {
	int sum = 0, i;

	for (i = 0; i < str.length() - 1; i++) {
		string s1, s2;
		s1 = str[i];
		s2 = str[i + 1];
		int num1 = rToa[s1], num2 = rToa[s2];

		if (num1 >= num2) {
			sum += num1;
		}
		else {
			sum += rToa[s1 + s2];
			i++;
		}
	}

	if (i == str.length() - 1) {
		string s;
		s = str[i];
		sum += rToa[s];
	}
	return sum;
}

string changeToRoma(int num) {
	string s = to_string(num), result;

	for (int i = 0; i < s.length(); i++) {
		int n = s[i] - '0';
		int mok = pow(10, s.length() - i - 1);

		if(n > 0) {
			while (n > 0) {
				if (n == 4 or n == 9) {
					result += aTor[n * mok];
					n = 0;
				}
				else {
					if (n >= 5) {
						result += aTor[5 * mok];
						n -= 5;
					}
					else {
						for (int k = 0; k < n; k++) {
							result += aTor[mok];
						}
						n = 0;
					}
				}
			}
		}
	}

	return result;
}

void solve() {
	int num1 = changeToArab(roms[0]), num2 = changeToArab(roms[1]);
	cout << num1 + num2 << '\n' << changeToRoma(num1 + num2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	init();
	input();
	solve();

	return 0;
}