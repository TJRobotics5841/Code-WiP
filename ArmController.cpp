/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>

/**
 * This sample program shows how to control a motor using a joystick. In the
 * operator control part of the program, the joystick is read and the value is
 * written to the motor.
 *
 * Joystick analog values range from -1 to 1 and speed controller inputs as
 * range from -1 to 1 making it easy to work together.
 */
class Robot : public frc::TimedRobot {
 public:
  void TeleopPeriodic() override { 
    m_motor1.Set(m_control.GetY(kLeft)/4);
    m_motor2.Set(m_control.GetY(kLeft)/4);
    m_motor3.Set(m_control.GetY(kRight)/2);
  
    }

 private:
  frc::XboxController m_control{0};
  frc::Spark m_motor1{0};
  frc::Spark m_motor2{1};
  frc::Spark m_motor3{2};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
