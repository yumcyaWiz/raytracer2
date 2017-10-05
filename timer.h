#ifndef TIMER_H
#define TIMER_H
#include <chrono>
class Timer {
    public:
        std::chrono::system_clock::time_point t_start;
        std::chrono::system_clock::time_point t_end;

        Timer() {};
        ~Timer() {};

        void start() { t_start = std::chrono::system_clock::now(); };
        void stop() {
            t_end = std::chrono::system_clock::now();
            auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
            std::cout << msec << "ms\n";
        };
};
#endif
