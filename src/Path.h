#ifndef Path_H_
#define Path_H_

#include "Robot.h"

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

    Path() {}
    Path(Robot robot, Step steps[]) {
        _robot = robot;
        _steps = steps;
    }
    
    void _executeStep(Step step, int direction = 1) {
        if (step.state == MOVE){
            _robot.move(step.value * direction);
        } else {
            _robot.rotate(step.value * direction);
        }
    }

    void execute(int length) {
        for (int i = 0; i < length; i++) {
            _executeStep(_steps[i]);
        }
    }

    void reverse(int length) {
        for (int i = length; i > 0; i--) {
            _executeStep(_steps[i], -1);
        }
    }
};

#endif