#include <rational.h>
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <numeric>

Rational::Rational(int value) {           // NOLINT
    Set(value, static_cast<int64_t>(1));  // NOLINT
}  // NOLINT

Rational::Rational(int numer, int denom) {
    Set(static_cast<int64_t>(numer), static_cast<int64_t>(denom));
}

Rational::Rational() {
    Set(static_cast<int64_t>(0), static_cast<int64_t>(1));
}

int Rational::GetNumerator() const {
    return static_cast<int>(numer_);
}

int Rational::GetDenominator() const {
    return static_cast<int>(denom_);
}
void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    int64_t gcd = std::gcd(numer, denom);
    numer_ = numer / gcd;
    denom_ = denom / gcd;
    if (denom < 0) {
        numer_ *= -1;
        denom_ *= -1;
    }
}

void Rational::SetNumerator(int value) {
    Set(value, denom_);
}

void Rational::SetDenominator(int value) {
    Set(numer_, value);
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int64_t new_denom = std::lcm(lhs.denom_, rhs.denom_);
    int64_t multiply_by_first_ratio = new_denom / lhs.denom_;
    int64_t multiply_by_second_ratio = new_denom / rhs.denom_;
    int64_t new_numer = lhs.numer_ * multiply_by_first_ratio + rhs.numer_ * multiply_by_second_ratio;
    lhs.Set(new_numer, new_denom);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.Set(lhs.numer_ * rhs.numer_, lhs.denom_ * rhs.denom_);
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.numer_ += ratio.denom_;
    if (ratio.numer_ % ratio.denom_ == 0) {
        ratio.numer_ /= ratio.denom_;
        ratio.denom_ = static_cast<int64_t>(1);
    }
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.numer_ -= ratio.denom_;
    if (ratio.numer_ % ratio.denom_ == 0) {
        ratio.numer_ /= ratio.denom_;
        ratio.denom_ = static_cast<int64_t>(1);
    }
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    std::string s1;
    is >> s1;
    std::string numer;
    std::string denom;
    bool have_found_slash = false;
    for (size_t i = static_cast<size_t>(0); i < s1.size(); ++i) {
        if (s1[i] == '/') {
            have_found_slash = true;
            break;
        }
        if (!have_found_slash) {
            numer.push_back(s1[i]);
        } else {
            denom.push_back(s1[i]);
        }
    }
    if (denom.empty()) {
        denom = "1";
    }
    ratio.SetNumerator(std::stoi(numer));
    ratio.SetDenominator(std::stoi(denom));
    return is;
}

Rational operator+(const Rational& ratio) {
    return Rational(ratio.GetNumerator(), ratio.GetDenominator());
};

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
};

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs += -rhs;
    return lhs;
};

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    Rational flp = Rational(rhs.GetDenominator(), rhs.GetNumerator());
    lhs *= flp;
    return lhs;
};

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int64_t new_denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int64_t multiply_by_first_ratio = new_denom / lhs.GetDenominator();
    int64_t multiply_by_second_ratio = new_denom / rhs.GetDenominator();
    return Rational(
        static_cast<int>(lhs.GetNumerator() * multiply_by_first_ratio + rhs.GetNumerator() * multiply_by_second_ratio),
        static_cast<int>(new_denom));
};

Rational operator-(const Rational& lhs, const Rational& rhs) {
    return lhs + -rhs;
};

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational ret = Rational(lhs.GetNumerator(), lhs.GetDenominator());
    ret *= rhs;
    return ret;
};

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational ret = Rational(lhs.GetNumerator(), lhs.GetDenominator());
    ret /= rhs;
    return ret;
};

Rational operator++(Rational& ratio, int) {
    Rational ret = ratio;
    ratio.SetNumerator(ratio.GetNumerator() + ratio.GetDenominator());
    return ret;
};

Rational operator--(Rational& ratio, int) {
    Rational ret = ratio;
    ratio.SetNumerator(ratio.GetNumerator() - ratio.GetDenominator());
    return ret;
};

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() < lhs.GetDenominator() * rhs.GetNumerator();
};

bool operator>(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() > lhs.GetDenominator() * rhs.GetNumerator();
};

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() <= lhs.GetDenominator() * rhs.GetNumerator();
};

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() >= lhs.GetDenominator() * rhs.GetNumerator();
};

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() == rhs.GetNumerator() && lhs.GetDenominator() == rhs.GetDenominator();
};

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() != rhs.GetNumerator() || lhs.GetDenominator() != rhs.GetDenominator();
};

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    os << ratio.GetNumerator();
    if (ratio.GetDenominator() != 1) {
        os << "/" << ratio.GetDenominator();
    }
    return os;
};