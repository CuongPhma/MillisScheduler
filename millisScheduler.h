#ifndef MILLIS_SCHEDULER_H
#define MILLIS_SCHEDULER_H

#define MAX_TASKS 10

typedef void (*TaskFunction)();

struct Task {
  unsigned long interval;
  unsigned long lastRun;
  TaskFunction func;
  bool active;
};

class MillisScheduler {
private:
  Task tasks[MAX_TASKS];

public:
  MillisScheduler() {
    for (int i = 0; i < MAX_TASKS; i++) {
      tasks[i].active = false;
    }
  }

  void addTask(unsigned long interval, TaskFunction func) {
    for (int i = 0; i < MAX_TASKS; i++) {
      if (!tasks[i].active) {
        tasks[i].interval = interval;
        tasks[i].lastRun = 0;
        tasks[i].func = func;
        tasks[i].active = true;
        return;
      }
    }
  }

  void update() {
    unsigned long now = millis();
    for (int i = 0; i < MAX_TASKS; i++) {
      if (tasks[i].active && (now - tasks[i].lastRun >= tasks[i].interval)) {
        tasks[i].lastRun = now;
        tasks[i].func();
      }
    }
  }
};

#endif
