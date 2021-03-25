/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <cameraserver/CameraServer.h>
#include <cscore_oo.h>
#include <frc/TimedRobot.h>
#include <wpi/raw_ostream.h>
#include <Joystick.h>
#include <frc/Servo.h>

/**
 * Uses the CameraServer class to automatically capture video from a USB webcam
 * and send it to the FRC dashboard without doing any vision processing. This is
 * the easiest way to get camera images to the dashboard. Just add this to the
 * RobotInit() method in your program.
 */
class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override {

#if defined(__linux__)
  cs::UsbCamera videoBoi = frc::CameraServer::GetInstance()->StartAutomaticCapture();
  //videoBoi.SetResolution(1080, 1920);

#else
    wpi::errs() << "Vision only available on Linux.\n";
    wpi::errs().flush();
#endif
  }
  void TeleopPeriodic() {

    bool button5;
    button5 = joy.GetRawButton(5);

    bool button6;
    button6 = joy.GetRawButton(6);

    if (button6) {
      s_servo1.SetAngle(0.0);
    } else if (button5) {
      s_servo1.SetAngle(90.0);
    }
    else{
      s_servo1.SetAngle(15.0);
    }
  }
  private:
  frc::Joystick joy{0};
  frc::Servo s_servo1{6};

};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
