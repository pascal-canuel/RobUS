#ifndef Path_H_
#define Path_H_

#include "Robot.h"
#include <stddef.h>

enum State {
    MOVE,
    ROTATE
};

struct Step
{
    State state;
    float value;
};

struct Path
{
    Robot _robot;
    Step* _steps;

    Path(Robot robot, Step steps[]) {
        _robot = robot;
        _steps = steps;
    }
    
    void _executeStep(Step step, int direction = 1) {
        if(step.state == MOVE){
            _robot.move(step.value * direction);
        } else {
            _robot.rotate(step.value * direction);
        }
    }

    template <size_t length>
    void execute() {
        for(Step step: _steps) {
            _executeStep(step);
        }
    }

    template <size_t length>
    void reverse() {
        for (int i = length; i > 0; i--) {
            Serial.println(i);
            _reverseStep(path[i]);
        }
    }
};

/*
template <size_t length>
void execute(Step (&path)[length]) {
  for (Step step: path) {

  }
}
*/

#endif