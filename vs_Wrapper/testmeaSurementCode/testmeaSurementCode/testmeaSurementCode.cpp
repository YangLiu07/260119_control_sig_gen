#using "D:\NPU\Project_material\Auto_Testing\QT_Stduy\exp_project\260119_control_sig_gen\vs_Wrapper\Bode100WrapperVersion2\x64\Debug\Bode100WrapperVersion2.dll"


using namespace System;

int main()
{
    array<double>^ f;
    array<double>^ m;
    array<double>^ p;

    int ret;

    ret = Bode100Wrapper::Connect();
    Console::WriteLine("Connect: " + ret);

    ret = Bode100Wrapper::CreateMeasurement();
    Console::WriteLine("Measure: " + ret);

    int n = Bode100Wrapper::GetData(f, m, p);

    Console::WriteLine("Points: " + n);

    Console::WriteLine("First freq: " + f[0]);
    Console::WriteLine("First mag: " + m[0]);
    Console::WriteLine("First phase: " + p[0]);

    return 0;
}
