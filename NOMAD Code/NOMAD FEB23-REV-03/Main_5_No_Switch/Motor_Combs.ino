/*
   Assuming Motor A is on the left, and Motor B is on the right when the stabilizer wheel is on the back when the Nomad is going forward

*/

void nomad_CW(int pwm_val = set_pwm)
{
  MA_F(pwm_val);
  MB_B(pwm_val);
}

void nomad_CCW(int pwm_val = set_pwm)
{
  MA_B(pwm_val);
  MB_F(pwm_val);
}

void nomad_forward(int pwm_val = set_pwm)
{
  MA_F(pwm_val);
  MB_F(pwm_val);
}

void nomad_backward(int pwm_val = set_pwm)
{
  MA_B(pwm_val);
  MB_B(pwm_val);
}

void nomad_stop()
{
  MA_STOP();
  MB_STOP();
}


// === Slights
void nomad_forward_turn(int a_pwm_val = set_pwm, int b_pwm_val = set_pwm)
{
  MA_F(a_pwm_val);
  MB_F(b_pwm_val);
}

void nomad_backward_turn(int a_pwm_val = set_pwm, int b_pwm_val = set_pwm)
{
  MA_B(a_pwm_val);
  MB_B(b_pwm_val);
}
