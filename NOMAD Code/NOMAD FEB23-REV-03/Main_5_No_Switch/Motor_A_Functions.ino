/*
 * MA = Motor A
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

void MA_F(int pwm_val = set_pwm)
{
  //digitalWrite(enA, HIGH);
  analogWrite(enA, pwm_val);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void MA_B(int pwm_val = set_pwm)
{
  //digitalWrite(enA, HIGH);
  analogWrite(enA, pwm_val);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void MA_PWM(char dir, int pwm_val)
{
  /*
   * dir = F for forward
   * dir = B for backward
   * 
   */

   if (dir == "F")
   {
    MA_F();
   }
   else if (dir == "B")
   {
    MA_B();
   }

   //digitalWrite(enA, HIGH);
   analogWrite(enA, pwm_val);
}

void MA_STOP()
{
  digitalWrite(enA, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
