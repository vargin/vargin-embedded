#include <stdint.h>

#ifndef MIKATRON_SCHEDULER_H
#define MIKATRON_SCHEDULER_H

enum CommitType {
  Seconds = 1,
  Minutes,
  Hours,
  Time
};

class Scheduler {
public:
  Scheduler(uint8_t maxScheduleLength, uint8_t maxBufferLength);

  void push(uint8_t digit);

  uint32_t commit(CommitType commitType);

private:
  uint8_t *pBuffer;
  uint8_t pBufferIndex;
  uint8_t pMaxBufferLength;

  uint32_t *pSchedules;
  uint8_t pScheduleIndex;
  uint8_t pMaxScheduleLength;
};


#endif //MIKATRON_SCHEDULER_H
