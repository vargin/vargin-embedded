#include <stdint.h>
#include "scheduler.h"

Scheduler::Scheduler(uint8_t maxScheduleLength, uint8_t maxBufferLength) {
  pBuffer = new uint8_t[maxBufferLength];
  pBufferIndex = 0;
  pMaxBufferLength = maxBufferLength;

  pSchedules = new uint32_t[maxScheduleLength];
  pScheduleIndex = 0;
  pMaxScheduleLength = maxScheduleLength;
}

void Scheduler::push(uint8_t digit) {
  if (pBufferIndex == pMaxBufferLength) {
    return;
  }

  pBuffer[pBufferIndex++] = digit;
}

uint32_t Scheduler::commit(CommitType commitType) {
  uint32_t numberOfSeconds = 0;
  for (uint8_t i = 0; i < pBufferIndex; i++) {
    uint32_t multiplier = 1;
    uint8_t power = pBufferIndex - i - 1;
    if (power > 0) {
      for (uint8_t multiplierIndex = 0; multiplierIndex < power; multiplierIndex++) {
        multiplier *= 10;
      }
    }

    numberOfSeconds += pBuffer[i] * multiplier;
  }

  switch (commitType) {
    case CommitType::Minutes:
      numberOfSeconds *= 60;
      break;
    case CommitType::Hours:
      numberOfSeconds *= 60 * 60;
      break;
    default:
      break;
  }

  pBufferIndex = 0;

  pSchedules[pScheduleIndex++] = numberOfSeconds;

  return numberOfSeconds;
}

uint8_t *Scheduler::getBuffer() {
  return pBuffer;
}

uint8_t Scheduler::getBufferLength() {
  return pBufferIndex;
}