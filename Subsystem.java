package frc.robot;
import edu.wpi.first.wpilibj2.command.SubsystemBase;
import edu.wpi.first.wpilibj.PWMVictorSPX;
import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.DoubleSolenoid.Value;
import edu.wpi.first.wpilibj.Spark;
import edu.wpi.first.wpilibj.DigitalInput;

public class Subsystem extends SubsystemBase{
    private final Spark liftStage1 = new Spark(6);
    private final PWMVictorSPX lift1Stage2 = new PWMVictorSPX(1);
    private final PWMVictorSPX lift2Stage2 = new PWMVictorSPX(7);
    private final DoubleSolenoid liftLock = new DoubleSolenoid(2, 3);
    private final DigitalInput limit = new DigitalInput(5);

    public void Lift() {
        boolean wait = true;
        while (wait) {
            if (limit.get()) {
                liftLock.set(Value.kReverse);
                liftStage1.set(.8);
                lift1Stage2.set(-1);
                lift2Stage2.set(-1);
            } else {
                wait = false;
            }
        }
    }
}
