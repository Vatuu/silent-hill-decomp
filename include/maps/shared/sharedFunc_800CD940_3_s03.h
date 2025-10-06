q19_12 sharedFunc_800CD940_3_s03(q19_12 pos0, q19_12 pos1)
{
    q19_12 delta;
    q19_12 absDelta;
    q19_12 result;

    delta    = pos0 - pos1;
    absDelta = ABS(delta);
    if (absDelta > Q12(1.0f / 32.0f))
    {
        if (delta <= 0)
        {
            pos0 = pos1 - Q12(1.0f / 32.0f);
        }
        else
        {
            pos0 = pos1 + Q12(1.0f / 32.0f);
        }
    }

    if (pos0 <= Q12(0.35f))
    {
        result = pos0;
    }
    else
    {
        result = Q12(0.35f);
    }

    return result;
}
