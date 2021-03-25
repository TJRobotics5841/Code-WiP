//Megan Bell
//Joystick motor controller
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <frc/TimedRobot.h>

class Robot : public frc::TimedRobot {
 public:
  void TeleopPeriodic() override 
  {
    bool joystickYAxis;
    joystickYAxis = joystick.GetRawAxis(1);

    bool joystickRotateZAxis;
    joystickRotateZAxis = joystick.GetRawAxis(2);

//will have to change speed, motor location, and direction

//moves the robot forward with push forward of joystick
  if(joystickYAxis>.5)
  {
    leftWheelMotor.Set(.5);
    rightWheelMotor.Set(.5);
  }

  //moves the robot backward with pull backward of joystick
  else if(joystickYAxis<.5)
  {
    leftWheelMotor.Set(-.5);
    rightWheelMotor.Set(-.5);
  }

//rotates the robot counterclockwise with joystick's z axis
  if(joystickRotateZAxis<75)
  {
    leftWheelMotor.Set(.25);
    rightWheelMotor.Set(0);
  }
//rotates the robot clockwise with joystick's z axis
  else if(joystickRotateZAxis>25)
  {
    leftWheelMotor.Set(0);
    rightWheelMotor.Set(.25);
  }

//when the joystick is not in use the robot does not move
  else
  {
    leftWheelMotor.Set(0);
    rightWheelMotor.Set(0);
  }
  
  }

 private:
  frc::Joystick joystick{0};
  frc::Spark leftWheelMotor{0};
  frc::Spark rightWheelMotor{1};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
