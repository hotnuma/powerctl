#if 0

int PowerTool::execute(int argc, char **argv)
{
    int size = argc;

    if (size != 2)
        return 1;

    int count = 0;

    int n = 1;
    while (n < size)
    {
        const char *part = argv[n];

        count = atoi(part);

        if (count < 0)
            return 1;

        n++;
    }

    if (count < 1)
        return 1;

    count *= 60;

    print("suspend after %d seconds...", count);

    sleep(count);

    print("suspend");

    int ret = system("systemctl suspend");

    return ret;

}


}


float get_loadavg()
{
    CString buffer(MAX_BUFF);

    FILE *fp = fopen ("/proc/loadavg", "r");

    size_t bytes_read = fread(buffer.data(), 1,
                              MAX_BUFF, fp);
    fclose (fp);

    if (bytes_read == 0)
    {
        print("read error");
        return 0;
    }

    buffer.terminate(MAX_BUFF - 1);

    //print(buffer);

    CStringList parts = buffer.split(" ");

    int size = parts.size();

    if (size < 3)
        return 0;

    print(parts.at(0));
    fflush(stdout);

//    double one = strtod(parts.at(0), nullptr);
//    double two = strtod(parts.at(1), nullptr);
//    double three = strtod(parts.at(3), nullptr);

    return 0;
}

float get_value()
{
    CString buffer(MAX_BUFF);

    FILE *fp = fopen ("/proc/stat", "r");

    size_t bytes_read = fread(buffer.data(), 1,
                              MAX_BUFF, fp);
    fclose (fp);

    if (bytes_read == 0)
    {
        print("read error");
        return 0;
    }

    buffer.terminate(MAX_BUFF - 1);

    char *start = buffer.data();

    CString result;
    fileGetLine(&start, result);

    //print(result);

    CString params = result.mid(5);

    //print(params);

    CStringList parts = params.split(" ", true);

    int size = parts.size();

    if (size < 3)
        return 0;

    double user = strtod(parts.at(0), nullptr);
    double system = strtod(parts.at(2), nullptr);
    double nprocs = get_nprocs();

    if (nprocs < 1)
        return 0;


    return 0;
}

#endif


