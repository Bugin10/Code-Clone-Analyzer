 for (int i = 0; i < fileSize; i++)
    {
        for (int j = 0; j < file2.size(); j++)
        {
            if (file1[i] == file2[j])
            {
                j++;
                int k = i;
                k++;
                if (j >= file2.size())
                {
                    break;
                }
                if (k >= file1.size())
                {
                    break;
                }
                while (file1[k] == file2[j])
                {
;//character added
                    score += scoreMulti;
                    scoreMulti += 1;
                    j++;
                    k++;
                    if (j >= file2.size())
                    {
                        break;
                    }
                    if (k >= file1.size())
                    {
                        break;
                    }
                }
                scoreMulti = 1;
            }
        }
    }
