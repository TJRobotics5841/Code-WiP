//Megan Bell
//Gabe Najera
//xbox controller to control functions of robot and camera angle, joystick controller to control movement of robot

#include <frc/XboxController.h>
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <wpi/raw_ostream.h>
#include <cameraserver/CameraServer.h>
#include <frc/Servo.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>

class Robot : public frc::TimedRobot 
{
public:

void RobotInit() override
{
//camera code may need fixing, go into robot init
#if defined(__linux__)

// Get the USB camera from CameraServer
frc::CameraServer::GetInstance()->StartAutomaticCapture("Camera 5841",0);

#else
wpi::errs() << "Vision only available on Linux.\n";
wpi::errs().flush();
#endif
}
//begin auto code
void AutonomousPeriodic() {
    //controls wrist with xbox
double leftJoystick;
leftJoystick = xbox.GetRawAxis(1);
upAndDownWristMotor.Set(leftJoystick/2.5);

//controlls arm with xbox
double rightJoystick;
rightJoystick = xbox.GetRawAxis(5);
topUpAndDownArmMotor.Set(-rightJoystick/2);
bottomUpAndDownArmMotor.Set(-leftJoystick/2);

//open and close claw with xbox
bool rTrigger;
rTrigger = xbox.GetRawButton(5);

bool lTrigger;
lTrigger = xbox.GetRawButton(6);

//LIGHTSPEED ACTIVATE
float lightspeed = 1;
bool toggle;

if (joystick.GetRawButton(3) && toggle == false) {
lightspeed = 1.5;
toggle = true;
} else if (joystick.GetRawButton(3) && toggle == true) {
lightspeed = 1;
toggle = false;
}

//moves robot with joystick
m_robotDrive.ArcadeDrive(joystick.GetY() * lightspeed, joystick.GetX());

//controls angle of camera with joystick
bool button5;
button5 = joystick.GetRawButton(5);

//controls angle of camera with joystick
bool button6;
button6 = joystick.GetRawButton(6);

//controls angle of camera with joystick
bool button4;
button4 = joystick.GetRawButton(4);

//locks motor in place (hopefully)
if (rightJoystick == .5)
{
topUpAndDownArmMotor.Set(.4);
bottomUpAndDownArmMotor.Set(.4);
}

if(lTrigger)
{
lClawMotor.Set(1);
rClawMotor.Set(1);

}
//closes claw with xbox
else if(rTrigger)
{
lClawMotor.Set(-1);
rClawMotor.Set(-1);
}

else
{
lClawMotor.Set(0);
rClawMotor.Set(0);
}


//sets camera angle 
float servoAngle = 15.0;

if (button6) 
{
servoAngle++;
servo.SetAngle(servoAngle);
}

//sets camera angle
else if (button4) 
{
servoAngle--; 
servo.SetAngle(servoAngle);
}

//sets camera angle
else if(button5)
{
servo.SetAngle(15.0);
}
}

void TeleopPeriodic()
{
//controls wrist with xbox
double leftJoystick;
leftJoystick = xbox.GetRawAxis(1);
upAndDownWristMotor.Set(leftJoystick/2.5);

//controlls arm with xbox
double rightJoystick;
rightJoystick = xbox.GetRawAxis(5);
topUpAndDownArmMotor.Set(-rightJoystick/2);
bottomUpAndDownArmMotor.Set(-leftJoystick/2);

//open and close claw with xbox
bool rTrigger;
rTrigger = xbox.GetRawButton(5);

bool lTrigger;
lTrigger = xbox.GetRawButton(6);

//LIGHTSPEED ACTIVATE
float lightspeed = 1;
bool toggle;

if (joystick.GetRawButton(3) && toggle == false) {
lightspeed = 1.5;
toggle = true;
} else if (joystick.GetRawButton(3) && toggle == true) {
lightspeed = 1;
toggle = false;
}

//moves robot with joystick
m_robotDrive.ArcadeDrive(joystick.GetY() * lightspeed, joystick.GetX());

//controls angle of camera with joystick
bool button5;
button5 = joystick.GetRawButton(5);

//controls angle of camera with joystick
bool button6;
button6 = joystick.GetRawButton(6);

//controls angle of camera with joystick
bool button4;
button4 = joystick.GetRawButton(4);

//locks motor in place (hopefully)
if (rightJoystick == .5)
{
topUpAndDownArmMotor.Set(.4);
bottomUpAndDownArmMotor.Set(.4);
}

if(lTrigger)
{
lClawMotor.Set(1);
rClawMotor.Set(1);

}
//closes claw with xbox
else if(rTrigger)
{
lClawMotor.Set(-1);
rClawMotor.Set(-1);
}

else
{
lClawMotor.Set(0);
rClawMotor.Set(0);
}


//sets camera angle 
float servoAngle = 15.0;

if (button6) 
{
servoAngle++;
servo.SetAngle(servoAngle);
}

//sets camera angle
else if (button4) 
{
servoAngle--; 
servo.SetAngle(servoAngle);
}

//sets camera angle
else if(button5)
{
servo.SetAngle(15.0);
}
}

private:
frc::Joystick joystick{0};
frc::XboxController xbox{1};
frc::Servo servo{6};

//these may not be correct but they should be
frc::PWMVictorSPX upAndDownWristMotor{3};
frc::PWMVictorSPX topUpAndDownArmMotor{2};
frc::PWMVictorSPX bottomUpAndDownArmMotor{8};
frc::PWMVictorSPX rClawMotor{7};
frc::PWMVictorSPX lClawMotor{5};

//drive motor may be switched
frc::PWMVictorSPX leftWheelMotor{0};
frc::PWMVictorSPX rightWheelMotor{1};
frc::DifferentialDrive m_robotDrive{leftWheelMotor,rightWheelMotor};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
//RIP Shag, 2019-2019
