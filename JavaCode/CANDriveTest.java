// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package frc.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.PWMVictorSPX;
import edu.wpi.first.wpilibj.SpeedControllerGroup;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.drive.DifferentialDrive;
import edu.wpi.first.wpilibj.XboxController;
import edu.wpi.first.wpilibj.GenericHID.Hand;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

import com.revrobotics.CANSparkMax;
import com.revrobotics.CANEncoder;
import com.revrobotics.CANSparkMaxLowLevel.MotorType;
import com.ctre.phoenix.motorcontrol.can.WPI_VictorSPX;
/**
 * This is a demo program showing the use of the DifferentialDrive class. Runs the motors with
 * arcade steering.
 */
public class Robot extends TimedRobot {
  private final CANSparkMax lMotorMax = new CANSparkMax(5, MotorType.kBrushless);
  private final WPI_VictorSPX lMotorVictor = new WPI_VictorSPX(2);
  private final SpeedControllerGroup lGroup = new SpeedControllerGroup(lMotorMax, lMotorVictor);
  private final CANSparkMax rMotorMax = new CANSparkMax(6, MotorType.kBrushless);
  private final WPI_VictorSPX rMotorVictor = new WPI_VictorSPX(2);
  private final SpeedControllerGroup rGroup = new SpeedControllerGroup(rMotorMax, rMotorVictor);
  //private final PWMVictorSPX m_leftMotor = new PWMVictorSPX(0);
  //private final PWMVictorSPX m_rightMotor = new PWMVictorSPX(1);
  private final DifferentialDrive m_robotDrive = new DifferentialDrive(lGroup, rGroup);
  private final Joystick m_stick = new Joystick(0);
  private final XboxController xbox = new XboxController(0);
  private final CANEncoder lEncoder = lMotorMax.getEncoder();
  private final CANEncoder rEncoder = rMotorMax.getEncoder();


  @Override 
  public void robotInit() {
    lMotorMax.restoreFactoryDefaults();
    rMotorMax.restoreFactoryDefaults();
  }

  @Override
  public void teleopPeriodic() {
    // Drive with arcade drive.
    // That means that the Y axis drives forward
    // and backward, and the X turns left and right.
    m_robotDrive.arcadeDrive(xbox.getY(Hand.kLeft), xbox.getX(Hand.kRight));
    SmartDashboard.putNumber("LeftVel", lEncoder.getVelocity());
    SmartDashboard.putNumber("RightVel", rEncoder.getVelocity());
  }
}
