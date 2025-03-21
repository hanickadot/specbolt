#pragma once

#ifndef SPECBOLT_MODULES
#include <algorithm>
#include <limits>
#include <vector>
#endif

namespace specbolt {

SPECBOLT_EXPORT
class Scheduler {
public:
  class Task {
  public:
    Task() = default;
    virtual ~Task() = default;
    virtual void run(std::size_t cycles) = 0;
    Task(const Task &) = delete;
    Task &operator=(const Task &) = delete;
  };

  void schedule(Task &task, const std::size_t in_cycles) {
    const auto insertion_point = std::ranges::lower_bound(tasks_, in_cycles, {}, &ScheduledTask::cycle);
    tasks_.insert(insertion_point, ScheduledTask{cycles_ + in_cycles, &task});
  }

  void tick(const size_t cycles) {
    const auto end_cycle = cycles_ + cycles;
    while (cycles_ < end_cycle) {
      if (tasks_.empty())
        break;
      // Take a _copy_ of the information about the front task.
      if (auto [cycle, task] = tasks_.front(); cycle <= end_cycle) {
        tasks_.erase(tasks_.begin()); // Remove immediately.

        cycles_ = cycle;
        task->run(cycle);
      }
      else {
        break;
      }
    }
    cycles_ = end_cycle;
  }

  [[nodiscard]] std::size_t headroom() const {
    return tasks_.empty() ? std::numeric_limits<size_t>::max() : tasks_.front().cycle - cycles_;
  }

  [[nodiscard]] auto cycles() const { return cycles_; }

private:
  std::size_t cycles_ = 0;
  struct ScheduledTask {
    std::size_t cycle{};
    Task *task{};
  };
  std::vector<ScheduledTask> tasks_;
};

} // namespace specbolt
