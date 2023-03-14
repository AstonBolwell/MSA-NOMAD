/*
 * MB = Motor B
 * 
 * F = Forward
 * 
 * B = Backward
 * 
 * // --
 * 
 * There are four functions associated with each motor:
 * 
 * Motor Forward
 * 
 * Motor Backward
 * 
 * Motor PWM Speed
 * 
 * Motor Stop
 * 
 * // --
 * 
 */

void MB_F(int pwm_val = set_pwm)
{
  //digitalWrite(enB, HIGH);
  analogWrite(enB, pwm_val);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void MB_B(int pwm_val = set_pwm)
{
  //digitalWrite(enB, HIGH);
  analogWrite(enB, pwm_val);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void MB_PWM(char dir, int pwm_val)
{
  /*
   * dir = F for forward
   * dir = B for backward
   * 
   */

   if (dir == "A")
   {
    MB_F();
   }
   else if (dir == "B")
   {
    MB_B();
   }

   analogWrite(enA, pwm_val);
}

void MB_STOP()
{
  digitalWrite(enB, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
