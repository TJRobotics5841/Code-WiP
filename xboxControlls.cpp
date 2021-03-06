//Megan Bell
//xbox controller to control functions of robot

#include <frc/XboxController.h>
#include <frc/Spark.h>
#include <frc/TimedRobot.h>

class Robot : public frc::TimedRobot 
{
 public:
  void TeleopPeriodic() override 
  {
    //lifts rear wheels
    bool leftBumper;
    leftBumper = xbox.GetRawButton(5);

    //lifts front wheels
    bool rightBumper;
    rightBumper = xbox.GetRawButton(6);

    //brings wheels down
    double rightTrigger;
    rightTrigger = xbox.GetRawAxis(3);

    //controls arm
    double leftJoystick;
    leftJoystick = xbox.GetRawAxis(1);
    upAndDownArmMotor.Set(leftJoystick);

    //controlls knuckle/wrist
    double rightJoystick;
    rightJoystick = xbox.GetRawAxis(5);
    upAndDownWristMotor.Set(rightJoystick);

    //open claw
    bool aButton;
    aButton = xbox.GetRawButton(1);

    //closes claw
    bool bButton;
    bButton = xbox.GetRawButton(2);

  //change speed, spin clockwise or counterclockwise?
    if(rightTrigger>.5)
  {
    frontWheelsMotor.Set(-.5);
    rearWheelsMotor.Set(-.5);
  } 

  if(leftBumper)
  {
    rearWheelsMotor.Set(.5);
  }
  else
  {
    rearWheelsMotor.Set(0);
  }

  if(rightBumper)
  {
    frontWheelsMotor.Set(.5);
  }
  else
  {
    frontWheelsMotor.Set(0);
  }

  if(aButton)
  {
    clawMotor.Set(.5);
  }
  else if(bButton)
  {
    clawMotor.Set(-.5);
  }
  else
  {
    clawMotor.Set(0);
  }

  }

 private:
  frc::XboxController xbox{0};
  //Motor numbers and brand will need to change
  frc::Spark rearWheelsMotor{0};
  frc::Spark frontWheelsMotor{1};
  frc::Spark upAndDownArmMotor{3};
  frc::Spark upAndDownWristMotor{4};
  frc::Spark clawMotor{5};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
