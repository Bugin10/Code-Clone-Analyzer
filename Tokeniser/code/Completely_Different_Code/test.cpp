if (getline(cin, line))
{
    linenumber++;
    //ignore single line comments
    if (line.find("//") != string::npos)
    {
        line = line.substr(0, line.find("//"));
        line += '\r';
    }
    if (line.find("#") != string::npos)
    {
        line = line.substr(0, line.find("#"));
        line += '\r';
        linenumber++;
    }
    //line is empty
    return "Empty";
}
