#ifndef SOLVER_H
#define SOLVER_H

#include <cmath>
#include <functional>
#include <vector>

template <typename T>
using CalcFunc = std::function<void(T&)>;

class Solver {
public:
    explicit Solver(double br_koef = 0.7, double epsilon = 1e-3)
        : br_koef_{br_koef}, epsilon_{epsilon} {
    };

    template <typename T>
    void Solve(T& res0, CalcFunc<T>& calc_func) {
        T res1 = res0;
        do {
            res1 = res0 + (res1 - res0) * br_koef_;
            res0 = res1;
            calc_func(res1);
        } while (std::abs(res1 - res0) > epsilon_);
    }
private:
    // braking coefficient
    double br_koef_;
    // accuracy
    double epsilon_;
};

#endif // SOLVER_H
