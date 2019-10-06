#ifndef Path_H_
#define Path_H_

#include "Robot.h"

enum State {
    MOVE,
    ROTATE,
    TURN,
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
        if (step.state == MOVE) {
            _robot.move(step.value);
        } else if (step.state == ROTATE) {
            _robot.rotate(step.value * direction);
        } else {
            _robot.turn(step.value * direction);
        }
    }

    void execute(int length) {
        for (int i = 0; i < length; i++) {
            _executeStep(_steps[i]);
        }
    }

    void reverse(int length) {
        delay(500);
        _robot.turn(180);
        delay(500);
        for (int i = length - 1; i >= 0; i--) {
            _executeStep(_steps[i], -1);
        }
    }
};

#endif