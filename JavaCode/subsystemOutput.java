package frc.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.PWMVictorSPX;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.drive.DifferentialDrive;
import edu.wpi.first.wpilibj.XboxController;
import edu.wpi.first.wpilibj2.command.SubsystemBase;

public class subsystemOutput extends SubsystemBase {
    private final PWMVictorSPX outputMotorLeft = new PWMVictorSPX(1);
    //private final PWMVictorSPX outputMotorRight = new PWMVictorSPX(4);

    public void outputMotorLeft() {
        //outputMotorLeft.set(.75);
    }

    public void stopOutputMotorLeft() {
        //outputMotorLeft.set(0);
    }

    public void outputMotorRight() {
        //outputMotorRight.set(-.75);
    }

    public void stopOutputMotorRight() {
        //outputMotorRight.set(0);
    }
    
}
