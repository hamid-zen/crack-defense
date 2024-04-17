/*
 * This timer handles ticks, ticks are a predetermined duration, usually in msecs.
 * This is part of 2f, a 2D game engine based on SFML I'm currently creating.
 */

#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class timer
{
private:
    int _tick_duration; // Tick duration in msec
    int _max_tick;      // Max ticks before max ticks gets back to 0
    int _current_tick;  // Current tick
    bool _update;       // If the tick count has updated
    /* Timers */
    std::chrono::time_point<std::chrono::system_clock> _start; // Time start
    std::chrono::time_point<std::chrono::system_clock> _end;   // End
    std::chrono::duration<double> _elapsed;                    // Delta
    /* Calculations */
    void calculate(); // Calculates the stuff

public:
    timer(int const &tick_duration, int const &max_tick = 10000); // Creates a timer
    /* Getters */
    int get_tick(); // Returns current tick
    /* Setters */
    void set_tick_duration(int const &d); // Sets tick duration
    void set_max_tick(int const &max);    // Sets max tick
    /* Methods */
    void start();   // Starts the timer
    void reset();   // Resets the timer
    bool updated(); // If the tick count has changed
};

#endif
