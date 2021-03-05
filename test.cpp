#include <bits/stdc++.h>

using namespace std;

struct LONG_INT{
private:

    vector <int> _digits; // storing digits in the reversed order to simplify realisation
    int _sign; // _sign = 1, if number is positive, otherwise _sign = 0 (if number equals 0, then _sign = 0)

public:

    LONG_INT() {
        _sign = 0;
    }

    LONG_INT(long long number) {
        if(number > 0){
            _sign = 1;
        }else{
            _sign = 0;
        }
        if(number < 0){
            number = - number;
        }
        while(number > 0){
            _digits.push_back(number % 10);
            number /= 10;
        }
    }

    LONG_INT(string number) {
        if(number[0] == '-'){
            _sign = 0;
            for(int i = number.size() - 1; i > 0; i --){
                _digits.push_back(number[i] - '0');
            }
        }else if(number[number.size()-1] != 0){
            _sign = 1;
            for(int i = number.size() - 1; i > -1; i --){
                _digits.push_back(number[i] - '0');
            }
        }else{
            _sign = 0;
            _digits.push_back(0);
        }
    }

    LONG_INT(vector <int> digits, int sign) {
        _digits = digits;
        _sign = sign;
    }

    LONG_INT(const LONG_INT& copied) {
        _digits = copied._digits;
        _sign = copied._sign;
    }

    LONG_INT& operator=(const LONG_INT& other) {
        _digits = other._digits;
        _sign = other._sign;
    }

    LONG_INT& operator-() {
        if(_digits.size() == 0 || (_digits.size() == 1 && _digits[0] == 0)){

        }else{
            _sign = 1 - _sign;
        }
        return (*this);
    }

    LONG_INT plus(const LONG_INT& b) const{
        int carry = 0;
        vector <int> result;
        for(int i = 0; i < max((_digits).size(), (b._digits).size()); i ++){
            if(i < (_digits).size() && i < (b._digits).size()){
                result.push_back(((_digits)[i] + (b._digits)[i] + carry)%10);
                carry = ((_digits)[i] + (b._digits)[i] + carry)/10;
            }else if(i < (_digits).size()){
                result.push_back(((_digits)[i] + carry)%10);
                carry = ((_digits)[i] + carry)/10;
            }else{
                result.push_back(((b._digits)[i] + carry)%10);
                carry = ((b._digits)[i] + carry)/10;
            }
        }
        if(carry > 0){
            result.push_back(1);
        }
        LONG_INT SUM(result, 1);

        return SUM;
    }

    LONG_INT minus(const LONG_INT& t) const {
        LONG_INT b = t;
        LONG_INT a (*this); //firstly we need to check if a < b. If it's true, then swap them
        if(a.zero() && b.zero()){
            return LONG_INT(0);
        }
        bool whoisbigger = false;
        if((a._digits).size() > (b._digits).size()){
            whoisbigger = true;
        }else if((a._digits).size() == (b._digits).size()){
            for(int i = (a._digits).size()-1; i > -1; i --){
                if((a._digits)[i] > (b._digits)[i]){
                    whoisbigger = true;
                }else if((a._digits)[i] < (b._digits)[i]){
                    i = -1;
                }
            }
        }
        vector <int> result;
        int sign = 1;
        if(!whoisbigger){
            sign = 0;
            b = a;
            a = t;
        } //swapping done
        int carry = 0;
        for(int i = 0; i < (a._digits).size(); i ++){
            if(i < (b._digits).size()){
                if((a._digits)[i] - carry >= (b._digits)[i]){
                    result.push_back((a._digits)[i] - carry - (b._digits)[i]);
                    carry = 0;
                }else{
                    result.push_back((a._digits)[i] - carry - (b._digits)[i] + 10);
                    carry = 1;
                }
            }else{
                if((a._digits)[i] - carry >= 0){
                    result.push_back((a._digits)[i] - carry);
                    carry = 0;
                }else{
                    result.push_back((a._digits)[i] - carry + 10);
                    carry = 1;
                }
            }
        }
        vector <int> fresult; // result may contain group of zeros at the end, so we need to delete them
        int j = result.size()-1;
        while(result[j] == 0){
            j--;
        }
        for(int i = 0; i <= j; i ++){
            fresult.push_back(result[i]);
        }
        LONG_INT RESULT(fresult, sign);
        return RESULT;
    }

    bool bigger(const LONG_INT& b) const {
        LONG_INT a (*this);
        bool whoisbigger = true;
        if((a._digits).size() < (b._digits).size()){
            whoisbigger = false;
        }else if((a._digits).size() == (b._digits).size()){
            for(int i = (a._digits).size()-1; i > -1; i --){
                if((a._digits)[i] < (b._digits)[i]){
                    whoisbigger = false;
                }else if((a._digits)[i] > (b._digits)[i]){
                    i = -1;
                }
            }
        }
        if(whoisbigger){
            return true;
        }else{
            return false;
        }
    }

    LONG_INT multiply(const LONG_INT& b) const {
        vector <int> answer(b._digits.size() + _digits.size() + 1, 0);
        for(int i = 0; i < _digits.size(); i ++){
            for(int j = 0; j < b._digits.size(); j ++){
                answer[i+j] += _digits[i] * b._digits[j];
            }
        }
        for(int i = 0; i < answer.size() - 1; i ++){
            int w = answer[i];
            answer[i] = answer[i] % 10;
            answer[i+1] += w / 10;
        }
        vector <int> fresult; // answer may contain group of zeros at the end, so we need to delete them
        int j = answer.size()-1;
        while(answer[j] == 0){
            j--;
        }
        for(int i = 0; i <= j; i ++){
            fresult.push_back(answer[i]);
        }
        LONG_INT RESULT(fresult, 1);
        return RESULT;
    }

    LONG_INT division(const LONG_INT& b) const {
        LONG_INT a(*this);
        if(!a.bigger(b)){
            vector <int> ans;
            LONG_INT ANS(ans, 0);
            return ANS;
        }
        vector <int> emptty;
        vector <int> answer;
        LONG_INT current(emptty, 1);
        bool iszeros = true;
        LONG_INT ten(10);
        for(int i = a._digits.size()-1; i > -1; i --){
            current = current*ten + a._digits[i];
            if(!current.bigger(b)){
                if(!iszeros){
                    answer.push_back(0);
                }
            }else{
                iszeros = false;
                bool t = false;
                long long ii = 1;
                LONG_INT one(1);
                LONG_INT I;
                while(!t){
                    LONG_INT I(ii);
                    if(current.bigger(b*I) && !current.bigger(b*(I+one))){
                        t = true;
                    }
                    ii ++;
                }
                answer.push_back(ii-1);
                LONG_INT mult(ii-1);
                current = current - b*mult;
                //cout << "**" << current << "**" << endl;
            }
        }
        vector <int> result;
        for(int i = answer.size()-1; i > -1; i --){
            result.push_back(answer[i]);
        }
        LONG_INT RESULT(result, 1);
        return RESULT;
    }


    LONG_INT operator+(const LONG_INT& other) const {
        LONG_INT it(*this);
        if(it._sign == other._sign){
            if(it._sign == 0){
                LONG_INT c = it.plus(other);
                c._sign = 0;
                return c;
            }else{
                return it.plus(other);
            }
        }else{
            if(it._sign == 0){
                return other.minus(it);
            }else{
                return it.minus(other);
            }
        }
    }

    LONG_INT operator-(const LONG_INT& other) const {
        LONG_INT it(*this);
        if(it._sign == other._sign){
            if(it._sign == 0){
                return other.minus(it);
            }else{
                return it.minus(other);
            }
        }else{
            if(it._sign == 0){
                LONG_INT c = it.plus(other);
                c._sign = 0;
                return c;
            }else{
                return it.plus(other);
            }
        }
    }

    LONG_INT operator*(const LONG_INT& other) const {
        LONG_INT it(*this);
        /*if(other._digits.size() == 0 || it._digits.size() == 0){
            return LONG_INT(0);
        }*/
        if(it._sign == other._sign){
            LONG_INT answer = it.multiply(other);
            return answer;
        }else{
            LONG_INT answer = it.multiply(other);
            answer._sign = 0;
            return answer;
        }
    }

    LONG_INT operator/(const LONG_INT& other) const {
        LONG_INT it(*this);
        if(it._sign == other._sign){
            if(it._sign == 1){
                LONG_INT answer = it.division(other);
                return answer;
            }else{
                LONG_INT itt;
                itt._digits = it._digits;
                itt._sign = 1 - it._sign;
                LONG_INT o;
                o._digits = other._digits;
                o._sign = 1 - other._sign;
                LONG_INT answer = itt.division(o);
                return answer;

            }
        }else{
            if(other._sign == 0){
                LONG_INT o;
                o._digits = other._digits;
                o._sign = 1 - other._sign;
            LONG_INT answer = it.division(o);
            answer._sign = 0;
            return answer;
            }else{
             LONG_INT itt;
                itt._digits = it._digits;
                itt._sign = 1 - it._sign;
            LONG_INT answer = itt.division(other);
            answer._sign = 0;
            return answer;
            }
        }
    }

    LONG_INT operator%(const LONG_INT& other) const {
        LONG_INT it(*this);
        LONG_INT div = it / other;
        return it - other*div;
    }

    bool zero() const {
        if(_digits.size() == 0){
            return true;
        }
        return false;
    }

    bool operator!=(const LONG_INT& other) const {
        LONG_INT it(*this);
        if(it.zero() && other.zero()){
            return false;
        }
        if(it._sign == other._sign && it._digits.size() == other._digits.size()){
            bool equal = true;
            for(int i = 0; i < it._digits.size(); i ++){
                if(it._digits[i] != other._digits[i]){
                    equal = false;
                }
            }
            if(equal){
                return false;
            }
        }
        return true;

    }

    bool operator==(const LONG_INT& other) const {
        LONG_INT it(*this);
        if(it.zero() && other.zero()){
            return true;
        }
        if(it._sign == other._sign && it._digits.size() == other._digits.size()){
            bool equal = true;
            for(int i = 0; i < it._digits.size(); i ++){
                if(it._digits[i] != other._digits[i]){
                    equal = false;
                }
            }
            if(equal){
                return true;
            }
        }
        return false;

    }

    bool operator<(const LONG_INT& other) const {
        LONG_INT it(*this);
        if(it._sign == 0 && other._sign == 1){
            return true;
        }
        if(it._sign == 1 && other._sign == 0){
            return false;
        }
        if(it._sign == 1 && other._sign == 1){
            if(it.bigger(other)){
                return false;
            }else{
                return true;
            }
        }
        if(it._sign == 0 && other._sign == 0){
            if((other).bigger(it)){
                return false;
            }else{
                return true;
            }
        }
        return true;
    }

    bool operator>(const LONG_INT& other) const {
        LONG_INT it(*this);
        if(it._sign == 0 && other._sign == 1){
            return false;
        }
        if(it._sign == 1 && other._sign == 0){
            return true;
        }
        if(it._sign == 1 && other._sign == 1){
            if(other.bigger(it)){
                return false;
            }else{
                return true;
            }
        }
        if(it._sign == 0 && other._sign == 0){
            if((it).bigger(other)){
                return false;
            }else{
                return true;
            }
        }
        return true;
    }

    bool operator<=(const LONG_INT& other) const {
        LONG_INT it(*this);
        if(it._sign == 0 && other._sign == 1){
            return true;
        }
        if(it._sign == 1 && other._sign == 0){
            return false;
        }
        if(it._sign == 1 && other._sign == 1){
            if(other.bigger(it)){
                return true;
            }else{
                return false;
            }
        }
        if(it._sign == 0 && other._sign == 0){
            if((it).bigger(other)){
                return true;
            }else{
                return false;
            }
        }
        return true;
    }

    bool operator>=(const LONG_INT& other) const {
        LONG_INT it(*this);
        if(it._sign == 0 && other._sign == 1){
            return false;
        }
        if(it._sign == 1 && other._sign == 0){
            return true;
        }
        if(it._sign == 1 && other._sign == 1){
            if(it.bigger(other)){
                return true;
            }else{
                return false;
            }
        }
        if(it._sign == 0 && other._sign == 0){
            if((other).bigger(it)){
                return true;
            }else{
                return false;
            }
        }
        return true;
    }

    friend ostream& operator<<(ostream&, const LONG_INT&);

};

ostream& operator<<(ostream& out, const LONG_INT& it){
    if(it._digits.size() == 0){
        out << 0;
    }else{
        if(it._sign == 0){
        out << '-';
        }
        for(int i = it._digits.size() - 1; i > -1; i --){
            out << (it._digits)[i];
        }
    }
    return out;
}

std::string toString(const LONG_INT& value)
{
    std::stringstream buf;
    buf << value;
    return buf.str();
}

void check(int64_t x, int64_t y)
{
    const LONG_INT bigX = x;
    const LONG_INT bigY = y;
    if ((bigX + bigY) != LONG_INT(x + y))
    {
        std::cout << x << " + " << y << " != " << x + y << " got " << bigX + bigY << '\n';
    }

    if (bigX - bigY != LONG_INT(x - y))
    {
        std::cout << x << " - " << y << " != " << x - y << " got " << bigX - bigY << '\n';
    }

    if (bigX * bigY != LONG_INT(x * y))
    {
        std::cout << x << " * " << y << " != " << x * y << " got " << bigX * bigY << '\n';
    }

    if (x != 0 && y != 0)
    {
        if (bigX / bigY != LONG_INT(x / y))
        {
            std::cout << x << " / " << y << " != " << x / y << " got " << bigX / bigY << '\n';
        }
        if (bigX % bigY != LONG_INT(x % y))
        {
            std::cout << x << " % " << y << " != " << x % y << " got " << bigX % bigY << '\n';
        }
    }
}

void doCheckEqual(const LONG_INT& actual, const char* expected, size_t line)
{
    const auto str = toString(actual);
    if (str != expected)
    {
        std::cout << "at line " << line << ": " << str << " != " << expected << '\n';
    }
}

#define checkEqual(x, y) do { doCheckEqual((x), (y), __LINE__); } while(0)
#define checkTrue(cond) do { if (!(cond)) std::cout << "at line " << __LINE__ << ": " << #cond << '\n'; } while(0)

int main()
{
    cout << (LONG_INT(0) != -LONG_INT(0));
    LONG_INT x = 3;
    checkEqual(x, "3");
    LONG_INT y = x;
    checkEqual(y, "3");
    LONG_INT z;
    checkEqual(z, "0");

    checkEqual(LONG_INT(-10), "-10");

    checkTrue(x == y);
    checkTrue(y == x);
    checkTrue(x != z);
    checkTrue(z != x);
    z = y;
    checkEqual(z, "3");

    x = 100;
    checkEqual(x, "100");

    checkTrue(!(x < x));
    checkTrue(x < 200);
    checkTrue(LONG_INT(50) < x);
    checkTrue(LONG_INT(-500) < x);
    checkTrue(LONG_INT(-500) < LONG_INT(-200));

    checkTrue(!(x > x));
    checkTrue(LONG_INT(200) > x);
    checkTrue(x > LONG_INT(50));
    checkTrue(x > LONG_INT(-500));
    checkTrue(LONG_INT(-200) > LONG_INT(-500));
    //
    checkTrue(x <= x);
    checkTrue(x <= 200);
    checkTrue(LONG_INT(50) <= x);
    checkTrue(LONG_INT(-500) <= x);
    checkTrue(LONG_INT(-500) <= LONG_INT(-200));

    checkTrue(x >= x);
    checkTrue(LONG_INT(200) >= x);
    checkTrue(x >= LONG_INT(50));
    checkTrue(x >= LONG_INT(-500));
    checkTrue(LONG_INT(-200) >= LONG_INT(-500));
    checkTrue(LONG_INT(0) == -LONG_INT(0));

    checkEqual(LONG_INT(10) + LONG_INT(10), "20");
    checkEqual(LONG_INT(-10) + LONG_INT(10), "0");
    checkEqual(LONG_INT(10) + LONG_INT(-10), "0");
    checkEqual(LONG_INT(-10) + LONG_INT(-10), "-20");
    //
    checkEqual(LONG_INT(10) - LONG_INT(10), "0");
    checkEqual(LONG_INT(-10) - LONG_INT(10), "-20");
    checkEqual(LONG_INT(10) - LONG_INT(-10), "20");
    checkEqual(LONG_INT(-10) - LONG_INT(-10), "0");
    checkEqual(LONG_INT(0) + LONG_INT(-1), "-1");
    checkEqual(LONG_INT(0) - LONG_INT(1), "-1");
    //
    checkEqual(LONG_INT(100) - LONG_INT(100), "0");
    checkEqual(LONG_INT(99) - LONG_INT(100), "-1");
    checkEqual(LONG_INT(10) - LONG_INT(11), "-1");
    checkEqual(LONG_INT(20) - LONG_INT(19), "1");

    for (int i = -21; i <= 21; ++i)
    {
        for (int j = -21; j <= 21; ++j)
        {
            check(i, j);
        }
    }
    /*
    const int64_t step = std::numeric_limits<uint32_t>::max() / 99;
    const int64_t lower = std::numeric_limits<int32_t>::min() + step;
    const int64_t upper = std::numeric_limits<int32_t>::max() - step;

    for (int64_t i = lower; i < upper; i += step)
    {
        for (int64_t j = -99; j < 99; ++j)
        {
            check(i, j);
        }
    }
    */
    const LONG_INT big1 = std::numeric_limits<int64_t>::max();
    checkEqual(big1, "9223372036854775807");

    const LONG_INT big2 = big1 * big1;
    std::cout << "9223372036854775807 * 9223372036854775807\n";
    checkEqual(big2, "85070591730234615847396907784232501249");

    const LONG_INT big3 = big2 * big2;
    std::cout << "85070591730234615847396907784232501249 * 85070591730234615847396907784232501249\n";
    checkEqual(big3, "7237005577332262210834635695349653859421902880380109739573089701262786560001");

    std::cout << "done\n";

    return 0;
}
