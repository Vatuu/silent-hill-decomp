bool sharedFunc_800D3214_5_s00(s_SubCharacter* scratcher)
{
    s_Collision coll;

    Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);

#ifdef MAP5_S00
    if (coll.field_8 != 7)
    {
        if (scratcher->position_18.vx > Q12(-40.0f))
        {
            return scratcher->position_18.vz > Q12(-9.0f);
        }
        else if (scratcher->position_18.vx > Q12(-80.0f))
        {
            if (scratcher->position_18.vx <= Q12(-57.0f))
            {
                if (scratcher->position_18.vx >= Q12(-62.0f))
                {
                    if (scratcher->position_18.vz > Q12(-10.0f))
                    {
                        return true;
                    }

                    return scratcher->position_18.vz < Q12(-14.0f);
                }
            }
        }
        else if (scratcher->position_18.vz <= Q12(-89.0f))
        {
            return (scratcher->position_18.vx >= Q12(-89.0f));
        }
    }

    return false;
#else
    // M6S03 version.
    if (coll.field_8 != 7)
    {
        if (scratcher->position_18.vx < 0)
        {
            if (scratcher->position_18.vz < Q12(38.0f))
            {
                return true;
            }

            if (scratcher->position_18.vz < Q12(57.0f))
            {
                return false;
            }

            if (scratcher->position_18.vz <= Q12(63.0f))
            {
                if (scratcher->position_18.vx >= Q12(-22.0f))
                {
                    return scratcher->position_18.vx > Q12(-18.0f);
                }
            }
            else
            {
                return false;
            }
        }
        else if (scratcher->position_18.vz > Q12(40.0f))
        {
            if (scratcher->position_18.vz <= Q12(63.0f))
            {
                if (scratcher->position_18.vz >= Q12(57.0f))
                {
                    if (scratcher->position_18.vx >= Q12(18.0f))
                    {
                        return scratcher->position_18.vx > Q12(22.0f);
                    }

                    return true;
                }
            }

            return false;
        }
        else if (scratcher->position_18.vz <= Q12(23.0f))
        {
            if (scratcher->position_18.vz >= Q12(17.0f))
            {
                if (scratcher->position_18.vx >= Q12(18.0f))
                {
                    return scratcher->position_18.vx > Q12(22.0f);
                }

                return true;
            }

            return false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
#endif
}
