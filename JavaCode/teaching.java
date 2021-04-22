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
import frc.robot.Subsystem;
import frc.robot.subsystemOutput;

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
  private final Subsystem inputmotor = new Subsystem();
  private final subsystemOutput outputMotor = new subsystemOutput();
  //private final subsystemOutput outputMotorR = new subsystemOutput();

  @Override
  public void teleopPeriodic() {
    // Drive with arcade drive.
    // That means that the Y axis drives forward
    // and backward, and the X turns left and right.
    m_robotDrive.arcadeDrive(xbox.getY(Hand.kRight), xbox.getX(Hand.kLeft));
    double triggerInput = xbox.getTriggerAxis(Hand.kLeft);
    double triggerOutputMotorLeft = xbox.getTriggerAxis(Hand.kRight);
    double triggerOutputMotorRight = xbox.getTriggerAxis(Hand.kRight);

    if (triggerInput > 0.2) {
      inputmotor.input();
    } else if (triggerInput < 0.2) {
      inputmotor.stopInput();
    }

    if(triggerOutputMotorLeft > 0.2) {
      outputMotor.outputMotorLeft();
    } else if (triggerOutputMotorLeft < 0.2) {
      outputMotor.stopOutputMotorLeft();
    }

    if(triggerOutputMotorRight > 0.2) {
      outputMotor.outputMotorRight();
    } else if (triggerOutputMotorRight < 0.2) {
      outputMotor.stopOutputMotorRight();
    }
  }
}


