//changed variable names
for (int h = 0; h < size; h++)
{
    for (int n = 0; n < second.size(); n++)
    {
        if (first[h] == second[n])
        {
            n++;
            int k = h;
            k++;
            if (j >= second.size())
            {
                break;
            }
            if (k >= first.size())
            {
                break;
            }
            while (first[k] == second[n])
            {

                result += amount;
                amount += 1;
                n++;
                k++;
                if (n >= second.size())
                {
                    break;
                }
                if (k >= first.size())
                {
                    break;
                }
            }
            amount = 1;
        }
    }
}
