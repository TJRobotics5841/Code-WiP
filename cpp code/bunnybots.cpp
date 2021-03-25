#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/drive/DifferentialDrive.h>
#include <cameraserver/CameraServer.h>
#include <wpi/raw_ostream.h>
#include <frc/AnalogInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <frc/Timer.h>
 
class Robot : public frc::TimedRobot {
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
 
 void AutonomousInit(){
   timer.Reset();
   timer.Start();
   
 }


 void AutonomousPeriodic() {
 /*
 5 points awarded for crossing into neutral zone during auto period
 Can not cross into the opponents zone
 Ranking point for ball in one low goal and high goal
 No human interaction
 */

//just move forward some and stop while having intake on

  if (timer.Get() < 4.0){
    robotDrive.ArcadeDrive(-0.55, 0);
    intake.Set(-.5);
  }
  else if (timer.Get() < 8.0){
    robotDrive.ArcadeDrive(0.55,0);
    intake.Set(0);
 
  }
  else if (timer.Get() < 10.0){
    robotDrive.ArcadeDrive(0,0);
    intake.Set(0);
         output1.Set(-.75);
     output2.Set(.75);
  }
  else{
        robotDrive.ArcadeDrive(0,0);
    intake.Set(0);
         output1.Set(0);
     output2.Set(0);
  }
}
 
 void TeleopPeriodic() override {
   robotDrive.ArcadeDrive(joystick.GetY(), joystick.GetX()/1.25);
  
 
   //both will be used for input
   double lTrigger = xbox.GetRawAxis(2);
   bool  lBackButton = xbox.GetRawButton(5);
 
   //takes in balls with push of button of trigger
   if(lTrigger > .5 || lBackButton) {
     intake.Set(-.75);
   } else {
     intake.Set(0);
   }
 
   //both will be used for output
   double rTrigger = xbox.GetRawAxis(3);
   bool rBackButton = xbox.GetRawButton(6);
   frc::SmartDashboard::PutNumber("sweetspot", rTrigger);
   //shoots out balls with push of trigger
   if(rBackButton) {
     output1.Set(-.75);
     output2.Set(.75);   
   } else if (rTrigger > .05){
     output1.Set(-rTrigger);
     output2.Set(rTrigger);
   } else {
     output1.Set(0);
     output2.Set(0);
   }
  
   //gets the value of distance from something in inches
   double currentDistance = sensor.GetValue()*0.125;
   frc::SmartDashboard::PutNumber("Distance", currentDistance);
 
   //tells the driver if they are in shootinig distance
   //std::string message
   while (currentDistance < 24){
     if (currentDistance>16){
        //if (frc::SmartDashboard::GetString("Warn", "If you wish to shoot, back up") || frc::SmartDashboard::GetString("Warn", "" )) {
          frc::SmartDashboard::PutString("Warn" , "You are in key shooting distance");
        //}
     }
     if (currentDistance<16){
        //if (frc::SmartDashboard::GetString("Warn", "You are in key shooting distance") || frc::SmartDashboard::GetString("Warn", "" )) {
          frc::SmartDashboard::PutString("Warn", "If you wish to shoot, back up");
        //}
     }
   }
 
 }
 
private:
 frc::Joystick joystick{0};
 frc::XboxController xbox{1};
 
 frc::AnalogInput sensor{0};
 
 //will have to be verified after wiring
 frc::PWMVictorSPX lDrive{2};
 frc::PWMVictorSPX rDrive{3};
 frc::PWMVictorSPX intake{0};
 frc::PWMVictorSPX output1{1};
 frc::PWMVictorSPX output2{4};
 frc::DifferentialDrive robotDrive{lDrive, rDrive};

 frc::Timer timer;
};
 
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
