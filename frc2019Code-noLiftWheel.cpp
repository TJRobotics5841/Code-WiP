//Megan Bell
//Gabe Najera
//xbox controller to control functions of robot and camera angle, joystick controller to control movement of robot

#include <frc/XboxController.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <wpi/raw_ostream.h>
#include <cameraserver/CameraServer.h>
#include <frc/Servo.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>

class Robot : public frc::TimedRobot 
{
 public:

  void RobotInit() override
  {
    //camera code may need fixing, go into robot init
    #if defined(__linux__)
      
  // Get the USB camera from CameraServer
   cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture("Camera",0);
    camera.SetResolution(360, 480);

    #else
      wpi::errs() << "Vision only available on Linux.\n";
      wpi::errs().flush();
    #endif
  }

  void TeleopPeriodic()
   {
    //controls wrist with xbox
    double leftJoystick;
    leftJoystick = xbox.GetRawAxis(1);
    upAndDownWristMotor.Set(leftJoystick);

    //controlls arm with xbox
    double rightJoystick;
    rightJoystick = xbox.GetRawAxis(5);
    upAndDownArmMotor.Set(-rightJoystick/2);

    //open and close claw with xbox
    double rTrigger;
    rTrigger = xbox.GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand);

    double lTrigger;
    lTrigger = xbox.GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand);

    //LIGHTSPEED ACTIVATE
    float lightspeed = 1;
    bool toggle;
    
    if (joystick.GetRawButton(3) && toggle == false) {
      lightspeed = 1.5;
      toggle = true;
    } else if (joystick.GetRawButton(3) && toggle == true) {
      lightspeed = 1;
      toggle = false;
    }

    //moves robot with joystick
     m_robotDrive.ArcadeDrive(joystick.GetY() * lightspeed, joystick.GetX());
   
    //controls angle of camera with joystick
    bool button5;
    button5 = joystick.GetRawButton(5);

    //controls angle of camera with joystick
    bool button6;
    button6 = joystick.GetRawButton(6);
    
    //controls angle of camera with joystick
    bool button4;
    button4 = joystick.GetRawButton(4);

  //locks motor in place (hopefully)
  if (rightJoystick == .5)
   {
    upAndDownArmMotor.Set(.4);
   }
  
  //opens claw with xbox
  if(aButton)
  {
    clawMotor.Set(1);
  }
  
  bool closed = false;
  //opens claw with xbox
  if(lTrigger < 0.5)
  {
    clawMotor.Set(1);
    closed = false;
  }
  //closes claw with xbox
  else if(rTrigger > - 0.5)
  {
    clawMotor.Set(-1 );
    closed = true;
  }
  else if (closed) 
  {
    clawMotor.Set(0.5);
  }

  //sets camera angle 
  float servoAngle = 15.0;

  if (button6) 
  {
    servoAngle++;
    servo.SetAngle(servoAngle);
  }

  //sets camera angle
  else if (button4) 
  {
    servoAngle--; 
    servo.SetAngle(servoAngle);
  }

  //sets camera angle
  else if(button5)
  {
    servo.SetAngle(15.0);
  }
  }

 private:
  frc::Joystick joystick{1};
  frc::XboxController xbox{0};
  
  //servo motors not attatched yet
  frc::Servo servo{5};
  
  //these may not be correct but they should be
  frc::Spark upAndDownWristMotor{3};
  frc::Spark upAndDownArmMotor{2};
  frc::Spark clawMotor{4};
  
  //drive motor may be switched
  frc::Spark leftWheelMotor{0};
  frc::Spark rightWheelMotor{1};
  frc::DifferentialDrive m_robotDrive{leftWheelMotor,rightWheelMotor};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

//begin the invoking of shag

/*

                This code invokes the universal power of the godlike being
                that is Shaggy Rogers. We insert his likeness for his blessing of
                a robot that fuctions at a higher level than any other. Course though the copper 
                vessels that line the aluminum frame and distribute your legendary
                energy. God speed, Shaggy.
                                                                       
                                                                       
                                  '##'                                 
                               '#+::::;#:                              
                          ';: #::::::::::#                             
                            #'::::::::::::#                            
                            ;+::::'::::;::'                            
                           #:::::::::::+::#                            
                           ;::+:::';:::::+                             
                          #:::''''.:::':;:'                            
                          #:::;.#:.':,'.::#                            
                          +:':;.+ ,,' :.::#                            
                          ::::;. 0..:0:,::''                           
                         ::'::;.:.|....,::+#                           
                         ::+':;...|....,:::#                           
                         :';#;'../......:+:+                           
                          #:;:'.'\...'..;+:+                           
                          +:'.#'+.____.+.:':#                           
                           ::,#.:.....:.;::+                           
                           #:;#..+'.::..;:#                            
                            #:'...'.....+#                             
                             :#.........#                              
                              #..,...,..#                              
                               #..;..:;::                              
                                #:+.;'+;                               
                                 ++###                                 
                                 #...'                                 
                                 #...;                                 
                                 +...;+;#                              
                        :::    :#;...,:::                              
                       #+;;;;'#;:,....:#:#;                            
                      #;:::::;:'+.....+:'::'#'                         
                      #:::::::;.......,.#:::::##                       
                     :;:::::::+.........#:::::::#                      
                     #::::::::'.........':::::::'                      
                     ++:::::::#........,:::::::::'                     
                    +::::::::::,.......#:::::::::+                     
                   #:::':::::::'......,:::::::::'#                     
                  #:::::;:::::::+.....+:::::;::::#                     
                 #::::::;::::::::;,..'::::::'::':'                     
               :#::::::::+:::::::::#.:::::::::+:::#                    
               ;:::::::::::::::::::::::::::#:'::::;:                   
                #::::::::::::::::::::::::::;'::::::#                   
                '::::::::::::::::::::::::::':::::::;;                  
                 #:::::::::::::::::::::::::'::::::::#                  
                 '+##::::::::::::::::::::::'::::::::#                  
                    #::::::::::::::::::::::+::::::::#                  
                   ::+:::::::::::::::::::::+::::::;#                   
                   #.#:::::::::::::::::::::+:::::+                     
                   #..+::::::::::::::::::::+::::'.'                    
                  :,..,##+:::::::::::::::::'::::#.#                    
                  #....# ':::::::::::::::::':::#:.#                    
                  #....' ':::::::::::::::::####...:                    
                  :...:  +:::::::::::::::::+  #....'                   
                 ;....#  +:::::::::::::::::+  #....#                   
                 #....'  +:::::::::::::::::+  #....+                   
                 #....#  +:::::::::::::::::+  +....,                   
                 #....#  #:::::::::::::::::+  :....,                   
                 #....+  #:::::::::::::::::+ ;.....:                   
                 '....;  +:::::::::::::::::+ #.....'                   
                 '....;  +:::::::::::::::::' #.....#                   
                 ;....'  +:::::::::::::::::' #.....#                   
                 ;....#  +:::::::::::::::::: #.....#                   
                 ;....#  #:::::::::::::::::: #.....#                   
                 ;....#  #:::::::::::::::::  '.....#                   
                 ;....#  #:::::::::::::::+:  :....,'                   
                 ;....'  #::::::::::::::;#::  ,...'                    
                 '...,:  #:::::::::::::#:;:'  ;...#                    
                 #...'   +::::::::::::#:+::+  '...#                    
                 #...#   '::::::::::;'::;::#  #...#                    
                 #...#  :::::::::::#:::#:::#  #...'                    
                 #...#  ':::::;##+::::#::::#  '...                     
                 #...#  #::::::::::::+:::::#  '..;                     
                 +...+  #:::::::::::+::::::#  :..#                     
                 :...'  #::::::::::+:::::::+  ...#                     
                  ...'  #:::::::::#::::::::;::...#                     
                  ,..'  #:::::+:;#::::::::::''...;                     
                  '..+  '::::#'#;:::::::::::##...                      
                  #..# :::::::::::::::::::::##..'                      
                  #..# ;::::::::::::::::::::#,..#                      
                  '..: '::::::::::::::::::::#...+                      
                   ...#;:::::::::::::::::;#;....:                      
                   ,...##;::::::::::::::++.....,                       
                   ;....#:#':::::::::::#+'.....+                       
                   '....# #'##+::::::+#'+.+....#                       
                   ;..... +''''+####+'''+.:....+                       
                   ,...+.#:+'''''#'''''#.#.....'                       
                   .... ..'#'''''#''''#.;;.....:                       
                   ..:. #.##'''''+''''''#+....+                        
                  :..'.    #'''''+''''''##.:','                        
                  ',++.#   #'''''+''''''#....`                         
                  ;.:,..'  ''''''+''''''+.'+'`                         
                   '..,..:  '''''+''''';.:.,'#                         
                    +.',.+  +''''+'''':.+...'                          
                     #.+;.  #''''+'''',,.+.#                           
                       ++.: #''''+'''+.#.#                             
                         '  #''''+'''''''                              
                            #''''+'''''''                              
                            #''''+''''''':                             
                            #''''+''''''''                             
                            '''''''''''''+                             
                           +'''''''''''''#                             
                           #'''''''''''''#                             
                          ;''''''''''''''#                             
                          #''''''''''''''+                             
                          #''''''''''''''+                             
                          #''''''''''''''':                            
                          #'''''''''''''##:                            
                           #'''''''''''':                              
                            '''''''''''''                              
                           '''''''''''''#                              
                           #''''''''''''#                              
                           '''''''+'''''':                             
                          #'''''''+''''''#                             
                          #'''''''+''''''+                             
                         ;''''''''#'''''''+                            
                         #''''''''#'''''''#                            
                         #''''''''#''''''''#                           
                        #'''''''''#''''''''#                           
                        #'''''''''#'''#'''''#                          
                       ;''+'''''''#''''+''''#                          
                       #''''''''''#'''''#''''#                         
                      :#''''''''''#'''''''#''#                         
                     ++'''''''''''#'''''''''''                         
                     '''''''''''''#''''''''''''                        
              ###':;#++'''''''''''#''''''''+####++++#                  
             +''''+''''#''''''''''#''''''++'''''''''+                  
             #'''''+'''''#''''''''##''''#'''+'''''''':                 
             '''''''+''''''###+++##''+###'''''''''''''                 
              '''''''''''''+##'''#:####  #'''''''''+#;                 
              ##+'''''''''#   +#+:        '+######':                   
                :'########                                     
*/
