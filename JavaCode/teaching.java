// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package frc.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.PWMVictorSPX;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.drive.DifferentialDrive;
import edu.wpi.first.wpilibj.XboxController;
import edu.wpi.first.wpilibj.GenericHID.Hand;

/**
 * This is a demo program showing the use of the DifferentialDrive class. Runs the motors with
 * arcade steering.
 */
public class Robot extends TimedRobot {
  private final PWMVictorSPX m_leftMotor = new PWMVictorSPX(2);
  private final PWMVictorSPX m_rightMotor = new PWMVictorSPX(3);
  private final DifferentialDrive m_robotDrive = new DifferentialDrive(m_leftMotor, m_rightMotor);
  //private final Joystick m_stick = new Joystick(0);
  private final XboxController xbox = new XboxController(0);
  private final PWMVictorSPX intakeMotor = new PWMVictorSPX(0);
  private final PWMVictorSPX outputMotorLeft = new PWMVictorSPX(1);
  private final PWMVictorSPX outputMotorRight = new PWMVictorSPX(4);


  @Override
  public void teleopPeriodic() {
    // Drive with arcade drive.
    // That means that the Y axis drives forward
    // and backward, and the X turns left and right.
    m_robotDrive.arcadeDrive(xbox.getY(Hand.kRight), xbox.getX(Hand.kLeft));
    if(xbox.getTriggerAxis(Hand.kLeft) > 0.20) {
      intakeMotor.set(-0.75);
    } else if(xbox.getTriggerAxis(Hand.kLeft) < .20) {
      intakeMotor.set(0);
    }
    if(xbox.getTriggerAxis(Hand.kRight) > 0.20) {
      outputMotorLeft.set(-0.75);
    } else if(xbox.getTriggerAxis(Hand.kLeft) < 0.20) {
      outputMotorLeft.set(0);
    }
    if(xbox.getTriggerAxis(Hand.kRight) > 0.20) {
      outputMotorRight.set(0.75);
    } else if(xbox.getTriggerAxis(Hand.kLeft) < 0.20) {
      outputMotorRight.set(0);
    }
  }
}
