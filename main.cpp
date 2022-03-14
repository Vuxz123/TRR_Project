#include <bits/stdc++.h>
using namespace std;

const string CREATOR = "Dajunctic Vu";

#define int long long
#define double long double
#define fill(list) memset(list, 0, sizeof(list))
#define fill_(list,value) memset(list, value, sizeof(list))
#define fill_value(list,value) for(int i = 0 ; i < N ; i++) list[i] = value;
#define max_range(list,a,b) *max_element(list + a, list + b + 1);
#define clear(list) list.clear()
#define all(list) list.begin(),list.end()
#define fi first
#define se second
#define endl '\n'

typedef pair<int,int> ii;

const ii dir[] = {{0, -1}, {-1, 0}, {1, 0}, {0,1}};
const double PI = 3.14159265359;
const int inf = 1e18;
const int mod = 1e9 + 7;
const int N = 2e5 + 10;
const int N2 = 2e3 + 100;
const int N3 = 60;

/* #######################  Function  ########################### */
string add(string a, string b){
	while(a.length() < b.length()) a = '0' + a;
	while(b.length() < a.length()) b = '0' + b;

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	string c = "";
	int carry = 0;
	for(int i = 0 ; i < a.length() ; i++){
		int res = (a[i] - '0') + (b[i] - '0') + carry;
		carry = res / 10;

		c += char(res%10 + '0');
	}
	if(carry) c += '1';
	reverse(c.begin(), c.end());
	return c;
}

string subtract(string a, string b){
	while(a.length() < b.length()) a = '0' + a;
	while(b.length() < a.length()) b = '0' + b;
	if(a < b) swap(a, b);

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	string c = "";
	int carry = 0;
	for(int i = 0 ; i < a.length() ; i++){
		int res = (a[i] - '0') - (b[i] - '0') - carry;
		carry = (res < 0);

		if(res < 0) c += char(10 + res + '0');
		else c += char(res + '0');
	}
	reverse(c.begin(), c.end());
	return c;
}

string multiply_single(string a, int n){
	reverse(a.begin(),a.end());
	int carry = 0;
	string c = "";
	for(int i = 0 ; i < a.length() ; i++){
		int res = (a[i] - '0') * n + carry;
		carry = res / 10;

		c += char(res%10 + '0');
	}
	if(carry) c += char(carry + '0');
	reverse(c.begin(), c.end());
	return c;
}

string multiply(string a, string b){
	reverse(b.begin(), b.end());
	string c = "0";
	for(int i = 0 ; i < b.length() ; i++){
		string res = multiply_single(a, b[i] - '0');
		for(int j = 0 ; j < i ; j++) res += '0';
		c = add(c, res);
	}

	return c;
}

pair<string,string> divide(string a, string b){
	string tmp = "", c = "";
	for(int i = 0 ; i < a.length() ; i++){
		tmp += a[i];
		if(tmp.size() < b.size() or (tmp.size() == b.size() and tmp < b)){
			c += '0';
		}
		else{
			for(int i = 0 ; i < 10 ; i++){
				string res = multiply_single(b, i);

				while(tmp.length() < res.length()) tmp = '0' + tmp;
				while(res.length() < tmp.length()) res = '0' + res;


				if(res == tmp){
					c += char(i + '0');
					tmp = subtract(res,tmp);

					reverse(tmp.begin(), tmp.end());
					while(tmp.back() == '0') tmp.pop_back();
					reverse(tmp.begin(), tmp.end());
					break;
				}else if(res > tmp){
					c += char(i  - 1 + '0');
					res = multiply_single(b, i - 1);
					tmp = subtract(res,tmp);

					reverse(tmp.begin(), tmp.end());
					while(tmp.back() == '0') tmp.pop_back();
					reverse(tmp.begin(), tmp.end());
					break;
				}
			}
		}
	}

	reverse(c.begin(), c.end());
	while(c.back() == '0') c.pop_back();
	reverse(c.begin(), c.end());

	if(tmp.empty()) tmp = "0";
	if(c.empty()) c = "0";

	return {c, tmp};
	// c : thuong
	// tmp : du
}

string gcd(string a, string b){
	if(a == "0" or b == "0") return add(a, b);

	while(a != b){
		if(a > b)
			a = subtract(a, b);
		else
			b = subtract(a, b);
	}

	reverse(a.begin(), a.end());
	while(a.back() == '0') a.pop_back();
	reverse(a.begin(), a.end());

	return a;
}

// string gcd(string a, string b) {
//     if (b == "0") return a;
//     return gcd(b, divide(a, b).se);
// }

struct BigInteger{
	string number; 
	int sign;

	BigInteger(int sign = 0, string number = ""){
		this->sign = sign;
		this->number = number;
	}
};

BigInteger sum(BigInteger first, BigInteger second){
	string fstring = first.number;
	string sstring = second.number;

	while(fstring.size() < sstring.size()) fstring = '0' + fstring;
	while(sstring.size() < fstring.size()) sstring = '0' + sstring; 

	int sign = ((fstring > sstring) ? first.sign : second.sign);
	if(fstring < sstring) swap(fstring, sstring);

	reverse(fstring.begin(), fstring.end());
	reverse(sstring.begin(), sstring.end());

	if(first.sign == second.sign){
		int carry = 0;
		string result = "";

		for(int i = 0 ; i < fstring.size() ; i++){
			int tmp = (fstring[i] - '0' ) + (sstring[i] - '0') + carry;
			carry = tmp / 10; 

			result += char(tmp % 10 + '0');
		}
		if(carry) result += char(carry + '0');
		reverse(result.begin(), result.end());
		return BigInteger(sign, result);
	}else{
		int carry = 0;
		string result = "";

		for(int i = 0 ; i < fstring.size() ; i++){
			int tmp = (fstring[i] - '0' ) - (sstring[i] - '0') - carry;
			carry = (tmp < 0); 

			if(tmp < 0) result += char(10 + tmp + '0');
			else result += char(tmp + '0');
		}
		while(result.back() == '0') result.pop_back();

		reverse(result.begin(), result.end());

		return BigInteger(sign, result);
	}


	return BigInteger(first.sign, "dsdsdsdsdsds");
}


BigInteger x, y;
string gcd_;
void extendedEuclid(string a, string b) {
    if (b == "0") {
        gcd_ = a;
        x.number = "1";
        y.number = "0";
    }
    else {
        extendedEuclid(b, divide(a,b).se);
        BigInteger temp = x;
        x = y;

        BigInteger tmp2 = BigInteger(y.sign, multiply(divide(a,b).fi , y.number));
        tmp2.sign = 1 - tmp2.sign;
        y = sum(tmp2 , temp);
    }
}

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	/* ###################   Main Code    ##########################*/

	string a;
	string b;
	cin >> a >> b;

	cout << "Value of GCD(A,B) is: \n";
	cout << gcd(a, b) << endl ;

	extendedEuclid(b, a);

	cout << "Value of \"B^-1 mod A\" is: \n";
	if(x.sign == 1) cout << "-";
	cout << x.number;

	cout << endl << endl << "Code by handsome " << CREATOR << endl;

  	return 0;
} 