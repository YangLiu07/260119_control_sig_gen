#include <iostream>
#include <tchar.h>

//using namespace OmicronLab_VectorNetworkAnalysis_AutomationInterface;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::DataTypes;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::Enumerations;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::Helper;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::Interfaces;

using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::Interfaces::Calibration;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::Interfaces::Measurements;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::Interfaces::PortExtension;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::Interfaces::Results;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::Interfaces::Results::SpecialResults;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::Interfaces::Shaping;

using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::PortExtension;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::Properties;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::ResultProcessors;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::Shaping;
using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface::TaskProcessors;

int _tmain(int argc, _TCHAR* argv[])
{
    BodeAutomation^ automation = gcnew BodeAutomation();
    BodeDevice^ bode = automation->Connect();
    S21Measurement^ s21 = bode->Transmission->CreateS21Measurement();
    s21->ConfigureSweep(10, 1000, 201, SweepMode::Linear);
    s21->ReceiverBandwidth = ReceiverBandwidth::kHz1;

    ExecutionState state = s21->ExecuteMeasurement();
    std::cout << "Execution state: " << (int)state << std::endl;
    auto mag = s21->Results->Magnitude(MagnitudeUnit::dB);
    std::cout << "Data length: " << mag->Length << std::endl;
    for (int i = 0; i < s21->Results->Magnitude(MagnitudeUnit::dB)->Length; i++)
    {
        std::cout << safe_cast<double>(s21->Results->Magnitude(MagnitudeUnit::dB)->GetValue(i));
        std::cout << "\n";
    }
    bode->ShutDown();
    return 0;
}


//public ref class Bode100Wrapper
//{
//private:
//
//    static BodeAutomation^ bode = nullptr;
//    static BodeDevice^ device = nullptr;
//    //static MeasurementImplementation^ measurement = nullptr;
//    static AdapterMeasurement^ adaMeasure = nullptr;
//    ExecutionState^ state;
//public:
//
//    // 连接设备
//    static int Connect()
//    {
//        try
//        {
//            bode = gcnew BodeAutomation();
//
//            device = bode->Connect();
//
//            return 0;
//        }
//        catch (Exception^)
//        {
//            return -1;
//        }
//    }
//
//    // 创建阻抗测量
//    static int CreateMeasurement()
//    {
//        try
//        {
//            adaMeasure = device->Impedance->CreateAdapterMeasurement();
//            adaMeasure->ConfigureSweep(100,            // startFrequency
//                1000000,        // stopFrequency
//                201,            // numberOfPoints
//                SweepMode::Linear);
//            ExecutionState state = adaMeasure->ExecuteMeasurement();
//            if (state != ExecutionState::Ok)
//            {
//                return -2;
//            }
//            return 0;
//        }
//        catch (Exception^)
//        {
//            return -1;
//        }
//    }
//
//
//    // 获取数据
//    static int GetData(
//        array<double>^% freq,
//        array<double>^% magnitude,
//        array<double>^% phase)
//    {
//        try
//        {
//            auto results = adaMeasure->Results;
//
//            magnitude =
//                results->Magnitude(MagnitudeUnit::dB);
//            freq =
//                results->MeasurementFrequencies;
//            phase =
//                results->Phase(AngleUnit::Degree);
//
//
//
//
//            return freq->Length;
//        }
//        catch (Exception)
//        {
//            return -1;
//        }
//    }
//};
