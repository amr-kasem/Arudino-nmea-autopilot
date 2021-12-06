class ODOMETERY{
public:
  float velocity;
  float angular_velocity;
  float X;
  float Y;
  float dt = 0.1;
  void Init(){
    velocity = 0;
    angular_velocity = 0;
    X = 0;
    Y = 0;
  }
  void Compute(){
    unsigned long c = millis();
    if(c - Timer > 100){
      X += velocity * cos(yaw) * dt;
      Y += velocity * sin(yaw) * dt;
      Timer = c;
    }
  }
  
  
private:
  float yaw = 0;
  unsigned long Timer;
};
