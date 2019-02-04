//Megan Bell
//xbox controller to control functions of robot, joystick controller to control movement of robot

#include <frc/XboxController.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <wpi/raw_ostream.h>
#include <cameraserver/CameraServer.h>
#include <frc/Servo.h>
#include <frc/TimedRobot.h>

class Robot : public frc::TimedRobot 
{
 public:
  void TeleopPeriodic() override 
  {
    //camera code may need fixing
    #if defined(__linux__)
      cs::UsbCamera videoBoi = frc::CameraServer::GetInstance()->StartAutomaticCapture();
      videoBoi.SetResolution(720, 1280);

    #else
      wpi::errs() << "Vision only available on Linux.\n";
      wpi::errs().flush();
    #endif

    //lifts rear wheels with xbox
    bool leftBumper;
    leftBumper = xbox.GetRawButton(5);

    //lifts front wheels with xbox
    bool rightBumper;
    rightBumper = xbox.GetRawButton(6);

    //brings wheels down with x box
    double rightTrigger;
    rightTrigger = xbox.GetRawAxis(3);

    //controls arm with xbox
    double leftJoystick;
    leftJoystick = xbox.GetRawAxis(1);
    upAndDownArmMotor.Set(leftJoystick);

    //controlls knuckle/wrist with xbox
    double rightJoystick;
    rightJoystick = xbox.GetRawAxis(5);
    upAndDownWristMotor.Set(rightJoystick);

    //open claw with xbox
    bool aButton;
    aButton = xbox.GetRawButton(1);

    //closes claw with xbox
    bool bButton;
    bButton = xbox.GetRawButton(2);

    //controls forward and backward movement of robot with joystick
    bool joystickYAxis;
    joystickYAxis = joystick.GetRawAxis(1);

    //controls pivot with joystick
    bool joystickRotateZAxis;
    joystickRotateZAxis = joystick.GetRawAxis(2);

    //controls angle of camera
    bool button5;
    button5 = joystick.GetRawButton(5);

    //controls angle of camera
    bool button6;
    button6 = joystick.GetRawButton(6);


  //change speed, spin clockwise or counterclockwise of motors?
  
  //brings wheels down with xbox
    if(rightTrigger>.5)
  {
    frontWheelsMotor.Set(-.5);
    rearWheelsMotor.Set(-.5);
  } 
  //lifts rear wheels with xbox
  if(leftBumper)
  {
    rearWheelsMotor.Set(.5);
  }
  else
  {
    rearWheelsMotor.Set(0);
  }
  //lifts front wheels with xbox
  if(rightBumper)
  {
    frontWheelsMotor.Set(.5);
  }
  else
  {
    frontWheelsMotor.Set(0);
  }
  //opens claw with xbox
  if(aButton)
  {
    clawMotor.Set(.5);
  }
  //closes claw with xbox
  else if(bButton)
  {
    clawMotor.Set(-.5);
  }
  else
  {
    clawMotor.Set(0);
  }



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



  //sets camera angle 
  if (button6) 
  {
    servo.SetAngle(0.0);
  }
  //sets camera angle
  else if (button5) 
  {
    servo.SetAngle(90.0);
  }
  //sets camera angle
  else
  {
    servo.SetAngle(15.0);
  }

  }

 private:
  frc::Joystick joystick{0};
  frc::XboxController xbox{1};
  //Motor numbers and brand will need to change
  frc::Spark rearWheelsMotor{0};
  frc::Spark frontWheelsMotor{1};
  frc::Spark upAndDownArmMotor{3};
  frc::Spark upAndDownWristMotor{4};
  frc::Spark clawMotor{5};
  frc::Spark leftWheelMotor{6};
  frc::Spark rightWheelMotor{7};
  frc::Servo servo{8};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
