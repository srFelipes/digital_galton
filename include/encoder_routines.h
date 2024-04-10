boolean pin_comparation(byte enc_read, int a, int b)
{
    return (((enc_read >> a) & 1) == ((enc_read >> b) & 1));
}
byte enc_read;
unsigned int encoder_value = 0;
void enc0_b_callback(void)
{
    // pin 20
    enc_read = PIND;
    if (pin_comparation(enc_read, 2, 4))
    {
        // ccw
        encoder_value--;
    }

    else
    {
        // cw
        encoder_value++;
    }
}
