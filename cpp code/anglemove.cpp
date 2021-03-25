/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <cmath>
#include <frc/AnalogGyro.h>
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/smartdashboard/Smartdashboard.h>
#include <frc/ADXRS450_Gyro.h>
#include <frc/SPI.h>


/**
 * This is a sample program to demonstrate how to use a gyro sensor to make a
 * robot drive straight. This program uses a joystick to drive forwards and
 * backwards while the gyro is used for direction keeping.
 */
class Robot : public frc::TimedRobot {
 public:

  double turnBot(int angle, int target) {
    if (angle > target) {
      //for (int i; i == diff; i++) {
        return 0.3;
      //z}
   } else if (angle < target) {
        return -0.3;
   } else if (target == 90) {
        return 1;
   }
    else {
      return 0;
    }
  } 
  void RobotInit() override { 
    //m_gyro.Calibrate(); 
  }

  /**
   * The motor speed is set from the joystick while the DifferentialDrive
   * turning value is assigned from the error between the setpoint and the gyro
   * angle.
   */
  void TeleopPeriodic() override {
    //double turningValue = (kAngleSetpoint - m_gyro.GetAngle()) * kP;
    int currentAngle = std::floor(m_gyro.GetAngle());
    int angleDifference = std::floor(currentAngle - 0);
    int targetAngle = 0;

    if (m_joystick.GetTrigger()) {
      targetAngle = 90;
      m_robotDrive.ArcadeDrive(0, turnBot(currentAngle, targetAngle));
    }

    // Invert the direction of the turn if we are going backwards
    // turningValue = std::copysign(turningValue, m_joystick.GetY());
    if (m_joystick.GetY() > 0.2 || m_joystick.GetY() < -0.2) {
      m_robotDrive.ArcadeDrive(m_joystick.GetY(), turnBot(currentAngle, targetAngle));
    }
    
    frc::SmartDashboard::PutNumber("Angle", m_gyro.GetAngle());
  }

 private:
  static constexpr double kAngleSetpoint = 0.0;
  static constexpr double kP = 0.005;  // Proportional turning constant

  // Gyro calibration constant, may need to be adjusted. Gyro value of 360 is
  // set to correspond to one full revolution.
  static constexpr double kVoltsPerDegreePerSecond = 0.0128;

  static constexpr int kLeftMotorPort  = 2;
  static constexpr int kRightMotorPort = 3;
  static constexpr int kGyroPort = 0;
  static constexpr int kJoystickPort = 0;

  frc::PWMVictorSPX m_left{kLeftMotorPort};
  frc::PWMVictorSPX m_right{kRightMotorPort};
  frc::DifferentialDrive m_robotDrive{m_left, m_right};

  frc::ADXRS450_Gyro m_gyro{frc::SPI::Port(0)};
  frc::Joystick m_joystick{kJoystickPort};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
