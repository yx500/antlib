#pragma once


#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>

namespace alib::tools {


using clk        = std::chrono::high_resolution_clock;
using time_point = std::chrono::time_point<clk>;
using std::chrono::duration;
using std::chrono::duration_cast;

class ProfilerTimer {
  time_point  start_;
  std::string label;
public:


  explicit ProfilerTimer(std::string label_) : start_{clk::now()}, label{std::move(label_)} {}

  ProfilerTimer(const ProfilerTimer& other) = default;
  ProfilerTimer& operator=(const ProfilerTimer& other) = default;

  ProfilerTimer(ProfilerTimer&& other) = default;
  ProfilerTimer& operator=(ProfilerTimer&& other) = default;

  ~ProfilerTimer() { print(); }

  void print() {
    time_point finish_         = clk::now();
    auto elapsed    = finish_ - start_;
    auto elapsed_s  = duration_cast<duration<double>>(elapsed).count();
    auto elapsed_ms = elapsed_s * 1000;
    char buf[50]{0};                                                // NOLINT
    std::sprintf(buf, "%-20s %12.4f ms", label.data(), elapsed_ms); // NOLINT
    std::cerr << buf << '\n';                                       // NOLINT
  }
};






} // namespace
