#include <iostream>
#include <tchar.h>

using namespace OmicronLab::VectorNetworkAnalysis::AutomationInterface;
using namespace System;

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

    for (int i = 0; i < s21->Results->Magnitude(MagnitudeUnit::dB)->Length; i++)
    {
        std::cout << safe_cast<double>(s21->Results->Magnitude(MagnitudeUnit::dB)->GetValue(i));
        std::cout << "\n";
    }
    bode->ShutDown();
    return 0;
}