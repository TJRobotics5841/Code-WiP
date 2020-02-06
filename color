#include <frc/TimedRobot.h>
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/PWMVictorSPX.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include "rev/ColorSensorV3.h"
#include <string>

using namespace std;

class Robot : public frc::TimedRobot {

  void rotationControl(string color) {
    int count;
    count = 0;
    do  {
      auto detectedColor = currentColor();
      if (detectedColor == color) {
        motor.Set(0.2);
        count++;
      } else {
        motor.Set(0.2);
      }
    } while (count < 8);
    motor.Set(0);
  }

  string currentColor() {
    frc::Color detectedColor = m_colorSensor.GetColor();
    if (detectedColor.red >.5){
      return "RED";
    } else if (detectedColor.green>.5 && detectedColor.blue>0.2){
      return "GREEN";
    } else if (detectedColor.blue>.4){
      return "BLUE";
    } else if (detectedColor.red >0.3 && detectedColor.green >0.5) {
      return "YELLOW";
    } else {
      return "No color detected";
    }
  }
  
  
  static constexpr auto i2cPort = frc::I2C::Port::kOnboard;

  rev::ColorSensorV3 m_colorSensor{i2cPort};

public:
  void TeleopPeriodic() override {
    
    motor.Set(m_stick.GetY()); 

    frc::Color detectedColor = m_colorSensor.GetColor();

    string color = currentColor();

    double IR = m_colorSensor.GetIR();

    rotationControl(color);

    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("IR", IR);

    frc::SmartDashboard::PutString("Color", color);
    
   
    uint32_t proximity = m_colorSensor.GetProximity();

    frc::SmartDashboard::PutNumber("Proximity", proximity);
    //m_othermotor.Set(m_stick.GetY());
  }
private:
  frc::Joystick m_stick{0};
  frc::XboxController xbox{1};
  frc::PWMVictorSPX motor{0};
  //frc::PWMVictorSPX m_othermotor{1};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
