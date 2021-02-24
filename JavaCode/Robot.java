// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package frc.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.PWM;
import edu.wpi.first.wpilibj.PWMVictorSPX;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.drive.DifferentialDrive;
import edu.wpi.first.wpilibj.XboxController;
import edu.wpi.first.wpilibj.DoubleSolenoid.Value;
import edu.wpi.first.wpilibj.GenericHID.Hand;
import edu.wpi.first.cameraserver.*;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.GenericHID;
import edu.wpi.first.wpilibj.Spark;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import edu.wpi.first.wpilibj.AnalogInput;
import edu.wpi.first.wpilibj.DoubleSolenoid;
import java.lang.Math;
import frc.robot.Subsystem;

public class Robot extends TimedRobot {
  private final PWMVictorSPX m_leftMotor = new PWMVictorSPX(5);
  private final PWMVictorSPX m_rightMotor = new PWMVictorSPX(0);
  private final DifferentialDrive m_robotDrive = new DifferentialDrive(m_leftMotor, m_rightMotor);
  private final Joystick m_stick = new Joystick(0);
  private final XboxController fXbox = new XboxController(0);
  private final XboxController dXbox = new XboxController(1);
  private final PWMVictorSPX intake = new PWMVictorSPX(8);
  private final PWMVictorSPX output1 = new PWMVictorSPX(2);
  private final AnalogInput sensor = new AnalogInput(0);
  private final PWMVictorSPX output2 = new PWMVictorSPX(3);
  //private final Spark liftStage1 = new Spark(6);
  //private final PWMVictorSPX lift1Stage2 = new PWMVictorSPX(1);
  //private final PWMVictorSPX lift2Stage2 = new PWMVictorSPX(7);
  private final DoubleSolenoid outputSolenoid = new DoubleSolenoid(0, 1);
  //private final DoubleSolenoid liftLock = new DoubleSolenoid(2, 3);
  private final Subsystem Lift = new Subsystem();

  private Timer timer = new Timer();


  public void RobotInit() {
    CameraServer.getInstance().startAutomaticCapture("Front_Cam", 0);
    CameraServer.getInstance().startAutomaticCapture("Back_Cam", 1);
  }

  @Override
  public void autonomousInit() {
    timer.reset();
    timer.start();
  }

  @Override
  public void autonomousPeriodic() {
    if (timer.get() < 2) {
      m_leftMotor.set(.3);
      m_rightMotor.set(-3);
    }
  }

  @Override
  public void teleopPeriodic() {
    // Drive with arcade drive.
    // That means that the Y axis drives forward
    // and backward, and the X turns left and right.
    m_robotDrive.arcadeDrive(fXbox.getY(Hand.kLeft), fXbox.getX(Hand.kRight));

    //Intake
    if (fXbox.getTriggerAxis(Hand.kLeft) > 0.2 || fXbox.getBumper(Hand.kLeft)){
      intake.set(0.5);
    } else {
      intake.set(0);
    }

    if (dXbox.getBumper(Hand.kLeft)) {
      Lift.Lift();
    }
    
    /*
    //Output
    if (fXbox.getBumper(Hand.kRight)) {
      output1.set(0.5);
      output2.set(0.5);
    } else if (fXbox.getTriggerAxis(Hand.kRight) > 0.2) {
      output1.set(1);
      output2.set(1);
    } else {
      output1.set(0);
      output2.set(0);
    }

    //Lift stage 1
    if (dXbox.getBumper(Hand.kLeft)) {
      liftStage1.set(-0.3);
    } else if (dXbox.getTriggerAxis(Hand.kLeft) > 0.2) {
      liftStage1.set(.8);
    } else {
      liftStage1.set(0);
    }

    //Lift stage 2
    if (dXbox.getBumper(Hand.kRight)) {
      lift1Stage2.set(1);
      lift2Stage2.set(1);
    } else if (dXbox.getTriggerAxis(Hand.kRight) > 0.2) {
      lift1Stage2.set(-1);
      lift2Stage2.set(-1);
    } else {
      lift1Stage2.set(0);
      lift2Stage2.set(0);
    }

    //Ratchet solenoid
    if (dXbox.getRawButton(1)) {
      liftLock.set(Value.kForward);
    } else if (dXbox.getRawButton(2)) {
      liftLock.set(Value.kReverse);
    }
    */

    //Output solenoid
    if (fXbox.getY(Hand.kRight) > 0.3) {
      outputSolenoid.set(Value.kForward);
    } else if (fXbox.getY(Hand.kRight) < -0.3) {
      outputSolenoid.set(Value.kReverse);
    }

    

  }
}
