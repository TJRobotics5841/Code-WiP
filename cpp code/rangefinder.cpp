/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/AnalogInput.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

/**
 * This is a sample program demonstrating how to use an ultrasonic sensor and
 * proportional control to maintain a set distance from an object.
 */
class Robot : public frc::TimedRobot {
 public:
  /**
   * Tells the robot to drive to a set distance (in inches) from an object using
   * proportional control.
   */
  void TeleopPeriodic() override {
    // Sensor returns a value from 0-4095 that is scaled to inches
    double currentDistance = m_ultrasonic.GetValue() * kValueToInches;
    std::cout << currentDistance;
    frc::SmartDashboard::PutNumber("haha end me", currentDistance);
    // Convert distance error to a motor speed
    while (currentDistance != kHoldDistance) {
      if (currentDistance < kHoldDistance) {
        drive.ArcadeDrive(0, -.3);
      }
    }

  }

 private:
  // Distance in inches the robot wants to stay from an object
  static constexpr int kHoldDistance = 24;

  // Factor to convert sensor values to a distance in inches
  static constexpr double kValueToInches = 0.125;

  // Proportional speed constant
  static constexpr int kUltrasonicPort = 0;

  frc::AnalogInput m_ultrasonic{kUltrasonicPort};
  frc::PWMVictorSPX m_right{1};
  frc::PWMVictorSPX m_left{0};
  frc::DifferentialDrive drive{m_right, m_right};


};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
