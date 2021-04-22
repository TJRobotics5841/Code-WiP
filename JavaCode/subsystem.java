package frc.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.PWMVictorSPX;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.drive.DifferentialDrive;
import edu.wpi.first.wpilibj.XboxController;
import edu.wpi.first.wpilibj2.command.SubsystemBase;

public class subsystem extends SubsystemBase {
    private final PWMVictorSPX input = new PWMVictorSPX(0);

    public void input() {
        input.set(.75);
    }

    public void stopInput() {
        input.set(0);
    }
}
